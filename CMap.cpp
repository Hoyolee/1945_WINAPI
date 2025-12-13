#include "pch.h"
#include "CMap.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CEnemy.h"
#include "CBigEnemy.h"
#include "CStealthEnemy.h"
#include "CHeli.h"
#include "CUFO.h"
#include "CPlayer.h"
#include "CSoundMgr.h"
#include "CBoss.h"

CMap::CMap():iEnemyWave(0)
{
}

CMap::~CMap()
{
}

void CMap::Initialize()
{ 
  m_fTime = GetTickCount();
  m_fSpeed = 20.f;
  m_tInfo = { 300, 1300, (float)WINCX, 4288.f };
  isSpawned = false;
  CBmpMgr::Get_Instance()->Insert_Bmp(L"Image/backGround.bmp", L"Ground");
  CSoundMgr::Get_Instance()->PlaySound(L"gameStart.mp3", SOUND_BGM, 0.35f);
  // 캐릭터 생성
  CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(300, 600));
}

int CMap::Update()
{
  __super::Update_Rect();
  

  DWORD m_fSpawnTime = GetTickCount();
  float fElapsedTime = m_fSpawnTime - m_fTime;

  //if (!isSpawned && fElapsedTime >= 1000.f)
  //{
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(120.0f, -70.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(70.0f,   0.f ));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(170.0f,  0.f ));
  //  isSpawned = true;
  //  ++iEnemyWave;
  //}
  //
  //if (m_fTime + 1750 == m_fSpawnTime && iEnemyWave == 1)
  //{
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(460.0f, -70.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(410.0f, 0.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(510.0f, 0.f));
  //  ++iEnemyWave;
  //}
  //
  //if (m_fTime + 2750 == m_fSpawnTime && iEnemyWave == 2)
  //{
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(290.0f, -70.f ));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(240.0f,  0.f  ));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(340.0f,  0.f  ));
  //  ++iEnemyWave;
  //}
  //
  //if (m_fTime + 8000 == m_fSpawnTime && iEnemyWave == 3)
  //{
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CUFO>::Create(450.f, 0.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CUFO>::Create(150.f, 0.f));
  // 
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(120.0f, -70.f)); 
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(70.0f, 0.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(170.0f, 0.f));
  //  
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(460.0f, -70.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(410.0f, 0.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(510.0f, 0.f));
  //  ++iEnemyWave;
  //}
  //
  //if (m_fTime + 22000 == m_fSpawnTime && iEnemyWave == 4)
  //{
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CBigEnemy>::Create(300.f, 0.f));
  // 
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(460.0f, -70.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(410.0f, 0.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(510.0f, 0.f));
  //
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(120.0f, -70.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(70.0f, 0.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(170.0f, 0.f));
  //
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CHeli>::Create(300.f, 0.f));
  //  ++iEnemyWave;
  //}
  //
  //if(m_fTime + 20000 == m_fSpawnTime && iEnemyWave == 5)
  //{
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CBigEnemy>::Create(150.f, 0.f));
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CBigEnemy>::Create(450.f, 0.f));
  //
  //  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CHeli>::Create());
  //  ++iEnemyWave;
  //}

  if(m_fTime + 1500 == m_fSpawnTime&&iEnemyWave == 0)
  {
    CSoundMgr::Get_Instance()->StopAll();
    CObjMgr::Get_Instance()->AddObject(OBJ_BOSS, CAbstractFactory<CBoss>::Create(300.f, 0.f));
    CSoundMgr::Get_Instance()->PlayBGM(L"Boss_BGM.mp3", 0.35);
    ++iEnemyWave;
  }

  return OBJ_NOEVENT;
}

void CMap::Late_Update()
{
  Map_Scrolling();
}

void CMap::Render(HDC hDC)
{
  HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");

  int   iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
  int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

  GdiTransparentBlt(hDC,												// 복사 받을 DC
    m_tRect.left + iScrollX,										// 복사 받을 공간의 LEFT	
    m_tRect.top  - iScrollY,										// 복사 받을 공간의 TOP
    (int)m_tInfo.fCX,														// 복사 받을 공간의 가로 
    (int)m_tInfo.fCY,														// 복사 받을 공간의 세로 
    hGroundDC,																	// 복사 할 DC
    0,					                                // 복사할 이미지의 LEFT, TOP
    0,
    (INT)m_tInfo.fCX,														// 복사할 이미지의 가로, 세로
    (INT)m_tInfo.fCY,
    RGB(255, 0, 255));	// 제거할 색상
}

void CMap::Map_Scrolling()
{
  int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
  CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CMap::Release()
{
}

void CMap::Triangle()
{
  // 위
  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(120.0f, 100.f));
  // 아래
  // 왼쪽
  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(70.0f, 150.f));
  // 오른쪽
  CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(170.0f, 150.f));

  // 410 460 510
}