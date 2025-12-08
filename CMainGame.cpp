#include "pch.h"
#include "CMainGame.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"

CMainGame::CMainGame()
  : m_iFPS(0), m_dwTime(GetTickCount())
{
  ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
  Release();
}

void CMainGame::Initialize()
{
  m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Title/inGameStart.bmp", L"Back");
	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);

#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG

}

void CMainGame::Update()
{

	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CKeyMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;

		SetWindowText(g_hWnd, m_szFPS);

		m_dwTime = GetTickCount();
	}
	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	CSceneMgr::Get_Instance()->Render(hBackDC);

	BitBlt(m_hDC,				// 복사 받을 DC
		0,	// 복사 받을 공간의 LEFT	
		0,	// 복사 받을 공간의 TOP
		WINCX,			// 복사 받을 공간의 가로 
		WINCY,			// 복사 받을 공간의 세로 
		hBackDC,				// 복사 할 DC
		0,					// 복사할 이미지의 LEFT, TOP
		0,
		SRCCOPY);			// 그대로 복사
}

void CMainGame::Release()
{
	CBmpMgr::Get_Instance()->Release();
	CBmpMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
  CScrollMgr::Destroy_Instance();
  CTileMgr::Destroy_Instance();
  CKeyMgr::Destroy_Instance();
  CObjMgr::Destroy_Instance();

  ReleaseDC(g_hWnd, m_hDC);
}
