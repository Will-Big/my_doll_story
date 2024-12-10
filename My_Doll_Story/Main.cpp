#include "pch.h"
#include "Main.h"

#include "TimeManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CollisonManager.h"
#include "EventManager.h"
#include "BlendManager.h"

#include "Object.h"
#include "PathManager.h"

#include "SoundManager.h"

#include "UIManager.h"
//undo test
#include "GameManager.h"

Main::Main()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_hDC(nullptr)
	, m_memDC(nullptr)
	, m_hBit(nullptr)
	, m_arrBrush{}
	, m_arrPen{}
{
}

Main::~Main()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

int Main::init(HWND hWnd, int x, int y)
{
	m_hWnd = hWnd;
	m_ptResolution = POINT{ x, y };

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	int sWidth = GetSystemMetrics(SM_CXSCREEN);
	int sHeight = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(m_hWnd, nullptr
		, (sWidth - (rt.right - rt.left)) / 2
		, (sHeight - (rt.bottom - rt.top)) / 2
		, rt.right - rt.left, rt.bottom - rt.top, 0);

	GetClientRect(m_hWnd, &rt);
	m_ptResolution = POINT{ rt.right - rt.left, rt.bottom - rt.top };
	// 메인 DC 생성
	m_hDC = GetDC(hWnd);

	// 백 DC 생성, 백 비트맵 생성
	m_memDC = CreateCompatibleDC(m_hDC);
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// DC <-> 비트맵 연결
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);


	CreateBrushPen();

	// Manager 초기화
	PathManager::GetInst()->init();
	InputManager::GetInst()->init();
	TimeManager::GetInst()->init();
	SceneManager::GetInst()->init();
	SoundManager::GetInst()->init();
	SoundManager::GetInst()->PlaySound(SOUND::BGM, CHANNEL::BACKGROUND);
	SoundManager::GetInst()->SetVolume(CHANNEL::BACKGROUND, 0.2f);
	
	// 5/26 01:30 블렌드매니저 추가
	BlendManager::GetInst()->init();

	return S_OK;
}
	
void Main::progress()
{
	// ====================================
	// Manager Update
	// ====================================
	TimeManager::GetInst()->update();
	InputManager::GetInst()->update();
	SceneManager::GetInst()->update();
	SoundManager::GetInst()->update();
	
	// UI 이벤트 체크
	UIManager::GetInst()->update();

	// ====================================
	// Rendering
	// ====================================
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	TimeManager::GetInst()->render();
	SceneManager::GetInst()->render(m_memDC);
	
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	// ====================================
	// Event Update
	// ====================================
 	EventManager::GetInst()->update();
}

void Main::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// Yellow brush
	m_arrBrush[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(252, 242, 206));

	//T
	m_arrBrush[(UINT)BRUSH_TYPE::T] = (HBRUSH)CreateSolidBrush(RGB(249, 250, 238));

	// green pen
	m_arrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

	//white pen
	m_arrPen[(UINT)PEN_TYPE::WHITE] = (HPEN)CreatePen(PS_SOLID,2, RGB(255, 255, 255));

}