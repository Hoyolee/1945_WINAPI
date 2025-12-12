#pragma once

#include "CObj.h"

class CEffect : public CObj
{
public:
  enum STATE {PLAYING, DONE};

  CEffect();
  virtual ~CEffect();

public:
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
private:
  STATE m_eCurState;
  bool m_isEnd;

};

