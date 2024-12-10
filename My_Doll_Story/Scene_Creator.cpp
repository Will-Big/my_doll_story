#include "pch.h"
#include "Scene_Creator.h"

#include "Main.h"

#include "InputManager.h"
#include "ResManager.h"

#include "ButtonUI.h"
#include "Background.h"
#include "Texture.h"


void Scene_Creator::Enter()
{
	m_vResolution = Main::GetInst()->GetResolution();
	ButtonUI* pButtonHome = new ButtonUI;
	pButtonHome->SetName(L"Home");
	pButtonHome->SetActivate(true);
	pButtonHome->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectHome_A", L"texture\\공통 UI\\홈a.bmp"));
	pButtonHome->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectHome_O", L"texture\\공통 UI\\홈o.bmp"));
	pButtonHome->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectHome_C", L"texture\\공통 UI\\홈c.bmp"));
	pButtonHome->SetScale(Vec2((int)(pButtonHome->GetVecTexture()[0]->Width() * 0.25f), (int)(pButtonHome->GetVecTexture()[0]->Height() * 0.25f)));
	pButtonHome->SetPos(Vec2(m_vResolution.x * 0.05f, m_vResolution.y * 0.07f));
	AddObject(pButtonHome, GROUP_TYPE::UI);
	pButtonHome->SetClickedCallBack(ToMenu, 0, 0);

	m_pBack = new Background;
	m_pBack->SetTexture(ResManager::GetInst()->LoadTexture(L"Help", L"texture\\메인 메뉴\\제작자.bmp"));
	m_pBack->SetScale(Vec2(1600, 900));
	m_pBack->SetCenterPos();
	AddObject(m_pBack, GROUP_TYPE::BACK);
}

void Scene_Creator::Exit()
{
	DeleteAll();
}

void Scene_Creator::update()
{
	Scene::update();

	if (InputManager::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		ChangeScene(SCENE_TYPE::MENU);
	}
}

void Scene_Creator::finalupdate()
{
	Scene::finalupdate();
}

void Scene_Creator::render(HDC _dc)
{
	Scene::render(_dc);
}

Scene_Creator::Scene_Creator()
{
}

Scene_Creator::~Scene_Creator()
{
}

