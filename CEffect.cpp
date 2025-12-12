#include"pch.h"
#include "CEffect.h"
#include "CBmpMgr.h"


CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

void CEffect::Initialize()
{
	m_tInfo.fCX = 92;
	m_tInfo.fCY = 94;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Monster/Damaged.bmp", L"Damaged");
	
	m_isEnd = false;

	m_tFrame.iStart  = 0;
	m_tFrame.iEnd		 = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime	 = GetTickCount();

	m_eCurState = PLAYING;

	m_pFrameKey = L"Damaged";
}

int CEffect::Update()
{
  __super::Update_Rect();

	Move_Frame();

  return OBJ_NOEVENT;
}

void CEffect::Late_Update()
{
}

void CEffect::Render(HDC hDC)
{

	if (m_eCurState == PLAYING)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		// 플레이어 렌더
		GdiTransparentBlt(hDC,												// 복사 받을 DC
			m_tRect.left,										// 복사 받을 공간의 LEFT	
			m_tRect.top,											// 복사 받을 공간의 TOP
			(int)m_tInfo.fCX,														// 복사 받을 공간의 가로 
			(int)m_tInfo.fCY,														// 복사 받을 공간의 세로 
			hMemDC,																			// 복사 할 DC
			m_tFrame.iStart * (int) m_tInfo.fCX,					// 복사할 이미지의 LEFT, TOP
			m_tFrame.iStart * (int) m_tInfo.fCY,
			(INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
			(INT)m_tInfo.fCY,
			RGB(255, 0, 255));													// 제거할 색상
	}
}

void CEffect::Release()
{
}
