#include "pch.h"
#include "CBullet.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CSoundMgr.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 31.f;
	m_tInfo.fCY = 53.f;
	m_fSpeed = 10.f;
	m_bDead = false;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Bullet/Player/playerAttack.bmp", L"Bullet");

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	m_tInfo.fY -= m_fSpeed;

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (m_tInfo.fY <= 0)
		m_bDead=true;
}


void CBullet::Render(HDC hDC)
{
	m_pFrameKey = L"Bullet";

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				// 복사 받을 DC
		m_tRect.left,	// 복사 받을 공간의 LEFT	
		m_tRect.top ,				// 복사 받을 공간의 TOP
		(int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
		(int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
		hMemDC,				// 복사 할 DC
		m_tFrame.iStart * (int)m_tInfo.fCX,					// 복사할 이미지의 LEFT, TOP
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
		(INT)m_tInfo.fCY,
		RGB(255, 0, 255));	// 제거할 색상
}

void CBullet::Release()
{
}