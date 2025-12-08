#pragma once

#include "CObj.h"
class CPlayer : public CObj
{
public:
	enum STATE { IDLE, LEFT_MOVE, RIGHT_MOVE , ATTACK, DEAD, ST_END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:
	void Offset();
private:
	void	Key_Input();
	void	Motion_Change();
	void	Player_Move_Frame();
	void Insert_Player_Animation();
private:

	int					m_iScore;
	int					m_iBombCount;
	int					m_iLife;

	float				m_fTime;

	STATE				m_ePreState;
	STATE				m_eCurState;

	float				m_fBulletTime;
};

