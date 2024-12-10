#pragma once
#include "PanelUI.h"


class MenuPanel :
    public PanelUI
{
private:
	Vec2    m_vDragStart;
	Texture* m_pTex;
	ButtonUI* m_BackButton;
	ButtonUI* m_SelectButton;
	ButtonUI* m_TitleButton;

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

public:
	virtual void MouseOnAction() override;
	virtual void MouseLbtnDownAction() override;
	virtual void MouseLbtnUpAction() override;
	virtual void MouseLbtnClickedAction() override;

public:
	MenuPanel();
    ~MenuPanel();
};

