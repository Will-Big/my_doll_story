#pragma once
#include "Scene.h"

class ButtonUI;
class Background;
class Texture;

class Scene_Help :
    public Scene
{
private:
    Vec2 m_vResolution;
    Background* m_pBack[2];

public:
    bool m_bNext;

public:
    void Enter() override;
    void Exit() override;

public:
    void update() override;
    void finalupdate() override;
    void render(HDC _dc) override;


public:
    Scene_Help();
    ~Scene_Help();

};

