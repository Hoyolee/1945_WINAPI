#include "pch.h"
#include "CGameClear.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"
#include "CBoss.h"

CGameClear::CGameClear()
{
}

CGameClear::~CGameClear()
{
}

void CGameClear::Initialize()
{
  m_tInfo.fCX = 600;
  m_tInfo.fCY = 800;

  CSoundMgr::Get_Instance()->StopAll();

  CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/UI/missionComplete.bmp", L"GameClear");
  CSoundMgr::Get_Instance()->PlaySound(L"missionComplete.mp3", SOUND_BGM, 0.5f);
}

int CGameClear::Update()
{
  __super::Update_Rect();

  return OBJ_NOEVENT;
}

void CGameClear::Late_Update()
{
}

void CGameClear::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GameClear");

	GdiTransparentBlt(hDC,				// 복사 받을 DC
		m_tRect.left,								// 복사 받을 공간의 LEFT	
		m_tRect.top,								// 복사 받을 공간의 TOP
		(int)m_tInfo.fCX,						// 복사 받을 공간의 가로 
		(int)m_tInfo.fCY,						// 복사 받을 공간의 세로 
		hMemDC,											// 복사 할 DC
		0,													// 복사할 이미지의 LEFT, TOP
		0,
		(INT)m_tInfo.fCX,						// 복사할 이미지의 가로, 세로
		(INT)m_tInfo.fCY,
		RGB(255, 0, 255));					// 제거할 색상

}

void CGameClear::Release()
{
}
