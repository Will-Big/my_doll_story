#include "pch.h"
#include "UIManager.h"

#include "SceneManager.h"
#include "Scene.h"
#include "UI.h"

#include "InputManager.h"


void UIManager::update()
{
	//// 1. FocusedUI 확인
	//m_pFocusedUI = GetFocusedUI();

	//if (m_pFocusedUI == nullptr)
	//	return;

	//// 2. FocusedUI  내에서, 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI 를 가져온다
	//UI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	Scene* pCurScene = SceneManager::GetInst()->GetCurScene();
	vector<Object*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = InputManager::GetInst()->GetKeyState(KEY::LBTN) == KEY_STATE::TAP;
	bool bLbtnAway = InputManager::GetInst()->GetKeyState(KEY::LBTN) == KEY_STATE::AWAY;

	for(size_t i = 0; i < vecUI.size(); i++)
	{
		UI* pTargetUI = (UI*)vecUI[i];
		pTargetUI = GetTargetedUI(pTargetUI);

		if (pTargetUI != nullptr)
		{
			if (!pTargetUI->GetOn())
				continue;

			pTargetUI->MouseOnAction();

			if (bLbtnTap)
			{
				pTargetUI->MouseLbtnDownAction();
				pTargetUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{
				pTargetUI->MouseLbtnUpAction();

				if (pTargetUI->m_bLbtnDown)
				{
					pTargetUI->MouseLbtnClickedAction();
				}

				// 왼쪽 버튼을 떼면, 눌렸던 체크를 다시 해제한다.
				pTargetUI->m_bLbtnDown = false;
			}
		}
	}
}


UI* UIManager::GetTargetedUI(UI* _pParentUI)
{
	bool bLbtnAway = InputManager::GetInst()->GetKeyState(KEY::LBTN) == KEY_STATE::AWAY;

	UI* pTargetUI = nullptr;

	// 부모 UI 포함, 모든 자식들을 검사한다.
	static list<UI*> queue;
	static vector<UI*> vecNoneTarget;

	// 정적 변수이므로 사용시마다 clear
	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		UI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI 가 TargetUI 인지 확인
		// 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{
			if (pTargetUI != nullptr)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<UI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}

		// 왼쪽 버튼을 떼면, 눌렸던 체크를 다시 해제한다.
		if (bLbtnAway)
		{
			for (size_t i = 0; i < vecNoneTarget.size(); i++)
			{
				vecNoneTarget[i]->m_bLbtnDown = false;
			}
		}
	}



	return pTargetUI;
}

UI* UIManager::GetFocusedUI()
{
	Scene* pCurScene = SceneManager::GetInst()->GetCurScene();
	vector<Object*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = InputManager::GetInst()->GetKeyState(KEY::LBTN) == KEY_STATE::TAP;

	// 기존 포커싱 UI 를 받아두고 변경되었는지 확인한다.
	UI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// 왼쪽버튼 TAP 이 발생했다는 전제
	vector<Object*>::iterator targetIter = vecUI.end();
	vector<Object*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		if (((UI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	// 이번에 Focus 된 UI 가 없다
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	pFocusedUI = (UI*)*targetIter;

	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

void UIManager::SetFocusedUI(UI* _pUI)
{
	// 이미 포커싱 중인 경우 or 포커싱 해제 요청인 경우
	if (m_pFocusedUI == _pUI || _pUI == nullptr)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	Scene* pCurScene = SceneManager::GetInst()->GetCurScene();
	vector<Object*>& vecUI = pCurScene->GetUIGroup();

	// 왼쪽버튼 TAP 이 발생했다는 전제
	vector<Object*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

UIManager::UIManager()
	: m_pFocusedUI(nullptr)
{

}

UIManager::~UIManager()
{

}