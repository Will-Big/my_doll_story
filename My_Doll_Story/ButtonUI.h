#pragma once
#include "UI.h"

typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

class ButtonUI :
    public UI
{
private:
    bool                m_bActivate;
    bool                m_bClear;

    bool                m_bMouseOn;
    bool                m_bMouseDown;
    bool                m_bMouseClicked;

    BTN_FUNC            m_pFunc;
    DWORD_PTR           m_param1;
    DWORD_PTR           m_param2;

    vector<Texture*>    m_vecTex; // 0:활성화, 1:마우스on, 2:버튼클릭, 3:비활성화
    

public:
    virtual ButtonUI* Clone() override { return new ButtonUI(*this); }

public:
    virtual void render(HDC _dc) override;

public:
    virtual void MouseOnAction() override;
    virtual void MouseLbtnDownAction() override;
    virtual void MouseLbtnUpAction() override;
    virtual void MouseLbtnClickedAction() override;

    void SetActivate(bool _bAct) { m_bActivate = _bAct; }
    vector<Texture*>& GetVecTexture() { return m_vecTex; }

    void SetClear(bool _bClear) { m_bClear = _bClear; }

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

private:
    void Trans(HDC _dc, int _index);

public:
    ButtonUI();
    ~ButtonUI();
};

