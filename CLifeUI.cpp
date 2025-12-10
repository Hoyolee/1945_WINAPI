#include "pch.h"
#include "CLifeUI.h"
#include "CBmpMgr.h"
#include "CPlayer.h"

CLifeUI::CLifeUI()
{

}
CLifeUI::~CLifeUI()
{

}

void CLifeUI::Initialize()
{
  m_tInfo = { 50,100, 43,30 };
  CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Player/Player_Tool/playerLifeCount.bmp", L"Life");
}

int CLifeUI::Update()
{
  __super::Update_Rect();

  return OBJ_NOEVENT;
}

void CLifeUI::Late_Update()
{
}

void CLifeUI::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Life");

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

void CLifeUI::Release()
{
}
