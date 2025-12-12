#pragma once
#include "CObj.h"
#include "CBullet.h"


class CBoss : public CObj
{
public:
  enum STATE { DOWN, MOVE ,PATTERN1 ,PATTERN2 ,PATTERN3 , DEAD, ST_END };

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

  void OnCollision(CObj* pOther);
  bool Anim_Dead();

public:
  void Bullet_Rain();
  void Boss_Frame();
  void Sector_Pattern();
  void Move_State_Boss();
  void Down_State_Boss();
  void Pattern_Sector();

private:

  float       m_fBulletTime;
  float       m_fPatternTime;

  bool        m_bIsTarget;
  bool        m_bisShot;
  bool        m_biSDead;

  STATE				m_ePreState;
  STATE				m_eCurState;
  POINT       m_BossLocation;

  std::vector<int>  m_vPattern;
};