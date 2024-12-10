#include "pch.h"
#include "framework.h"
#include "My_Doll_Story.h"

#include "Main.h"



#define MAX_LOADSTRING 100

// 전역 변수:
HWND hWnd;                                      // 메인 윈도우 핸들입니다.
int g_X = 1600;
int g_Y = 900;


HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void SetFullScreen()
{
    DEVMODE dmScreenSettings = { 0 };
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);

    dmScreenSettings.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN);
    dmScreenSettings.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
    dmScreenSettings.dmBitsPerPel = GetDeviceCaps(GetDC(NULL), BITSPIXEL);
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    // 전체화면 모드로 변경
    if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        assert(false);
        // 전체화면 모드로 변경 실패
        // 오류 처리 로직 추가
    }
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow){

    //// 메모리 릭(누수) 체크
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(237);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYDOLLSTORY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 객체 초기화
    if (Main::GetInst()->init(hWnd, g_X, g_Y) != S_OK)
        assert(false);

    //SetFullScreen();

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYDOLLSTORY));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (true)
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// 메시지가 발생하지 않는 대부분의 시간
			Main::GetInst()->progress();
		}
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYDOLLSTORY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rt = { 0, 0, g_X, g_Y };

   AdjustWindowRect(&rt, WS_POPUP, false);

   g_X = rt.right - rt.left;
   g_Y = rt.bottom - rt.top;

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP,
      rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}