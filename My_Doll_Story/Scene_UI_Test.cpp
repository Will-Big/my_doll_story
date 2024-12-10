#include "pch.h"
#include "Scene_UI_Test.h"

#include "UIManager.h"
#include "UI.h"
#include "ButtonUI.h"
#include "PanelUI.h"
#include "GameEndPanel.h"

#include "Main.h"

#include "InputManager.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

Scene_UI_Test::Scene_UI_Test()
{
}

Scene_UI_Test::~Scene_UI_Test()
{
}

void Scene_UI_Test::Enter()
{
	Vec2 vResolution = Main::GetInst()->GetResolution();

	/*PanelUI* pPanelUI = new PanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(500.f, 300.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));*/

	ButtonUI* pEnd=nullptr;
	ButtonUI* pContinue=nullptr;

	GameEndPanel* pGameEndPanel = new GameEndPanel(&pEnd, &pContinue);
	pGameEndPanel->SetName(L"GameEndPanel");
	pGameEndPanel->SetScale(Vec2(800.f, 530.f));
	pGameEndPanel->SetPos(Vec2(800.f, 450.f));
	

	/*pButtonUI->SetName(L"ChildUI");
	pButtonUI->SetScale(Vec2(100.f, 40.f));
	pButtonUI->SetPos(Vec2(0.f, 0.f));
	pButtonUI->SetClickedCallBack(ChangeScene, 0, 0);*/

	//pPanelUI->AddChild(pButtonUI);

	pGameEndPanel->AddChild(pEnd);
	pGameEndPanel->AddChild(pContinue);
	AddObject(pGameEndPanel, GROUP_TYPE::UI);

	//AddObject(pGameEndPanel, GROUP_TYPE::UI);

	//UI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pPanelUI->GetPos() + Vec2(-300.f, 0.f));
	//AddObject(pClonePanel, GROUP_TYPE::UI);

	//m_pUI = pClonePanel;
}

void Scene_UI_Test::Exit()
{
	DeleteAll();
}

void Scene_UI_Test::update()
{
	Scene::update();

	if (InputManager::GetInst()->GetKeyState(KEY::ENTER) == KEY_STATE::TAP)
	{
		UIManager::GetInst()->SetFocusedUI(m_pUI);
	}
}

void Scene_UI_Test::finalupdate()
{
	Scene::finalupdate();
}

void Scene_UI_Test::render(HDC _dc)
{
	Scene::render(_dc);
}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::MAIN);
}

