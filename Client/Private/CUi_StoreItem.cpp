#include "CUi_StoreItem.h"
#include "Shader.h"
#include "Texture.h"
#include "GameInstance.h"
#include "VIBuffer_Rect.h"
#include "CUi_StoreBar.h"
#include "CUi_Default.h"
#include "PlayerManager.h"
#include "CUi_StoreEdge.h"


wstring CUi_StoreItem::ObjID = L"CUi_StoreItem";

CUi_StoreItem::CUi_StoreItem(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CUi_Store(pDevice, pContext)
{
}

CUi_StoreItem::CUi_StoreItem(const CUi_StoreItem& rhs)
	:CUi_Store(rhs)
{
}

CUi_StoreItem::~CUi_StoreItem()
{
}

HRESULT CUi_StoreItem::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CUi_StoreItem::Initialize(void* pArg)
{
	Initialize_Transform();
	Initialize_StoreDesc();
	Initialize_Boundary(250, -100, -250, 450);
	Initialize_Item();
	Initialize_ItemMap();


	return S_OK;
}

void CUi_StoreItem::PriorityTick(_float fTimeDelta)
{
}

void CUi_StoreItem::Tick(_float fTimeDelta)
{
	Check_Has();
	Scrolling(fTimeDelta);
	Progress_Store(fTimeDelta);
	wstring SkillName = m_StoreBarVec[m_iFocusIndex]->Get_Name();
	m_StoreDesc->Set_Desc((m_ItemMap.find(SkillName)->second));
}

void CUi_StoreItem::LateTick(_float fTimeDelta)
{
	
}

void CUi_StoreItem::Initialize_Item()
{
	CUi_StoreBar::Desc Desc;
	Desc.fSizeX = 440;
	Desc.fSizeY = 50;
	Desc.fSpeed = 300;
	Desc.fX = -255;
	Desc.fY = 200 - _float(m_StoreBarVec.size() * 60);
	Desc.eRenderType = RenderType::Normal;
	Desc.iPriority = 0;
	Desc.ShaderFileName = L"Prototype_Component_Shader_VtxPosTex";
	Desc.ShaderPass = ShaderPass::Blend;
	Desc.TextureFileName = L"Prototype_Component_Texture_StoreBar";
	Desc.TextureLevel = LEVEL_STATIC;
	Desc.Price = 5000;
	Desc.fUpLimitPos = m_pBoundaryVec[0]->Get_Pos().y;
	Desc.fDownLimitPos = m_pBoundaryVec[1]->Get_Pos().y;
	Desc.StringFont = L"������ ������";
	Desc.type = CPlayer_Manager::ThingType::Item;
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));


	Desc.fY = 200 - _float(m_StoreBarVec.size() * 60);
	Desc.Price = 10000;
	Desc.StringFont = L"���� ������ �ھ�";
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));

	Desc.fY = 200 - _float(m_StoreBarVec.size() * 60);
	Desc.Price = 50000;
	Desc.StringFont = L"ü�� ��ũ";
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));

	Desc.fY = 200 - _float(m_StoreBarVec.size() * 60);
	Desc.Price = 40000;
	Desc.StringFont = L"Ư�� ���� ���� Ȯ��";
	m_StoreBarVec.emplace_back(static_pointer_cast<CUi_StoreBar>
		(CUi_Mgr::Get_Instance()->Add_Clone_Return(CUi_StoreBar::ObjID, m_iLevelIndex, L"CUi", CUi_StoreBar::ObjID, &Desc)));

	m_StoreBarVec[0]->Set_Focus(true);
}

void CUi_StoreItem::Initialize_ItemMap()
{
	CUi_StoreDesc::ItemDesc Desc;
	Desc.PriceFont = to_wstring(5000);
	Desc.TitleFont = L"������ ������";
	Desc.ExplainFont = L"�Ͻ�Ʈ�� ������Ʈ ��ǰ�� ȣȯ�Ǵ� �ݵ�������&������ �������Դϴ�!&&������ �ִ� ü���� �����մϴ�!&&�������!?";
	Desc.iEnterCount = 5;
	m_ItemMap.emplace(L"������ ������", Desc);

	Desc.PriceFont = to_wstring(10000);
	Desc.TitleFont = L"���� ������ �ھ�";
	Desc.ExplainFont = L"�������� ������� ���� �ݵ������� ��������& ���� �ھ��Դϴ�.&&��� ���� ¥������ �����ϴ� ����, ������ �ִ� ������ �������� �ϳ�&������Ų�ٴ� ���� Ư¡�Դϴ�!";
	Desc.iEnterCount = 4;
	m_ItemMap.emplace(L"���� ������ �ھ�", Desc);

	Desc.PriceFont = to_wstring(50000);
	Desc.TitleFont = L"ü�� ��ũ";
	Desc.ExplainFont = L"�������� ���� ������ å�����ϴ�! �Դٰ� ���� �۵� ����!&&�� ü�� ��ũ�� ���̰� ü���� ������&ȸ���� �� ���� ��ŭ�� �������� �����ϸ�,&������ ü���� �ٴڳ��� �ڵ����� �ߵ��˴ϴ�.&&ü���� ������ ���¿��� ȸ�� �������� �ֿ��,&��ũ�� �߰� ü���� ����˴ϴ�.";
	Desc.iEnterCount = 7;
	m_ItemMap.emplace(L"ü�� ��ũ", Desc);

	Desc.PriceFont = to_wstring(40000);
	Desc.TitleFont = L"Ư�� ���� ���� Ȯ��";
	Desc.ExplainFont = L"Ư�� ���� �� ���δ� �����մϴ�!&&������ ���׷��̵��ϸ�, ���̰� �� ���� Ư�� ������ �����ϰ�&�׶��׶� ��Ȳ�� ���� ��ü�� �� �ְ� �˴ϴ�!&&Ư�� ������ ���� ������ ��, ������ �÷����ϴ� ���� �ƹ� ����&������ Ű�� ������ Ư�� ������ ������ �� �ֽ��ϴ�.&&������ ������ �������� ������� �� Ȯ���ϼ���!";
	Desc.iEnterCount = 8;
	m_ItemMap.emplace(L"Ư�� ���� ���� Ȯ��", Desc);
}

void CUi_StoreItem::Initialize_Back()
{
	CUi_Default::Desc Desc;
	Desc.fColor = { 1, 1, 1, 0 };
	Desc.fSizeX = 220;
	Desc.fSizeY = 60;
	Desc.fX = -_float(g_iWinSizeX * 0.5f) + Desc.fSizeX * 0.5f + 30;
	Desc.fY = g_iWinSizeY * 0.5f - Desc.fSizeY * 0.5f - 20;
	Desc.fZ = 0.9f;
	Desc.eRenderType = RenderType::BackGround;
	Desc.iPriority = 0;
	Desc.ShaderFileName = L"Prototype_Component_Shader_VtxPosTex";
	Desc.ShaderPass = ShaderPass::Blend;
	Desc.TextureFileName = L"Prototype_Component_Texture_StoreTitle";
	Desc.TextureLevel = LEVEL_STATIC;
	m_BackVec.emplace_back(static_pointer_cast<CUi_Default>(CUi_Mgr::Get_Instance()->
		Add_Clone_Return(CUi_Default::ObjID, m_iLevelIndex, L"CUi", CUi_Default::ObjID, &Desc)));
}

void CUi_StoreItem::Check_Has()
{
	if (PLAYERMANAGER->Is_HasThing(CPlayer_Manager::ThingType::Item, m_StoreBarVec[m_iFocusIndex]->Get_Name()))
		m_StoreDesc->Set_BuyBarType(CUi_StoreBuyBar::Type::Has);
	else
		m_StoreDesc->Set_BuyBarType(CUi_StoreBuyBar::Type::NeedBuy);
}

void CUi_StoreItem::Select_Bar()
{
	PLAYERMANAGER->Sub_PlayerGear(m_StoreBarVec[m_iFocusIndex]->Get_Price());
	CPlayer_Manager::ItemDesc Desc;
	wstring Name = m_StoreBarVec[m_iFocusIndex]->Get_Name();
	Desc.Test = 1;
	if(Name == L"������ ������")
	{
		_float fMaxHp = CPlayer_Manager::Get_Instance()->Get_MaxHp();
		CPlayer_Manager::Get_Instance()->Set_MaxHp(fMaxHp + 50);
		CPlayer_Manager::Get_Instance()->Set_Hp(fMaxHp + 50);
	}
	else if(Name == L"���� ������ �ھ�")
	{
		_float fReverb = CPlayer_Manager::Get_Instance()->Get_MaxReverb();
		CPlayer_Manager::Get_Instance()->Set_MaxReverb(fReverb + 50);
		CPlayer_Manager::Get_Instance()->Set_Reverb(fReverb + 50);
	}
	PLAYERMANAGER->Add_Thing(CPlayer_Manager::ThingType::Item, m_StoreBarVec[m_iFocusIndex]->Get_Name(), &Desc);
	m_StoreDesc->Set_BuyBarType(CUi_StoreBuyBar::Type::Has);
}

shared_ptr<CUi_StoreItem> CUi_StoreItem::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	struct MakeSharedEnabler : public CUi_StoreItem
	{
		MakeSharedEnabler(ID3D11Device* pDevice, ID3D11DeviceContext* pContext) : CUi_StoreItem(pDevice, pContext) { }
	};

	shared_ptr<CUi_StoreItem> pInstance = make_shared<MakeSharedEnabler>(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
		assert(false);

	return pInstance;
}

shared_ptr<CGameObject> CUi_StoreItem::Clone(void* pArg)
{
	struct MakeSharedEnabler : public CUi_StoreItem
	{
		MakeSharedEnabler(const CUi_StoreItem& rhs) : CUi_StoreItem(rhs) { }
	};

	shared_ptr<CUi_StoreItem> pInstance = make_shared<MakeSharedEnabler>(*this);


	if (FAILED(pInstance->Initialize(pArg)))
		assert(false);


	return pInstance;
}
