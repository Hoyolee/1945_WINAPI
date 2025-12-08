#include "pch.h"
#include "CEnemy.h"
#include "CStealthEnemy.h"
#include "CBigEnemy.h"
#include "CEnemyBullet.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CCollisionMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"

CEnemy::CEnemy():m_eCurState(IDLE)
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Monster/enemy.bmp", L"Enemy1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Monster/deathExplosions_resized.bmp", L"EnemyDead");

	m_iHp = 1;

	// 플레이어 크기 및 위치지정
	m_tInfo.fCX			= 52.f;
	m_tInfo.fCY			= 34.f;

	m_fTime					= GetTickCount();

	m_fSpeed				= 7.0f;

	m_fDistance     = 100.f;
	m_fBulletTime   = 1.0f;

	m_pFrameKey = L"Enemy1";

	m_bDead = false;
}

int CEnemy::Update()
{
	__super::Update_Rect();
	
	POINT fPrevPos = {m_tInfo.fX, m_tInfo.fY};

	if(m_eCurState == IDLE)
		m_tInfo.fY += m_fSpeed;
	else
	{
		m_tInfo.fX = fPrevPos.x; m_tInfo.fY = fPrevPos.y;
	}
	
	if (m_eCurState == DEAD)
	{
		if (Anim_Dead())
		{
			return OBJ_DEAD;
		}
		return OBJ_NOEVENT;
	}

	Move_Frame();

  return OBJ_NOEVENT;
}

void CEnemy::Late_Update()
{
}

void CEnemy::Render(HDC hDC)
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
			0,					// 복사할 이미지의 LEFT, TOP
			0,
			(INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
			(INT)m_tInfo.fCY,
			RGB(255, 0, 255));													// 제거할 색상
	}
	if (m_eCurState == DEAD)
	{
		HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		// 플레이어 렌더
		GdiTransparentBlt(hDC,												// 복사 받을 DC
			m_tRect.left,																// 복사 받을 공간의 LEFT	
			m_tRect.top,																// 복사 받을 공간의 TOP
			(int)m_tInfo.fCX,														// 복사 받을 공간의 가로 
			(int)m_tInfo.fCY,														// 복사 받을 공간의 세로 
			hMemDC2,																		// 복사 할 DC
			m_tFrame.iStart * (int) m_tInfo.fCX,				// 복사할 이미지의 LEFT, TOP
			m_tFrame.iStart * (int) m_tInfo.fCY,
			(INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
			(INT)m_tInfo.fCY,
			RGB(255, 0, 255));													// 제거할 색상
	}
}

void CEnemy::Release()
{
}

void CEnemy::OnCollision(CObj* pOther)
{
	if (m_eCurState == DEAD)
		return;

	m_eCurState = DEAD;
	m_biSDead = true;

	// 데드 스프라이트로 전환, 프레임 초기화
	m_pFrameKey = L"EnemyDead";

	m_tFrame.iStart  = 0;
	m_tFrame.iEnd    = 11;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime  = GetTickCount();

	// 체력 감소 등 다른 처리(필요하면) 추가
}

bool CEnemy::Anim_Dead()
{
	if (!m_biSDead)
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