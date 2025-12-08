#include "pch.h"
#include "CBoss.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CScrollMgr.h"
#include "CEnemyBullet.h"
#include "CAbstractFactory.h"
#include "CCollisionMgr.h"
#include "CBullet.h"
#include "CPlayer.h"

CBoss::CBoss():m_eCurState(IDLE),m_ePreState(ST_END)
{

}

CBoss::~CBoss()
{
	Release();
}

void CBoss::Initialize()
{
  m_tInfo = { 300.f, 200.f,188.f,186.f };
  
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Boss/enemyBoss.bmp", L"Boss");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Boss/bossExplosion.bmp", L"BossDead");

	m_fAngle = 10.f;
	
	m_fDistance = 100.f;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 19;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_bDead = false;
}

int CBoss::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	Boss_Frame();
	
	Sector_Pattern();

  return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{
}

void CBoss::Render(HDC hDC)
{
	if (m_eCurState == IDLE)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss");

		GdiTransparentBlt(hDC,								// 복사 받을 DC
			m_tRect.left,						// 복사 받을 공간의 LEFT	
			m_tRect.top,						// 복사 받을 공간의 TOP
			(int)m_tInfo.fCX ,										// 복사 받을 공간의 가로 
			(int)m_tInfo.fCY ,										// 복사 받을 공간의 세로 
			hMemDC,															// 복사 할 DC
			m_tFrame.iStart * (int)m_tInfo.fCX,	// 복사할 이미지의 LEFT, TOP
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(INT)m_tInfo.fCX,										// 복사할 이미지의 가로, 세로
			(INT)m_tInfo.fCY,
			RGB(255, 0, 255));									// 제거할 색상
	}

	if (m_eCurState == DEAD)
		{
			HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"BossDead");
			GdiTransparentBlt(hDC,								// 복사 받을 DC
				m_tRect.left,						// 복사 받을 공간의 LEFT	
				m_tRect.top,						// 복사 받을 공간의 TOP
				(int)m_tInfo.fCX,										// 복사 받을 공간의 가로 
				(int)m_tInfo.fCY,										// 복사 받을 공간의 세로 
				hMemDC2,															// 복사 할 DC
				m_tFrame.iStart  * (int)m_tInfo.fCX,	// 복사할 이미지의 LEFT, TOP
				m_tFrame.iMotion * (int)m_tInfo.fCY,
				(INT)m_tInfo.fCX,										// 복사할 이미지의 가로, 세로
				(INT)m_tInfo.fCY,
				RGB(255, 0, 255));									// 제거할 색상
	}
}


void CBoss::Release()
{
}

void CBoss::Boss_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;
	}
}

void CBoss::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 19;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 19;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBoss::Sector_Pattern()
{
	m_tPosin.x = long(m_tInfo.fX + cosf(m_fAngle * (PI / 180.f)));
	m_tPosin.y = long(m_tInfo.fY - sinf(m_fAngle * (PI / 180.f)));

	const int count = 8;
	const float spread = 40.f; // 각 탄 사이의 각도 간격(조정 가능)
	// 중심 각을 m_fAngle으로 사용(원하면 매 호출마다 증가시켜 회전 효과)

	for (int i = 0; i < count; ++i)
	{
		float angle = m_fAngle + (i - count / 2) * spread; // 중앙을 향한 팬
		float rad = angle * (PI / 180.f);

		// 총알 생성 위치 (보스에서 약간 떨어진 지점)
		float px = m_tInfo.fX + m_fDistance * cosf(rad);
		float py = m_tInfo.fY - m_fDistance * sinf(rad);

		CObj* pBullet = CAbstractFactory<CEnemyBullet>::Create(px, py);
		pBullet->Set_Angle(angle);    // 각도 설정 (도 단위)
		pBullet->Set_Speed(6.0f);     // 속도 설정(필요에 따라 변경)

		CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET, pBullet);
	}

}