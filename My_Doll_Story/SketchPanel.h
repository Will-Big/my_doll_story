#pragma once
#include "PanelUI.h"
class SketchPanel :
    public PanelUI
{
private:
	SCENE_TYPE m_SceneType; // ÇöÀç ¾À
	Texture* m_pTexSketch;

public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

public:
	virtual void MouseOnAction() override;
	virtual void MouseLbtnDownAction() override;
	virtual void MouseLbtnUpAction() override;
	virtual void MouseLbtnClickedAction() override;

	SketchPanel* Getinst() { return this; }



public:
	SketchPanel(SCENE_TYPE _scene);
	~SketchPanel();

};

