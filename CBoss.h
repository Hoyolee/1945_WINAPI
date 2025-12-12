#pragma once
#include "CObj.h"
#include "CBullet.h"


class CBoss : public CObj
{
public:
  enum STATE { IDLE, MOVE ,ATTACK,PATTERN1 ,PATTERN2 ,DEAD, ST_END };

public:
  CBoss();
  virtual  ~CBoss();
  // CObj을(를) 통해 상속됨
public:
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
  void Motion_Change();
public:
  void Pattern1_Bullet_Rain();
  void Boss_Frame();
  void Sector_Pattern();

private:
  STATE				m_ePreState;
  STATE				m_eCurState;
  POINT       m_BossLocation;
};
