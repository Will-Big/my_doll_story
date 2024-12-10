#include "pch.h"
#include "GameEndPanel.h"

#include "ButtonUI.h"
#include "ResManager.h"

#include "Texture.h"

#include "Main.h"

#include "BlendManager.h"

GameEndPanel::GameEndPanel(ButtonUI** _end,ButtonUI** _continue)
{
	m_pTex=ResManager::GetInst()->LoadTexture(L"EndGame", L"texture\\메인 메뉴\\패널 UI\\종료창.bmp");

	 m_EndButton = new ButtonUI;
	*_end = m_EndButton;
	(*_end)->SetName(L"EndButton");
	//(*_end)->SetActivate(true);
	(*_end)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"EndButton_A", L"texture\\메인 메뉴\\패널 UI\\예a.bmp"));
	(*_end)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"EndButton_O", L"texture\\메인 메뉴\\패널 UI\\예o.bmp"));
	(*_end)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"EndButton_C", L"texture\\메인 메뉴\\패널 UI\\예c.bmp"));
	(*_end)->SetScale(Vec2(285.f,105.f));
	(*_end)->SetPos(Vec2(-185.f, 80.f));
	

	 m_ContinueButton = new ButtonUI;
	*_continue = m_ContinueButton;
	(*_continue)->SetName(L"ContinueButton");
	//(*_continue)->SetActivate(true);
	(*_continue)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"ContinueButton_A", L"texture\\메인 메뉴\\패널 UI\\아니오a.bmp"));
	(*_continue)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"ContinueButton_O", L"texture\\메인 메뉴\\패널 UI\\아니오o.bmp"));
	(*_continue)->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"ContinueButton_C", L"texture\\메인 메뉴\\패널 UI\\아니오c.bmp"));
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

