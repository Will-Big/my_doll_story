#pragma once
#include "Scene.h"

class Background;


class Scene_Menu :
    public Scene
{

private:
	vector<wstring> m_vecTexInfo[2];
	Vec2 m_vResolution;
	Background* m_pBack;

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
	Scene_Menu();
	~Scene_Menu();
};