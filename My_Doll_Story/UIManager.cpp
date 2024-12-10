#include "pch.h"
#include "UIManager.h"

#include "SceneManager.h"
#include "Scene.h"
#include "UI.h"

#include "InputManager.h"


void UIManager::update()
{
	//// 1. FocusedUI Ȯ��
	//m_pFocusedUI = GetFocusedUI();

	//if (m_pFocusedUI == nullptr)
	//	return;

	//// 2. FocusedUI  ������, �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI �� �����´�
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

				// ���� ��ư�� ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
				pTargetUI->m_bLbtnDown = false;
			}
		}
	}
}


UI* UIManager::GetTargetedUI(UI* _pParentUI)
{
	bool bLbtnAway = InputManager::GetInst()->GetKeyState(KEY::LBTN) == KEY_STATE::AWAY;

	UI* pTargetUI = nullptr;

	// �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�.
	static list<UI*> queue;
	static vector<UI*> vecNoneTarget;

	// ���� �����̹Ƿ� ���ø��� clear
	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		UI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI �� TargetUI ���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
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

		// ���� ��ư�� ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
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

	// ���� ��Ŀ�� UI �� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	UI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// ���ʹ�ư TAP �� �߻��ߴٴ� ����
	vector<Object*>::iterator targetIter = vecUI.end();
	vector<Object*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		if (((UI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	// �̹��� Focus �� UI �� ����
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	pFocusedUI = (UI*)*targetIter;

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

void UIManager::SetFocusedUI(UI* _pUI)
{
	// �̹� ��Ŀ�� ���� ��� or ��Ŀ�� ���� ��û�� ���
	if (m_pFocusedUI == _pUI || _pUI == nullptr)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	Scene* pCurScene = SceneManager::GetInst()->GetCurScene();
	vector<Object*>& vecUI = pCurScene->GetUIGroup();

	// ���ʹ�ư TAP �� �߻��ߴٴ� ����
	vector<Object*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	// ���� ������ �� �ڷ� ���� ��ü
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