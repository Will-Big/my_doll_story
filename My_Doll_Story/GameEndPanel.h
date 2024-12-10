#pragma once
#include "PanelUI.h"

class ButtonUI;


class GameEndPanel :
	public PanelUI
{
private:
	Vec2    m_vDragStart;

	ButtonUI* m_EndButton;
	ButtonUI* m_ContinueButton;

	Texture* m_pTex;

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

public:
	virtual void MouseOnAction() override;
	virtual void MouseLbtnDownAction() override;
	virtual void MouseLbtnUpAction() override;
	virtual void MouseLbtnClickedAction() override;

	GameEndPanel* Getinst() { return this; }



public:
	GameEndPanel(ButtonUI** _end, ButtonUI** _continue);
	~GameEndPanel();

};

