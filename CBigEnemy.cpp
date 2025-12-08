#include "pch.h"
#include "CBigEnemy.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CEnemyBullet.h"
#include "CBigBullet.h"

CBigEnemy::CBigEnemy()
{
}

CBigEnemy::~CBigEnemy()
{
}

void CBigEnemy::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Monster/enemy2.bmp", L"Enemy2");

	m_iHp = 1;
	// 플레이어 크기 및 위치지정
	m_tInfo.fCX = 153.f;
	m_tInfo.fCY = 134.f;
	m_fTime = GetTickCount();
	m_fSpeed = 2.f;

	m_fDistance = 100.f;

	m_pFrameKey = L"Enemy2";
}

int CBigEnemy::Update()
{
	__super::Update_Rect();

	if (m_tInfo.fY <= 200.f)
		m_tInfo.fY += m_fSpeed;
	else
	{
		float speed = fabsf(m_fSpeed);

		if (m_fSpeed > 0.f)
		{
			m_tInfo.fX += m_fSpeed;
			if (m_tInfo.fX >= WINCX - 100.f)
			{
				m_fSpeed = -speed;
			}
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
	
	if (m_fTime + 250 < GetTickCount())
	{
		float fWidth(0.f), fHeight(0.f);
		fWidth = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fX - m_tInfo.fX;
		fHeight = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fY - m_tInfo.fY;
		m_fAngle = atan2f(fHeight, fWidth);
		CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
		m_fTime = GetTickCount();
	}


    return OBJ_NOEVENT;
}

void CBigEnemy::Late_Update()
{
#ifdef _DEBUG
	cout << m_tInfo.fX << "\t" << m_tInfo.fY << endl;
#endif // _DEBUG

}

void CBigEnemy::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	// 플레이어 렌더

	GdiTransparentBlt(hDC,												// 복사 받을 DC
		m_tRect.left,										// 복사 받을 공간의 LEFT	
		m_tRect.top,											// 복사 받을 공간의 TOP
		(int)m_tInfo.fCX,														// 복사 받을 공간의 가로 
		(int)m_tInfo.fCY,														// 복사 받을 공간의 세로 
		hMemDC,																			// 복사 할 DC
		0,					// 복사할 이미지의 LEFT, TOP
		0,
		(INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
		(INT)m_tInfo.fCY,
		RGB(255, 0, 255));													// 제거할 색상

}

void CBigEnemy::Release()
{
}
