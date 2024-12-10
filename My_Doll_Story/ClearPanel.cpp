#include "pch.h"
#include "ClearPanel.h"

#include "ButtonUI.h"
#include "ResManager.h"

#include "Texture.h"

#include "Main.h"

#include "SceneManager.h"

#include "BlendManager.h"


ClearPanel::ClearPanel(SCENE_TYPE _scene)
	: m_SceneType(_scene)
{
	m_SelectButton = new ButtonUI;
	m_SelectButton->SetName(L"SelectDoll");
	m_SelectButton->SetActivate(true);
	m_SelectButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectDoll_A", L"texture\\��������\\�г� UI\\��������a.bmp"));
	m_SelectButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectDoll_O", L"texture\\��������\\�г� UI\\��������o.bmp"));
	m_SelectButton->GetVecTexture().push_back(ResManager::GetInst()->LoadTexture(L"SelectDoll_C", L"texture\\��������\\�г� UI\\��������c.bmp"));
	m_SelectButton->SetScale(Vec2(300.f, 90.f));
	m_SelectButton->SetPos(Vec2(0.f, 250.f));

	if ((UINT)SCENE_TYPE::STAGE_05 > (UINT)_scene&& (UINT)SCENE_TYPE::SELECT_STAGE2 < (UINT)_scene)
	{
		m_SelectButton->SetClickedCallBack(ToSelect, (DWORD_PTR)this, 0);
	}
	else
		m_SelectButton->SetClickedCallBack(ToSelect2, (DWORD_PTR)this, 0);
	
	
	AddChild(m_SelectButton);

	switch (m_SceneType)
	{
	case SCENE_TYPE::STAGE_01:
		m_pTexClear = ResManager::GetInst()->LoadTexture(L"ClearImage_1", L"texture\\��������\\�ƾ�\\1.bmp");
		break;
	case SCENE_TYPE::STAGE_02:
		m_pTexClear = ResManager::GetInst()->LoadTexture(L"ClearImage_2", L"texture\\��������\\�ƾ�\\2.bmp");
		break;
	case SCENE_TYPE::STAGE_03:
		m_pTexClear = ResManager::GetInst()->LoadTexture(L"ClearImage_3", L"texture\\��������\\�ƾ�\\3.bmp");
		break;																		 
	case SCENE_TYPE::STAGE_04:														 
		m_pTexClear = ResManager::GetInst()->LoadTexture(L"ClearImage_4", L"texture\\��������\\�ƾ�\\4.bmp");
		break;
	case SCENE_TYPE::STAGE_05:
		m_pTexClear = ResManager::GetInst()->LoadTexture(L"ClearImage_5", L"texture\\��������\\�ƾ�\\5.bmp");
		break;
	case SCENE_TYPE::STAGE_06:
		m_pTexClear = ResManager::GetInst()->LoadTexture(L"ClearImage_6", L"texture\\��������\\�ƾ�\\6.bmp");
		break;
	case SCENE_TYPE::STAGE_07:
		m_pTexClear = ResManager::GetInst()->LoadTexture(L"ClearImage_7", L"texture\\��������\\�ƾ�\\7.bmp");
		break;
	case SCENE_TYPE::STAGE_08:
		m_pTexClear = ResManager::GetInst()->LoadTexture(L"ClearImage_8", L"texture\\��������\\�ƾ�\\8.bmp");
		break;
	default:
		assert(false);
	}
}

ClearPanel::~ClearPanel()
{
}
void ClearPanel::update()
{
}

void ClearPanel::render(HDC _dc)
{
	Vec2 vResolution = Main::GetInst()->GetResolution();

	if (GetOn())
	{
		if (BlendManager::GetInst()->m_bFadeIn)
		{
			BlendManager::GetInst()->FadeIn();
		}

		else
		{
			BlendManager::GetInst()->DisplayBackground();

			TransparentBlt(_dc,
				int((vResolution.x - m_pTexClear->Width()) / 2.f),
				int((vResolution.y - m_pTexClear->Height()) / 2.f),
				int(m_pTexClear->Width()),
				int(m_pTexClear->Height()),
				m_pTexClear->GetDC(),
				0,
				0,
				int(m_pTexClear->Width()),
				int(m_pTexClear->Height()),
				RGB(255, 255, 255));

			PanelUI::render(_dc);
		}
	}
	else
		BlendManager::GetInst()->SetFadeIn(true);
}

void ClearPanel::MouseOnAction()
{
}

void ClearPanel::MouseLbtnDownAction()
{

}

void ClearPanel::MouseLbtnUpAction()
{
}

void ClearPanel::MouseLbtnClickedAction()
{
}

