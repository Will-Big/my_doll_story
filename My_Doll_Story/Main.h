#pragma once

#include "Singleton.h"

class Main : public Singleton<Main> {
	friend class Singleton<Main>;
	friend class Player;

private:
	HWND	m_hWnd;				// 메인 윈도우
	POINT	m_ptResolution;		// 윈도우 해상도
	HDC		m_hDC;				// 메인 DC
	HDC		m_memDC;			// 백DC
	HBITMAP m_hBit;				// 백DC 비트맵

	// 자주 사용하는 GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

public:
	int init(HWND hWnd, int x, int y);
	void progress();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	HDC GetBackDC() { return m_memDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

private:
	void CreateBrushPen();

private:
	Main();
	~Main();

	// Main 클래스의 protected 함수들...
};
