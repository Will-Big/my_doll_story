#pragma once
#include "Scene.h"


class Scene_Start :
    public Scene
{
public:
	void Enter() override;
	void Exit() override;

public:
    Scene_Start();
    ~Scene_Start();
};

