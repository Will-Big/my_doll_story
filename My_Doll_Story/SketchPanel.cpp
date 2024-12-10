#include "pch.h"
#include "SketchPanel.h"

#include "ButtonUI.h"
#include "ResManager.h"

#include "Texture.h"

#include "Main.h"

#include "SceneManager.h"



SketchPanel::SketchPanel(SCENE_TYPE _scene)
	: m_SceneType(_scene)
{
	switch (m_SceneType)
	{
	case SCENE_TYPE::STAGE_01:
		m_pTexSketch = ResManager::GetInst()->LoadTexture(L"SketchImage_1", L"texture\\스테이지\\스케치북\\검은오리.bmp");
		break;
	case SCENE_TYPE::STAGE_02:
		m_pTexSketch = ResManager::GetInst()->LoadTexture(L"SketchImage_2", L"texture\\스테이지\\스케치북\\코끼리.bmp");
		break;
	case SCENE_TYPE::STAGE_03:
		m_pTexSketch = ResManager::GetInst()->LoadTexture(L"SketchImage_3", L"texture\\스테이지\\스케치북\\상어.bmp");
		break;
	case SCENE_TYPE::STAGE_04:
		m_pTexSketch = ResManager::GetInst()->LoadTexture(L"SketchImage_4", L"texture\\스테이지\\스케치북\\오리.bmp");
		break;
	case SCENE_TYPE::STAGE_05:
		m_pTexSketch = ResManager::GetInst()->LoadTexture(L"SketchImage_5", L"texture\\스테이지\\스케치북\\퍼런코끼리.bmp");
		break;
	case SCENE_TYPE::STAGE_06:
		m_pTexSketch = ResManager::GetInst()->LoadTexture(L"SketchImage_6", L"texture\\스테이지\\스케치북\\곰.bmp");
		break;
	case SCENE_TYPE::STAGE_07:
		m_pTexSketch = ResManager::GetInst()->LoadTexture(L"SketchImage_7", L"texture\\스테이지\\스케치북\\병아리.bmp");
		break;
	case SCENE_TYPE::STAGE_08:
		m_pTexSketch = ResManager::GetInst()->LoadTexture(L"SketchImage_8", L"texture\\스테이지\\스케치북\\토끼.bmp");
		break;
	default:
		assert(false);
	}
}

SketchPanel::~SketchPanel()
{
}
void SketchPanel::update()
{
}

void SketchPanel::render(HDC _dc)
{
	Vec2 vResolution = Main::GetInst()->GetResolution();

	TransparentBlt(_dc,
		int(vResolution.x * 0.03f),
		int(vResolution.y * 0.41f),
		int(m_pTexSketch->Width() * 0.6f),
		int(m_pTexSketch->Height() * 0.6f),
		m_pTexSketch->GetDC(),
		0,
		0,
		int(m_pTexSketch->Width()),
		int(m_pTexSketch->Height()),
		RGB(255, 255, 255)
	);
}

void SketchPanel::MouseOnAction()
{
}

void SketchPanel::MouseLbtnDownAction()
{

}

void SketchPanel::MouseLbtnUpAction()
{
}

void SketchPanel::MouseLbtnClickedAction()
{
}

