#include "pch.h"
#include "ButtonUI.h"

#include "Texture.h"
#include "SoundManager.h"

ButtonUI::ButtonUI()
	: UI(false)
	, m_bActivate(false)
	, m_bClear(false)
	, m_pFunc(nullptr)
{
}

ButtonUI::~ButtonUI()
{
}

void ButtonUI::render(HDC _dc)
{
	if (m_bActivate && GetOn()) // Ȱ��ȭ ���� 0�� �ε���	
	{
		if (!m_bClear) // �̿Ϸ� ���¶��
		{
			if (m_bMouseOn or m_vecTex.size() == 1) // ���콺�� �ö� ���� ���
			{
				Trans(_dc, 0);
				m_bMouseOn = false;
			}
			else if (m_bMouseDown) // ���콺�� ���� ���� ���
			{
				Trans(_dc, 1);
				m_bMouseDown = false;
			}
			else // ���콺�� Ŭ���� ���� ���
			{
				Trans(_dc, 2);
				m_bMouseClicked = false;
			}
		}
		else // �Ϸ� ���¶��
		{
			if (m_bMouseOn or m_vecTex.size() == 1) // ���콺�� �ö� ���� ���
			{
				Trans(_dc, 4);
				m_bMouseOn = false;
			}
			else if (m_bMouseDown) // ���콺�� ���� ���� ���
			{
				Trans(_dc, 5);
				m_bMouseDown = false;
			}
			else // ���콺�� Ŭ���� ���� ���
			{
				Trans(_dc, 6);
				m_bMouseClicked = false;
			}
		}
	}
	else if(!m_bActivate) // ��Ȱ��ȭ ����
	{
		if (m_vecTex.size() != 7)
		{
			assert(false);
			return;
		}
		else
		{
			Trans(_dc, 3);
		}
	}
}

void ButtonUI::Trans(HDC _dc, int _index)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();


	if (GetParent() != nullptr)
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		vPos = vPos + vParentPos;
	}

	TransparentBlt(_dc,
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vScale.x),
		int(vScale.y),
		m_vecTex[_index]->GetDC(),
		0,
		0,
		m_vecTex[_index]->Width(),
		m_vecTex[_index]->Height(),
		RGB(255, 255, 255)
	);
}

void ButtonUI::MouseOnAction()
{
	m_bMouseOn = true;
}

void ButtonUI::MouseLbtnDownAction()
{
	m_bMouseDown = true;
}

void ButtonUI::MouseLbtnUpAction()
{
	m_bMouseClicked = true;
}

void ButtonUI::MouseLbtnClickedAction()
{
	SoundManager::GetInst()->PlaySound(SOUND::E_BUTTON, CHANNEL::EFFECT);
	if (m_pFunc != nullptr)
	{
		m_pFunc(m_param1, m_param2);
	}
}

