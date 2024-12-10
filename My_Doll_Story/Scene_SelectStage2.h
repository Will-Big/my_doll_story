#pragma once
#include "Scene.h"

class Background;
class ButtonUI;

class Scene_SelectStage2 :
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
	Scene_SelectStage2();
	~Scene_SelectStage2();
};

