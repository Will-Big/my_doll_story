#pragma once
#include "Item.h"
class Scissors :
    public Item
{
private:
    MapIndex     m_sCurIndex;
    Texture*     m_pTexture;
    bool         m_bIsUse;

public: 
    void Use() override;
    void update() override;    
    void render(HDC _dc) override;

public:
    Scissors();
    Scissors(int _x, int _y);
    ~Scissors();
};

