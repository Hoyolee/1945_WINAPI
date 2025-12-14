#pragma once
#include "CObj.h"
class CGameClear :  public CObj
{
public:
  CGameClear();
  virtual ~CGameClear();

public:
  // CObj을(를) 통해 상속됨
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
};

