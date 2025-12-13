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

public:
  // 애니메이션 관련 함수
  void Motion_Change();
  void Boss_Frame();
  
public:
  // 충돌 관련 함수
  void OnCollision(CObj* pOther);
  bool Anim_Dead();

public:
  // 패턴 관련 함수
  void Bullet_Rain();
  void Sector_Pattern();
  void Move_State_Boss();
  void Down_State_Boss();
  void Whip_Pattern();
  void Select_Pattern();
private:
  
  int         m_iPatternCount;
  
  float       m_fBulletTime;
  float       m_fPatternTime;
  float       m_fWhipTime;

  bool        m_bisTarget;
  bool        m_bisShot;
  bool        m_biSDead;
  bool        m_bisArrive;

  STATE				m_ePreState;
  STATE				m_eCurState;
  STATE       m_eCurPattern;     

  size_t      m_iPatternIndex;

  std::vector<STATE>  m_vPattern;
};