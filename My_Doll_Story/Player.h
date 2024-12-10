#pragma once
#include "Object.h"

class Texture;
class GameManager;

class Player :
    public Object
{
private:
    bool m_bMoving;
    bool m_bGrab;
    char m_cLookAt;  //'u' = up, 'd' = down, 'l' = left, 'r' = right
    Vec2 m_vDir;
    Texture* m_pTex;

    MapIndex m_playerIndex;

    

public:
    void SetDir(Vec2 _dir) { _dir = m_vDir; }
    Vec2 GetDir() { return m_vDir; }

    char GetLookAt() { return m_cLookAt; }

    bool IsGrab() { return m_bGrab; }

public:
    void update() override;
    void render(HDC _dc) override;

public:
    void MovePlayer(Vec2& currentPosition, const Vec2& displacement, float duration);
    void UndoMovePlayer(POS _pos);
    void MoveByKey(KEY _eKey);
   // MapIndex GetPlayerIndex() { return m_playerIndex; }
    
public:
    Player();
    ~Player();
};
