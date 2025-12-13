#include "pch.h"
#include "CBoss.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CScrollMgr.h"
#include "CEnemyBullet.h"
#include "CAbstractFactory.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"
#include "CBigBullet.h"
#include "CEffect.h"
#include "CSoundMgr.h"

CBoss::CBoss():m_eCurState(DOWN),m_ePreState(ST_END)
{

}

CBoss::~CBoss()
{
	Release();
}

void CBoss::Initialize()
{
	m_tInfo.fCX = 188.f;
	m_tInfo.fCY = 186.f;

	m_fPatternTime = GetTickCount();

	m_biSDead = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Boss/enemyBoss.bmp", L"Boss");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Boss/bossExplosion.bmp", L"BossDead");

  m_fAngle = 0.f;
	
	m_iHp = 90.f;

	m_iScore = 1000;
	m_iPatternCount = 0;


	m_fDistance = 100.f;
	m_fSpeed = 5.f;

	m_fTime = GetTickCount();
	m_fBulletTime = GetTickCount();
	m_fPatternTime = GetTickCount();

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 19;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_bDead = false;
	m_bisTarget = false;
	m_bisShot = false;
}

int CBoss::Update()
{
	__super::Update_Rect();

	if (m_eCurState == DOWN)
		Down_State_Boss();

	if (m_eCurState == MOVE)
	{
		Move_State_Boss();
		if (m_fTime + 5500 < GetTickCount())
		{
			m_eCurState = PATTERN1;
			m_fTime = GetTickCount();
		}
	}

	if (m_eCurState == PATTERN1)
		Bullet_Rain();

	Boss_Frame();	

  return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{
}

void CBoss::Render(HDC hDC)
{
	if (m_eCurState == DOWN || m_eCurState == MOVE || m_eCurState == PATTERN1 ||
			m_eCurState == PATTERN2 || m_eCurState == PATTERN3)
	{
		MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
		LineTo(hDC, m_tPosin.x, m_tPosin.y);

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

void CBoss::Bullet_Rain()
{
	const float Speed = fabsf(m_fSpeed);
	float TargetX = 600.f;
	float SecTargetX = 25.f;

	const float spawnX = m_tInfo.fX;
	const float spawnY = m_tInfo.fY + (m_tInfo.fCY * 0.5f) + 5.f;

	const float downAngle = PI / 2.f;
	
	if(m_iPatternCount < 4)
	{
		if (!m_bisTarget)
		{
			if (m_tInfo.fX < TargetX)
			{
				m_tInfo.fX += m_fSpeed;
				if (m_fBulletTime + 150 <= GetTickCount())
				{
					CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET,
						CAbstractFactory<CBigBullet>::Create(spawnX, spawnY, downAngle, 7.0f));
					m_fBulletTime = GetTickCount();
				}
				if (m_tInfo.fX >= TargetX)
				{
					m_bisTarget = true;
					m_iPatternCount++;
				}
			}
		}

		if (m_bisTarget)
		{
			if (m_tInfo.fX >= SecTargetX)
			{
				m_tInfo.fX -= m_fSpeed;

				if (m_fBulletTime + 150 <= GetTickCount())
				{
					CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET,
						CAbstractFactory<CBigBullet>::Create(spawnX, spawnY, downAngle, 7.0f));
					m_fBulletTime = GetTickCount();
				}
			}
			else
			{
				m_bisTarget = false;
				m_iPatternCount++;
			}
		}
	}
	else
	{
		m_eCurState == MOVE;
		return;
	}
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

		case MOVE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 19;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();

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
	if (m_tInfo.fX < 300)
	{
		m_fSpeed = fabsf(m_fSpeed);
		m_tInfo.fX += m_fSpeed;
	}
	 if (m_tInfo.fX > 300)
	{
		m_fSpeed = fabsf(m_fSpeed);
		m_tInfo.fX -= m_fSpeed;
	}
	 	
	CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET, 
		CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
}

void CBoss::Move_State_Boss()
{
	if (m_tInfo.fY <= 230.f)
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
	//if (m_fBulletTime + 250 < GetTickCount())
	//{
	//	float fWidth(0.f), fHeight(0.f);
	//	fWidth = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fX - m_tInfo.fX;
	//	fHeight = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fY - m_tInfo.fY;
	//	m_fAngle = atan2f(fHeight, fWidth);
	//	CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
	//	m_fBulletTime = GetTickCount();
	//}
}

void CBoss::Down_State_Boss()
{
	if (m_tInfo.fY <= 230.f)
		m_tInfo.fY += m_fSpeed;
	if (m_tInfo.fY >= 200.f)
		m_eCurState = MOVE;
}

void CBoss::Pattern_Sector()
{
}

void CBoss::OnCollision(CObj* pOther)
{
	CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CEffect>::Create(m_tInfo.fX, m_tInfo.fY - 25));

	CSoundMgr::Get_Instance()->PlaySound(L"Hit.mp3", SOUND_EFFECT, 0.75f);
	
	--m_iHp;

	if (m_eCurState == DEAD)
		return;

	if (m_iHp <= 0)
	{
		m_eCurState = DEAD;
		m_biSDead = true;

		CObjMgr::Get_Instance()->Get_Object(OBJ_STAGE_UI).back()->Add_Score(m_iScore);

		CSoundMgr::Get_Instance()->PlaySound(L"Object_Dead.mp3", SOUND_EFFECT, 0.25f);

		m_pFrameKey = L"EnemyDead";

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 11;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount();
	}
}

bool CBoss::Anim_Dead()
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