#pragma once
#include "Scene.h"


class UI;

class Scene_UI_Test :
    public Scene
{
private:
    UI* m_pUI;

public:
    void Enter() override;
    void Exit() override;

public:
    void update() override;
    void finalupdate() override;
    void render(HDC _dc) override;
    
public:
    Scene_UI_Test();
    ~Scene_UI_Test();
};

