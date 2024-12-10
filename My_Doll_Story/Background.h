#pragma once

#include "Object.h"

class Texture;

class Background :
    public Object
{
private:
    Texture*	m_pTex;

public:
	void SetCenterPos();
	void SetTexture(Texture* _pTex) { m_pTex = _pTex; }
	virtual void update() override;
	virtual void render(HDC _dc) override;
	virtual void finalupdate() override;

public:
	Background();
	~Background();
};
