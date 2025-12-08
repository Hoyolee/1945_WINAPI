#pragma once

#include "CObj.h"

class CObjMgr
{
private:
	CObjMgr();
	CObjMgr& operator=(CObjMgr&) = delete;
	CObjMgr(const CObj& rhs) = delete;
	~CObjMgr();

public:
	void	AddObject(OBJID eID, CObj* pObj = nullptr);
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	CObj* Get_Target(OBJID eID, CObj* pObj);
	void	Delete_ID(OBJID eID);

public:
	static CObjMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	list<CObj*>	Get_Object(int index) {

		return m_ObjList[index];

	}


private:
	list<CObj*>	m_ObjList[OBJ_END];

	static CObjMgr* m_pInstance;
};

