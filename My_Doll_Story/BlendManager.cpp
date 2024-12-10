#include "pch.h"
#include "BlendManager.h"

#include "TimeManager.h"
#include "ResManager.h"

#include "Main.h"


BlendManager::BlendManager()
	: m_hBackgroundBitMap(nullptr)
	, m_hBackgroundDC(nullptr)
	, m_bFadeIn(true)
	, m_fEffectDuration(1.5f)
	, m_fCurTime(0.f)
	, m_fRatio(0.f)
	, m_iAlphaImage(0.f)
{

}

BlendManager::~BlendManager()
{

}

void BlendManager::init()
{
	// �̹��� DC ����, �̹��� ��Ʈ�� ����
	m_hBackgroundDC = CreateCompatibleDC(Main::GetInst()->GetBackDC());
	m_hBackgroundBitMap = CreateCompatibleBitmap(m_hBackgroundDC, 1600, 900);
	m_hBackgroundBitMap = (HBITMAP)LoadImage(NULL, L"..\\resource\\texture\\��������\\����ȭ��(���).bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


	// ������ DC �� ��Ʈ�� �����ϱ�
	SelectObject(m_hBackgroundDC, m_hBackgroundBitMap);

	// ���� ó��

	if (m_hBackgroundBitMap == NULL)
	{
		MessageBox(Main::GetInst()->GetMainHwnd(), L"��׶��� �̹��� �ε� ����", L"�̹��� �ε� ����", MB_OK);
	}
}

void BlendManager::FadeIn()
{
	// ȿ�� ���� ���	 
	m_fCurTime += fDT;
	m_fRatio = m_fCurTime / m_fEffectDuration;

	// ���� ���
	m_iAlphaImage = (int)(170 * m_fRatio);

	// �̹��� ���� ���� ����
	BLENDFUNCTION bfBackground;
	bfBackground.BlendOp = AC_SRC_OVER;
	bfBackground.BlendFlags = 0;
	bfBackground.SourceConstantAlpha = m_iAlphaImage;
	bfBackground.AlphaFormat = AC_SRC_ALPHA;

	if (m_fCurTime > m_fEffectDuration)
	{
		m_fCurTime = 0.f;
		m_fRatio = 0.f;
		m_bFadeIn = false;

		AlphaBlend(Main::GetInst()->GetBackDC(), 0, 0, 1600, 900, m_hBackgroundDC, 0, 0, 1600, 900, bfBackground);
		return;
	}


	// ����
	AlphaBlend(Main::GetInst()->GetBackDC(), 0, 0, 1600, 900, m_hBackgroundDC, 0, 0, 1600, 900, bfBackground);
}



void BlendManager::DisplayBackground()
{
	// ��� ���� ���� ����
	BLENDFUNCTION bfBackGround;
	bfBackGround.BlendOp = AC_SRC_OVER;
	bfBackGround.BlendFlags = 0;

	if (m_fCurTime == 0.f)
		bfBackGround.SourceConstantAlpha = 170.f;
	else
		bfBackGround.SourceConstantAlpha = m_iAlphaImage;

	bfBackGround.AlphaFormat = AC_SRC_ALPHA;


	// ��� ����
	AlphaBlend(Main::GetInst()->GetBackDC(), 0, 0, 1600, 900, m_hBackgroundDC, 0, 0, 1600, 900, bfBackGround);
}