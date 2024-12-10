#pragma once
#include "Scene.h"
#include "Stage.h"


class UI;
class Background;

class Scene_Title :
    public Scene
{
private:
    vector<wstring> m_vecTexInfo[2];
    Vec2 m_vResolution;
    Background* m_pBack;

public:
    void Enter() override;
    void Exit() override;

public:
    void update() override;
    void finalupdate() override;
    void render(HDC _dc) override;


public:
    Scene_Title();
    ~Scene_Title();
};

