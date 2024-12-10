#pragma once
#include "Singleton.h"

class UI;

class UIManager : public Singleton<UIManager>
{
	friend class Singleton<UIManager>;

private:
	UI*		m_pFocusedUI;

public:
	void update();


private:
	UI* GetTargetedUI(UI* _pParentUI); // �θ� UI ������ ������ Ÿ���� �� UI �� ã�Ƽ� ��ȯ
	UI* GetFocusedUI();

public:
	void SetFocusedUI(UI* _pUI);

private:
	UIManager();
	~UIManager();
};

