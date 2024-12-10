#include "pch.h"
#include "InputManager.h"

#include "Main.h"

int g_arrKey[(UINT)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP, 
	VK_DOWN,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	VK_LBUTTON,
	VK_LCONTROL,
	'Z',
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
};

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
}

void InputManager::init()
{
	//vertor size �����ֱ�
	m_vecKey.resize((UINT)KEY::LAST);
	//Ű �ʱ�ȭ
	for (int i = 0; i <(UINT)KEY::LAST; i++)
	{
		m_vecKey[i].eState = KEY_STATE::NONE;
		m_vecKey[i].bPrevPush = false;
	}
}

void InputManager::update()
{
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i = 0; i < (UINT)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrKey[i]) & 0x8000)				
			{
				if (m_vecKey[i].bPrevPush)                          //������ Ű�� �����־��ٸ� ��� �����ִ� ����
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;			
				}
				else
				{													
					m_vecKey[i].eState = KEY_STATE::TAP;			//������ Ű�� ���������ʾҾ��������� ���� ����
					m_vecKey[i].bPrevPush = true;					//Ű ���¸� true
				}
			}
			else													
			{
				if (m_vecKey[i].bPrevPush)							 
				{
  					m_vecKey[i].eState = KEY_STATE::AWAY;			//������ Ű�� �����־��� ������ ������ �ʾҴٸ� Ű�� �� ����
					m_vecKey[i].bPrevPush = false;					//Ű ���¸� false
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;			//�������� ������ �ʾҰ� ���絵 ������ ���� ����
				}
			}
		}

		m_vMousePos = UpdateMouse();
	}
	// ������ ��Ŀ�� ���� ����
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}

Vec2 InputManager::UpdateMouse()
{
	static POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(Main::GetInst()->GetMainHwnd(), &mousePos);

	return Vec2(mousePos);
}
