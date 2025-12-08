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

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	float m_fSpeed = 5.f;

	// 배경 이미지
	CObjMgr::Get_Instance()->AddObject(OBJ_STAGE_UI, CAbstractFactory<CMap>::Create(300, 0));
	
	// 캐릭터 생성
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(300,600));

	// UI 생성
  CObjMgr::Get_Instance()->AddObject(OBJ_STAGE_UI, CAbstractFactory<CBombUI>::Create(30,WINCY-50));
	CObjMgr::Get_Instance()->AddObject(OBJ_STAGE_UI, CAbstractFactory<CLifeUI>::Create(50, 100));
	
	// 보스 생성
	//CObjMgr::Get_Instance()->AddObject(OBJ_BOSS, CAbstractFactory<CBoss>::Create(300.f,200.f));	
	//CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER, CAbstractFactory<CEnemy>::Create(300.f, 100.f));
}

int CStage::Update()
{
	CObjMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CStage::Late_Update()
{
	CCollisionMgr::Collision_Circle(
		CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER),
		CObjMgr::Get_Instance()->Get_Object(OBJ_BOSSBULLET)
	);

	CCollisionMgr::Collision_Circle(
		CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER),
		CObjMgr::Get_Instance()->Get_Object(OBJ_MON_BULLET)
	);
	
	CCollisionMgr::Collision_Circle(
		CObjMgr::Get_Instance()->Get_Object(OBJ_BULLET),
		CObjMgr::Get_Instance()->Get_Object(OBJ_MONSTER)
	);

	CCollisionMgr::Collision_Circle(
		CObjMgr::Get_Instance()->Get_Object(OBJ_BOSS),
		CObjMgr::Get_Instance()->Get_Object(OBJ_BULLET)
	);

	CCollisionMgr::Collision_Rect(
		CObjMgr::Get_Instance()->Get_Object(OBJ_PLAYER),
		CObjMgr::Get_Instance()->Get_Object(OBJ_MONSTER)
	);

	// Collision_Circle에서는 콜리션 반응 있으면 바로 Set_Dead()처리 하는데, 	
	// 잡몹은 상관 없으나, 보스 관련해서는 HP가 닳게 설정해야함.

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
}
