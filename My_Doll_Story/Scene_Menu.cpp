#include "pch.h"
#include "Scene_Menu.h"

#include "Main.h"

#include "ButtonUI.h"
#include "GameEndPanel.h"

#include "Texture.h"
#include "ResManager.h"

#include "Background.h"

void MenuToSelect(DWORD_PTR, DWORD_PTR);
void MenuToExit(DWORD_PTR, DWORD_PTR);
void NOButtonClicked(DWORD_PTR, DWORD_PTR);
void YESButtonClicked(DWORD_PTR, DWORD_PTR);
void MenuToCredit(DWORD_PTR, DWORD_PTR);
void MenuToHelp(DWORD_PTR, DWORD_PTR);

Scene_Menu::Scene_Menu()
	: m_pBack(nullptr)
{

}

Scene_Menu::~Scene_Menu()
{

}

void Scene_Menu::Enter()
{
	MakeUI();
}

void Scene_Menu::Exit()
{
	DeleteAll();
}

void Scene_Menu::MakeUI()
{
	// 배경 띄우기
	m_pBack = new Background;
	m_pBack->SetTexture(ResManager::GetInst()->LoadTexture(L"Background_Menu", L"texture\\메인 메뉴\\배경.bmp"));
	m_pBack->SetScale(Vec2(1600, 900));
	m_pBack->SetCenterPos();
	AddObject(m_pBack, GROUP_TYPE::BACK);

	// 버튼 띄우기
	m_vResolution = Main::GetInst()->GetResolution();

	float height_firstbutton = 0.515f;
	float height_lastbutton = 0.85f;
	float height_interval = (height_lastbutton - height_firstbutton) / 3.f;

	ButtonUI* pButtonStart = new ButtonUI;
	pButtonStart->SetName(L"Game Start");
	pButtonStart->SetActivate(true);
	pButtonStart->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"GameStart_A", L"texture\\메인 메뉴\\버튼 UI\\게임시작a.bmp"));
	pButtonStart->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"GameStart_O", L"texture\\메인 메뉴\\버튼 UI\\게임시작o.bmp"));
	pButtonStart->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"GameStart_C", L"texture\\메인 메뉴\\버튼 UI\\게임시작c.bmp"));
	pButtonStart->SetScale(Vec2((int)(pButtonStart->GetVecTexture()[0]->Width() * 0.45f), (int)(pButtonStart->GetVecTexture()[0]->Height() * 0.45f)));
	pButtonStart->SetPos(Vec2(m_vResolution.x * 0.5f, m_vResolution.y * height_firstbutton));
	AddObject(pButtonStart, GROUP_TYPE::UI);

	ButtonUI* pButtonHelp = new ButtonUI;
	pButtonHelp->SetName(L"Help");
	pButtonHelp->SetActivate(true);
	pButtonHelp->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Help_A", L"texture\\메인 메뉴\\버튼 UI\\게임설명a.bmp"));
	pButtonHelp->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Help_O", L"texture\\메인 메뉴\\버튼 UI\\게임설명o.bmp"));
	pButtonHelp->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Help_C", L"texture\\메인 메뉴\\버튼 UI\\게임설명c.bmp"));
	pButtonHelp->SetScale(Vec2((int)(pButtonHelp->GetVecTexture()[0]->Width() * 0.45f), (int)(pButtonHelp->GetVecTexture()[0]->Height() * 0.45f)));
	pButtonHelp->SetPos(Vec2(m_vResolution.x * 0.5f, m_vResolution.y * (height_firstbutton + height_interval)));
	AddObject(pButtonHelp, GROUP_TYPE::UI);

	ButtonUI* pButtonCredit = new ButtonUI;
	pButtonCredit->SetName(L"Credits");
	pButtonCredit->SetActivate(true);
	pButtonCredit->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"MenuCredits_A", L"texture\\메인 메뉴\\버튼 UI\\제작자a.bmp"));
	pButtonCredit->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"MenuCredits_O", L"texture\\메인 메뉴\\버튼 UI\\제작자o.bmp"));
	pButtonCredit->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"MenuCredits_C", L"texture\\메인 메뉴\\버튼 UI\\제작자c.bmp"));
	pButtonCredit->SetScale(Vec2((int)(pButtonCredit->GetVecTexture()[0]->Width() * 0.45f), (int)(pButtonCredit->GetVecTexture()[0]->Height() * 0.45f)));
	pButtonCredit->SetPos(Vec2(m_vResolution.x * 0.5f, m_vResolution.y * (height_firstbutton + 2 * height_interval)));
	AddObject(pButtonCredit, GROUP_TYPE::UI);

	ButtonUI* pButtonExit = new ButtonUI;
	pButtonExit->SetName(L"Game Exit");
	pButtonExit->SetActivate(true);
	pButtonExit->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"MenuButton_ExitGame_A", L"texture\\메인 메뉴\\버튼 UI\\게임종료a.bmp"));
	pButtonExit->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"MenuButton_ExitGame_O", L"texture\\메인 메뉴\\버튼 UI\\게임종료o.bmp"));
	pButtonExit->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"MenuButton_ExitGame_C", L"texture\\메인 메뉴\\버튼 UI\\게임종료c.bmp"));
	pButtonExit->SetScale(Vec2((int)(pButtonExit->GetVecTexture()[0]->Width() * 0.45f), (int)(pButtonExit->GetVecTexture()[0]->Height() * 0.45f)));
	pButtonExit->SetPos(Vec2(m_vResolution.x * 0.5f, m_vResolution.y * height_lastbutton));
	AddObject(pButtonExit, GROUP_TYPE::UI);


	ButtonUI* pEnd = nullptr;
	ButtonUI* pContinue = nullptr;

	GameEndPanel* pGameEndPanel = new GameEndPanel(&pEnd, &pContinue);
	pGameEndPanel->SetName(L"GameEndPanel");
	pGameEndPanel->SetScale(Vec2(800.f, 530.f));
	pGameEndPanel->SetPos(Vec2(800.f, 450.f));

	pGameEndPanel->AddChild(pEnd);
	pGameEndPanel->AddChild(pContinue);
	pGameEndPanel->SetOn(false);

	AddObject(pGameEndPanel, GROUP_TYPE::UI);

	// 버튼 클릭 옵션
	pButtonStart->SetClickedCallBack(MenuToSelect, 0, 0);
	pButtonExit->SetClickedCallBack(MenuToExit,(DWORD_PTR)pGameEndPanel, 0);
	pButtonCredit->SetClickedCallBack(MenuToCredit, 0, 0);
	pButtonHelp->SetClickedCallBack(MenuToHelp, 0, 0);
	pEnd->SetClickedCallBack(YESButtonClicked,0, 0);
	pContinue->SetClickedCallBack(NOButtonClicked, (DWORD_PTR)pGameEndPanel, 0);
}

void Scene_Menu::update()
{
	Scene::update();
}

void Scene_Menu::finalupdate()
{
	Scene::finalupdate();
}

void Scene_Menu::render(HDC _dc)
{
	Scene::render(_dc);
}

void MenuToSelect(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::SELECT_STAGE);
}

void MenuToExit(DWORD_PTR _panel, DWORD_PTR)
{
	((GameEndPanel*)_panel)->SetOn(true);
}

void NOButtonClicked(DWORD_PTR _panel, DWORD_PTR)
{
	((GameEndPanel*)_panel)->SetOn(false);
}

void YESButtonClicked(DWORD_PTR, DWORD_PTR)
{
	DestroyWindow(Main::GetInst()->GetMainHwnd());
}

void MenuToCredit(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::CREATOR);
}

void MenuToHelp(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::HELP);
}
