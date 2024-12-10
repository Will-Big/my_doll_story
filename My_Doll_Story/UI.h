#pragma once
#include "Object.h"

class Texture;


class UI :
    public Object
{
    // UI 는 계층 구조를 띄어서 부모 -> 자식 순으로 업데이트, 렌더함 굳이...? 왜...?
    // 입력은 자식이 받지 않나? 그럼 업데이트가 역순으로 되어야 하는거 아닌가?
private:
    UI*             m_pParentUI;
    vector<UI*>     m_vecChildUI;
    Vec2            m_vFinalPos;
    Texture*        m_pTexture;

    bool            m_bCamAffected; // UI 카메라 영향 여부
    bool            m_bMouseOn;     // UI 위에 마우스가 있는지
    bool            m_bLbtnDown;    // UI 에 왼쪽 버튼이 눌린적이 있는지

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

