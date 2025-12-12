#include "pch.h"
#include "CStealthEnemy.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CEnemyBullet.h"

CStealthEnemy::CStealthEnemy()
{
}
CStealthEnemy::~CStealthEnemy()
{
}

void CStealthEnemy::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Monster/enemy3.bmp", L"Enemy3");

	m_iHp = 1;
	// 플레이어 크기 및 위치지정
	m_tInfo.fCX = 125.f;
	m_tInfo.fCY = 65.f;
	m_fTime = GetTickCount();
	m_fSpeed = 5.5f;
	
	m_bDead = false;

	m_pFrameKey = L"Enemy3";
}

int CStealthEnemy::Update()
{
	__super::Update_Rect();

	srand(time(NULL));

	if(m_tInfo.fY<=200.f)
		m_tInfo.fY += m_fSpeed;
	else
		if (m_fTime + 5000 < GetTickCount())
		{
			float speed = fabsf(m_fSpeed);

			int RandX = ((int)rand() / RAND_MAX) * (600 - 100) + 100;
			int RandY = ((int)rand() / RAND_MAX) * (600 - 200) + 200;

			if (m_tInfo.fX <= RandX && m_tInfo.fY <= RandY)
			{
				m_tInfo.fX += m_fSpeed;
				m_tInfo.fY += m_fSpeed;
			}
			else if (m_tInfo.fX <= RandX && m_tInfo.fY >= RandY)
			{
				m_tInfo.fX += m_fSpeed;
				m_fSpeed = -speed;
				m_tInfo.fY += m_fSpeed;
			}
			else if (m_tInfo.fX >= RandX && m_tInfo.fY <= RandY)
			{
				m_tInfo.fY += m_fSpeed;
				m_fSpeed = -speed;
				m_tInfo.fX -= m_fSpeed;
			}
			else
			{
				m_fSpeed = -speed;
				m_tInfo.fX += m_fSpeed;
				m_tInfo.fY += m_fSpeed;
			}
		}
	if (m_fTime + 500 < GetTickCount())
	{
		float fWidth(0.f), fHeight(0.f);
		fWidth = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fX - m_tInfo.fX;
		fHeight = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fY - m_tInfo.fY;
		m_fAngle = atan2f(fHeight, fWidth);
		CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET, CAbstractFactory<CEnemyBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
		m_fTime = GetTickCount();
	}
	return OBJ_NOEVENT;
}

void CStealthEnemy::Late_Update()
{
}

void CStealthEnemy::Render(HDC hDC)
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

void CStealthEnemy::Release()
{
}

