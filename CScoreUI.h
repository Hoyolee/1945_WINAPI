#pragma once
#include "CObj.h"
class CScoreUI :  public CObj
{
public:
  CScoreUI();
  virtual ~CScoreUI();
  // CObj을(를) 통해 상속됨
public:
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
};

