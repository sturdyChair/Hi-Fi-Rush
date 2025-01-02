#pragma once

#include "Client_Defines.h"

/* 2. �ε� ���� ������ �ʿ��� �ڿ��� �����Ѵ�.  */
/* ���� ������ ���� �ڿ� �ε� : ��Ƽ������ */

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CLoader
{
private:
	CLoader(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

public:
	~CLoader();

public:
	HRESULT Initialize(LEVEL eNextLevelID);
	_uint Loading();
	_bool isFinished() const {
		return m_isFinished;
	}

	void Show_LoadingText() {
		SetWindowText(g_hWnd, m_szLoadingText);
	}

	HRESULT Load_Ui();

	HRESULT Load_Ui_Skill_Textures();
	HRESULT Load_Ui_Skill_Prototype();

	HRESULT Load_Object_Textures();

	HRESULT Load_Model();

private:
	ID3D11Device*			m_pDevice = { nullptr };
	ID3D11DeviceContext*	m_pContext = { nullptr };
	HANDLE					m_hThread = {};
	CRITICAL_SECTION		m_CriticalSection = {};
	LEVEL					m_eNextLevelID = { LEVEL_END };

	_tchar					m_szLoadingText[MAX_PATH] = TEXT("");
	_float					m_fLoadingPercent = { 0.0f };
	_bool					m_isFinished = { false };

private:
	weak_ptr<CGameInstance> m_pGameInstance;


private:
	HRESULT Loading_For_Logo_Level();
	HRESULT Loading_For_Test_Level();
	HRESULT Loading_For_AnimTool_Level();
	HRESULT Loading_For_MapTool_Level();
	HRESULT Loading_For_EffectTool_Level();
	HRESULT Loading_For_UITool_Level();
	HRESULT Loading_For_KorsicaTest_Level();
	HRESULT Loading_For_ModelTest_Level();
	HRESULT Loading_For_Lift_Level();
	HRESULT Loading_For_KaleBoss_Level();
	HRESULT Loading_For_CineTool_Level();
	HRESULT Loading_For_MimosaBoss_Level();
	HRESULT Loading_For_GimmicTest_Level();
	HRESULT Loading_For_KaleStage_Level();

public:
	static shared_ptr<CLoader> Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVEL eNextLevelID);
	void Free();
};

END