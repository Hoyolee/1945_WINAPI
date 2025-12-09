#include "pch.h"
#include "CObj.h"

CObj::CObj() : m_fSpeed(0.f)
{
  ZeroMemory(&m_tInfo, sizeof(INFO));
  ZeroMemory(&m_tRect, sizeof(RECT));
}
CObj::~CObj()
{
}
 
void CObj::Update_Rect()
{
  m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
  m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
  m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
  m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
void CObj::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();


		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iEnd = 0;
	}
}
