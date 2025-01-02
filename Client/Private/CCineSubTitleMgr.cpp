#include "CCineSubTitleMgr.h"
#include "GameInstance.h"
#include "iostream"
#include "Cine_Manager.h"


IMPLEMENT_SINGLETON(CCineSubTitleMgr)

CCineSubTitleMgr::CCineSubTitleMgr()
{
}

CCineSubTitleMgr::~CCineSubTitleMgr()
{
	Free();
}

void CCineSubTitleMgr::Initialize()
{
	for (size_t i = 0; i < (_uint)CineType::End; ++i)
	{
		m_SubTitleVec[i].resize(100);
	}

	Initialize_CS0106();

	Initialize_CS0230();
	Initialize_CS0235();
	Initialize_CS0240();
	Initialize_CS0245();

	
	Initialize_CS0620();


	Initialize_CS0820();
	Initialize_CS0825();
	Initialize_CS0830();
	Initialize_CS0835();
	Initialize_CS0840();


	Initialize_CS1125();
	Initialize_CS1130();
	Initialize_EV1120();
	Initialize_EV1130();
	Initialize_EV1150();
	Initialize_EV1160();
	Initialize_EV1170();
	Initialize_EV1180();
	Initialize_EV1190();


	Initialize_CS1205();
	Initialize_CS1210();
	Initialize_CS1215();
	Initialize_CS1220();
	Initialize_CS1225();
	Initialize_EV1250();
}

void CCineSubTitleMgr::PriorityTick(_float fTimeDelta)
{
	//if (CCine_Manager::Get_Instance()->IsInGame())
	//{
	//	m_RenderFontTitleVec.clear();
	//}
}

void CCineSubTitleMgr::Tick(_float fTimeDelta)
{
}

void CCineSubTitleMgr::LateTick(_float fTimeDelta)
{
	for (auto& iter : m_RenderFontTitleVec)
		iter.m_fLifeTime -= fTimeDelta;
}

void CCineSubTitleMgr::Tick_Engine(_float fTimeDelta)
{
	PriorityTick(fTimeDelta);
	Tick(fTimeDelta);
	LateTick(fTimeDelta);
}

void CCineSubTitleMgr::Render()
{
	if (m_RenderFontTitleVec.size() >= 2)
	{
		while(m_RenderFontTitleVec.size() >= 2)
		{
			m_RenderFontTitleVec.erase(m_RenderFontTitleVec.begin());
		}
	}
	
	if (m_RenderFontTitleVec.size() != 0)
	{
		if (m_RenderFontTitleVec[0].m_fLifeTime > 0)
		{
			RenderFont(m_RenderFontTitleVec[0]);
		}
	}
}

void CCineSubTitleMgr::RenderStartSetting(CineType eType, _uint vecindex, _float Time)
{
	if ((_uint)CineType::End <= (_uint)eType)
	{
		cout << "SubTitleVec OutofRange" << endl;
		assert(false);
	}

	if (m_SubTitleVec[(_uint)eType].size() <= vecindex)
	{
		cout << "SubTitleVec OutofRange" << endl;
		assert(false);
	}

	m_SubTitleVec[(_uint)eType][vecindex].m_fLifeTime = Time;
	m_RenderFontTitleVec.emplace_back(m_SubTitleVec[(_uint)eType][vecindex]);
}

void CCineSubTitleMgr::Initialize_IntroCallBack()
{
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0106", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0106, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0106", 3, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0106, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0106", 5, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0106, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0106", 6, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0106, 3, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0106", 10, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0106, 4, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0106", 11, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0106, 5, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0106", 12, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0106, 6, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0106", 13, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0106, 7, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0106", 31, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0106, 8, Time);
		}
	);
}

void CCineSubTitleMgr::Initialize_RekkaCallBack()
{
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 1, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 1, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 8, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 2, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 14, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 3, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 15, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 4, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 16, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 5, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 17, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 6, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 21, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 7, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 21, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 8, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 23, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 9, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 23, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 10, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 24, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 11, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 26, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 12, Time);
		}
	);
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0230", 27, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0230, 13, Time);
		}
	);


	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0235", 3, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0235, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0235", 19, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0235, 1, Time);
		}
	);


	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0240", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0240, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0240", 10, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0240, 1, Time);
		}
	);


	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0245", 4, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0245, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0245", 5, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0245, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0245", 6, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0245, 2, Time);
		}
	);
}

void CCineSubTitleMgr::Initialize_KorsicaCallBack()
{
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 0, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 3, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 3, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 4, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 3, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 6, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 4, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 6, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 5, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 6, 2, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 6, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 6, 3, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 7, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 6, 4, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 8, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 6, 5, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 9, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 6, 6, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 10, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 6, 7, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 11, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0620", 9, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0620, 12, Time);
		}
	);
}

void CCineSubTitleMgr::Initialize_MimosaCallBack()
{
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 11, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 12, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 13, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 14, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 3, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 15, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 4, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 17, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 5, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 17, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 6, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 19, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 7, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 20, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 8, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0820", 21, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0820, 9, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0825", 1, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0825, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0825", 1, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0825, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0830", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0830, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0830", 3, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0830, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0830", 3, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0830, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0830", 4, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0830, 3, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0835", 1, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0835, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0840", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0840, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS0840", 3, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS0840, 1, Time);
		}
	);
}

void CCineSubTitleMgr::Initialize_KaleStageCallBack()
{
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1130", 0, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1130, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1130", 0, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1130, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1150", 0, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1150, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1150", 1, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1150, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1180", 5, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1180, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1180", 5, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1180, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1180", 5, 2, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1180, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1180", 6, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1180, 3, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1125", 1, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1125, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1125", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1125, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1125", 9, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1125, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1170", 0, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1170, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1170", 0, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1170, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("EV1170", 0, 2, [&](_float Time)
		{
			RenderStartSetting(CineType::EV1170, 2, Time);
		}
	);
}

void CCineSubTitleMgr::Initialize_KaleBossCallBack()
{
	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1205", 4, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1205, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1205", 5, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1205, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1205", 6, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1205, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1205", 7, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1205, 3, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1205", 8, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1205, 4, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1205", 11, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1205, 5, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1205", 16, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1205, 6, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1210", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1210, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1210", 3, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1210, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1210", 4, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1210, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1210", 8, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1210, 3, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1210", 9, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1210, 4, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1215", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1215, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1215", 9, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1215, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1215", 10, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1215, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1215", 11, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1215, 3, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1220", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1220, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1220", 3, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1220, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1220", 10, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1220, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1225", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1225, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1225", 2, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1225, 0, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1225", 3, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1225, 1, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1225", 6, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1225, 2, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1225", 7, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1225, 3, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1225", 7, 1, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1225, 4, Time);
		}
	);

	CCine_Manager::Get_Instance()->AddConversation_Callback
	("CS1225", 16, 0, [&](_float Time)
		{
			RenderStartSetting(CineType::CS1225, 5, Time);
		}
	);
}

void CCineSubTitleMgr::Initialize_CS0106()
{
	CineType eType = CineType::CS0106;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"���!");
	Emplace_SubTitle(eType, 1, SpeakerType::SBR, 9999, L"����, ������.&�κ� �� LX-DUST75. �ڼ� ��⹰ ���� ���.");
	Emplace_SubTitle(eType, 2, SpeakerType::Chai, 9999, L"���... �ڼ� ��⹰ ���� ���?");
	Emplace_SubTitle(eType, 3, SpeakerType::SBR, 9999, L"��Ȯ�� ��ü ���. �ҷ�ǰ�� �� ����. ��Ƶ鿩!");
	Emplace_SubTitle(eType, 4, SpeakerType::SBR, 9999, L"�װ� �����ΰ�?");
	Emplace_SubTitle(eType, 5, SpeakerType::Chai, 9999, L"��.. �ƴҰ�?");
	Emplace_SubTitle(eType, 6, SpeakerType::SBR, 9999, L"�����Ϸ��� ����.");
	Emplace_SubTitle(eType, 7, SpeakerType::Chai, 9999, L"���, ��?");
	Emplace_SubTitle(eType, 8, SpeakerType::SBR, 9999, L"���!");
}

void CCineSubTitleMgr::Initialize_CS0230()
{
	CineType eType = CineType::CS0230;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"�����ϳ�. ������ ���� ���� ����");
	Emplace_SubTitle(eType, 1, SpeakerType::RekkaHost, 9999, L"�Ұ��մϴ�... ��ī!");
	Emplace_SubTitle(eType, 2, SpeakerType::Rekka, 9999, L"�����ϰ� �ͳ�? �������̰� �ͳ�?&�׷��ٸ� ���������� �޷�����!");
	Emplace_SubTitle(eType, 3, SpeakerType::Rekka, 9999, L"�ҷ�ǰ �ּ��� �༮, ���⼭ ����ġ�� �ϴٴ�,&���� ������ �ش�±�.");
	Emplace_SubTitle(eType, 4, SpeakerType::Chai, 9999, L"�� �����Ѵٴ� �ǵ�?");
	Emplace_SubTitle(eType, 5, SpeakerType::Rekka, 9999, L"�� ������ �༮. �� �ǰھ�. �۷��긦 ����߰ڱ�.");
	Emplace_SubTitle(eType, 6, SpeakerType::Chai, 9999, L"��¥ ����...");
	Emplace_SubTitle(eType, 7, SpeakerType::Chai, 9999, L"�̷� ��쿣 ��� �� ��ȹ�̾���, ���۹�Ʈ?");
	Emplace_SubTitle(eType, 8, SpeakerType::Peppermint, 9999, L"�۽�... �ο��?");
	Emplace_SubTitle(eType, 9, SpeakerType::Chai, 9999, L"�̹� ������ �ι�� ��� �Ұž�.");
	Emplace_SubTitle(eType, 10, SpeakerType::Peppermint, 9999, L"������� �� ��Ҹ���.");
	Emplace_SubTitle(eType, 11, SpeakerType::Rekka, 9999, L"����! �� ���� �ֿ��� ����.");
	Emplace_SubTitle(eType, 12, SpeakerType::Rekka, 9999, L"�ο� �غ� �϶��!");
	Emplace_SubTitle(eType, 13, SpeakerType::Rekka, 9999, L"��! �Ͷ�!");
}

void CCineSubTitleMgr::Initialize_CS0235()
{
	CineType eType = CineType::CS0235;
	Emplace_SubTitle(eType, 0, SpeakerType::Rekka, 9999, L"�ҷ�ǰġ��� �����̱�.");
	Emplace_SubTitle(eType, 1, SpeakerType::Rekka, 9999, L"��ī�� ������ �� �ؾ߰ھ�!");
}

void CCineSubTitleMgr::Initialize_CS0240()
{
	CineType eType = CineType::CS0240;
	Emplace_SubTitle(eType, 0, SpeakerType::Rekka, 9999, L"ȸ���� ���� ������ �� �� ����!");
	Emplace_SubTitle(eType, 1, SpeakerType::Rekka, 9999, L"�������뿡 ó�ھ� �ָ�.");
}

void CCineSubTitleMgr::Initialize_CS0245()
{ 
	CineType eType = CineType::CS0245;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"�� �ο��� �� �й��, �� ����.");
	Emplace_SubTitle(eType, 1, SpeakerType::Rekka, 9999, L"���� �� ���� �ּ������� �� �� ����?");
	Emplace_SubTitle(eType, 2, SpeakerType::Chai, 9999, L"��, �׷� �� ������.");

}

void CCineSubTitleMgr::Initialize_CS0620()
{
	CineType eType = CineType::CS0620;
	Emplace_SubTitle(eType, 0, SpeakerType::Korsica, 9999, L"����!?");
	Emplace_SubTitle(eType, 1, SpeakerType::Chai, 9999, L"�̰� ���ؾ�, �ڸ���ī!");
	Emplace_SubTitle(eType, 2, SpeakerType::Chai, 9999, L"�׳� ���ض��!");
	Emplace_SubTitle(eType, 3, SpeakerType::Korsica, 9999, L"�ò�����!");
	Emplace_SubTitle(eType, 4, SpeakerType::Korsica, 9999, L"��ü ���� ���ض� ����?");
	Emplace_SubTitle(eType, 5, SpeakerType::Chai, 9999, L"��... �� �׳� ��ȭ�Ϸ� �� �ž�.");
	Emplace_SubTitle(eType, 6, SpeakerType::Korsica, 9999, L"�� ������ ������ġ���� ������ �ٵ�.");
	Emplace_SubTitle(eType, 7, SpeakerType::Chai, 9999, L"�ϳ����� �����ϴ���.");
	Emplace_SubTitle(eType, 8, SpeakerType::CNMN, 9999, L"�̽��� ����, �ڱ����� ������!");
	Emplace_SubTitle(eType, 9, SpeakerType::Peppermint, 9999, L"�� ��û�� �༮!");
	Emplace_SubTitle(eType, 10, SpeakerType::Macaron, 9999, L"�̷�, ū���̾�...");
	Emplace_SubTitle(eType, 11, SpeakerType::Korsica, 9999, L"�� ���Ͽ� �ںν��� ������. �̹��� ���� �� ��������.");
	Emplace_SubTitle(eType, 12, SpeakerType::Chai, 9999, L"��... ��...");
}

void CCineSubTitleMgr::Initialize_CS0820()
{
	CineType eType = CineType::CS0820;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"�� �� �Ŵ�, �̸��!");
	Emplace_SubTitle(eType, 1, SpeakerType::Mimosa, 9999, L"ť ���� ��ٷ�����...");
	Emplace_SubTitle(eType, 2, SpeakerType::Chai, 9999, L"����Ʈ�� ��ȣ�� ����!");
	Emplace_SubTitle(eType, 3, SpeakerType::Mimosa, 9999, L"��! � ��ġ�ٴ�...! �ƴ���...");
	Emplace_SubTitle(eType, 4, SpeakerType::Mimosa, 9999, L"�������� ���� ���� Ư���� ������ �غ��߽��ϴ�! �� ģ����&�����ַ� �Գ׿�.");
	Emplace_SubTitle(eType, 5, SpeakerType::Mimosa, 9999, L"�� ������ �����̴�. �̰� �� ���!");
	Emplace_SubTitle(eType, 6, SpeakerType::Mimosa, 9999, L"������!");
	Emplace_SubTitle(eType, 7, SpeakerType::Mimosa, 9999, L"�׸��� ������...");
	Emplace_SubTitle(eType, 8, SpeakerType::Mimosa, 9999, L"� �����ϰڽ��ϴ�!");
	Emplace_SubTitle(eType, 9, SpeakerType::Mimosa, 9999, L"���� ť!");
}

void CCineSubTitleMgr::Initialize_CS0825()
{
	CineType eType = CineType::CS0825;
	Emplace_SubTitle(eType, 0, SpeakerType::Mimosa, 9999, L"�̰� ��մ°�...");
	Emplace_SubTitle(eType, 1, SpeakerType::Mimosa, 9999, L"������ �� ���� �÷� ����! ���� ��.");
}

void CCineSubTitleMgr::Initialize_CS0830()
{
	CineType eType = CineType::CS0830;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"�ٵ� ���� ���µ�, �̸��.");
	Emplace_SubTitle(eType, 1, SpeakerType::Mimosa, 9999, L"���ߵ��� �� �վȿ� �־�.");
	Emplace_SubTitle(eType, 2, SpeakerType::Mimosa, 9999, L"��ΰ� ����� �� ������ ���� �;� ����.");
	Emplace_SubTitle(eType, 3, SpeakerType::Mimosa, 9999, L"���� ���� �ִ��� Ȯ���� ����.");

}

void CCineSubTitleMgr::Initialize_CS0835()
{
	CineType eType = CineType::CS0835;
	Emplace_SubTitle(eType, 0, SpeakerType::Mimosa, 9999, L"�� ����Ʈ����Ʈ�� ���Ѱ� ��Ƴ��� �� ����!");
}

void CCineSubTitleMgr::Initialize_CS0840()
{
	CineType eType = CineType::CS0840;
	Emplace_SubTitle(eType, 0, SpeakerType::Mimosa, 9999, L"�� ��... ���� �� �� ����...");
	Emplace_SubTitle(eType, 1, SpeakerType::Chai, 9999, L"������ ���� � �ִ� ������.");
}

void CCineSubTitleMgr::Initialize_CS1125()
{
	CineType eType = CineType::CS1125;
	Emplace_SubTitle(eType, 0, SpeakerType::Macaron, 9999, L"�ó���! �׷�, ���Ҿ�! �ٵ� �ó����� ������!");
	Emplace_SubTitle(eType, 1, SpeakerType::Chai, 9999, L"�غ�ƾ�?");
	Emplace_SubTitle(eType, 2, SpeakerType::EVERYONE, 9999, L"�� ���ڰ�!");
}

void CCineSubTitleMgr::Initialize_CS1130()
{
	CineType eType = CineType::CS1130;
}

void CCineSubTitleMgr::Initialize_EV1120()
{
	CineType eType = CineType::EV1120;
}

void CCineSubTitleMgr::Initialize_EV1130()
{
	CineType eType = CineType::EV1130;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"���� �� ���ڳ�...");
	Emplace_SubTitle(eType, 1, SpeakerType::CNMN, 9999, L"�̽��� ����! ���� ���� ���ʷα���!");
}

void CCineSubTitleMgr::Initialize_EV1150()
{
	CineType eType = CineType::EV1150;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"����ĥ ���� ����...");
	Emplace_SubTitle(eType, 1, SpeakerType::Chai, 9999, L"�ڸ���ī! ������� �Դµ�, �� �Ǹ���Ű�� �����.");
}

void CCineSubTitleMgr::Initialize_EV1160()
{
	CineType eType = CineType::EV1160;
}

void CCineSubTitleMgr::Initialize_EV1170()
{
	CineType eType = CineType::EV1170;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"�ȵ�!");
	Emplace_SubTitle(eType, 1, SpeakerType::Kale, 9999, L"�׷� ���� �ҿ����.");
	Emplace_SubTitle(eType, 2, SpeakerType::Macaron, 9999, L"����! ���� �� �����̶�� ������ ��ȸ��!");
}

void CCineSubTitleMgr::Initialize_EV1180()
{
	CineType eType = CineType::EV1180;
	Emplace_SubTitle(eType, 0, SpeakerType::Korsica, 9999, L"��� ���� ����߾�!");
	Emplace_SubTitle(eType, 1, SpeakerType::Peppermint, 9999, L"���� ��� ����?");
	Emplace_SubTitle(eType, 2, SpeakerType::Macaron, 9999, L"���, �ó�����?");
	Emplace_SubTitle(eType, 3, SpeakerType::CNMN, 9999, L"�̰Ŷ�� �� ������ �𸣰ڱ���!");
}

void CCineSubTitleMgr::Initialize_EV1190()
{
	CineType eType = CineType::EV1190;
}

void CCineSubTitleMgr::Initialize_CS1205()
{
	CineType eType = CineType::CS1205;
	Emplace_SubTitle(eType, 0, SpeakerType::Kale, 9999, L"���ο� ������ ���屺. �� �� �� ���������� ���ھ�.");
	Emplace_SubTitle(eType, 1, SpeakerType::Chai, 9999, L"�ݵ����� �йи��� �Ͽ��� �Ǿ� �ڶ��������ϴ�.");
	Emplace_SubTitle(eType, 2, SpeakerType::Macaron, 9999, L"���̴� �׷� �� �� ��!");
	Emplace_SubTitle(eType, 3, SpeakerType::Kale, 9999, L"�׷�, �װ� �ٽ��̾�. ���� �༮�� �����ϰ� ��...");
	Emplace_SubTitle(eType, 4, SpeakerType::Kale, 9999, L"������! ��, ����...?");
	Emplace_SubTitle(eType, 5, SpeakerType::Peppermint, 9999, L"�׷�, �ٷ� �װž�. ���Ѵ�, 808!");
	Emplace_SubTitle(eType, 6, SpeakerType::Kale, 9999, L"�峭�ϴ� �ǰ�? ���� ����... ����� �������� �� �� ����?");
} 

void CCineSubTitleMgr::Initialize_CS1210()
{
	CineType eType = CineType::CS1210;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"���!");
	Emplace_SubTitle(eType, 1, SpeakerType::Kale, 9999, L"����!");
	Emplace_SubTitle(eType, 2, SpeakerType::Korsica, 9999, L"��ġ��, ����!");
	Emplace_SubTitle(eType, 3, SpeakerType::Chai, 9999, L"���ƿԴٰ� ���� ��.");
	Emplace_SubTitle(eType, 4, SpeakerType::Kale, 9999, L"���� ��ġ ���� �༮�̱�. �� �ǰھ�, ������ �����ڰ�.");
}

void CCineSubTitleMgr::Initialize_CS1215()
{
	CineType eType = CineType::CS1215;
	Emplace_SubTitle(eType, 0, SpeakerType::Kale, 9999, L"�� ���� ������ ������ ���� ����.");
	Emplace_SubTitle(eType, 1, SpeakerType::Kale, 9999, L"�� ������ �Ͻ�Ʈ�� ��ũ ������ �񱳵� �� ��.");
	Emplace_SubTitle(eType, 2, SpeakerType::Chai, 9999, L"�װ� �ΰ� ������.");
	Emplace_SubTitle(eType, 3, SpeakerType::Kale, 9999, L"�׷�, �ΰ� ���ڰ�.");
}

void CCineSubTitleMgr::Initialize_CS1220()
{
	CineType eType = CineType::CS1220;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"������ ����!");
	Emplace_SubTitle(eType, 1, SpeakerType::Kale, 9999, L"�� �� ���ٸ�, �� ���� �� �� �־��� �ٵ�.");
	Emplace_SubTitle(eType, 2, SpeakerType::Kale, 9999, L"��Ÿ������ �� ������ ������ ���⼭ ���̴�.");
}

void CCineSubTitleMgr::Initialize_CS1225()
{
	CineType eType = CineType::CS1225;
	Emplace_SubTitle(eType, 0, SpeakerType::Chai, 9999, L"���� �����ϰ� ��ȣ�� �Ѱ�.");
	Emplace_SubTitle(eType, 1, SpeakerType::Kale, 9999, L"�����ϰھ�.");
	Emplace_SubTitle(eType, 2, SpeakerType::Kale, 9999, L"����� �й��ڿ� �Ұ���!");
	Emplace_SubTitle(eType, 3, SpeakerType::Chai, 9999, L"�׷����� ����. ������ �Բ���� �츰 �����̾�.");
	Emplace_SubTitle(eType, 4, SpeakerType::Peppermint, 9999, L"����!");
	Emplace_SubTitle(eType, 5, SpeakerType::Kale, 9999, L"�� �̻��� �� �� �԰ڳ�...");
}

void CCineSubTitleMgr::Initialize_EV1250()
{
	CineType eType = CineType::EV1250;
}

void CCineSubTitleMgr::Emplace_SubTitle(CineType CineType, _uint Index, SpeakerType eType = SpeakerType::End, _float fLifeTime = 9999, wstring SubtitleString = L"")
{
	if (Index > 500)
	{
		cout << "SubtitleIndexoutofrange" << endl;
		assert(false);
	}
	if (m_SubTitleVec[(_uint)CineType][Index].String != L"")
	{
		cout << "OverLap!" << endl;
		cout << "Stage: " << (_uint)CineType << endl;
		cout << "Index: " << Index << endl;
	}

	Desc SubTitle;
	switch (eType)
	{
	case SpeakerType::Chai:
		SubTitle.SpeakerName = L"����";
		break;
	case SpeakerType::Peppermint:
		SubTitle.SpeakerName = L"���۹�Ʈ";
		break;
	case SpeakerType::Macaron:
		SubTitle.SpeakerName = L"��ī��";
		break;
	case SpeakerType::Korsica:
		SubTitle.SpeakerName = L"�ڸ���ī";
		break;
	case SpeakerType::SBR:
		SubTitle.SpeakerName = L"SBR-001";
		break;
	case SpeakerType::Rekka:
		SubTitle.SpeakerName = L"��ī";
		break;
	case SpeakerType::Mimosa:
		SubTitle.SpeakerName = L"�̸��";
		break;
	case SpeakerType::Kale:
		SubTitle.SpeakerName = L"����";
		break;
	case SpeakerType::RekkaHost:
		SubTitle.SpeakerName = L"�ٶ�����";
		break;
	case SpeakerType::CNMN:
		SubTitle.SpeakerName = L"�ó���";
		break;
	case SpeakerType::EVERYONE:
		SubTitle.SpeakerName = L"���";
		break;
	default:
		SubTitle.SpeakerName = L"";
		break;
	}
	SubTitle.String = SubtitleString;
	SubTitle.m_fLifeTime = fLifeTime;
	m_SubTitleVec[(_uint)CineType][Index] = SubTitle;
}

void CCineSubTitleMgr::RenderFont(Desc FontDesc)
{
	auto pGI = CGameInstance::Get_Instance();
	_float4 SpeakerColor = { 0, 0.3f, 1, 1 };
	_float Scale = { 0.7f };
#ifdef PERFECTION_LOAD
	Scale *= 2;
#endif
	_float Rotation = { 0 };
	_float2 SpeakerPos = { 640 - _float(FontDesc.SpeakerName.size() * 9), 620 };
#ifdef PERFECTION_LOAD
	SpeakerPos.x *= 2;
	SpeakerPos.y *= 2;
#endif
	_float2 SubTitlePos = { 0, 0 };
	_float4 SubTitleColor = { 1, 1, 1, 1 };
	_float4 OutlineColor = { 0, 0, 0, 1 };
	size_t count = 0;
	size_t pos = 0;
	_float2 OutlinePosition = {};
	
	if (FontDesc.String.find(L"&") == string::npos)
	{
		OutlinePosition = { SpeakerPos.x, SpeakerPos.y };
		for (_int i = -1; i <= 1; ++i)
		{
			OutlinePosition.x += i;
			for (_int j = -1; j <= 1; ++j)
			{
				OutlinePosition.y += j;
				pGI->Render_Font(L"Nexon", FontDesc.SpeakerName, OutlinePosition,
					XMLoadFloat4(&OutlineColor), Rotation, Scale);
			}
		}

		pGI->Render_Font(L"Nexon", FontDesc.SpeakerName, SpeakerPos,
			XMLoadFloat4(&SpeakerColor), Rotation, Scale);

		pos = FontDesc.String.find(L".");
		while (pos != wstring::npos)
		{
			count++;
			pos = FontDesc.String.find(L".", pos + 1);
		}
		pos = FontDesc.String.find(L"?");
		while (pos != wstring::npos)
		{
			count++;
			pos = FontDesc.String.find(L"?", pos + 1);
		}

		pos = FontDesc.String.find(L"!");
		while (pos != wstring::npos)
		{
			count++;
			pos = FontDesc.String.find(L"!", pos + 1);
		}

		SubTitlePos = { 640 - _float(FontDesc.String.size() * 10) + count * 5, 660 };
#ifdef PERFECTION_LOAD
		SubTitlePos = { (640 - _float(FontDesc.String.size() * 10) + count * 5) * 2, 660 * 2 };
#endif
		OutlinePosition = { SubTitlePos.x, SubTitlePos.y };
		for (_int i = -1; i <= 1; ++i)
		{
			OutlinePosition.x += i;
			for (_int j = -1; j <= 1; ++j)
			{
				OutlinePosition.y += j;
				pGI->Render_Font(L"Nexon", FontDesc.String, OutlinePosition,
					XMLoadFloat4(&OutlineColor), Rotation, Scale);
			}
		}

		pGI->Render_Font(L"Nexon", FontDesc.String, SubTitlePos,
			XMLoadFloat4(&SubTitleColor), Rotation, Scale);
	}
	else
	{
		SpeakerPos.y = 600;
#ifdef PERFECTION_LOAD
		SpeakerPos.y *= 2;
#endif
		OutlinePosition = { SpeakerPos.x, SpeakerPos.y };
		for (_int i = -1; i <= 1; ++i)
		{
			OutlinePosition.x += i;
			for (_int j = -1; j <= 1; ++j)
			{
				OutlinePosition.y += j;
				pGI->Render_Font(L"Nexon", FontDesc.SpeakerName, OutlinePosition,
					XMLoadFloat4(&OutlineColor), Rotation, Scale);
			}
		}

		pGI->Render_Font(L"Nexon", FontDesc.SpeakerName, SpeakerPos,
			XMLoadFloat4(&SpeakerColor), Rotation, Scale);


		Desc TempFont;
		size_t Find = FontDesc.String.find(L"&");
		TempFont.String = FontDesc.String.substr(0, Find);
		size_t PreviousCount = Find + 1;


		pos = TempFont.String.find(L".");
		while (pos != wstring::npos)
		{
			count++;
			pos = TempFont.String.find(L".", pos + 1);
		}

		pos = TempFont.String.find(L"?");
		while (pos != wstring::npos)
		{
			count++;
			pos = TempFont.String.find(L"?", pos + 1);
		}

		pos = TempFont.String.find(L"!");
		while (pos != wstring::npos)
		{
			count++;
			pos = TempFont.String.find(L"!", pos + 1);
		}

		SubTitlePos = { 640 - _float(TempFont.String.size() * 10) + count * 5, 640 };
#ifdef PERFECTION_LOAD
		SubTitlePos = { (640 - _float(TempFont.String.size() * 10) + count * 5) * 2, 640 * 2 };
#endif
		OutlinePosition = { SubTitlePos.x, SubTitlePos.y };

		for (_int i = -1; i <= 1; ++i)
		{
			OutlinePosition.x += i;
			for (_int j = -1; j <= 1; ++j)
			{
				OutlinePosition.y += j;
				pGI->Render_Font(L"Nexon", TempFont.SpeakerName, OutlinePosition,
					XMLoadFloat4(&OutlineColor), Rotation, Scale);
			}
		}	
		pGI->Render_Font(L"Nexon", TempFont.String, SubTitlePos, XMLoadFloat4(&SubTitleColor), Rotation, Scale);


		count = 0;
		pos = TempFont.String.find(L".");
		while (pos != wstring::npos)
		{
			count++;
			pos = TempFont.String.find(L".", pos + 1);
		}
		pos = TempFont.String.find(L"?");
		while (pos != wstring::npos)
		{
			count++;
			pos = TempFont.String.find(L"?", pos + 1);
		}

		pos = TempFont.String.find(L"!");
		while (pos != wstring::npos)
		{
			count++;
			pos = TempFont.String.find(L"!", pos + 1);
		}


		TempFont.String = FontDesc.String.substr(PreviousCount, FontDesc.String.size() - PreviousCount);
		SubTitlePos = { 640 - _float(TempFont.String.size() * 10) + count * 5, 680 };
#ifdef PERFECTION_LOAD
		SubTitlePos = { (640 - _float(TempFont.String.size() * 10) + count * 5) * 2, 680 * 2};
#endif
		OutlinePosition = { SubTitlePos.x, SubTitlePos.y };

		for (_int i = -1; i <= 1; ++i)
		{
			OutlinePosition.x += i;
			for (_int j = -1; j <= 1; ++j)
			{
				OutlinePosition.y += j;
				pGI->Render_Font(L"Nexon", TempFont.SpeakerName, OutlinePosition,
					XMLoadFloat4(&OutlineColor), Rotation, Scale);
			}
		}
		pGI->Render_Font(L"Nexon", TempFont.String, SubTitlePos, XMLoadFloat4(&SubTitleColor), Rotation, Scale);
	}
}

void CCineSubTitleMgr::Free()
{
	for (_uint i = 0; i < (_uint)CineType::End; ++i)
	{
		m_SubTitleVec[i].clear();
	}
	m_RenderFontTitleVec.clear();
}
