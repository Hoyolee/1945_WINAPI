#pragma once

#define		WINCX 600
#define		WINCY 800

#define		TILECX 64
#define		TILECY 64

#define		TILEX 30
#define		TILEY 20

#define	  PI 3.141592f

#define		PURE = 0

#define		OBJ_NOEVENT 0
#define		OBJ_DEAD    1
#define		OBJ_DEADANI 2

#define		VK_MAX		0xff

#define		PI	3.141592f

enum OBJID { OBJ_MAIN_UI, OBJ_STAGE_UI, OBJ_LIFE_UI, OBJ_GAMEOVER_UI,
						 OBJ_PLAYER , OBJ_BULLET, 
						 OBJ_MONSTER, OBJ_MON_BULLET, 
						 OBJ_BUTTON, 
						 OBJ_BOSS   , OBJ_BOSSBULLET,
						 OBJ_END };
enum SCENEID {SC_MENU, SC_STAGE, SC_END };
enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };
enum RENDERID { BACKGROUND, GAMEOBJECT, EFFECT, UI, RENDER_END };
enum CHANNELID { SOUND_BGM, SOUND_EFFECT, MAXCHANNEL };


template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

typedef struct tagInfo
{
	float		fX, fY;	// 중점
	float		fCX, fCY; // 가로, 세로 길이

}INFO;


struct tagFinder
{
	tagFinder(const TCHAR* pTag) : m_pTag(pTag) {}

	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(Pair.first, m_pTag);
	}
	const TCHAR* m_pTag;
};


struct tagDeleteMap
{
	template<typename T>
	void operator()(T& pair)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
};

typedef struct tagFrame
{
	int		iStart;
	int		iEnd;
	int		iMotion;
	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;

extern HWND g_hWnd;