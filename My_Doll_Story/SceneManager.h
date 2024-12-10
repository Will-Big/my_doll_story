#pragma once
#include "Singleton.h"

class Scene; // Ŭ���� ���� ���� 

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;
	friend class EventManager;

private:
	Scene* m_arrScene[(UINT)SCENE_TYPE::END];  // ��� �� ���
	Scene* m_pCurScene;						   // ���� �� 
	bool m_arrClear[(UINT)SCENE_TYPE::END];

public:
	void init();				// ��� �� ���� �� ù��° ������ ����
	void update();				// ���� �� ������Ʈ
	void render(HDC _dc);		// ���� �� ����

public:
	Scene* GetCurScene() { return m_pCurScene; }	// ���� �� ��ȯ
	bool IsClear(SCENE_TYPE _eType) { return m_arrClear[(UINT)_eType]; }
	void SetClear(SCENE_TYPE _eType, bool _b);
	void SetArrayClear(SCENE_TYPE _eType, bool _b) { m_arrClear[(UINT)_eType] = _b; }
	void Reset();
	
private:
	void ChangeScene(SCENE_TYPE _sceneType);		// ���� �� ����, ���ο� �� ����

private:
	SceneManager();
	~SceneManager();
};