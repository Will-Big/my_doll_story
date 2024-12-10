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
	// 이미지 DC 생성, 이미지 비트맵 생성
	m_hBackgroundDC = CreateCompatibleDC(Main::GetInst()->GetBackDC());
	m_hBackgroundBitMap = CreateCompatibleBitmap(m_hBackgroundDC, 1600, 900);
	m_hBackgroundBitMap = (HBITMAP)LoadImage(NULL, L"..\\resource\\texture\\스테이지\\검은화면(배경).bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


	// 생성한 DC 를 비트맵 선택하기
	SelectObject(m_hBackgroundDC, m_hBackgroundBitMap);

	// 예외 처리

	if (m_hBackgroundBitMap == NULL)
	{
		MessageBox(Main::GetInst()->GetMainHwnd(), L"백그라운드 이미지 로드 실패", L"이미지 로드 실패", MB_OK);
	}
}

void BlendManager::FadeIn()
{
	// 효과 진행 계산	 
	m_fCurTime += fDT;
	m_fRatio = m_fCurTime / m_fEffectDuration;

	// 투명도 계산
	m_iAlphaImage = (int)(170 * m_fRatio);

	// 이미지 알파 블렌딩 설정
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


	// 블렌딩
	AlphaBlend(Main::GetInst()->GetBackDC(), 0, 0, 1600, 900, m_hBackgroundDC, 0, 0, 1600, 900, bfBackground);
}



void BlendManager::DisplayBackground()
{
	// 배경 알파 블렌딩 설정
	BLENDFUNCTION bfBackGround;
	bfBackGround.BlendOp = AC_SRC_OVER;
	bfBackGround.BlendFlags = 0;

	if (m_fCurTime == 0.f)
		bfBackGround.SourceConstantAlpha = 170.f;
	else
		bfBackGround.SourceConstantAlpha = m_iAlphaImage;

	bfBackGround.AlphaFormat = AC_SRC_ALPHA;


	// 배경 블렌딩
	AlphaBlend(Main::GetInst()->GetBackDC(), 0, 0, 1600, 900, m_hBackgroundDC, 0, 0, 1600, 900, bfBackGround);
}