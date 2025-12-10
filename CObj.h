#pragma once

#include "Define.h"

class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	enum STATE {IDLE, DEAD};
	void		Set_Pos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}
	void		Set_Dead() { m_bDead = true; }
	bool		Get_Dead() { return m_bDead; }

	void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

	void		Set_Speed(float fSpeed) { m_fSpeed = fSpeed; }

	const RECT* Get_Rect() const { return &m_tRect; }
	const INFO* Get_Info() const { return &m_tInfo; }

	void		Set_PosX(float fX) { m_tInfo.fX += fX; }
	void		Set_PosY(float fY) { m_tInfo.fY += fY; }

	void		Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	int 		Get_HP()				{ return m_iHp; }
	void		Set_Hp(int iHp) { m_iHp = iHp; }

	float		Get_Angle() { return m_fAngle; }
	void		Set_Angle(float fAngle) { m_fAngle = fAngle; }

  void		Add_Score(int Score) { m_iScore += Score; }

public:
	virtual void	Initialize()		PURE;
	virtual int		Update()				PURE;
	virtual void	Late_Update()		PURE;
	virtual void	Render(HDC hDC)	PURE;
	virtual void	Release()				PURE;
	virtual void	OnCollision(CObj* pOther) { Set_Dead(); }
	//virtual void	Death_Animation() PURE;
protected:
	void		Update_Rect();
	void		Move_Frame();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;
	POINT				m_tPosin;

	float		m_fSpeed;
	float		m_fAngle;
	float		m_fDistance;
	float		m_fTime;
	bool		m_bDead;
	bool		m_bDameged;

	int			m_iHp;
	int			m_iAtk;
  int	    m_iScore;

	CObj* m_pTarget;
	const TCHAR* m_pFrameKey;
};

