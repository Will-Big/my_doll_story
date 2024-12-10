#pragma once
#include "Scene.h"

class Texture;
class Item;
class Player;
class Map;
class ClearPanel;
class MenuPanel;
class SketchPanel;

class Stage :
    public Scene
{
protected:
	SCENE_TYPE m_SceneType;
	Player* m_pPlayer;
	Map* m_pMap;

	Texture* m_pTexSketch;
	Texture* m_pTexClear;

	ClearPanel* m_pClearPanel;
	MenuPanel* m_pMenuPanel;
	SketchPanel* m_pSketchPanel;

	

public:
	void update() override;
	void finalupdate() override;
	void render(HDC _dc) override;
	void Enter() override;
	void Exit() override;

public:
	void MakeItem(ITEM_TYPE _eItemType, int _x, int _y);
	void SetClear(bool _b);
	void StageKeyInput();

public:
	Stage();
	~Stage();
};

