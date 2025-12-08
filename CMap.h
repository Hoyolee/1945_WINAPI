#pragma once
#include "CObj.h"
class CMap : public CObj
{
public:
  CMap();
  virtual ~CMap();
  // CObj을(를) 통해 상속됨
public:
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
public:
  void Map_Scrolling();
  void Triangle();
private:
  int  iEnemyWave;
  bool isSpawned;
};

