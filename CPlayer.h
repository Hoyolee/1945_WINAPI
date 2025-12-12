#pragma once

#include "CObj.h"
class CPlayer : public CObj
{
public:
	enum STATE { IDLE, RESPAWN, LEFT_MOVE, RIGHT_MOVE, ATTACK, DEAD, INVINCIBLE,GAMEOVER, ST_END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObj* pOther) override;

  bool isOnCollision();

	// 무적 설정 (ms)
	void Set_Invincible(DWORD dwDurationMs);

public:
  int  Get_LifeCount() { return m_iLifeCount; }
  void Set_LifeCount(int iLifeCount) { m_iLifeCount = iLifeCount; }

  int Get_BombCount() { return m_iBombCount; }
  void Set_BombCount(int iBombCount) { m_iBombCount = iBombCount; }

  STATE Get_State() { return m_eCurState; }

public:
	void Offset();
	bool Anim_Dead();
private:
	void	Key_Input();
	void	Motion_Change();
	void	Player_Move_Frame();
	void  Insert_Player_Animation();

private:
	int					m_iScore;
	int					m_iLife;
	int					m_iBombCount;
	int					m_iLifeCount;
	int         m_iCount;
	int					m_iCounting;

	bool				m_bIsLifeUI ;

	float				m_fTime;
	float				m_fBulletTime;

	STATE				m_ePreState;
	STATE				m_eCurState;
};

