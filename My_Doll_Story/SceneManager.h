#pragma once
#include "Singleton.h"

class Scene; // Å¬·¡½º Àü¹æ ¼±¾ð 

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;
	friend class EventManager;

private:
	Scene* m_arrScene[(UINT)SCENE_TYPE::END];  // ¸ðµç ¾À ¸ñ·Ï
	Scene* m_pCurScene;						   // ÇöÀç ¾À 
	bool m_arrClear[(UINT)SCENE_TYPE::END];

public:
	void init();				// ¸ðµç ¾À »ý¼º ¹× Ã¹¹øÂ° ¾ÀÀ¸·Î ÀÔÀå
	void update();				// ÇöÀç ¾À ¾÷µ¥ÀÌÆ®
	void render(HDC _dc);		// ÇöÀç ¾À ·»´õ

public:
	Scene* GetCurScene() { return m_pCurScene; }	// ÇöÀç ¾À ¹ÝÈ¯
	bool IsClear(SCENE_TYPE _eType) { return m_arrClear[(UINT)_eType]; }
	void SetClear(SCENE_TYPE _eType, bool _b);
	void SetArrayClear(SCENE_TYPE _eType, bool _b) { m_arrClear[(UINT)_eType] = _b; }
	void Reset();
	
private:
	void ChangeScene(SCENE_TYPE _sceneType);		// ÇöÀç ¾À ÅðÀå, »õ·Î¿î ¾À ÀÔÀå

private:
	SceneManager();
	~SceneManager();
};