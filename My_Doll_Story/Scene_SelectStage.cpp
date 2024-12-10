#include "pch.h"
#include "Scene_SelectStage.h"

#include "Main.h"

#include "ButtonUI.h"

#include "Texture.h"
#include "ResManager.h"

#include "Background.h"
#include "SceneManager.h"
#include "InputManager.h"

void SelectToMenu(DWORD_PTR, DWORD_PTR);
void SelectToStage1(DWORD_PTR, DWORD_PTR);
void SelectToStage2(DWORD_PTR, DWORD_PTR);
void SelectToStage3(DWORD_PTR, DWORD_PTR);
void SelectToStage4(DWORD_PTR, DWORD_PTR);
void NextStage(DWORD_PTR, DWORD_PTR);
void StageReset(DWORD_PTR _arrButton, DWORD_PTR);

Scene_SelectStage::Scene_SelectStage()
	:m_pBack(nullptr)
{

}

Scene_SelectStage::~Scene_SelectStage()
{

}

void Scene_SelectStage::Enter()
{
	m_ppArrButton = m_arrButton;

	MakeUI();
	if (SceneManager::GetInst()->IsClear(SCENE_TYPE::STAGE_01))
	{
		m_arrButton[0]->SetClear(true);
		m_arrButton[1]->SetOn(true);
		m_arrButton[1]->SetActivate(true);
	}
	if (SceneManager::GetInst()->IsClear(SCENE_TYPE::STAGE_02))
	{
		m_arrButton[1]->SetClear(true);
		m_arrButton[2]->SetOn(true);
		m_arrButton[2]->SetActivate(true);
	}
	if (SceneManager::GetInst()->IsClear(SCENE_TYPE::STAGE_03))
	{
		m_arrButton[2]->SetClear(true);
		m_arrButton[3]->SetOn(true);
		m_arrButton[3]->SetActivate(true);
	}
	if (SceneManager::GetInst()->IsClear(SCENE_TYPE::STAGE_04))
	{
		m_arrButton[3]->SetClear(true);
	}
}

void Scene_SelectStage::Exit()
{
	DeleteAll();
}

void Scene_SelectStage::MakeUI()
{
	m_vResolution = Main::GetInst()->GetResolution();

	// 배경 띄우기
	m_pBack = new Background;
	m_pBack->SetTexture(ResManager::GetInst()->LoadTexture(L"Background_Select_1", L"texture\\스테이지 선택\\배경1.bmp"));
	m_pBack->SetScale(Vec2(1600, 900));
	m_pBack->SetCenterPos();
	AddObject(m_pBack, GROUP_TYPE::BACK);

	// 스테이지 선택버튼
	m_arrButton[0] = new ButtonUI;
	m_arrButton[0]->SetName(L"Stage 1");
	m_arrButton[0]->SetOn(true);
	m_arrButton[0]->SetActivate(true);
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage1_A", L"texture\\스테이지 선택\\버튼 UI\\스테이지1\\검은오리a.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage1_O", L"texture\\스테이지 선택\\버튼 UI\\스테이지1\\검은오리o.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage1_C", L"texture\\스테이지 선택\\버튼 UI\\스테이지1\\검은오리c.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage1_D", L"texture\\스테이지 선택\\버튼 UI\\스테이지1\\검은오리d.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage1_CA", L"texture\\스테이지 선택\\버튼 UI\\스테이지1\\검은오리ca.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage1_CO", L"texture\\스테이지 선택\\버튼 UI\\스테이지1\\검은오리co.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage1_CC", L"texture\\스테이지 선택\\버튼 UI\\스테이지1\\검은오리cc.bmp"));
	m_arrButton[0]->SetScale(Vec2((int)(m_arrButton[0]->GetVecTexture()[0]->Width() * 0.5f), (int)(m_arrButton[0]->GetVecTexture()[0]->Height() * 0.5f)));
	m_arrButton[0]->SetPos(Vec2(m_vResolution.x * 0.2f, m_vResolution.y * 0.3f));
	AddObject(m_arrButton[0], GROUP_TYPE::UI);

	m_arrButton[1] = new ButtonUI;
	m_arrButton[1]->SetName(L"Stage 2");
	m_arrButton[1]->SetOn(false);
	m_arrButton[1]->SetActivate(false);
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage2_A", L"texture\\스테이지 선택\\버튼 UI\\스테이지2\\코끼리a.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage2_O", L"texture\\스테이지 선택\\버튼 UI\\스테이지2\\코끼리o.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage2_C", L"texture\\스테이지 선택\\버튼 UI\\스테이지2\\코끼리c.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage2_D", L"texture\\스테이지 선택\\버튼 UI\\스테이지2\\코끼리d.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage2_CA", L"texture\\스테이지 선택\\버튼 UI\\스테이지2\\코끼리ca.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage2_CO", L"texture\\스테이지 선택\\버튼 UI\\스테이지2\\코끼리co.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage2_CC", L"texture\\스테이지 선택\\버튼 UI\\스테이지2\\코끼리cc.bmp"));
	m_arrButton[1]->SetScale(Vec2((int)(m_arrButton[1]->GetVecTexture()[0]->Width() * 0.5f), (int)(m_arrButton[1]->GetVecTexture()[0]->Height() * 0.5f)));
	m_arrButton[1]->SetPos(Vec2(m_vResolution.x * 0.4f, m_vResolution.y * 0.7f));
	AddObject(m_arrButton[1], GROUP_TYPE::UI);

	m_arrButton[2] = new ButtonUI;
	m_arrButton[2]->SetName(L"Stage 3");
	m_arrButton[2]->SetOn(false);
	m_arrButton[2]->SetActivate(false);
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage3_A", L"texture\\스테이지 선택\\버튼 UI\\스테이지3\\상어a.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage3_O", L"texture\\스테이지 선택\\버튼 UI\\스테이지3\\상어o.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage3_C", L"texture\\스테이지 선택\\버튼 UI\\스테이지3\\상어c.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage3_D", L"texture\\스테이지 선택\\버튼 UI\\스테이지3\\상어d.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage3_CA", L"texture\\스테이지 선택\\버튼 UI\\스테이지3\\상어ca.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage3_CO", L"texture\\스테이지 선택\\버튼 UI\\스테이지3\\상어co.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage3_CC", L"texture\\스테이지 선택\\버튼 UI\\스테이지3\\상어cc.bmp"));
	m_arrButton[2]->SetScale(Vec2((int)(m_arrButton[2]->GetVecTexture()[0]->Width() * 0.5f), (int)(m_arrButton[2]->GetVecTexture()[0]->Height() * 0.5f)));
	m_arrButton[2]->SetPos(Vec2(m_vResolution.x * 0.6f, m_vResolution.y * 0.3f));
	AddObject(m_arrButton[2], GROUP_TYPE::UI);

	m_arrButton[3] = new ButtonUI;
	m_arrButton[3]->SetName(L"Stage 4");
	m_arrButton[3]->SetOn(false);
	m_arrButton[3]->SetActivate(false);
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage4_A", L"texture\\스테이지 선택\\버튼 UI\\스테이지4\\오리a.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage4_O", L"texture\\스테이지 선택\\버튼 UI\\스테이지4\\오리o.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage4_C", L"texture\\스테이지 선택\\버튼 UI\\스테이지4\\오리c.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage4_D", L"texture\\스테이지 선택\\버튼 UI\\스테이지4\\오리d.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage4_CA", L"texture\\스테이지 선택\\버튼 UI\\스테이지4\\오리ca.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage4_CO", L"texture\\스테이지 선택\\버튼 UI\\스테이지4\\오리co.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage4_CC", L"texture\\스테이지 선택\\버튼 UI\\스테이지4\\오리cc.bmp"));
	m_arrButton[3]->SetScale(Vec2((int)(m_arrButton[3]->GetVecTexture()[0]->Width() * 0.5f), (int)(m_arrButton[3]->GetVecTexture()[0]->Height() * 0.5f)));
	m_arrButton[3]->SetPos(Vec2(m_vResolution.x * 0.8f, m_vResolution.y * 0.7f));
	AddObject(m_arrButton[3], GROUP_TYPE::UI);

	// 홈, 설정버튼
	ButtonUI* pButtonHome = new ButtonUI;
	pButtonHome->SetName(L"Home");
	pButtonHome->SetActivate(true);
	pButtonHome->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectHome_A", L"texture\\공통 UI\\홈a.bmp"));
	pButtonHome->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectHome_O", L"texture\\공통 UI\\홈o.bmp"));
	pButtonHome->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectHome_C", L"texture\\공통 UI\\홈c.bmp"));
	pButtonHome->SetScale(Vec2((int)(pButtonHome->GetVecTexture()[0]->Width() * 0.25f), (int)(pButtonHome->GetVecTexture()[0]->Height() * 0.25f)));
	pButtonHome->SetPos(Vec2(m_vResolution.x * 0.05f, m_vResolution.y * 0.07f));
	AddObject(pButtonHome, GROUP_TYPE::UI);

	ButtonUI* pButtonStageReset = new ButtonUI;
	pButtonStageReset->SetName(L"StageReset");
	pButtonStageReset->SetActivate(true);
	pButtonStageReset->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageReset_A", L"texture\\공통 UI\\초기화a.bmp"));
	pButtonStageReset->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageReset_O", L"texture\\공통 UI\\초기화o.bmp"));
	pButtonStageReset->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageReset_C", L"texture\\공통 UI\\초기화c.bmp"));
	pButtonStageReset->SetScale(Vec2((int)(pButtonStageReset->GetVecTexture()[0]->Width() * 0.25f), (int)(pButtonStageReset->GetVecTexture()[0]->Height() * 0.25f)));
	pButtonStageReset->SetPos(Vec2(m_vResolution.x * 0.95f, m_vResolution.y * 0.07f));
	AddObject(pButtonStageReset, GROUP_TYPE::UI);

	pButtonStageReset->SetClickedCallBack(StageReset, (DWORD_PTR)&m_ppArrButton, 0);

	// 다음으로 넘어가기
	ButtonUI* pButtonNextStage = new ButtonUI;
	pButtonNextStage->SetName(L"NextR Stage");
	pButtonNextStage->SetActivate(true);
	pButtonNextStage->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageR_A", L"texture\\스테이지 선택\\버튼 UI\\화살표_오른쪽a.bmp"));
	pButtonNextStage->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageR_O", L"texture\\스테이지 선택\\버튼 UI\\화살표_오른쪽o.bmp"));
	pButtonNextStage->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageR_C", L"texture\\스테이지 선택\\버튼 UI\\화살표_오른쪽c.bmp"));
	pButtonNextStage->SetScale(Vec2((int)(pButtonNextStage->GetVecTexture()[0]->Width() * 0.35f), (int)(pButtonNextStage->GetVecTexture()[0]->Height() * 0.35f)));
	pButtonNextStage->SetPos(Vec2(m_vResolution.x * 0.95f, m_vResolution.y * 0.905f));
	AddObject(pButtonNextStage, GROUP_TYPE::UI);

	// 버튼 클릭 옵션
	pButtonHome->SetClickedCallBack(SelectToMenu, 0, 0);
	m_arrButton[0]->SetClickedCallBack(SelectToStage1, 0, 0);
	m_arrButton[1]->SetClickedCallBack(SelectToStage2, 0, 0);
	m_arrButton[2]->SetClickedCallBack(SelectToStage3, 0, 0);
	m_arrButton[3]->SetClickedCallBack(SelectToStage4, 0, 0);
	pButtonNextStage->SetClickedCallBack(NextStage, 0, 0);

}

void Scene_SelectStage::update()
{
	Scene::update();

#ifdef DEV_MODE
	if (InputManager::GetInst()->GetKeyState(KEY::F1) == KEY_STATE::TAP)
	{
		static bool bToggle = false;
		bToggle = !bToggle;

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_01, true);
		m_arrButton[0]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_02, true);
		m_arrButton[1]->SetActivate(bToggle);
		m_arrButton[1]->SetOn(bToggle);
		m_arrButton[1]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_03, true);
		m_arrButton[2]->SetActivate(bToggle);
		m_arrButton[2]->SetOn(bToggle);
		m_arrButton[2]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_04, true);
		m_arrButton[3]->SetActivate(bToggle);
		m_arrButton[3]->SetOn(bToggle);
		m_arrButton[3]->SetClear(bToggle);
	}
	if (InputManager::GetInst()->GetKeyState(KEY::F2) == KEY_STATE::TAP)
	{
		static bool bToggle = false;
		bToggle = !bToggle;

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_02, false);
		m_arrButton[0]->SetActivate(true);
		m_arrButton[0]->SetOn(true);
		m_arrButton[0]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_02, false);
		m_arrButton[1]->SetActivate(true);
		m_arrButton[1]->SetOn(true);
		m_arrButton[1]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_02, false);
		m_arrButton[2]->SetActivate(true);
		m_arrButton[2]->SetOn(true);
		m_arrButton[2]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_02, false);
		m_arrButton[3]->SetActivate(true);
		m_arrButton[3]->SetOn(true);
		m_arrButton[3]->SetClear(bToggle);
	}
#endif
}

void Scene_SelectStage::finalupdate()
{
	Scene::finalupdate();
}

void Scene_SelectStage::render(HDC _dc)
{
	Scene::render(_dc);
}

void SelectToMenu(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::MENU);
}

void SelectToStage1(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::STAGE_01);
}

void SelectToStage2(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::STAGE_02);
}

void SelectToStage3(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::STAGE_03);
}

void SelectToStage4(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::STAGE_04);
}

void StageReset(DWORD_PTR _arrButton, DWORD_PTR)
{
	SceneManager::GetInst()->Reset();
	ButtonUI*** _ppButton = ((ButtonUI***)(_arrButton));
	ButtonUI** _pButton = *_ppButton;

	for (int i = 1; i < 4; i++)
	{
		_pButton[i]->SetOn(false);
		_pButton[i]->SetActivate(false);
	}
}

void NextStage(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::SELECT_STAGE2);
}
