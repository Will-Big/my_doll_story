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
	//vertor size 정해주기
	m_vecKey.resize((UINT)KEY::LAST);
	//키 초기화
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
				if (m_vecKey[i].bPrevPush)                          //이전에 키가 눌려있었다면 계속 눌려있는 상태
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;			
				}
				else
				{													
					m_vecKey[i].eState = KEY_STATE::TAP;			//이전에 키가 눌려있지않았었고지금은 눌린 상태
					m_vecKey[i].bPrevPush = true;					//키 상태를 true
				}
			}
			else													
			{
				if (m_vecKey[i].bPrevPush)							 
				{
  					m_vecKey[i].eState = KEY_STATE::AWAY;			//이전에 키가 눌려있었고 지금은 눌리지 않았다면 키를 뗀 상태
					m_vecKey[i].bPrevPush = false;					//키 상태를 false
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;			//이전에도 눌리지 않았고 현재도 눌리지 않은 상태
				}
			}
		}

		m_vMousePos = UpdateMouse();
	}
	// 윈도우 포커싱 해제 상태
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
