#pragma once
#include "Scene.h"

class ButtonUI;
class Background;
class Texture;

class Scene_Creator :
    public Scene
{
private:
    Vec2 m_vResolution;
    Background* m_pBack;

    Texture* m_pTex;

public:
    void Enter() override;
    void Exit() override;

public:
    void update() override;
    void finalupdate() override;
    void render(HDC _dc) override;


public:
    Scene_Creator();
    ~Scene_Creator();
};

