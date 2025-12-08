#pragma once

#include "CObj.h"

class CCollisionMgr
{
public:
	static void Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);

	static void Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);
	static bool	Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);

	static bool Check_Circle(CObj* pDst, CObj* pSrc);
	static void Collision_Circle(list<CObj*> _Dst, list<CObj*> _Src);
};

