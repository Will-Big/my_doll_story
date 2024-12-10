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
	UI* GetTargetedUI(UI* _pParentUI); // 부모 UI 내에서 실제로 타겟팅 된 UI 를 찾아서 반환
	UI* GetFocusedUI();

public:
	void SetFocusedUI(UI* _pUI);

private:
	UIManager();
	~UIManager();
};

