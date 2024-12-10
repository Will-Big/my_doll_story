#include "pch.h"
#include "MenuPanel.h"

#include "ButtonUI.h"
#include "ResManager.h"
#include "Texture.h"

#include "BlendManager.h"

void BackButtonClicked(DWORD_PTR _panel, DWORD_PTR);
void SelectBtnClicked(DWORD_PTR, DWORD_PTR);
void TitleBtnClicked(DWORD_PTR, DWORD_PTR);
MenuPanel::MenuPanel()
{
	m_pTex = ResManager::GetInst()->LoadTexture(L"MenuPanel", L"texture\\스테이지\\패널 UI\\빈창.bmp");
	m_BackButton = new ButtonUI;

	m_BackButton->SetName(L"Back");
	m_BackButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Back_A", L"texture\\스테이지\\패널 UI\\돌아가기a.bmp"));
	m_BackButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Back_O", L"texture\\스테이지\\패널 UI\\돌아가기o.bmp"));
	m_BackButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Back_C", L"texture\\스테이지\\패널 UI\\돌아가기c.bmp"));
	m_BackButton->SetScale(Vec2(300.f, 97.f));
	m_BackButton->SetPos(Vec2(0.f, -150.f));

	this->AddChild(m_BackButton);

	m_SelectButton = new ButtonUI;

	m_SelectButton->SetName(L"SelectButton");
	m_SelectButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Select_A", L"texture\\스테이지\\패널 UI\\인형선택a.bmp"));
	m_SelectButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Select_O", L"texture\\스테이지\\패널 UI\\인형선택o.bmp"));
	m_SelectButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Select_C", L"texture\\스테이지\\패널 UI\\인형선택c.bmp"));
	m_SelectButton->SetScale(Vec2(300.f, 97.f));
	m_SelectButton->SetPos(Vec2(0.f, 0.f));

	this->AddChild(m_SelectButton);

	m_TitleButton = new ButtonUI;

	m_TitleButton->SetName(L"Title");
	m_TitleButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Title_A", L"texture\\스테이지\\패널 UI\\처음으로a.bmp"));
	m_TitleButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Title_O", L"texture\\스테이지\\패널 UI\\처음으로o.bmp"));
	m_TitleButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Title_C", L"texture\\스테이지\\패널 UI\\처음으로c.bmp"));
	m_TitleButton->SetScale(Vec2(300.f, 97.f));
	m_TitleButton->SetPos(Vec2(0.f, 150.f));
	
	this->AddChild(m_TitleButton);

	m_BackButton->SetClickedCallBack(BackButtonClicked, (DWORD_PTR)this, 0);
	m_SelectButton->SetClickedCallBack(SelectBtnClicked, (DWORD_PTR)this, 0);
	m_TitleButton->SetClickedCallBack(TitleBtnClicked, (DWORD_PTR)this, 0);

	this->SetOn(false);
}

MenuPanel::~MenuPanel()
{

}

void MenuPanel::update()
{

}

void MenuPanel::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();
	if (GetOn())
	{
		BlendManager::GetInst()->DisplayBackground();

		TransparentBlt(_dc							//전부 float으로 작업하기 때문에 int로의 형변환이 필요함
			, (int)(vPos.x - GetScale().x / 2.f)
			, (int)(vPos.y - GetScale().y / 2.f)
			, (int)GetScale().x		//가로길이
			, (int)GetScale().y		//세로길이
			, m_pTex->GetDC()
			, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
			, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
			, m_pTex->Width()	//자를 사이즈
			, m_pTex->Height()	//자를 사이즈
			, RGB(255, 255, 255));					//투명화할 색깔

		m_BackButton->SetActivate(true);
		m_SelectButton->SetActivate(true);
		m_TitleButton->SetActivate(true);

		PanelUI::render(_dc);
	}
}

void MenuPanel::MouseOnAction()
{

}

void MenuPanel::MouseLbtnDownAction()
{

}

void MenuPanel::MouseLbtnUpAction()
{

}

void MenuPanel::MouseLbtnClickedAction()
{

}

void BackButtonClicked(DWORD_PTR _panel, DWORD_PTR)
{
	((MenuPanel*)_panel)->SetOn(false);
}

void SelectBtnClicked(DWORD_PTR _panel, DWORD_PTR)
{
	((MenuPanel*)_panel)->SetOn(false);
	ChangeScene(SCENE_TYPE::SELECT_STAGE);
}

void TitleBtnClicked(DWORD_PTR _panel, DWORD_PTR)
{
	((MenuPanel*)_panel)->SetOn(false);
	ChangeScene(SCENE_TYPE::TITLE);
}
