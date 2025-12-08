#pragma once

#include"CScene.h"
#include"CStart.h"
class CMainMenu : public CScene
{
public:
   CMainMenu();
  ~CMainMenu();
public:
  void Initialize() override;
  int   Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
private:
  CStart* pStart;
};

