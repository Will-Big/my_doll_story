#include "pch.h"
#include "Stage_03.h"

#include "Player.h"
#include "Map.h"

#include "GameManager.h"
#include "Block.h"

#include "Main.h"
#include "Background.h"
#include "ResManager.h"
#include "ButtonUI.h"
#include "Texture.h"
#include "MenuPanel.h"
#include "ClearPanel.h"
#include "SketchPanel.h"

#include "SceneManager.h"
#include "SoundManager.h"

void Stage3Reset(DWORD_PTR, DWORD_PTR);

Stage_03::Stage_03()
	: m_pBack(nullptr)
{
	m_SceneType = SCENE_TYPE::STAGE_03;
}

Stage_03::~Stage_03()
{

}

void Stage_03::update()
{
	Scene::update();
	StageKeyInput();
}

void Stage_03::finalupdate()
{
	Scene::finalupdate();
}

void Stage_03::render(HDC _dc)
{
	Scene::render(_dc);
}

void Stage_03::Enter()
{
	MakeUI();

	MapIndex sPlayerIndex = { 4,3 };
	MapIndex startIndex;
	
	//map setting
	m_pPlayer = new Player;
	m_pMap = new Map;

	GameManager::GetInst()->SetInfo(m_pPlayer, m_pMap);
	m_pMap->init(m_pPlayer, 5, 4, sPlayerIndex, startIndex);

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			AddObject(m_pMap->m_vecMap[i][j], GROUP_TYPE::BLOCK);
		}
	}

	//item 
	MakeItem(ITEM_TYPE::SCISSORS, 4, 2);
	MakeItem(ITEM_TYPE::DOLL, 2, 4);
	MakeItem(ITEM_TYPE::DOLL, 6, 4);

	//wall
	m_pMap->SetWall(startIndex.x + 2, startIndex.y, POS::DOWN);
	m_pMap->SetWall(startIndex.x + 3, startIndex.y, POS::DOWN);
	m_pMap->SetWall(startIndex.x, startIndex.y + 1, POS::RIGHT);
	m_pMap->SetWall(startIndex.x + 1, startIndex.y + 1, POS::DOWN);
	m_pMap->SetWall(startIndex.x + 2, startIndex.y + 1, POS::DOWN);
	m_pMap->SetWall(startIndex.x + 3, startIndex.y + 1, POS::DOWN);
	m_pMap->SetWall(startIndex.x, startIndex.y + 2, POS::DOWN);
	m_pMap->SetWall(startIndex.x + 2, startIndex.y + 2, POS::RIGHT);
	m_pMap->SetWall(startIndex.x + 2, startIndex.y + 2, POS::DOWN);
	m_pMap->SetWall(startIndex.x + 3, startIndex.y + 2, POS::DOWN);

	//ribbon
	m_pMap->SetRibbon(startIndex.x + 4, startIndex.y + 3, POS::UP);

	//player setting
	m_pPlayer->SetPos(IndexToVec(sPlayerIndex));
	m_pPlayer->SetScale(Vec2(110.f, 110.f));

	//add obj
	AddObject(m_pMap, GROUP_TYPE::BACK);
	AddObject(m_pPlayer, GROUP_TYPE::PLAYER);
	
}

void Stage_03::Exit()
{
	DeleteAll();
}

void Stage_03::MakeUI() // 추가
{
	// 배경 띄우기
	m_pBack = new Background;
	m_pBack->SetTexture(ResManager::GetInst()->LoadTexture(L"Stage_Background", L"texture\\스테이지\\배경.bmp"));
	m_pBack->SetScale(Vec2(1600, 900));
	m_pBack->SetCenterPos();
	AddObject(m_pBack, GROUP_TYPE::BACK);

	// 버튼 띄우기
	m_vResolution = Main::GetInst()->GetResolution();

	ButtonUI* pButtonMenuPopup = new ButtonUI;
	pButtonMenuPopup->SetName(L"Stage Menu Pop-up");
	pButtonMenuPopup->SetActivate(true);
	pButtonMenuPopup->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageMenuPopup_A", L"texture\\스테이지\\버튼 UI\\메뉴a.bmp"));
	pButtonMenuPopup->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageMenyPopup_O", L"texture\\스테이지\\버튼 UI\\메뉴o.bmp"));
	pButtonMenuPopup->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageMenyPopup_C", L"texture\\스테이지\\버튼 UI\\메뉴c.bmp"));
	pButtonMenuPopup->SetScale(Vec2((int)(pButtonMenuPopup->GetVecTexture()[0]->Width() * 0.25f), (int)(pButtonMenuPopup->GetVecTexture()[0]->Height() * 0.25f)));
	pButtonMenuPopup->SetPos(Vec2(m_vResolution.x * 0.05f, m_vResolution.y * 0.07f));
	AddObject(pButtonMenuPopup, GROUP_TYPE::UI);

	ButtonUI* pButtonReset = new ButtonUI;
	pButtonReset->SetName(L"Stage Reset");
	pButtonReset->SetActivate(true);
	pButtonReset->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageReset1_A", L"texture\\스테이지\\버튼 UI\\리셋a.bmp"));
	pButtonReset->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageReset1_O", L"texture\\스테이지\\버튼 UI\\리셋o.bmp"));
	pButtonReset->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageReset1_C", L"texture\\스테이지\\버튼 UI\\리셋c.bmp"));
	pButtonReset->SetScale(Vec2((int)(pButtonReset->GetVecTexture()[0]->Width() * 0.38f), (int)(pButtonReset->GetVecTexture()[0]->Height() * 0.38f)));
	pButtonReset->SetPos(Vec2(m_vResolution.x * 0.1f, m_vResolution.y * 0.3f));
	AddObject(pButtonReset, GROUP_TYPE::UI);

	// Sketch
	m_pSketchPanel = new SketchPanel(m_SceneType);
	AddObject(m_pSketchPanel, GROUP_TYPE::UI);

	//Clear
	m_pClearPanel = new ClearPanel(this->m_SceneType);
	MakeClearPanel(m_pClearPanel);
	AddObject(m_pClearPanel, GROUP_TYPE::UI);
	m_pClearPanel->SetOn(false);
	
	// 패널 생성
	m_pMenuPanel = new MenuPanel();
	MakeMenuPanel(m_pMenuPanel);
	AddObject(m_pMenuPanel, GROUP_TYPE::UI);

	// 버튼 클릭 옵션
	pButtonMenuPopup->SetClickedCallBack(Menu, (DWORD_PTR)m_pMenuPanel, 0);
	pButtonReset->SetClickedCallBack(Stage3Reset, 0, 0);
}

void Stage3Reset(DWORD_PTR, DWORD_PTR)
{
	SoundManager::GetInst()->PlaySound(SOUND::E_RESET, CHANNEL::EFFECT);
	ChangeScene(SCENE_TYPE::STAGE_03);
}