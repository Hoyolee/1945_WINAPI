#include "pch.h"
#include "CHeli.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CEnemyBullet.h"
#include "CBigBullet.h"

CHeli::CHeli()
{
}

CHeli::~CHeli()
{
}

void CHeli::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Monster/enemyHelicopter.bmp", L"Heli");

	// 플레이어 크기 및 위치지정

	m_iScore = 300;

	m_iHp = 1;
	m_tInfo.fCX = 34.f;
	m_tInfo.fCY = 25.f;
	m_fTime = GetTickCount();
	m_fSpeed = 4.f;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iMotion = 1;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eCurState = IDLE;

	m_fDistance = 100.f;

	m_pFrameKey = L"Heli";
}

int CHeli::Update()
{
	__super::Update_Rect();

	if (m_tInfo.fY <= 300.f)
		m_tInfo.fY += m_fSpeed;
	else
	{
		float speed = fabsf(m_fSpeed);

		if (m_fSpeed > 0.f)
		{
			m_tInfo.fX += m_fSpeed;
			if (m_tInfo.fX >= WINCX - 100.f)
				m_fSpeed = -speed;
		}
		else if (m_fSpeed < 0.f)
		{
			m_tInfo.fX += m_fSpeed;
			if (m_tInfo.fX <= WINCX - 500.f)
			{
				m_fSpeed = speed;
				m_tInfo.fX += m_fSpeed;
			}
		}
	}



	if (m_fTime + 500 < GetTickCount())
	{
		float fWidth(0.f), fHeight(0.f);
		fWidth = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fX - m_tInfo.fX;
		fHeight = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fY - m_tInfo.fY;
		m_fAngle = atan2f(fHeight, fWidth);
		CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
		m_fTime = GetTickCount();
	}
	Heli_Move_Frame();

	return OBJ_NOEVENT;
}

void CHeli::Late_Update()
{
}

void CHeli::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	// 플레이어 렌더

	GdiTransparentBlt(hDC,												// 복사 받을 DC
		m_tRect.left,										// 복사 받을 공간의 LEFT	
		m_tRect.top,											// 복사 받을 공간의 TOP
		(int)m_tInfo.fCX,														// 복사 받을 공간의 가로 
		(int)m_tInfo.fCY,														// 복사 받을 공간의 세로 
		hMemDC,																			// 복사 할 DC
		m_tFrame.iStart  * (int)m_tInfo.fCX,						// 복사할 이미지의 LEFT, TOP
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
		(INT)m_tInfo.fCY,
		RGB(255, 0, 255));													// 제거할 색상

}
void CHeli::Heli_Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();


		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;
	}
}

void CHeli::OnCollision(CObj* pOther)
{
		m_iHp--;
		if (m_eCurState == DEAD)
			return;

		CObjMgr::Get_Instance()->Get_Object(OBJ_STAGE_UI).front()->Add_Score(m_iScore);

		if (m_iHp <= 0)
		{
			m_eCurState = DEAD;
			m_bDead = true;

			m_pFrameKey = L"EnemyExplode";

			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
		
	}

}

void CHeli::Release()
{
}
