#pragma once

#include "Singleton.h"

class Object;

struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR	lParam;   // DWORD_PTR ���� ������ �÷����� ���� ����Ʈ���� ������Ű�� ����
	DWORD_PTR	wParam;   // ���� ��� �÷����� ���� �����ʹ� 4byte �� 8byte�� �� �ֱ� ����
};

class EventManager : public Singleton<EventManager>
{
	friend class Singleton<EventManager>;

private:
	vector<tEvent> m_vecEvent;
	vector<Object*> m_vecDead;

public:
	void update();

private:
	void Excute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }


private:
	EventManager();
	~EventManager();
};

