#pragma once

#include "CObj.h"

class CEnemy : public CObj
{
public:
  CEnemy();
  virtual ~CEnemy();

  enum STATE {IDLE, DEAD};

  // CObj을(를) 통해 상속됨
public:
  void Initialize()     override;
  int  Update()         override;
  void Late_Update()    override;
  void Render(HDC hDC)  override;
  void Release()        override;

  // Related with Animation
  bool Anim_Dead();
  void OnCollision(CObj* pOther) override;
  void Enemy_Move_Frame();

private:
  float m_fBulletTime;
  bool  m_biSDead;
  STATE m_eCurState;
};