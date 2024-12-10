#pragma once

#include "Singleton.h"

class TimeManager : public Singleton<TimeManager> {
	friend class Singleton<TimeManager>;

private:
	LARGE_INTEGER m_CurCount;
	LARGE_INTEGER m_PrevCount;
	LARGE_INTEGER m_Frequency;

	double m_DeltaTime;			// ������ ���� �ð� ��
	double m_dAcc;				// 1�� üũ�� ���� ���� �ð�
	UINT m_iCallCount;			// �Լ� ȣ�� Ƚ��
	UINT m_iFPS;				// �ʴ� ȣ�� Ƚ��

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