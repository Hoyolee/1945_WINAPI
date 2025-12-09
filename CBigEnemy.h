#pragma once
#include "CObj.h"
class CBigEnemy : public CObj
{
public:
  CBigEnemy();
  virtual ~CBigEnemy();

  enum STATE { IDLE, DEAD };

public:
  // CObj을(를) 통해 상속됨
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
  // Related with Animation
  bool Anim_Dead();
  void OnCollision(CObj* pOther) override;
  void Enemy_Move_Frame();

private:
  bool  m_bisDead;
  STATE m_eCurState;
};

