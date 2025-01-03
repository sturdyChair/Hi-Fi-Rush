#include "Kale_FArm.h"

#include "GameInstance.h"
#include "PipeLine.h"
#include "Shader.h"
#include "Texture.h"
#include "VIBuffer_Cube.h"
#include "Model.h"
#include "Collider.h"
#include "Bounding_Sphere.h"
#include "PlayerManager.h"
#include "CombatManager.h"
#include "Effect_Manager.h"
#include "Effect_Union.h"

wstring CKale_FArm::ObjID = TEXT("CKale_FArm");

CKale_FArm::CKale_FArm(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CPartObject{ pDevice, pContext }
{
}

CKale_FArm::CKale_FArm(const CKale_FArm& rhs)
	: CPartObject(rhs)
{

}

HRESULT CKale_FArm::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	_matrix		LocalTransformMatrix = XMMatrixIdentity();

	LocalTransformMatrix = XMMatrixScaling(0.004f, 0.004f, 0.004f) * XMMatrixRotationRollPitchYaw(0.f, 0.f, XM_PI);
	_float4x4 preMatrix = {};
	XMStoreFloat4x4(&preMatrix, LocalTransformMatrix);
	m_List_ResourceInfo.push_back(
		make_shared<RES_MODEL>(TEXT("Prototype_Component_Model_Kale_FArm"), TEXT("../Bin/Resources/Models/Monsters/Kale/Kale_FArm.fbx"), MODEL_TYPE::ANIM, preMatrix)
	);

	return S_OK;
}

HRESULT CKale_FArm::Initialize(void* pArg)
{
	WEAPON_DESC* pDesc = static_cast<WEAPON_DESC*>(pArg);

	m_pBoneMatrix = pDesc->pBoneMatrix;

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	vector<shared_ptr<CAnimation>> animList = m_pModelCom->Get_Animation_List();
	for (auto& iter : animList)
	{
		m_vecAnimList.push_back(iter->Get_AnimName());
	}
	m_pModelCom->Set_AnimIndex("em7520_idle_000", true);
	//m_pTransformCom->Rotation(XMVectorSet(0, 0, 1, 0), XMConvertToRadians(-90));
	m_pColliderBone = m_pModelCom->Get_BoneMatrixPtr("damage_00");
	m_pModelCom->SetEffectCallback([&](string strName, _float4x4 matPos, _bool isAttach, _bool isBillBoard) {
		if (isAttach)
		{
			CEffect_Manager::Get_Instance()->Call_Union_Effect(strName, &m_WorldMatrix, m_fAnimSpeed, isBillBoard);
		}
		else
		{
			CEffect_Manager::Get_Instance()->Call_Fixed_Union_Effect(strName, &m_WorldMatrix, m_fAnimSpeed, isBillBoard);
		}
		}
	);
	return S_OK;
}

void CKale_FArm::PriorityTick(_float fTimeDelta)
{
	m_bCollision = false;
	m_bAtk = false;
}

void CKale_FArm::Tick(_float fTimeDelta)
{
	m_fHitRed -= fTimeDelta;
	_float4x4 mMat = {};
	m_pModelCom->Play_Animation(fTimeDelta, fTimeDelta * m_fAnimSpeed, 0.1f, mMat);

	_matrix		BoneMatrix = XMLoadFloat4x4(m_pBoneMatrix);

	for (size_t i = 0; i < 3; i++)
		BoneMatrix.r[i] = XMVector3Normalize(BoneMatrix.r[i]);

	SetUp_WorldMatrix(m_pTransformCom->Get_WorldMatrix_XMMat() * BoneMatrix);

	_matrix ColliderMat = XMLoadFloat4x4(m_pColliderBone) * XMLoadFloat4x4(&m_WorldMatrix);
	ColliderMat.r[0] = XMVector3Normalize(ColliderMat.r[0]);
	ColliderMat.r[1] = XMVector3Normalize(ColliderMat.r[1]);
	ColliderMat.r[2] = XMVector3Normalize(ColliderMat.r[2]);
	m_pColliderCom->Update(ColliderMat);
	ColliderMat.r[0] = XMVector3Normalize(ColliderMat.r[0]);
	ColliderMat.r[1] = XMVector3Normalize(ColliderMat.r[1]);
	ColliderMat.r[2] = XMVector3Normalize(ColliderMat.r[2]);
	XMStoreFloat4x4(&m_MatCollider, XMMatrixRotationY(-XM_PIDIV2 * 1.2f) * ColliderMat);
	if (m_pModelCom->Get_Finished())
	{
		if (m_pModelCom->Get_AnimName() == "em7520_atk-arm_000")
		{
			m_pModelCom->Set_AnimIndex("em7520_idle_000", true);
		}
	}
	m_pModelCom->PlayReservedCallbacks();

	if (m_FlameHoldUnion != nullptr)
	{
		if (m_FlameHoldUnion->GetUnionTimePer() >= 1.f) {
			m_FlameHoldUnion->UnionEffectEnd();
			m_FlameHoldUnion = nullptr;
		}
	}
}

void CKale_FArm::LateTick(_float fTimeDelta)
{
	m_iRenderCount = 0;
	auto pGI = m_pGameInstance.lock();
	pGI->Add_RenderObjects(CRenderer::RENDER_NONBLEND, shared_from_this());
	//GAMEINSTANCE->Add_RenderObjects(CRenderer::RENDER_NONBLEND_NON_LIT, shared_from_this());
	if (m_bAtk || m_bCollision)
		pGI->Add_Collider(COLLIDER_GROUP::COLLISION_MONSTER, m_pColliderCom);
}

HRESULT CKale_FArm::Render()
{
	++m_iRenderCount;
	if (m_iRenderCount == 1)
	{
		if (FAILED(Bind_ShaderResources()))
			return E_FAIL;
		_uint   iNumMeshes = m_pModelCom->Get_NumMeshes();

		for (size_t i = 0; i < iNumMeshes; i++)
		{
			_bool bEmit = true;
			if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, "g_Texture", (_uint)i, aiTextureType_DIFFUSE)))
			{
				continue;
			}
			if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, "g_Emission_Texture", (_uint)i, aiTextureType_EMISSIVE)))
			{
				bEmit = false;
			}
			if (FAILED(m_pModelCom->Bind_BoneMatrices(m_pShaderCom, "g_BoneMatrix", (_uint)i)))
				return E_FAIL;
			
			if (m_fHitRed > 0.f)
			{
				_float4 vColor{ 1.f,0.f,0.f,1.f };
				m_pShaderCom->Bind_Vector4("g_vColor", &vColor);
				m_pShaderCom->Begin((_uint)ANIMMESH_PASS::EmissionColor);
			}
			else if (bEmit)
			{
				m_pShaderCom->Begin((_uint)ANIMMESH_PASS::Emission);
			}
			else
			{
				m_pShaderCom->Begin(0);
			}

			//if (FAILED(m_pModelCom->Bind_Buffers(static_cast<_uint>(i))))
			//   return E_FAIL;

			m_pModelCom->Render((_uint)i);
			//if(!bEmit)
			//{
			//	m_pShaderCom->Bind_Float("g_OutlineWidth", 1.0f);
			//	m_pShaderCom->Begin((_uint)ANIMMESH_PASS::Outline);

			//	m_pModelCom->Draw((_uint)i);
			//}
		}
	}
	//else
	//{
	//	if (FAILED(Bind_ShaderResources()))
	//		return E_FAIL;
	//	_uint   iNumMeshes = m_pModelCom->Get_NumMeshes();

	//	for (size_t i = 0; i < iNumMeshes; i++)
	//	{
	//		if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, "g_Texture", (_uint)i, aiTextureType_DIFFUSE)))
	//		{
	//			continue;
	//		}

	//		if (FAILED(m_pModelCom->Bind_BoneMatrices(m_pShaderCom, "g_BoneMatrix", (_uint)i)))
	//			return E_FAIL;

	//		m_pShaderCom->Begin(0);

	//		//if (FAILED(m_pModelCom->Bind_Buffers(static_cast<_uint>(i))))
	//		//   return E_FAIL;

	//		m_pModelCom->Render((_uint)i);
	//	}
	//}
#ifdef _DEBUG
	m_pColliderCom->Render();
#endif // 

	return S_OK;
}

_bool CKale_FArm::Change_Animation(string strAnimName)
{
	if (m_pModelCom->Get_AnimName() == "em7520_atk-arm_000")
		return false;

	_bool bFind = false;
	string PlayerAnimName = strAnimName.substr(strAnimName.find("_"));
	//if (PlayerAnimName == "_atk_010")
	//{
	//	m_pModelCom->Set_AnimIndexNonCancle("em7520_atk-arm_000", false);
	//	return true;
	//}
	for (auto& iter : m_vecAnimList)
	{
		string animName = iter.substr(iter.find("_"));


		if (animName == PlayerAnimName)
		{
			if (iter == "em7520_idle_000")
			{
				bFind = false;
			}
			else
			{
				m_pModelCom->Set_AnimIndexNonCancle(iter, false);
				bFind = true;
			}
		}
	}
	if (bFind == false)
	{
		m_pModelCom->Set_AnimIndex("em7520_idle_000", true);

	}

	return bFind;
}

void CKale_FArm::Throw_Flame(_float fPlayTime)
{
	m_pModelCom->Get_Animation_PlayTime();
	EFFECTMANAGER->Call_Union_Effect("Flame_Throw_10Sec", &m_MatCollider, 10.f / fPlayTime, false);
}

void CKale_FArm::Hold_Flame(_float fPlayTime)
{
	m_pModelCom->Get_Animation_PlayTime();
	m_FlameHoldUnion = EFFECTMANAGER->Call_Union_Effect_Return("Flame_Hold", &m_MatCollider, 5.f / fPlayTime, false);
	
}

void CKale_FArm::Quite_Flame()
{
	if (m_FlameHoldUnion != nullptr)
	{
		m_FlameHoldUnion->UnionEffectEnd();
		m_FlameHoldUnion = nullptr;
	}
}

void CKale_FArm::Collision_Enter(shared_ptr<CCollider> pOther, shared_ptr<CCollider> pCaller)
{
	if (!m_bCollision && m_bAtk)
	{
		DamageInfo damageInfo{};
		damageInfo.fAmountDamage = 10.f;
		damageInfo.eAttackType = EAttackType::Hard;
		damageInfo.pObjectOwner = shared_from_this();

		pOther->Get_Owner()->TakeDamage(damageInfo);
	}
}

void CKale_FArm::TakeDamage(const DamageInfo& damageInfo)
{
	if (!m_bCollision && m_bAtk)
		return;
	_float fDamage = damageInfo.fAmountDamage;
	_float fTargetHp = m_fHp - fDamage;
	auto pPM = PLAYERMANAGER;
	pPM->Add_PlayerRankScore(fDamage / 1.5f);
	pPM->Add_PlayerScore((_int)fDamage * 10.f);
	CCombat_Manager::Get_Instance()->Add_Combo();
	m_fHp = fTargetHp;
	m_fHitRed = 0.1f;

	_matrix ColliderMat = XMLoadFloat4x4(m_pColliderBone) * XMLoadFloat4x4(&m_WorldMatrix);
	ColliderMat.r[0] = XMVector3Normalize(ColliderMat.r[0]);
	ColliderMat.r[1] = XMVector3Normalize(ColliderMat.r[1]);
	ColliderMat.r[2] = XMVector3Normalize(ColliderMat.r[2]);

	_float4x4 matUnion;
	XMStoreFloat4x4(&matUnion, ColliderMat);

	EFFECTMANAGER->Call_Union_Effect("Big_HitEffect", &matUnion, 1.f, true);
}

HRESULT CKale_FArm::Ready_Components()
{
	/* For.Com_Shader */
	m_pShaderCom = static_pointer_cast<CShader>(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnimMesh"), TEXT("Com_Shader")));

	/* For.Com_Model */
	m_pModelCom = static_pointer_cast<CModel>(__super::Add_Component(LEVEL_KALEBOSS, TEXT("Prototype_Component_Model_Kale_FArm"), TEXT("Com_Model")));

	{
		CBounding_Sphere::BOUNDING_SPHERE_DESC sphereDesc{};
		sphereDesc.vCenter = _float3{ 0.f, 0.f, 0.f };
		sphereDesc.fRadius = 1.5f;
		m_pColliderCom = static_pointer_cast<CCollider>(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Collider_Sphere"), TEXT("Collider_Hit"), &sphereDesc));
		m_pColliderCom->Set_Owner(shared_from_this());
		m_pColliderCom->Set_ColliderTag(TEXT("Monster_Hit"));
	}

	if (!m_pShaderCom || !m_pModelCom)
		assert(false);

	return S_OK;
}

HRESULT CKale_FArm::Bind_ShaderResources()
{
	_float4x4 ViewMat;
	XMStoreFloat4x4(&ViewMat, m_pGameInstance.lock()->Get_Transform_Matrix(CPipeLine::D3DTS_VIEW));
	_float4x4 ProjMat;
	XMStoreFloat4x4(&ProjMat, m_pGameInstance.lock()->Get_Transform_Matrix(CPipeLine::D3DTS_PROJ));
	/* 부모의 행렬을 완전히 무시한 상황. */
	if (FAILED(m_pShaderCom->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))
		return E_FAIL;
	//if (FAILED(m_pShaderCom->Bind_RawValue("g_ObjectID", &m_iObjectID, sizeof(_uint))))
	//   return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &ViewMat)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &ProjMat)))
		return E_FAIL;

	return S_OK;
}

shared_ptr<CKale_FArm> CKale_FArm::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	struct MakeSharedEnabler :public CKale_FArm
	{
		MakeSharedEnabler(ID3D11Device* pDevice, ID3D11DeviceContext* pContext) : CKale_FArm(pDevice, pContext)
		{}
	};


	shared_ptr<CKale_FArm> pInstance = make_shared<MakeSharedEnabler>(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CKale_FArm"));
		assert(false);
	}

	return pInstance;
}


shared_ptr<CGameObject> CKale_FArm::Clone(void* pArg)
{
	struct MakeSharedEnabler :public CKale_FArm
	{
		MakeSharedEnabler(const CKale_FArm& rhs) : CKale_FArm(rhs)
		{}
	};


	shared_ptr<CKale_FArm> pInstance = make_shared<MakeSharedEnabler>(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CKale_FArm"));
		assert(false);
	}

	return pInstance;
}


void CKale_FArm::Free()
{

}

CKale_FArm::~CKale_FArm()
{
	Free();
}
