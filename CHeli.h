#pragma once
#include "CObj.h"
class CHeli : public CObj
{
public:
  CHeli();
  virtual ~CHeli();

  // CObj을(를) 통해 상속됨
public:
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
  void Heli_Move_Frame();
  void OnCollision(CObj* pOther) override;
private:
  STATE m_eCurState;
};

