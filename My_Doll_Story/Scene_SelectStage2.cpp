#include "pch.h"
#include "Scene_SelectStage2.h"

#include "Main.h"

#include "ButtonUI.h"

#include "Texture.h"
#include "ResManager.h"

#include "Background.h"
#include "SceneManager.h"
#include "InputManager.h"

void Select2ToMenu(DWORD_PTR, DWORD_PTR);
void Select2ToStage5(DWORD_PTR, DWORD_PTR);
void Select2ToStage6(DWORD_PTR, DWORD_PTR);
void Select2ToStage7(DWORD_PTR, DWORD_PTR);
void Select2ToStage8(DWORD_PTR, DWORD_PTR);
void PrevStage(DWORD_PTR, DWORD_PTR);
void StageReset2(DWORD_PTR _arrButton, DWORD_PTR);

Scene_SelectStage2::Scene_SelectStage2()
	:m_pBack(nullptr)
{

}

Scene_SelectStage2::~Scene_SelectStage2()
{

}

void Scene_SelectStage2::Enter()
{
	m_ppArrButton = m_arrButton;

	MakeUI();
	if (SceneManager::GetInst()->IsClear(SCENE_TYPE::STAGE_04))
	{
		m_arrButton[0]->SetOn(true);
		m_arrButton[0]->SetActivate(true);
	}
	if (SceneManager::GetInst()->IsClear(SCENE_TYPE::STAGE_05))
	{
		m_arrButton[0]->SetClear(true);
		m_arrButton[1]->SetOn(true);
		m_arrButton[1]->SetActivate(true);
	}
	if (SceneManager::GetInst()->IsClear(SCENE_TYPE::STAGE_06))
	{
		m_arrButton[1]->SetClear(true);
		m_arrButton[2]->SetOn(true);
		m_arrButton[2]->SetActivate(true);
	}
	if (SceneManager::GetInst()->IsClear(SCENE_TYPE::STAGE_07))
	{
		m_arrButton[2]->SetClear(true);
		m_arrButton[3]->SetOn(true);
		m_arrButton[3]->SetActivate(true);
	}
	if (SceneManager::GetInst()->IsClear(SCENE_TYPE::STAGE_08))
	{
		m_arrButton[3]->SetClear(true);
	}
}

void Scene_SelectStage2::Exit()
{
	DeleteAll();
}

void Scene_SelectStage2::MakeUI()
{
	m_vResolution = Main::GetInst()->GetResolution();

	// 배경 띄우기
	m_pBack = new Background;
	m_pBack->SetTexture(ResManager::GetInst()->LoadTexture(L"Background_Select_2", L"texture\\스테이지 선택\\배경2.bmp"));
	m_pBack->SetScale(Vec2(1600, 900));
	m_pBack->SetCenterPos();
	AddObject(m_pBack, GROUP_TYPE::BACK);

	// 스테이지 선택버튼
	m_arrButton[0] = new ButtonUI;
	m_arrButton[0]->SetName(L"Stage 5");
	m_arrButton[0]->SetOn(false);
	m_arrButton[0]->SetActivate(false);
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage5_A", L"texture\\스테이지 선택\\버튼 UI\\스테이지5\\퍼런코끼리a.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage5_O", L"texture\\스테이지 선택\\버튼 UI\\스테이지5\\퍼런코끼리o.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage5_C", L"texture\\스테이지 선택\\버튼 UI\\스테이지5\\퍼런코끼리c.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage5_D", L"texture\\스테이지 선택\\버튼 UI\\스테이지5\\퍼런코끼리d.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage5_CA", L"texture\\스테이지 선택\\버튼 UI\\스테이지5\\퍼런코끼리ca.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage5_CO", L"texture\\스테이지 선택\\버튼 UI\\스테이지5\\퍼런코끼리co.bmp"));
	m_arrButton[0]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage5_CC", L"texture\\스테이지 선택\\버튼 UI\\스테이지5\\퍼런코끼리cc.bmp"));
	m_arrButton[0]->SetScale(Vec2((int)(m_arrButton[0]->GetVecTexture()[0]->Width() * 0.5f), (int)(m_arrButton[0]->GetVecTexture()[0]->Height() * 0.5f)));
	m_arrButton[0]->SetPos(Vec2(m_vResolution.x * 0.2f, m_vResolution.y * 0.3f));
	AddObject(m_arrButton[0], GROUP_TYPE::UI);

	m_arrButton[1] = new ButtonUI;
	m_arrButton[1]->SetName(L"Stage 6");
	m_arrButton[1]->SetOn(false);
	m_arrButton[1]->SetActivate(false);
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage6_A", L"texture\\스테이지 선택\\버튼 UI\\스테이지6\\곰a.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage6_O", L"texture\\스테이지 선택\\버튼 UI\\스테이지6\\곰o.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage6_C", L"texture\\스테이지 선택\\버튼 UI\\스테이지6\\곰c.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage6_D", L"texture\\스테이지 선택\\버튼 UI\\스테이지6\\곰d.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage6_CA", L"texture\\스테이지 선택\\버튼 UI\\스테이지6\\곰ca.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage6_CO", L"texture\\스테이지 선택\\버튼 UI\\스테이지6\\곰co.bmp"));
	m_arrButton[1]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage6_CC", L"texture\\스테이지 선택\\버튼 UI\\스테이지6\\곰cc.bmp"));
	m_arrButton[1]->SetScale(Vec2((int)(m_arrButton[1]->GetVecTexture()[0]->Width() * 0.5f), (int)(m_arrButton[1]->GetVecTexture()[0]->Height() * 0.5f)));
	m_arrButton[1]->SetPos(Vec2(m_vResolution.x * 0.4f, m_vResolution.y * 0.7f));
	AddObject(m_arrButton[1], GROUP_TYPE::UI);

	m_arrButton[2] = new ButtonUI;
	m_arrButton[2]->SetName(L"Stage 7");
	m_arrButton[2]->SetOn(false);
	m_arrButton[2]->SetActivate(false);
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage7_A", L"texture\\스테이지 선택\\버튼 UI\\스테이지7\\병아리a.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage7_O", L"texture\\스테이지 선택\\버튼 UI\\스테이지7\\병아리o.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage7_C", L"texture\\스테이지 선택\\버튼 UI\\스테이지7\\병아리c.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage7_D", L"texture\\스테이지 선택\\버튼 UI\\스테이지7\\병아리d.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage7_CA", L"texture\\스테이지 선택\\버튼 UI\\스테이지7\\병아리ca.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage7_CO", L"texture\\스테이지 선택\\버튼 UI\\스테이지7\\병아리co.bmp"));
	m_arrButton[2]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage7_CC", L"texture\\스테이지 선택\\버튼 UI\\스테이지7\\병아리cc.bmp"));
	m_arrButton[2]->SetScale(Vec2((int)(m_arrButton[2]->GetVecTexture()[0]->Width() * 0.5f), (int)(m_arrButton[2]->GetVecTexture()[0]->Height() * 0.5f)));
	m_arrButton[2]->SetPos(Vec2(m_vResolution.x * 0.6f, m_vResolution.y * 0.3f));
	AddObject(m_arrButton[2], GROUP_TYPE::UI);

	m_arrButton[3] = new ButtonUI;
	m_arrButton[3]->SetName(L"Stage 8");
	m_arrButton[3]->SetOn(false);
	m_arrButton[3]->SetActivate(false);
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage8_A", L"texture\\스테이지 선택\\버튼 UI\\스테이지8\\토끼a.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage8_O", L"texture\\스테이지 선택\\버튼 UI\\스테이지8\\토끼o.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage8_C", L"texture\\스테이지 선택\\버튼 UI\\스테이지8\\토끼c.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage8_D", L"texture\\스테이지 선택\\버튼 UI\\스테이지8\\토끼d.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage8_CA", L"texture\\스테이지 선택\\버튼 UI\\스테이지8\\토끼ca.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage8_CO", L"texture\\스테이지 선택\\버튼 UI\\스테이지8\\토끼co.bmp"));
	m_arrButton[3]->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Stage8_CC", L"texture\\스테이지 선택\\버튼 UI\\스테이지8\\토끼cc.bmp"));
	m_arrButton[3]->SetScale(Vec2((int)(m_arrButton[3]->GetVecTexture()[0]->Width() * 0.5f), (int)(m_arrButton[3]->GetVecTexture()[0]->Height() * 0.5f)));
	m_arrButton[3]->SetPos(Vec2(m_vResolution.x * 0.8f, m_vResolution.y * 0.7f));
	AddObject(m_arrButton[3], GROUP_TYPE::UI);

	// 홈, 설정버튼
	ButtonUI* pButtonHome = new ButtonUI;
	pButtonHome->SetName(L"Home");
	pButtonHome->SetActivate(true);
	pButtonHome->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectHome_A", L"texture\\공통 UI\\홈a.bmp"));
	pButtonHome->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectHome_O", L"texture\\공통 UI\\홈a.bmp"));
	pButtonHome->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectHome_C", L"texture\\공통 UI\\홈a.bmp"));
	pButtonHome->SetScale(Vec2((int)(pButtonHome->GetVecTexture()[0]->Width() * 0.25f), (int)(pButtonHome->GetVecTexture()[0]->Height() * 0.25f)));
	pButtonHome->SetPos(Vec2(m_vResolution.x * 0.05f, m_vResolution.y * 0.07f));
	AddObject(pButtonHome, GROUP_TYPE::UI);

	// 이전으로 돌아가기
	ButtonUI* pButtonNextStage = new ButtonUI;
	pButtonNextStage->SetName(L"NextL Stage");
	pButtonNextStage->SetActivate(true);
	pButtonNextStage->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageL_A", L"texture\\스테이지 선택\\버튼 UI\\화살표_왼쪽a.bmp"));
	pButtonNextStage->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageL_O", L"texture\\스테이지 선택\\버튼 UI\\화살표_왼쪽o.bmp"));
	pButtonNextStage->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageL_C", L"texture\\스테이지 선택\\버튼 UI\\화살표_왼쪽c.bmp"));
	pButtonNextStage->SetScale(Vec2((int)(pButtonNextStage->GetVecTexture()[0]->Width() * 0.35f), (int)(pButtonNextStage->GetVecTexture()[0]->Height() * 0.35f)));
	pButtonNextStage->SetPos(Vec2(m_vResolution.x * 0.05f, m_vResolution.y * 0.905f));

	AddObject(pButtonNextStage, GROUP_TYPE::UI);

	ButtonUI* pButtonStageReset = new ButtonUI;
	pButtonStageReset->SetName(L"StageReset");
	pButtonStageReset->SetActivate(true);
	pButtonStageReset->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageReset_A", L"texture\\공통 UI\\초기화a.bmp"));
	pButtonStageReset->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageReset_O", L"texture\\공통 UI\\초기화o.bmp"));
	pButtonStageReset->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"StageReset_C", L"texture\\공통 UI\\초기화c.bmp"));
	pButtonStageReset->SetScale(Vec2((int)(pButtonStageReset->GetVecTexture()[0]->Width() * 0.25f), (int)(pButtonStageReset->GetVecTexture()[0]->Height() * 0.25f)));
	pButtonStageReset->SetPos(Vec2(m_vResolution.x * 0.95f, m_vResolution.y * 0.07f));
	AddObject(pButtonStageReset, GROUP_TYPE::UI);

	pButtonStageReset->SetClickedCallBack(StageReset2, (DWORD_PTR)&m_ppArrButton, 0);

	 //버튼 클릭 옵션
	pButtonHome->SetClickedCallBack(Select2ToMenu, 0, 0);
	m_arrButton[0]->SetClickedCallBack(Select2ToStage5, 0, 0);
	m_arrButton[1]->SetClickedCallBack(Select2ToStage6, 0, 0);
	m_arrButton[2]->SetClickedCallBack(Select2ToStage7, 0, 0);
	m_arrButton[3]->SetClickedCallBack(Select2ToStage8, 0, 0);
	pButtonNextStage->SetClickedCallBack(PrevStage, 0, 0);
}

void Scene_SelectStage2::update()
{
	Scene::update();

#ifdef DEV_MODE
	if (InputManager::GetInst()->GetKeyState(KEY::F1) == KEY_STATE::TAP)
	{
		static bool bToggle = false;
		bToggle = !bToggle;

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_04, true);
		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_05, true);
		m_arrButton[0]->SetActivate(bToggle);
		m_arrButton[0]->SetOn(bToggle);
		m_arrButton[0]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_06, true);
		m_arrButton[1]->SetActivate(bToggle);
		m_arrButton[1]->SetOn(bToggle);
		m_arrButton[1]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_07, true);
		m_arrButton[2]->SetActivate(bToggle);
		m_arrButton[2]->SetOn(bToggle);
		m_arrButton[2]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_08, true);
		m_arrButton[3]->SetActivate(bToggle);
		m_arrButton[3]->SetOn(bToggle);
		m_arrButton[3]->SetClear(bToggle);
	}
	if (InputManager::GetInst()->GetKeyState(KEY::F2) == KEY_STATE::TAP)
	{
		static bool bToggle = false;
		bToggle = !bToggle;

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_05, false);
		m_arrButton[0]->SetActivate(true);
		m_arrButton[0]->SetOn(true);
		m_arrButton[0]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_06, false);
		m_arrButton[1]->SetActivate(true);
		m_arrButton[1]->SetOn(true);
		m_arrButton[1]->SetClear(bToggle);

		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_07, false);
		m_arrButton[2]->SetActivate(true);
		m_arrButton[2]->SetOn(true);
		m_arrButton[2]->SetClear(bToggle);
		
		SceneManager::GetInst()->SetArrayClear(SCENE_TYPE::STAGE_08, false);
		m_arrButton[3]->SetActivate(true);
		m_arrButton[3]->SetOn(true);
		m_arrButton[3]->SetClear(bToggle);
	}
#endif
}

void Scene_SelectStage2::finalupdate()
{
	Scene::finalupdate();
}

void Scene_SelectStage2::render(HDC _dc)
{
	Scene::render(_dc);
}

void Select2ToMenu(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::MENU);
}

void Select2ToStage5(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::STAGE_05);
}

void Select2ToStage6(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::STAGE_06);
}

void Select2ToStage7(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::STAGE_07);
}

void Select2ToStage8(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::STAGE_08);
}

void PrevStage(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::SELECT_STAGE);
}

void StageReset2(DWORD_PTR _arrButton, DWORD_PTR)
{
	SceneManager::GetInst()->Reset();
	ButtonUI*** _ppButton = ((ButtonUI***)(_arrButton));
	ButtonUI** _pButton = *_ppButton;

	for (int i = 0; i < 4; i++)
	{
		_pButton[i]->SetOn(false);
		_pButton[i]->SetActivate(false);
	}
}