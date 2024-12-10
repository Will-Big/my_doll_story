#pragma once

#include "Singleton.h"

class TimeManager : public Singleton<TimeManager> {
	friend class Singleton<TimeManager>;

private:
	LARGE_INTEGER m_CurCount;
	LARGE_INTEGER m_PrevCount;
	LARGE_INTEGER m_Frequency;

	double m_DeltaTime;			// 프레임 간의 시간 값
	double m_dAcc;				// 1초 체크를 위한 누적 시간
	UINT m_iCallCount;			// 함수 호출 횟수
	UINT m_iFPS;				// 초당 호출 횟수

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_DeltaTime; }
	float GetfDT() { return (float)m_DeltaTime; }

private:
	TimeManager();
	~TimeManager();
};