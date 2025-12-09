#pragma once

#include "CObj.h"
class CPlayer : public CObj
{
public:
	enum STATE { IDLE, RESPAWN, LEFT_MOVE, RIGHT_MOVE, ATTACK, DEAD, ST_END };

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

	float				m_fTime;
	float				m_fBulletTime;

	STATE				m_ePreState;
	STATE				m_eCurState;
};

