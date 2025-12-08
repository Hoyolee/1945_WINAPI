// 1945.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "1945.h"
#include "CMainGame.h"
#include  "Define.h"
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPWSTR    lpCmdLine,
  _In_ int       nCmdShow)
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // TODO: 여기에 코드를 입력합니다.

  // 전역 문자열을 초기화합니다.
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_MY1945, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // 애플리케이션 초기화를 수행합니다:
  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1945));

  MSG msg;
  msg.message = WM_NULL;

  CMainGame   MainGame;
  MainGame.Initialize();

  DWORD   dwTime = GetTickCount();


  // 기본 메시지 루프입니다:
  while (true)
  {
    // PM_REMOVE : 메세지 큐로부터 메세지를 가져오면서 실행(메세지 큐에서 기존 메세지는 삭제)
    // PM_NOREMOVE : 메세지가 들어왔는지만 확인하고 있으면 실행, 없으면 대기(Getmessage를 다시 호출 해야 메세지를 가져올 수 있음)

    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;

      if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

    else
    {
      if (dwTime + 10 < GetTickCount())
      {
        MainGame.Update();
        MainGame.Late_Update();
        MainGame.Render();

        dwTime = GetTickCount();
      }
    }
  }
  return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;

  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1945));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

  wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_1945);
  wcex.lpszClassName = szWindowClass;

  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

  RECT     rc{ 0, 0, WINCX, WINCY };

  AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, // 창 시작 x, y 좌표
    rc.right - rc.left,
    rc.bottom - rc.top, // 창 가로, 세로 사이즈
    nullptr, nullptr, hInstance, nullptr);

  if (!hWnd)
  {
    return FALSE;
  }

  g_hWnd = hWnd;
  // g_hWnd가 CMainGame에서 계속 받아와서 사용하는 윈도우 핸들인데
  // 여기서 hWnd를 g_hWnd에 넣어줘야 메인게임에서 잘 작동하는데 제대로 넣어주지
  // 못해서 이상하게 출력되었던 것.
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_KEYDOWN:

    switch (wParam)
    {
    case VK_ESCAPE:
      DestroyWindow(g_hWnd);
      break;
    }
    break;
  case WM_COMMAND:
  {
    int wmId = LOWORD(wParam);
    // 메뉴 선택을 구문 분석합니다:
    switch (wmId)
    {
    case IDM_ABOUT:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
  }
  break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);
  switch (message)
  {
  case WM_INITDIALOG:
    return (INT_PTR)TRUE;

  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
    {
      EndDialog(hDlg, LOWORD(wParam));
      return (INT_PTR)TRUE;
    }
    break;
  }
  return (INT_PTR)FALSE;
}
