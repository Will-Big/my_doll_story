#pragma once
#include "PanelUI.h"

class ClearPanel :
    public PanelUI
{
private:
	SCENE_TYPE m_SceneType; // ÇöÀç ¾À

	Vec2    m_vDragStart;
	ButtonUI* m_SelectButton;
	Texture* m_pTexClear;

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

public:
	virtual void MouseOnAction() override;
	virtual void MouseLbtnDownAction() override;
	virtual void MouseLbtnUpAction() override;
	virtual void MouseLbtnClickedAction() override;

	ClearPanel* Getinst() { return this; }



public:
	ClearPanel(SCENE_TYPE _scene);
	~ClearPanel();

};

