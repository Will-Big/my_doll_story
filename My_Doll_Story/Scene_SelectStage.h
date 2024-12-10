#pragma once
#include "Scene.h"

class ButtonUI;
class Background;

class Scene_SelectStage :
    public Scene
{
private:
	Vec2 m_vResolution;
	Background* m_pBack;
	ButtonUI* m_arrButton[4];
	ButtonUI** m_ppArrButton;

public:
	void Enter() override;
	void Exit() override;

private:
	void MakeUI();

public:
	void update() override;
	void finalupdate() override;
	void render(HDC _dc) override;

public:
	Scene_SelectStage();
	~Scene_SelectStage();
};

