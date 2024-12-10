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
	m_pTex = ResManager::GetInst()->LoadTexture(L"MenuPanel", L"texture\\��������\\�г� UI\\��â.bmp");
	m_BackButton = new ButtonUI;

	m_BackButton->SetName(L"Back");
	m_BackButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Back_A", L"texture\\��������\\�г� UI\\���ư���a.bmp"));
	m_BackButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Back_O", L"texture\\��������\\�г� UI\\���ư���o.bmp"));
	m_BackButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Back_C", L"texture\\��������\\�г� UI\\���ư���c.bmp"));
	m_BackButton->SetScale(Vec2(300.f, 97.f));
	m_BackButton->SetPos(Vec2(0.f, -150.f));

	this->AddChild(m_BackButton);

	m_SelectButton = new ButtonUI;

	m_SelectButton->SetName(L"SelectButton");
	m_SelectButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Select_A", L"texture\\��������\\�г� UI\\��������a.bmp"));
	m_SelectButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Select_O", L"texture\\��������\\�г� UI\\��������o.bmp"));
	m_SelectButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Select_C", L"texture\\��������\\�г� UI\\��������c.bmp"));
	m_SelectButton->SetScale(Vec2(300.f, 97.f));
	m_SelectButton->SetPos(Vec2(0.f, 0.f));

	this->AddChild(m_SelectButton);

	m_TitleButton = new ButtonUI;

	m_TitleButton->SetName(L"Title");
	m_TitleButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Title_A", L"texture\\��������\\�г� UI\\ó������a.bmp"));
	m_TitleButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Title_O", L"texture\\��������\\�г� UI\\ó������o.bmp"));
	m_TitleButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"Title_C", L"texture\\��������\\�г� UI\\ó������c.bmp"));
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

		TransparentBlt(_dc							//���� float���� �۾��ϱ� ������ int���� ����ȯ�� �ʿ���
			, (int)(vPos.x - GetScale().x / 2.f)
			, (int)(vPos.y - GetScale().y / 2.f)
			, (int)GetScale().x		//���α���
			, (int)GetScale().y		//���α���
			, m_pTex->GetDC()
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, m_pTex->Width()	//�ڸ� ������
			, m_pTex->Height()	//�ڸ� ������
			, RGB(255, 255, 255));					//����ȭ�� ����

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
