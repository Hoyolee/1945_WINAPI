#include "pch.h"
#include "CGameOverFont.h"
#include "CBmpMgr.h"

CGameOverFont::CGameOverFont()
{
}

CGameOverFont::~CGameOverFont()
{
}

void CGameOverFont::Initialize()
{
  CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Title/gameOver.bmp", L"GameOverFont");
  m_tInfo = { WINCX > 1, WINCY > 2,558.f,67.f };
}

int CGameOverFont::Update()
{
  __super::Update_Rect();
  return 0;
}

void CGameOverFont::Late_Update()
{

}

void CGameOverFont::Render(HDC hDC)
{
  HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"GameOverFont");

  GdiTransparentBlt(hDC,												// 복사 받을 DC
    m_tRect.left,										// 복사 받을 공간의 LEFT	
    m_tRect.top,										// 복사 받을 공간의 TOP
    (int)m_tInfo.fCX,														// 복사 받을 공간의 가로 
    (int)m_tInfo.fCY,														// 복사 받을 공간의 세로 
    hGroundDC,																	// 복사 할 DC
    0,					                                // 복사할 이미지의 LEFT, TOP
    0,
    (INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
    (INT)m_tInfo.fCY,
    RGB(255, 0, 255));	// 제거할 색상

}

void CGameOverFont::Release()
{
}
