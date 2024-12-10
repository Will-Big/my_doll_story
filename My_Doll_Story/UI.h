#pragma once
#include "Object.h"

class Texture;


class UI :
    public Object
{
    // UI �� ���� ������ �� �θ� -> �ڽ� ������ ������Ʈ, ������ ����...? ��...?
    // �Է��� �ڽ��� ���� �ʳ�? �׷� ������Ʈ�� �������� �Ǿ�� �ϴ°� �ƴѰ�?
private:
    UI*             m_pParentUI;
    vector<UI*>     m_vecChildUI;
    Vec2            m_vFinalPos;
    Texture*        m_pTexture;

    bool            m_bCamAffected; // UI ī�޶� ���� ����
    bool            m_bMouseOn;     // UI ���� ���콺�� �ִ���
    bool            m_bLbtnDown;    // UI �� ���� ��ư�� �������� �ִ���

    bool            m_bIsOn;

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    UI* GetParent() { return m_pParentUI; }
    Texture* GetTexture() { return m_pTexture; }
    void SetTexture(Texture* _pTex) { m_pTexture = _pTex; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }

    void SetOn(bool _b);
    bool GetOn() { return m_bIsOn; }

    void AddChild(UI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    const vector<UI*>& GetChildUI() { return m_vecChildUI; }

public:
    void update() override;
    void finalupdate() override;
    void render(HDC _dc) override;

    virtual UI* Clone() = 0;
    
private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

    void MouseOnCheck();

public:
    virtual void MouseOnAction() ;
    virtual void MouseLbtnDownAction();
    virtual void MouseLbtnUpAction(); 
    virtual void MouseLbtnClickedAction();

public:
    UI(bool _bCamAff);
    UI(const UI& _origin);
    virtual ~UI();

    friend class UIManager;
};

