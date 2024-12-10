#pragma once
#include "Singleton.h"

struct tKeyInfo
{
	KEY_STATE    eState;    // Ű�� ���� ��
	bool        bPrevPush; // ���� �����ӿ��� ���ȴ��� ����
};

class InputManager :public Singleton<InputManager>
{
	friend class Singleton<InputManager>;

private:
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vMousePos;

public:
	void init();
	void update();

private:
	Vec2 UpdateMouse();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
	Vec2 GetMousePos() { return m_vMousePos; }
	

private:
	InputManager();
	~InputManager();
};