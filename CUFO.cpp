#include "pch.h"
#include "CUFO.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CEnemyBullet.h"
#include "CBigBullet.h"

CUFO::CUFO():m_eCurState(IDLE)
{
}

CUFO::~CUFO()
{
}
// TODO: m_eCurState에 따른 애니메이션 변화 삽입 및 관련 함수 삽입
// CEnemy 참고
void CUFO::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Monster/enemyUFO.bmp", L"UFO");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Monster/deathExplosions.bmp", L"boom");

	m_iHp = 30;
	// 플레이어 크기 및 위치지정
	m_tInfo.fCX = 53.f;
	m_tInfo.fCY = 32.f;
	m_fTime = GetTickCount();
	m_fSpeed = 5.5f;

	m_iScore = 200;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_iHp = 20;

	m_fDistance = 100.f;

	m_pFrameKey = L"UFO";
	m_bDead = false;
	m_bDown = false;

	m_eCurState = IDLE;

	m_iTargetX = -1;
	m_iTargetY = -1;
	m_dwMoveStart = 0;
}

int CUFO::Update()
{
	__super::Update_Rect();

	POINT fPrevPos = { m_tInfo.fX, m_tInfo.fY };

	if (!m_bDown)
	{
		m_tInfo.fY += m_fSpeed;
		if (m_tInfo.fY >= 200.f)
			m_bDown = true;
	}
	
	if (m_eCurState == DEAD)
	{
		if (Anim_Dead())
		{
			return OBJ_DEAD;
		}
		return OBJ_NOEVENT;
	}

	if(m_eCurState==IDLE)
	{
		DWORD now = GetTickCount();

		if (m_dwMoveStart == 0)
			m_dwMoveStart = now;

		if (now - m_dwMoveStart >= 1000)
		{
			if (m_iTargetX < 0)
			{			
				const int minX = 100;
				const int maxX = WINCX - 100;
				const int minY = 200;
				const int maxY = 600; 

 				m_iTargetX = rand() % (maxX - minX + 1) + minX;
				m_iTargetY = rand() % (maxY - minY + 1) + minY;
			}
			  
			float dx = float(m_iTargetX) - m_tInfo.fX;
			float dy = float(m_iTargetY) - m_tInfo.fY;
			float dist = sqrtf(dx * dx + dy * dy);

			if (dist > 3.f) //3
			{
				m_tInfo.fX += (dx / dist) * m_fSpeed;
				m_tInfo.fY += (dy / dist) * m_fSpeed;
			}
			else
			{
				m_iTargetX = -1;
				m_iTargetY = -1;
				m_dwMoveStart = now;
			}
		}
		
		//if (m_fTime + 3000 < GetTickCount())
	//{
	//	if (m_tInfo.fX <= RandX && m_tInfo.fY <= RandY)
	//	{
	//		m_tInfo.fX += m_fSpeed;
	//		m_tInfo.fY += m_fSpeed;
	//	}
	//	else if (m_tInfo.fX <= RandX && m_tInfo.fY >= RandY)
	//	{
	//		m_tInfo.fX += m_fSpeed;
	//		m_fSpeed = -speed;
	//		m_tInfo.fY += m_fSpeed;
	//	}
	//	else if (m_tInfo.fX >= RandX && m_tInfo.fY <= RandY)
	//	{
	//		m_tInfo.fY += m_fSpeed;
	//		m_fSpeed = -speed;
	//		m_tInfo.fX -= m_fSpeed;
	//	}
	//	else
	//	{
	//		m_fSpeed = -speed;
	//		m_tInfo.fX += m_fSpeed;
	//		m_tInfo.fY += m_fSpeed;
	//	}
	//}
		if (m_fTime + 500 < GetTickCount())
		{
			float fWidth(0.f), fHeight(0.f);
			fWidth = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fX - m_tInfo.fX;
			fHeight = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fY - m_tInfo.fY;
			m_fAngle = atan2f(fHeight, fWidth);
			CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
			m_fTime = GetTickCount();
		}
		UFO_Move_Frame();
	}
	return OBJ_NOEVENT;
}

void CUFO::Late_Update()
{
}

void CUFO::Render(HDC hDC)
{
	if (m_eCurState == IDLE)
	{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	// 플레이어 렌더
	GdiTransparentBlt(hDC,												// 복사 받을 DC
		m_tRect.left,										// 복사 받을 공간의 LEFT	
		m_tRect.top,											// 복사 받을 공간의 TOP
		(int)m_tInfo.fCX,														// 복사 받을 공간의 가로 
		(int)m_tInfo.fCY,														// 복사 받을 공간의 세로 
		hMemDC,																			// 복사 할 DC
		m_tFrame.iStart * (int)m_tInfo.fCX,						// 복사할 이미지의 LEFT, TOP
		0,
		(INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
		(INT)m_tInfo.fCY,
		RGB(255, 0, 255));													// 제거할 색상
	}
	else
	{
		HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		// 플레이어 렌더
		GdiTransparentBlt(hDC,												// 복사 받을 DC
			m_tRect.left,																// 복사 받을 공간의 LEFT	
			m_tRect.top,																// 복사 받을 공간의 TOP
			(int)m_tInfo.fCX,														// 복사 받을 공간의 가로 
			(int)m_tInfo.fCY,														// 복사 받을 공간의 세로 
			hMemDC2,																		// 복사 할 DC
			m_tFrame.iStart * (int)m_tInfo.fCX,				// 복사할 이미지의 LEFT, TOP
			m_tFrame.iStart * (int)m_tInfo.fCY,
			(INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
			(INT)m_tInfo.fCY,
			RGB(255, 0, 255));													// 제거할 색상
	}
}

void CUFO::Release()
{
}

void CUFO::UFO_Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();


		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;
	}
}
bool CUFO::Anim_Dead()
{
	if (!m_bDead)
		return false;

	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStart > m_tFrame.iEnd)
			return true;
	}
	return false;
}

void CUFO::OnCollision(CObj* pOther)
{
	m_iHp--;

	if (m_eCurState == DEAD)
		return;

	CObjMgr::Get_Instance()->Get_Object(OBJ_STAGE_UI).front()->Add_Score(m_iScore);

	if(m_iHp<=0)
	{
		m_eCurState = DEAD;
		m_bDead = true;

		// 데드 스프라이트로 전환, 프레임 초기화
		m_pFrameKey = L"boom";

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 11;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount();
	}
}
