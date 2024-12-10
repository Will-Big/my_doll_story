#pragma once
#include "Scene.h"
#include "Stage.h"


class Item;
class Player;
class Map;

class Background; // �߰�

class Scene_Main :
    public Stage
{
private:
    Player* m_pPlayer;
    Map* m_pMap;

private:
    // UI ���� ����
	vector<wstring> m_vecTexInfo[2];
	Vec2 m_vResolution;
    Background* m_pBack;

public:
    void update() override;
    void render(HDC _dc) override;
	void Enter() override;
	void Exit() override;

public:
    void MakeItem(ITEM_TYPE _eItemType, int _x, int _y);
    void MakeUI(); // �߰�

public:
    Scene_Main();
    ~Scene_Main();
};