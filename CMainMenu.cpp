#include "pch.h"
#include "CMainMenu.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CAbstractFactory.h"

float fVolume = 0.25f;
CMainMenu::CMainMenu()
{
}

CMainMenu::~CMainMenu()
{
	Release();
}

void CMainMenu::Initialize()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Logo.mp3", SOUND_EFFECT, fVolume);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Title/inGameStart.bmp", L"Menu");


	CObjMgr::Get_Instance()->AddObject(OBJ_MAIN_UI, CAbstractFactory<CStart>::Create());
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
  CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
}
