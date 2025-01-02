#include "CUi_StoreAttack.h"
#include "Shader.h"
#include "Texture.h"
#include "GameInstance.h"
#include "VIBuffer_Rect.h"
#include "CUi_StoreBar.h"
#include "CUi_Default.h"
#include "PlayerManager.h"
#include "CUi_StoreEdge.h"


wstring CUi_StoreAttack::ObjID = L"CUi_StoreAttack";

CUi_StoreAttack::CUi_StoreAttack(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CUi_Store(pDevice, pContext)
{
}

CUi_StoreAttack::CUi_StoreAttack(const CUi_StoreAttack& rhs)
	:CUi_Store(rhs)
{

}

CUi_StoreAttack::~CUi_StoreAttack()
{
}

HRESULT CUi_StoreAttack::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CUi_StoreAttack::Initialize(void* pArg)
{
	Initialize_Transform();
	Initialize_StoreDesc();
	Initialize_Boundary(250, -100, -250, 450);
	Initialize_Attack();
	Initialize_Back();
	Initialize_AttackMap();


	return S_OK;
}

void CUi_StoreAttack::PriorityTick(_float fTimeDelta)
{
}

void CUi_StoreAttack::Tick(_float fTimeDelta)
{
	Check_Has();
	Progress_Store(fTimeDelta);
	Adjust_Alpha(fTimeDelta);
	Scrolling(fTimeDelta);
	wstring AttackName = m_StoreBarVec[m_iFocusIndex]->Get_Name();
	m_StoreDesc->Set_Desc((m_AttackMap.find(AttackName)->second));
}

void CUi_StoreAttack::LateTick(_float fTimeDelta)
{
}

void CUi_StoreAttack::Initialize_Attack()
{
	m_StoreBarVec.reserve(6);

	CUi_StoreBar::Desc Desc;
	Desc.fColor = { 1, 1, 1, 0 };
	Desc.fSizeX = 440;
	Desc.fSizeY = 50;
	Desc.fSpeed = 300;
	Desc.fX = -255;
	Desc.fY = 70 - _float(m_StoreBarVec.size() * 70);
	Desc.eRenderType = RenderType::Normal;
	Desc.iPriority = 0;
	Desc.ShaderFileName = L"Prototype_Component_Shader_VtxPosTex";
	Desc.ShaderPass = ShaderPass::StoreScrollBar;
	Desc.TextureFileName = L"Prototype_Component_Texture_StoreBar";
	Desc.TextureLevel = LEVEL_STATIC;
	Desc.Price = 8000;
	Desc.fUpLimitPos = m_pBoundaryVec[0]->Get_Pos().y;
	Desc.fDownLimitPos = m_pBoundaryVec[1]->Get_Pos().y;
	Desc.StringFont = L"���� ���÷���";
	Desc.type = CPlayer_Manager::ThingType::Attack;
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));

	Desc.fY = 70 - _float(m_StoreBarVec.size() * 70);
	Desc.Price = 6000;
	Desc.StringFont = L"ƪ ��";
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));

	Desc.fY = 70 - _float(m_StoreBarVec.size() * 70);
	Desc.Price = 10000;
	Desc.StringFont = L"������ �ڽ�";
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));


	Desc.fY = 70 - _float(m_StoreBarVec.size() * 70);
	Desc.Price = 8000;
	Desc.StringFont = L"�Ⱦ� ũ����";
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));


	Desc.fY = 70 - _float(m_StoreBarVec.size() * 70);
	Desc.Price = 10000;
	Desc.StringFont = L"�ϸ�� ��";
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));

	Desc.fY = 70 - _float(m_StoreBarVec.size() * 70);
	Desc.Price = 16000;
	Desc.StringFont = L"�������� ����";
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));

	m_StoreBarVec[0]->Set_Focus(true);
}

void CUi_StoreAttack::Initialize_AttackMap()
{
	CUi_StoreDesc::AttackDesc Desc;
	Desc.PriceFont = to_wstring(8000);
	Desc.TitleFont = L"���� ���÷���";
	Desc.ExplainFont = L"���� �޺��� �̾����� ���� �޺��� �ִٰ��? &���� �� ��!&&�װ� �ٷ� ���� ���÷����Դϴ�. ��Ʈ ��Ʈ�� ���߽��� &���� ���濡 �ִ� ������ �������� ��� ����, &��ó� �ڼ����� ������ �ٽ� �����ؼ� �����޺��� �����ϼ���.&&�ϰ� ���� �������!";
	Desc.iEnterCount = 7;
	m_AttackMap.emplace(L"���� ���÷���", Desc);

	Desc.PriceFont = to_wstring(6000);
	Desc.TitleFont = L"ƪ ��";
	Desc.ExplainFont = L"&&���� �տ� �ִ� ���� ���� ������ ����, ������ �������� �ټ��� ����&������ ���� ������ ����Ʈ �޺��Դϴ�. ���� ������ ȹ���ϸ鼭 �����̿�&�ִ� ���� �Ÿ��� ������ ���� ��, �ٸ� ������ ȥ���ϱ� �����ϴ�.";
	Desc.iEnterCount = 4;
	m_AttackMap.emplace(L"ƪ ��", Desc);

	Desc.PriceFont = to_wstring(10000);
	Desc.TitleFont = L"������ �ڽ�";
	Desc.ExplainFont = L"�������� ������ ��Ʈ ��Ʈ�� ���߽��� 360�� ���� ������ �����մϴ�.&�̶� ���� ������ �ڷ� ���� ���� �� �ֽ��ϴ�. ������ �ѷ��ο��� ��&����ϱ� ���� �����Դϴ�!";
	Desc.iEnterCount = 2;
	m_AttackMap.emplace(L"������ �ڽ�", Desc);

	Desc.PriceFont = to_wstring(8000);
	Desc.TitleFont = L"�Ⱦ� ũ����";
	Desc.ExplainFont = L"���̰� ���������� �������� ������, ������...�� ��Ÿ�� ��ȭ�մϴ�.&�״��� ������ �������� ������ ������� �Բ� �ڷ� ���� �����ϴ�. ���̾�&�ڼ� �׷��� ����ϸ�,�޺��� �̾� ���� ���׳� ��ũ ���ʽ��� ȹ���� ��&�ֽ��ϴ�.";
	Desc.iEnterCount = 3;
	m_AttackMap.emplace(L"�Ⱦ� ũ����", Desc);

	Desc.PriceFont = to_wstring(10000);
	Desc.TitleFont = L"�ϸ�� ��";
	Desc.ExplainFont = L"��� ���� �޺� �����Դϴ�. ����ݰ� �������� ������ ���߿� �ִ�&������ ���ظ� �� �Ӹ� �ƴ϶�, ���� ������ �������� ���� ���̰�&���߿��� ������ ���� �߻��� ���� ������ϴ�. ���� �ֺ��� �ִ� �����Ե�&���ظ� �ݴϴ�!";
	Desc.iEnterCount = 3;
	m_AttackMap.emplace(L"�ϸ�� ��", Desc);

	Desc.PriceFont = to_wstring(16000);
	Desc.TitleFont = L"�������� ����";
	Desc.ExplainFont = L"���� �� ������ �� ���������� ���� ���� �����ȴ� ���� �޺��Դϴ�.&&��ٷο� �޺� �� �ϳ��Դϴ�. ó�� �� ���� ������ ������ ����,&���̰� ȸ�� ������ ��ġ�� �޺��� ������ ������ �Է��ϼ���!";
	Desc.iEnterCount = 3;
	m_AttackMap.emplace(L"�������� ����", Desc);
}

void CUi_StoreAttack::Initialize_Back()
{
	CUi_Default::Desc Desc;
	Desc.fColor = { 1, 1, 1, 0 };
	Desc.fSizeX = 220;
	Desc.fSizeY = 60;
	Desc.fX = -_float(g_iWinSizeX * 0.5f) + Desc.fSizeX * 0.5f + 30;
	Desc.fY = g_iWinSizeY * 0.5f - Desc.fSizeY * 0.5f - 20;
	Desc.eRenderType = RenderType::BackGround;
	Desc.iPriority = 5;
	Desc.ShaderFileName = L"Prototype_Component_Shader_VtxPosTex";
	Desc.ShaderPass = ShaderPass::Blend;
	Desc.TextureFileName = L"Prototype_Component_Texture_StoreTitle";
	Desc.TextureLevel = LEVEL_STATIC;
	m_BackVec.emplace_back(static_pointer_cast<CUi_Default>(CUi_Mgr::Get_Instance()->
		Add_Clone_Return(CUi_Default::ObjID, m_iLevelIndex, L"CUi", CUi_Default::ObjID, &Desc)));

	Desc.fSizeX = 400;
	Desc.fSizeY = g_iWinSizeY * 0.8f;
	Desc.fX = -_float(g_iWinSizeX * 0.5f) + Desc.fSizeX * 0.4f;
	Desc.fY = g_iWinSizeY * 0.1f;
	Desc.fZ = 0.93f;
	Desc.eRenderType = RenderType::BackGround;
	Desc.iPriority = 0;
	Desc.TextureFileName = L"Prototype_Component_Texture_SelectAttackStore";
	m_BackVec.emplace_back(static_pointer_cast<CUi_Default>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_Default::ObjID, m_iLevelIndex, L"CUi", CUi_Default::ObjID, &Desc)));
}

void CUi_StoreAttack::Check_Has()
{
	if (PLAYERMANAGER->Is_HasThing(CPlayer_Manager::ThingType::Attack, m_StoreBarVec[m_iFocusIndex]->Get_Name()))
		m_StoreDesc->Set_BuyBarType(CUi_StoreBuyBar::Type::Has);
	else
		m_StoreDesc->Set_BuyBarType(CUi_StoreBuyBar::Type::NeedBuy);
}

void CUi_StoreAttack::Select_Bar()
{
	PLAYERMANAGER->Sub_PlayerGear(m_StoreBarVec[m_iFocusIndex]->Get_Price());
	CPlayer_Manager::AttackDesc Desc;
	Desc.Test = 1;
	PLAYERMANAGER->Add_Thing(m_StoreBarVec[m_iFocusIndex]->Get_Type(), m_StoreBarVec[m_iFocusIndex]->Get_Name(), &Desc);
	m_StoreDesc->Set_BuyBarType(CUi_StoreBuyBar::Type::Has);
}

shared_ptr<CUi_StoreAttack> CUi_StoreAttack::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	struct MakeSharedEnabler : public CUi_StoreAttack
	{
		MakeSharedEnabler(ID3D11Device* pDevice, ID3D11DeviceContext* pContext) : CUi_StoreAttack(pDevice, pContext) { }
	};

	shared_ptr<CUi_StoreAttack> pInstance = make_shared<MakeSharedEnabler>(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
		assert(false);

	return pInstance;
}

shared_ptr<CGameObject> CUi_StoreAttack::Clone(void* pArg)
{
	struct MakeSharedEnabler : public CUi_StoreAttack
	{
		MakeSharedEnabler(const CUi_StoreAttack& rhs) : CUi_StoreAttack(rhs) { }
	};

	shared_ptr<CUi_StoreAttack> pInstance = make_shared<MakeSharedEnabler>(*this);


	if (FAILED(pInstance->Initialize(pArg)))
		assert(false);


	return pInstance;
}
