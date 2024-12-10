#include "pch.h"
#include "EventManager.h"

#include "Object.h"
#include "Scene.h"
#include "SceneManager.h"

#include "UIManager.h"

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void EventManager::update()
{
	// ===============================================
	// ���� �����ӿ��� ����ص� Dead Object ���� �����Ѵ�.
	// ===============================================
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}

	m_vecDead.clear();

	// =========
	// Event ó��
	// =========

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void EventManager::Excute(const tEvent& _eve)
{
	_eve.eEven;

	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParm  : Object Adress
		// wParam : Group Type
		Object* pNewObj = (Object*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		SceneManager::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Address
		// wParam : NULL

		// Object �� Dead ���·� ����
		// ���� ���� ������Ʈ�� ��Ƶд�.
		Object* pDeadObj = (Object*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;

	case EVENT_TYPE::SCENE_CHANGE:
		// lParm : Next Scecne Type
		SceneManager::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		// ��Ŀ UI ���� (���� Scene �� UI�� ����Ű�� �ֱ� ����)
		UIManager::GetInst()->SetFocusedUI(nullptr);
		break;
	}
}