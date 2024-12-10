#pragma once
#include "Object.h"

class Texture;

class Item :
    public Object
{
private:
    ITEM_TYPE   m_eItemType;
    bool        m_bIsOn;
    bool        m_bMoving;
    Texture*    m_pTexture;
    bool        m_bIsDoll;

public:
    virtual void Use();
    bool IsDoll() { return m_bIsDoll; }
    void MakeDoll() { m_bIsDoll = true; }

   
public:
    void SetItemType(ITEM_TYPE _eType) { m_eItemType = _eType; }
    ITEM_TYPE GetItemType() { return m_eItemType;  }
    void SetIsOn() { m_bIsOn = !m_bIsOn; }
    bool ItemOn() { return m_bIsOn; }

public:   
    void update() override;
    void finalupdate() override;
    void render(HDC _dc) override;      // ���� ��������Ʈ �������̵� �ؼ� ���!

public:
    Item(Item* _pItem);
    Item(ITEM_TYPE _eType);
    Item();
    virtual ~Item();
};