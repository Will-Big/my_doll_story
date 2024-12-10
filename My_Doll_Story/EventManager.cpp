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
	// 이전 프레임에서 등록해둔 Dead Object 들을 삭제한다.
	// ===============================================
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}

	m_vecDead.clear();

	// =========
	// Event 처리
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

		// Object 를 Dead 상태로 변경
		// 삭제 예정 오브젝트를 모아둔다.
		Object* pDeadObj = (Object*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;

	case EVENT_TYPE::SCENE_CHANGE:
		// lParm : Next Scecne Type
		SceneManager::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		// 포커 UI 해제 (이전 Scene 의 UI를 가르키고 있기 떄문)
		UIManager::GetInst()->SetFocusedUI(nullptr);
		break;
	}
}