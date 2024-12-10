#include "pch.h"
#include "TimeManager.h"
#include "Main.h"


TimeManager::TimeManager()
	: m_CurCount{}
	, m_PrevCount{}
	, m_Frequency{}
	, m_DeltaTime(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iFPS(0)
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_PrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_Frequency);
}

void TimeManager::update()
{
	QueryPerformanceCounter(&m_CurCount);
	m_DeltaTime = (double)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (double)m_Frequency.QuadPart;
	m_PrevCount = m_CurCount;

	// 디버그를 위한 m_DeltaTime 최대값 보정
//#ifdef _DEBUG
//	if (m_DeltaTime > 1.f / 60.f)
//		m_DeltaTime = 1.f / 60.f;
//#endif
}

void TimeManager::render()
{
	++m_iCallCount;
	m_dAcc += m_DeltaTime;

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"나의 인형 이야기");
		SetWindowText(Main::GetInst()->GetMainHwnd(), szBuffer);
	}
}