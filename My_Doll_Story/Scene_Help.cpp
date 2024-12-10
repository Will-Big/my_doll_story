#include "pch.h"
#include "Scene_Help.h"

#include "Main.h"

#include "InputManager.h"
#include "ResManager.h"

#include "ButtonUI.h"
#include "Background.h"
#include "Texture.h"

void NextPage(DWORD_PTR _scene, DWORD_PTR);
void PrevPage(DWORD_PTR _scene, DWORD_PTR);
void HelpToMenu(DWORD_PTR, DWORD_PTR);

void Scene_Help::Enter()
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
	pButtonHome->SetClickedCallBack(HelpToMenu, (DWORD_PTR)this, 0);

	//백그라운드
	if (m_bNext)
	{
		m_pBack[1] = new Background;
		m_pBack[1]->SetTexture(ResManager::GetInst()->LoadTexture(L"key", L"texture\\메인 메뉴\\게임설명2.bmp"));
		m_pBack[1]->SetScale(Vec2(1600, 900));
		m_pBack[1]->SetCenterPos();
		AddObject(m_pBack[1], GROUP_TYPE::BACK);
	}
	else if (!m_bNext)
	{
		m_pBack[0] = new Background;
		m_pBack[0]->SetTexture(ResManager::GetInst()->LoadTexture(L"Item", L"texture\\메인 메뉴\\게임설명1.bmp"));
		m_pBack[0]->SetScale(Vec2(1600, 900));
		m_pBack[0]->SetCenterPos();
		AddObject(m_pBack[0], GROUP_TYPE::BACK);
	}
	//넘기는 버튼

	if (m_bNext)
	{
		ButtonUI* pButtonNext = new ButtonUI;
		pButtonNext->SetName(L"NextL Page");
		pButtonNext->SetActivate(true);
		pButtonNext->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageL_A", L"texture\\스테이지 선택\\버튼 UI\\화살표_왼쪽a.bmp"));
		pButtonNext->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageL_O", L"texture\\스테이지 선택\\버튼 UI\\화살표_왼쪽o.bmp"));
		pButtonNext->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageL_C", L"texture\\스테이지 선택\\버튼 UI\\화살표_왼쪽c.bmp"));
		pButtonNext->SetScale(Vec2((int)(pButtonNext->GetVecTexture()[0]->Width() * 0.4f), (int)(pButtonNext->GetVecTexture()[0]->Height() * 0.4f)));
		pButtonNext->SetPos(Vec2(150.f, 780.f));
		AddObject(pButtonNext, GROUP_TYPE::UI);
		pButtonNext->SetClickedCallBack(PrevPage, (DWORD_PTR)this, 0);
	}
	else 
	{
		ButtonUI* pButtonNext = new ButtonUI;
		pButtonNext->SetName(L"NextR Page");
		pButtonNext->SetActivate(true);
		pButtonNext->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageR_A", L"texture\\스테이지 선택\\버튼 UI\\화살표_오른쪽a.bmp"));
		pButtonNext->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageR_O", L"texture\\스테이지 선택\\버튼 UI\\화살표_오른쪽o.bmp"));
		pButtonNext->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"NextPageR_C", L"texture\\스테이지 선택\\버튼 UI\\화살표_오른쪽c.bmp"));
		pButtonNext->SetScale(Vec2((int)(pButtonNext->GetVecTexture()[0]->Width() * 0.4f), (int)(pButtonNext->GetVecTexture()[0]->Height() * 0.4f)));
		pButtonNext->SetPos(Vec2(1470.f,780.f));
		AddObject(pButtonNext, GROUP_TYPE::UI);
		pButtonNext->SetClickedCallBack(NextPage, (DWORD_PTR)this, 0);
	}
	
}

void Scene_Help::Exit()
{
	DeleteAll();
}

void Scene_Help::update()
{
	Scene::update();

	if (InputManager::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		m_bNext = true;
	}
}

void Scene_Help::finalupdate()
{
	Scene::finalupdate();
}

void Scene_Help::render(HDC _dc)
{
	
	Scene::render(_dc);
}

Scene_Help::Scene_Help()
	:m_bNext(false)
{
}

Scene_Help::~Scene_Help()
{
}

void NextPage(DWORD_PTR _scene, DWORD_PTR)
{
	((Scene_Help*)_scene)->m_bNext = true;
	ChangeScene(SCENE_TYPE::HELP);
}

void PrevPage(DWORD_PTR _scene, DWORD_PTR)
{
	((Scene_Help*)_scene)->m_bNext = false;
	ChangeScene(SCENE_TYPE::HELP);
}

void HelpToMenu(DWORD_PTR _scene, DWORD_PTR)
{
	((Scene_Help*)_scene)->m_bNext = false;
	ChangeScene(SCENE_TYPE::MENU);
}