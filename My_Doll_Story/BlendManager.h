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
	void FadeIn();	 // ����� ������ ��Ӱ�
	void DisplayBackground(); // ��ο����°� ���� ����� ��÷�

public:
	void SetFadeIn(bool _b) { m_bFadeIn = _b; }


private:
	BlendManager();
	~BlendManager();
};

