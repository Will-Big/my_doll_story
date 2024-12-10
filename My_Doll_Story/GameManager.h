#pragma once
#include "Singleton.h"

class Player;
class Map;

class GameManager :
    public Singleton<GameManager>
{
    friend class Singleton<GameManager>;

private:
    Player* m_pPlayer;
    Map* m_pMap;

public:
    Player* GetPlayer() { return m_pPlayer; }
    Map* GetMap() { return m_pMap; }

    void SetInfo(Player* _player, Map* _map);

    void update();

private:
    GameManager();
    ~GameManager();
};

