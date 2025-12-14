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
#include "CGameClear.h"

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

  m_fAngle = 30.f;
	
	m_iHp = 5.f;
	m_iScore = 1000;
	m_iPatternCount = 0;
	m_iPatternIndex = 0;
	m_iSectorCount = 0;
	m_iPattern = 0;
	m_iWhipCount = 0;
	

	m_fDistance = 100.f;
	m_fSpeed = 5.f;

	m_fTime = GetTickCount();
	m_fBulletTime = GetTickCount();
	m_fPatternTime = GetTickCount();
	m_fWhipTime = GetTickCount();
		
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
		if (m_fTime + 3500 < GetTickCount() && m_iPattern == 0)
		{
			m_eCurState = PATTERN1;
			m_fTime = GetTickCount();
			m_iPattern++;
		}
		if (m_fTime + 7500 < GetTickCount() && m_iPattern == 1)
		{
			m_eCurState = PATTERN2;
			m_bisTarget = false;
			m_iSectorCount = 0;
			m_fTime = GetTickCount();
			m_iPattern++;
		}
		if (m_fTime + 10500 < GetTickCount() && m_iPattern == 2)
		{
			m_bisTarget = false;
			m_eCurState = PATTERN3;
			m_fTime = GetTickCount();
		}
	}

	if (m_eCurState == PATTERN1)
		Bullet_Rain();

	if (m_eCurState == PATTERN2)
		Sector_Pattern();

	if (m_eCurState == PATTERN3)
		Whip_Pattern();

	if (m_eCurState == DEAD)
	{
		if (Anim_Dead())
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_GAMEOVER_UI,
				CAbstractFactory<CGameClear>::Create(300.f,400.f));
			return OBJ_DEAD;
		}
		return OBJ_NOEVENT;
	}

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
void CBoss::Whip_Pattern()
{
	const float TargetX = 300.f;
	float speed = fabsf(m_fSpeed);

	const float spawnX = m_tInfo.fX;
	const float spawnY = m_tInfo.fY + (m_tInfo.fCY * 0.5f);
	if (m_iWhipCount < 5)
	{
		if (!m_bisTarget)
		{
			if (m_tInfo.fX < TargetX)
				m_tInfo.fX += speed;
			else if (m_tInfo.fX > TargetX)
				m_tInfo.fX -= speed;
			else
				m_bisTarget = true;
		}
		if (m_bisTarget)
		{
			float fWidth(0.f), fHeight(0.f);
			fWidth = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fX - m_tInfo.fX;
			fHeight = CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER).front()->Get_Info()->fY - m_tInfo.fY;
			float playerAngle = atan2f(fHeight, fWidth);

			if (m_fBulletTime + 25 < GetTickCount())
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET,
					CAbstractFactory <CBigBullet>::Create(spawnX, spawnY, playerAngle, 4.0f));
				m_fBulletTime = GetTickCount();
			}
			if(m_fWhipTime + 3000 < GetTickCount())
			{
				m_fWhipTime = GetTickCount();
				m_iWhipCount++;
			}
		}
	}
	else
	{
		m_eCurState = MOVE;
		return;
	}

}
void CBoss::Bullet_Rain()
{

	const float Speed = fabsf(m_fSpeed);
	float TargetX = 600.f;
	float SecTargetX = 25.f;

	const float spawnX = m_tInfo.fX;
	const float spawnY = m_tInfo.fY + (m_tInfo.fCY * 0.5f) + 5.f;

	const float downAngle = PI / 2.f;

	if (m_iPatternCount < 7)
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
		m_eCurState = MOVE;
		m_iPatternCount = 0;
		return;
	}
}
void CBoss::Sector_Pattern()
{
	float TargetX = 300.f;
	const float speed = fabsf(m_fSpeed);

	const float spawnX = m_tInfo.fX;
	const float spawnY = m_tInfo.fY + (m_tInfo.fCY * 0.5f) + 5.f;
	
	if (m_iSectorCount < 7)
	{
		if (!m_bisTarget)
		{
			if (m_tInfo.fX < TargetX)
				m_tInfo.fX += speed;
			else if (m_tInfo.fX > TargetX)
				m_tInfo.fX -= speed;
			else
				m_bisTarget = true;
		}
		if (m_bisTarget)
		{
			if (m_fBulletTime + 1000 <= GetTickCount())
			{
				for (int i = 0; i < 33; i++)
				{
					CObjMgr::Get_Instance()->AddObject(OBJ_MON_BULLET,
						CAbstractFactory<CBigBullet>::Create(spawnX, spawnY, m_fAngle));
					m_fAngle += (i + 3);
				}
				m_fBulletTime = GetTickCount();
				m_iSectorCount++;
			}
		}
	}
	else
	{
		m_eCurState = MOVE;
		return;
	}
}
void CBoss::Select_Pattern()
{
	m_vPattern.push_back(PATTERN1);
	m_vPattern.push_back(PATTERN2);
	m_vPattern.push_back(PATTERN3);

	random_shuffle(m_vPattern.begin(), m_vPattern.end());

	m_eCurPattern = m_vPattern[m_iPatternIndex];

	switch (m_eCurPattern)
	{
	case PATTERN1:
		m_eCurState = PATTERN1;
		break;

	case PATTERN2:
		m_eCurState = PATTERN2;
		break;

	case PATTERN3:
		m_eCurState = PATTERN3;
		break;
	}

}
void CBoss::OnCollision(CObj* pOther)
{
	CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CEffect>::Create(m_tInfo.fX, m_tInfo.fY - 75));

	CSoundMgr::Get_Instance()->PlaySound(L"Hit.mp3", SOUND_EFFECT, 0.5f);
	
	--m_iHp;

	if (m_eCurState == DEAD)
		return;

	if (m_iHp <= 0)
	{
		m_eCurState = DEAD;
		m_biSDead = true;

		CObjMgr::Get_Instance()->Get_Object(OBJ_STAGE_UI).back()->Add_Score(m_iScore);

		CSoundMgr::Get_Instance()->PlaySound(L"Object_Dead.mp3", SOUND_EFFECT, 0.35f);

		m_pFrameKey = L"EnemyDead";

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 11;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 250;
		m_tFrame.dwTime = GetTickCount();
	}
}