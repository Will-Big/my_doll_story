#include "pch.h"
#include "GameManager.h"

#include "Scene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Object.h"
#include "Player.h"
#include "Map.h"



GameManager::GameManager()
	:m_pPlayer(nullptr)
	,m_pMap(nullptr)
{
}

GameManager::~GameManager()
{
}

void GameManager::SetInfo(Player* _player, Map* _map)
{
	m_pPlayer = _player;
	m_pMap = _map;
}

void GameManager::update()
{
}


