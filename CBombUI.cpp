#include "pch.h"
#include "CBombUI.h"
#include "CBmpMgr.h"

CBombUI::CBombUI()
{
}

CBombUI::~CBombUI()
{
}

void CBombUI::Initialize()
{
  m_tInfo = {50,WINCY-50, 32,30};
  CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Player/Player_Tool/playerBombCount.bmp", L"Bomb");
}

int CBombUI::Update()
{
  __super::Update_Rect();

  return OBJ_NOEVENT;
}

void CBombUI::Late_Update()
{
}

void CBombUI::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Bomb");

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

void CBombUI::Release()
{
}
