#include "pch.h"
#include "Scene_Main.h"

#include "Object.h"
#include "Player.h"
#include "Map.h"
#include "CollisonManager.h"
#include "InputManager.h"

#include "Block.h"

#include "GameManager.h"

#include "Item.h"

#include "Doll.h"
#include "Cotton.h"
#include "Scissors.h"
#include "Tape.h"

// UI 관련 추가
#include "Main.h"
#include "Background.h"
#include "ResManager.h"
#include "ButtonUI.h"
#include "Texture.h"

Scene_Main::Scene_Main()
	: m_pBack(nullptr)
{

}

Scene_Main::~Scene_Main()
{

}

void Scene_Main::update()
{
	Scene::update();

	if (InputManager::GetInst()->GetKeyState(KEY::ENTER) == KEY_STATE::TAP)
	{
		ChangeScene(SCENE_TYPE::STAGE_01);
	}
}

void Scene_Main::Enter()
{
	m_pPlayer = new Player;
	m_pMap = new Map;

	MapIndex sPIndex = { 3,3 };
	MapIndex startIndex;
	m_pMap->init(m_pPlayer, 9, 7, sPIndex, startIndex);



	GameManager::GetInst()->SetInfo(m_pPlayer, m_pMap);

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			AddObject(m_pMap->m_vecMap[i][j], GROUP_TYPE::BLOCK);
		}
	}

	// =================== Item 생성 코드
	MakeItem(ITEM_TYPE::COTTON, 4, 5);
	MakeItem(ITEM_TYPE::COTTON, 2, 5);
	MakeItem(ITEM_TYPE::SCISSORS, 5, 5);
	MakeItem(ITEM_TYPE::DOLL, 6, 5);
	MakeItem(ITEM_TYPE::TAPE, 7, 5);
	// =================== Wall 생성 코드

	m_pMap->SetWall(startIndex.x + 3, startIndex.y + 1, POS::DOWN);
	m_pMap->SetWall(startIndex.x + 3, startIndex.y + 1, POS::RIGHT);
	
	//ribbon
	m_pMap->SetRibbon(startIndex.x + 2, startIndex.y+1, POS::DOWN);
	m_pMap->SetRibbon(startIndex.x + 2, startIndex.y + 1, POS::RIGHT);

	//찢어진 종이 확인
	m_pMap->MakeTornOnOff(5, 4);

	m_pPlayer->SetPos(IndexToVec(sPIndex));
	m_pPlayer->SetScale(Vec2(110.f, 110.f));

	AddObject(m_pMap, GROUP_TYPE::BACK);
	AddObject(m_pPlayer, GROUP_TYPE::PLAYER);
	CollisonManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);

}


void Scene_Main::Exit()
{
	DeleteAll();
	CollisonManager::GetInst()->Reset();
}

void Scene_Main::MakeItem(ITEM_TYPE _eType, int _x, int _y)
{
	Item* pItem = nullptr;

	switch (_eType)
	{
	case ITEM_TYPE::DOLL:
		pItem = new Doll(SCENE_TYPE::STAGE_08);
		break;
	case ITEM_TYPE::SCISSORS:
		pItem = new Scissors(_x, _y);
		break;
	case ITEM_TYPE::COTTON:
		pItem = new Cotton(_x, _y);
		break;
	case ITEM_TYPE::TAPE:
		pItem = new Tape();
		break;
	case ITEM_TYPE::BUTTON:
		break;
	default:
		pItem = new Item();
		break;
	}

	m_pMap->SetItem(pItem, _x, _y);
}

void Scene_Main::render(HDC _dc)
{
	Scene::render(_dc);
}

void Scene_Main::MakeUI()
{
	// 배경 띄우기
	m_pBack = new Background;
	m_pBack->SetTexture(ResManager::GetInst()->LoadTexture(L"Stage_Background", L"texture\\Stage Scene\\stagebackground24.bmp"));
	m_pBack->SetScale(Vec2(1600, 900));
	m_pBack->SetCenterPos();
	AddObject(m_pBack, GROUP_TYPE::BACK);

	// 버튼 띄우기
	m_vResolution = Main::GetInst()->GetResolution();

	ButtonUI* pButtonMenuPopup = new ButtonUI;
	pButtonMenuPopup->SetName(L"Stage Menu Pop-up");
	pButtonMenuPopup->SetTexture(ResManager::GetInst()->LoadTexture(L"Stage_MenuPopup", L"texture\\Stage Scene\\stagemenu24_idle.bmp"));
	pButtonMenuPopup->SetScale(Vec2((int)(pButtonMenuPopup->GetTexture()->Width() * 0.25f), (int)(pButtonMenuPopup->GetTexture()->Height() * 0.25f)));
	pButtonMenuPopup->SetPos(Vec2(m_vResolution.x * 0.05f, m_vResolution.y * 0.07f));
	AddObject(pButtonMenuPopup, GROUP_TYPE::UI);

	ButtonUI* pButtonOptions = new ButtonUI;
	pButtonOptions->SetName(L"Stage Options");
	pButtonOptions->SetTexture(ResManager::GetInst()->LoadTexture(L"Stage_Options", L"texture\\Stage Scene\\stagesettings24_idle.bmp"));
	pButtonOptions->SetScale(Vec2((int)(pButtonOptions->GetTexture()->Width() * 0.25f), (int)(pButtonOptions->GetTexture()->Height() * 0.25f)));
	pButtonOptions->SetPos(Vec2(m_vResolution.x * 0.95f, m_vResolution.y * 0.07f));
	AddObject(pButtonOptions, GROUP_TYPE::UI);

	ButtonUI* pButtonReset = new ButtonUI;
	pButtonReset->SetName(L"Stage Reset");
	pButtonReset->SetTexture(ResManager::GetInst()->LoadTexture(L"Stage_Reset", L"texture\\Stage Scene\\reset24_idle.bmp"));
	pButtonReset->SetScale(Vec2((int)(pButtonReset->GetTexture()->Width() * 0.38f), (int)(pButtonReset->GetTexture()->Height() * 0.38f)));
	pButtonReset->SetPos(Vec2(m_vResolution.x * 0.1f, m_vResolution.y * 0.3f));
	AddObject(pButtonReset, GROUP_TYPE::UI);
}
