#include "pch.h"
#include "PanelUI.h"

#include "InputManager.h"

PanelUI::PanelUI()
	: UI(false)
{
	SetOn(false);
}

PanelUI::~PanelUI()
{
}

void PanelUI::update()
{
}

void PanelUI::MouseOnAction()	
{
	if (IsLbtnDown())
	{
		Vec2 vDiff = InputManager::GetInst()->GetMousePos() - m_vDragStart;
		Vec2 vCurPos = GetPos();
		vCurPos = vCurPos + vDiff;
		SetPos(vCurPos);

		m_vDragStart = InputManager::GetInst()->GetMousePos();
	}
}

void PanelUI::MouseLbtnDownAction()
{
	m_vDragStart = InputManager::GetInst()->GetMousePos();
}

void PanelUI::MouseLbtnUpAction()
{
}

void PanelUI::MouseLbtnClickedAction()
{
}

