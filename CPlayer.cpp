#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CScrollMgr.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CCollisionMgr.h"

// 플레이어가 사용하는 오브젝트 헤더
#include "CBomb.h"
//#include "CLife.h"

CPlayer::CPlayer() :  m_fTime(0.f)
, m_ePreState(ST_END), m_eCurState(IDLE)
, m_fBulletTime(0.f)
, m_iScore(0), m_iBombCount(3), m_iLife(3) 
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_iHp = 1;
	// 플레이어 크기 및 위치지정
	m_tInfo.fCX = 217.f / 7.0f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 4.f;

	m_fDistance = 100.f;
	m_fBulletTime = 0.5f;

	// 각종 아이템 개수
	m_iLifeCount = 3;
	m_iBombCount = 3;

	// 플레이어의 프레임 설정
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	Insert_Player_Animation();

	m_eCurState = IDLE;
	m_bDead = false;
}

int CPlayer::Update()
{
	__super::Update_Rect();

	if (m_eCurState == RESPAWN)
	{
    m_pFrameKey = L"Player_DOWN";
		Motion_Change();
		Player_Move_Frame();
		if(m_tInfo.fY > WINCY - 200.f)
			m_tInfo.fY -= m_fSpeed;
		else
		{
			m_eCurState = IDLE;
    }
	}

	if (m_eCurState == DEAD)
	{
    Motion_Change();
		Player_Move_Frame();
		m_iLifeCount--;
		if(m_iLifeCount <= 0)
		{ 
			if (Anim_Dead())
			{
				return OBJ_DEAD;
			}
		}
		else
		{
				m_tInfo.fY = WINCY + 100.f;
				m_tInfo.fX = WINCX / 2.f;
				m_eCurState = RESPAWN;
		}
		return OBJ_NOEVENT;
	}
	
	if (m_eCurState == IDLE || m_eCurState == LEFT_MOVE || m_eCurState == RIGHT_MOVE)
	{
		Motion_Change();

		Key_Input();

		Player_Move_Frame();
	}
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
#ifdef _DEBUG
	cout << m_eCurState << "\t " << m_iHp << "\t" << m_iLifeCount << endl;
#endif // _DEBUG
}

void CPlayer::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	// 플레이어 렌더
	GdiTransparentBlt(hDC,												// 복사 받을 DC
		m_tRect.left,										// 복사 받을 공간의 LEFT	
		m_tRect.top ,											// 복사 받을 공간의 TOP
		(int)m_tInfo.fCX,														// 복사 받을 공간의 가로 
		(int)m_tInfo.fCY,														// 복사 받을 공간의 세로 
		hMemDC,																			// 복사 할 DC
		m_tFrame.iStart * (int)m_tInfo.fCX,					// 복사할 이미지의 LEFT, TOP
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
		(INT)m_tInfo.fCY,
		RGB(255, 0, 255));													// 제거할 색상
}
void CPlayer::Key_Input()
{
	m_fBulletTime -= 1.0f / 15.f;
#pragma region 상좌우
	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_UP";
		m_eCurState = IDLE;
		if(GetAsyncKeyState(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			m_pFrameKey = L"Player_RIGHT";
			m_eCurState = RIGHT_MOVE;
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			m_pFrameKey = L"Player_LEFT";
			m_eCurState = LEFT_MOVE;
    }
	}
#pragma endregion
#pragma region 하좌우
	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = IDLE;

		if(GetAsyncKeyState(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			m_pFrameKey = L"Player_RIGHT";
			m_eCurState = RIGHT_MOVE;
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			m_pFrameKey = L"Player_LEFT";
			m_eCurState = LEFT_MOVE;
    }
	}
#pragma endregion
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_RIGHT";
		m_eCurState = RIGHT_MOVE;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"Player_LEFT";
		m_eCurState = LEFT_MOVE;
	}
	 if (GetAsyncKeyState(VK_SPACE))
	{
		 if (m_fBulletTime <= 0.f)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX,m_tInfo.fY));
			m_fBulletTime = 0.5f;
		}
	} 
	else
		m_eCurState = IDLE;
}
void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 3;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RESPAWN:
			m_tFrame.iStart = 3;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case LEFT_MOVE:
			m_tFrame.iStart = 3;
			m_tFrame.iEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RIGHT_MOVE:
			m_tFrame.iStart = 3;
			m_tFrame.iEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_pFrameKey = L"Player_Boom";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}

}
void CPlayer::Release()
{

}
void CPlayer::Player_Move_Frame()
{
	if (m_eCurState == IDLE || m_eCurState == RESPAWN)
	{
		m_tFrame.iStart = m_tFrame.iEnd;
	}
	if (m_eCurState == RIGHT_MOVE)
	{
		if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
		{
			++m_tFrame.iStart;
			m_tFrame.dwTime = GetTickCount();
		}

		if (m_tFrame.iStart > m_tFrame.iEnd)
		{
			m_tFrame.iStart = m_tFrame.iEnd;
		}
	}
	if (m_eCurState == LEFT_MOVE)
	{
		if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
		{
			--m_tFrame.iStart;
			m_tFrame.dwTime = GetTickCount();
		}	
		if (m_tFrame.iStart < m_tFrame.iEnd)
		{
			m_tFrame.iStart = m_tFrame.iEnd;
		}
	}
	if (m_eCurState == DEAD)
	{
		if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
		{
			++m_tFrame.iStart;
			m_tFrame.dwTime = GetTickCount();
    }
	}
}
void CPlayer::Offset()
{
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


}
void CPlayer::Insert_Player_Animation()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Player/playerMove.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Player/playerMove.bmp", L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Player/playerMove.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Player/playerMove.bmp", L"Player_RIGHT");
	//플레이어 피격 모션
	CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/Player/Resize.bmp", L"Player_Boom");
	m_pFrameKey = L"Player_DOWN";
}
void CPlayer::OnCollision(CObj* pOther)
{
	m_iHp--;

	if (m_eCurState == DEAD)
		return;

	if (m_iHp <= 0)
	{
		m_eCurState = DEAD;
		m_bDead = true;

		m_pFrameKey = L"Player_Boom";

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 7;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount();
	}

}
bool CPlayer::Anim_Dead()
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
