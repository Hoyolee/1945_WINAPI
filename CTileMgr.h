#pragma once

#include "CTile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	void		Picking_Tile(POINT ptMouse, int iDrawID, int iOption);
	void		Save_Tile();
	void		Load_Tile();


public:
	static CTileMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTileMgr;

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


private:
	static CTileMgr* m_pInstance;

	vector<CObj*>	m_vecTile;

};

