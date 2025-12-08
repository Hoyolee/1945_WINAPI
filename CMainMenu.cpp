#include "pch.h"
#include "CMainMenu.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"

CMainMenu::CMainMenu()
{
}

CMainMenu::~CMainMenu()
{
	Release();
}

void CMainMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Title/inGameStart.bmp", L"Menu");
	pStart = new CStart;
	pStart->Initialize();
  CObjMgr::Get_Instance()->AddObject(OBJ_MAIN_UI, pStart);
}

int CMainMenu::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
		return 0;
	}
	return 0;
}

void CMainMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMainMenu::Render(HDC hDC)
{
	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");
	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);

  CObjMgr::Get_Instance()->Render(hDC);
}

void CMainMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MAIN_UI);
}
