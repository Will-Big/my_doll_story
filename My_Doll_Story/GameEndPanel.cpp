#include "pch.h"
#include "GameEndPanel.h"

#include "ButtonUI.h"
#include "ResManager.h"

#include "Texture.h"

#include "Main.h"

#include "BlendManager.h"

GameEndPanel::GameEndPanel(ButtonUI** _end,ButtonUI** _continue)
{
	m_pTex=ResManager::GetInst()->LoadTexture(L"EndGame", L"texture\\���� �޴�\\�г� UI\\����â.bmp");

	 m_EndButton = new ButtonUI;
	*_end = m_EndButton;
	(*_end)->SetName(L"EndButton");
	//(*_end)->SetActivate(true);
	(*_end)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"EndButton_A", L"texture\\���� �޴�\\�г� UI\\��a.bmp"));
	(*_end)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"EndButton_O", L"texture\\���� �޴�\\�г� UI\\��o.bmp"));
	(*_end)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"EndButton_C", L"texture\\���� �޴�\\�г� UI\\��c.bmp"));
	(*_end)->SetScale(Vec2(285.f,105.f));
	(*_end)->SetPos(Vec2(-185.f, 80.f));
	

	 m_ContinueButton = new ButtonUI;
	*_continue = m_ContinueButton;
	(*_continue)->SetName(L"ContinueButton");
	//(*_continue)->SetActivate(true);
	(*_continue)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"ContinueButton_A", L"texture\\���� �޴�\\�г� UI\\�ƴϿ�a.bmp"));
	(*_continue)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"ContinueButton_O", L"texture\\���� �޴�\\�г� UI\\�ƴϿ�o.bmp"));
	(*_continue)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"ContinueButton_C", L"texture\\���� �޴�\\�г� UI\\�ƴϿ�c.bmp"));
	(*_continue)->SetScale(Vec2(285.f, 105.f));
	(*_continue)->SetPos(Vec2(185.f, 80.f));
}

GameEndPanel::~GameEndPanel()
{
}
void GameEndPanel::update()
{
}

void GameEndPanel::render(HDC _dc)
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

		m_EndButton->SetActivate(true);
		m_ContinueButton->SetActivate(true);

		PanelUI::render(_dc);
	}
}

void GameEndPanel::MouseOnAction()
{
}

void GameEndPanel::MouseLbtnDownAction()
{

}

void GameEndPanel::MouseLbtnUpAction()
{
}

void GameEndPanel::MouseLbtnClickedAction()
{
}

