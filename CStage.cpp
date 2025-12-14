#include "pch.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CAbstractFactory.h"
#include "CEnemy.h"
#include "CCollisionMgr.h"
#include "CScrollMgr.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CTileMgr.h"
#include "CBombUI.h"
#include "CScoreUI.h"
#include "CGameOver.h"
#include "CSoundMgr.h"
#include "CBoss.h"
#include "CGameClear.h"

float sVolume = 0.25f;
CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CSoundMgr::Get_Instance()->PlaySound(L"gameStart.mp3", SOUND_EFFECT, 0.1f);

	// 배경 이미지
	CObjMgr::Get_Instance()->AddObject(OBJ_STAGE_UI, CAbstractFactory<CMap>::Create(300, 0));

	// UI 생성
  CObjMgr::Get_Instance()->AddObject(OBJ_STAGE_UI, CAbstractFactory<CBombUI>::Create(30,WINCY-50));
  CObjMgr::Get_Instance()->AddObject(OBJ_STAGE_UI, CAbstractFactory<CBombUI>::Create(60,WINCY-50));
	
	CObjMgr::Get_Instance()->AddObject(OBJ_LIFE_UI, CAbstractFactory<CLifeUI>::Create(50, 100));
	CObjMgr::Get_Instance()->AddObject(OBJ_LIFE_UI, CAbstractFactory<CLifeUI>::Create(100, 100));
	CObjMgr::Get_Instance()->AddObject(OBJ_LIFE_UI, CAbstractFactory<CLifeUI>::Create(150, 100));

	CObjMgr::Get_Instance()->AddObject(OBJ_STAGE_UI, CAbstractFactory<CScoreUI>::Create());	
}

int CStage::Update()
{
	CObjMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CStage::Late_Update()
{
	// 플레이어 몬스터 충돌 시 둘 다 삭제
	CCollisionMgr::Collision_Circle(
		CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER),
		CObjMgr::Get_Instance()->Get_Object(OBJ_BOSSBULLET)
	);

	CCollisionMgr::Collision_Circle(
		CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER),
		CObjMgr::Get_Instance()->Get_Object(OBJ_MON_BULLET)
	);
	
	CCollisionMgr::Collision_Circle(
		CObjMgr::Get_Instance()->Get_Object(OBJ_MONSTER),
		CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER)
	);

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER),
		CObjMgr::Get_Instance()->Get_Object(OBJ_MONSTER)
	);

	// 총알 관련 충돌 처리
	CCollisionMgr::Collision_Circle(
		CObjMgr::Get_Instance()->Get_Object(OBJ_BULLET),
		CObjMgr::Get_Instance()->Get_Object(OBJ_MONSTER)
	);

	CCollisionMgr::Collision_Circle(
		CObjMgr::Get_Instance()->Get_Object(OBJ_BOSS),
		CObjMgr::Get_Instance()->Get_Object(OBJ_BULLET)
	);
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CStage::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
  CObjMgr::Get_Instance()->Delete_ID(OBJ_STAGE_UI);
  CObjMgr::Get_Instance()->Delete_ID(OBJ_BOSS);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_LIFE_UI);
	CSoundMgr::Get_Instance()->Destroy_Instance();
}
