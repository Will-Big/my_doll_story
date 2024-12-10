#pragma once
#include "Item.h"

class Texture;

class Tape :
	public Item
{
private:
	//bool m_bActivated;
	Texture* m_pTex;
	bool m_bIsUse;

public:
	//void ToggleActivate();
	void Use() override;
	void update() override;

public:
	void render(HDC _dc) override;

public:
	Tape();
	~Tape();
};

