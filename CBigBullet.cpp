#include "pch.h"
#include "CBigBullet.h"
#include "CObjMgr.h"
#include "CScrollMgr.h"
#include "CCollisionMgr.h"
#include "CBmpMgr.h"

CBigBullet::CBigBullet()
{
}

CBigBullet::~CBigBullet()
{
  Release();
}

void CBigBullet::Initialize()
{
  CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Monster/enemyBullets2.bmp", L"BigBullet");

  m_tInfo.fCX = 120/9.0f;
  m_tInfo.fCY = 20.f;
  m_fSpeed = 5.0f;
  m_bDead = false;

  m_tFrame.iStart = 0;
  m_tFrame.iEnd = 8;
  m_tFrame.iMotion = 0;
  m_tFrame.dwSpeed = 200;
  m_tFrame.dwTime = GetTickCount();

}

int CBigBullet::Update()
{
  if (m_bDead)
    return OBJ_DEAD;

  __super::Update_Rect();

  Move_Frame();

  m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
  m_tInfo.fY += sinf(m_fAngle) * m_fSpeed;

  return OBJ_NOEVENT;
}

void CBigBullet::Late_Update()
{
  const int Margin = 100;
  if (m_tInfo.fY > WINCY + Margin || m_tInfo.fX > WINCX + Margin || m_tInfo.fX + Margin < 0)
    m_bDead = true;

//#ifdef _DEBUG
//  cout << m_tInfo.fX << "\t" << m_tInfo.fY << "\t " << m_iHp << endl;
//#endif // _DEBUG

}

void CBigBullet::Render(HDC hDC)
{
  m_pFrameKey = L"BigBullet";

  HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

  GdiTransparentBlt(hDC,				// 복사 받을 DC
    m_tRect.left,	// 복사 받을 공간의 LEFT	
    m_tRect.top,				// 복사 받을 공간의 TOP
    (int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
    (int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
    hMemDC,				// 복사 할 DC
    m_tFrame.iStart * (int)m_tInfo.fCX,					// 복사할 이미지의 LEFT, TOP
    m_tFrame.iMotion * (int)m_tInfo.fCY,
    (INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
    (INT)m_tInfo.fCY,
    RGB(255, 0, 255));	// 제거할 색상

}

void CBigBullet::Release()
{
}
