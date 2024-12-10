#pragma once

#include "Singleton.h"

class Main : public Singleton<Main> {
	friend class Singleton<Main>;
	friend class Player;

private:
	HWND	m_hWnd;				// ���� ������
	POINT	m_ptResolution;		// ������ �ػ�
	HDC		m_hDC;				// ���� DC
	HDC		m_memDC;			// ��DC
	HBITMAP m_hBit;				// ��DC ��Ʈ��

	// ���� ����ϴ� GDI Object
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

	// Main Ŭ������ protected �Լ���...
};
