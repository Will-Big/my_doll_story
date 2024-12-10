#pragma once
#include "UI.h"

class ButtonUI;

class PanelUI :
    public UI
{
private:
    Vec2    m_vDragStart;
    
    ButtonUI* m_BackButton;
    ButtonUI* m_RestartButton;
    ButtonUI* m_SelectButton;
    ButtonUI* m_TitleButton;

public:
    virtual void update() override;

    virtual PanelUI* Clone() override { return new PanelUI(*this); }

public:
    virtual void MouseOnAction() override;
    virtual void MouseLbtnDownAction() override;
    virtual void MouseLbtnUpAction() override;
    virtual void MouseLbtnClickedAction() override;

public:
    PanelUI();
    ~PanelUI();
};

