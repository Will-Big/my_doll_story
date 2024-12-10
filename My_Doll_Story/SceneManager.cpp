#include "pch.h"
#include "SceneManager.h"

#include "Scene_Title.h"
#include "Scene_Menu.h"
#include "Scene_SelectStage.h"
#include "Scene_SelectStage2.h"
#include "Scene_Creator.h"
#include "Scene_Help.h"
#include "Scene_Main.h"
#include "Scene_UI_Test.h"


#include "Stage.h"
#include "Stage_01.h"
#include "Stage_02.h"
#include "Stage_03.h"
#include "Stage_04.h"
#include "Stage_05.h"
#include "Stage_06.h"
#include "Stage_07.h"
#include "Stage_08.h"


SceneManager::SceneManager()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

SceneManager::~SceneManager()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void SceneManager::init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::TITLE] = new Scene_Title;
	m_arrScene[(UINT)SCENE_TYPE::TITLE]->SetName(L"Title Scene");

	m_arrScene[(UINT)SCENE_TYPE::MENU] = new Scene_Menu;
	m_arrScene[(UINT)SCENE_TYPE::MENU]->SetName(L"Menu Scene");

	m_arrScene[(UINT)SCENE_TYPE::MAIN] = new Scene_Main;
	m_arrScene[(UINT)SCENE_TYPE::MAIN]->SetName(L"Main Scene");

	m_arrScene[(UINT)SCENE_TYPE::SELECT_STAGE] = new Scene_SelectStage;
	m_arrScene[(UINT)SCENE_TYPE::SELECT_STAGE]->SetName(L"SelectStage Scene");

	m_arrScene[(UINT)SCENE_TYPE::SELECT_STAGE2] = new Scene_SelectStage2;
	m_arrScene[(UINT)SCENE_TYPE::SELECT_STAGE2]->SetName(L"SelectStage Scene 2");

	m_arrScene[(UINT)SCENE_TYPE::CREATOR] = new Scene_Creator;
	m_arrScene[(UINT)SCENE_TYPE::CREATOR]->SetName(L"Scene Creator");

	m_arrScene[(UINT)SCENE_TYPE::HELP] = new Scene_Help;
	m_arrScene[(UINT)SCENE_TYPE::HELP]->SetName(L"Scene_Help");

	m_arrScene[(UINT)SCENE_TYPE::UI_TEST] = new Scene_UI_Test;
	m_arrScene[(UINT)SCENE_TYPE::UI_TEST]->SetName(L"UI Test Scene");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new Stage_01;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01]->SetName(L"Stage_01");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new Stage_02;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02]->SetName(L"Stage_02");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_03] = new Stage_03;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_03]->SetName(L"Stage_03");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_04] = new Stage_04;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_04]->SetName(L"Stage_04");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_05] = new Stage_05;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_05]->SetName(L"Stage_05");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_06] = new Stage_06;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_06]->SetName(L"Stage_06");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_07] = new Stage_07;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_07]->SetName(L"STAGE_07");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_08] = new Stage_08;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_08]->SetName(L"STAGE_08");

	for (UINT i = (UINT)SCENE_TYPE::STAGE_01; i <= (UINT)SCENE_TYPE::STAGE_08; i++)
	{
		m_arrClear[i] = false;
	}
	
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TITLE];
	// 현재 씬 지정
	m_pCurScene->Enter();
}

void SceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}


void SceneManager::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void SceneManager::SetClear(SCENE_TYPE _eType, bool _b)
{
	m_arrClear[(UINT)_eType] = _b;
	((Stage*)m_arrScene[(UINT)_eType])->SetClear(true);
}

void SceneManager::Reset()
{
	for (UINT i = (UINT)SCENE_TYPE::STAGE_01; i <= (UINT)SCENE_TYPE::STAGE_08; i++)
	{
		m_arrClear[i] = false;
	}
}

void SceneManager::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	m_pCurScene->Enter();
}