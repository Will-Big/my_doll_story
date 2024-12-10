#include "pch.h"
#include "UI.h"

//#include "Camera.h"
#include "InputManager.h"

#include "SelectGDI.h"

UI::UI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_vFinalPos{}
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bIsOn(true)
{
}

UI::UI(const UI& _origin)
	: Object(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); i++)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

UI::~UI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void UI::SetOn(bool _b)
{
	m_bIsOn = _b;

	for (auto child : m_vecChildUI)
	{
		child->SetOn(_b);
	}
}

void UI::update()
{
	update_child();
}

void UI::finalupdate()
{
	Object::finalupdate();

	// UI �� ���� ��ǥ�� ���Ѵ�.
	m_vFinalPos = GetPos();

	if (GetParent() != nullptr)
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos = m_vFinalPos + vParentPos;
	}

	//UI Mouse üũ
	MouseOnCheck();

	finalupdate_child();
}

void UI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		//vPos = Camera::GetInst()->GetRenderPos(vPos);
	}

	render_child(_dc);
}

void UI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->update();
	}
}

void UI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void UI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void UI::MouseOnCheck()
{
	if (!m_bIsOn)
		return;

	Vec2 vMousePos = InputManager::GetInst()->GetMousePos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		//vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vFinalPos.x - vScale.x / 2.f <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x / 2.f
		&& m_vFinalPos.y - vScale.y / 2.f<= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y / 2.f)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void UI::MouseOnAction()
{
}

void UI::MouseLbtnDownAction()
{
}

void UI::MouseLbtnUpAction()
{
}

void UI::MouseLbtnClickedAction()
{
	// �̰� �� �Լ� ���������� �ߴ��� �ɸ� ������..?
}



// 53 �� 16�� 20�� ī�޶� ���� �ذ�
// ���κ��� üũ