#pragma once

#include "Singleton.h"
class Texture;

class BlendManager : public Singleton<BlendManager>
{
	friend class Singleton<BlendManager>;

public:
	HBITMAP		m_hBackgroundBitMap;
	HDC			m_hBackgroundDC;

	bool		m_bFadeIn;

	float		m_fEffectDuration;
	float		m_fCurTime;
	float		m_fRatio;

	int			m_iAlphaImage;

public:
	void init();
	void FadeIn();	 // 배경을 서서히 어둡게
	void DisplayBackground(); // 어두워지는게 끝난 배경을 상시로

public:
	void SetFadeIn(bool _b) { m_bFadeIn = _b; }


private:
	BlendManager();
	~BlendManager();
};

