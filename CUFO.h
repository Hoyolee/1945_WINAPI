#pragma once
#include "CObj.h"
class CUFO : public CObj
{
public:
  CUFO();
  virtual ~CUFO();

  enum STATE { IDLE, DEAD };

  // CObj을(를) 통해 상속됨
public:
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
  void UFO_Move_Frame();
private:
  bool    m_bDown;        
  int     m_iTargetX;     
  int     m_iTargetY;     
  DWORD   m_dwMoveStart; 
  STATE m_eCurState;

};

