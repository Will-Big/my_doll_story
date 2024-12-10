#include "pch.h"
#include "Scene_Title.h"

#include "Main.h"

#include "Object.h"
#include "UI.h"
#include "ButtonUI.h"
#include "PanelUI.h"

#include "InputManager.h"
#include "ResManager.h"

#include "Texture.h"
#include "Background.h"


Scene_Title::Scene_Title()
	: m_pBack(nullptr)
{
}

Scene_Title::~Scene_Title()
{
}

void Scene_Title::Enter()
{
	m_vResolution = Main::GetInst()->GetResolution();

	ButtonUI* pButtonUI = new ButtonUI;
	pButtonUI->SetName(L"Start Button");
	pButtonUI->GetVecTexture().push_back((ResManager::GetInst()->LoadTexture(L"Button_PressAnyKeyToStart", L"texture\\타이틀\\버튼 UI\\스페이스바.bmp")));
	pButtonUI->SetScale(Vec2((int)(pButtonUI->GetVecTexture()[0]->Width()), (int)(pButtonUI->GetVecTexture()[0]->Height())));
	pButtonUI->SetActivate(true);
	pButtonUI->SetPos(Vec2(m_vResolution.x * 0.5f, m_vResolution.y * 0.8f));
	pButtonUI->SetClickedCallBack(ToMenu, 0, 0);

	m_pBack = new Background;
	m_pBack->SetTexture(ResManager::GetInst()->LoadTexture(L"Title", L"texture\\타이틀\\배경.bmp"));
	m_pBack->SetScale(Vec2(m_vResolution.x, m_vResolution.y));
	m_pBack->SetCenterPos();

	AddObject(m_pBack, GROUP_TYPE::BACK);
	AddObject(pButtonUI, GROUP_TYPE::UI);
}

void Scene_Title::Exit()
{
	DeleteAll();
}

void Scene_Title::update()
{
	Scene::update();

	if (InputManager::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		ChangeScene(SCENE_TYPE::MENU);
	}
}

void Scene_Title::finalupdate()
{
	Scene::finalupdate();
}

void Scene_Title::render(HDC _dc)
{
	Scene::render(_dc);
}


