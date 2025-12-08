#pragma once

#include"Define.h"
#include"CMainMenu.h"
#include"CStage.h"

class CSceneMgr
{
private:
	CSceneMgr();
	CSceneMgr& operator=(CSceneMgr&) = delete;
	CSceneMgr(const CSceneMgr& rhs) = delete;
	~CSceneMgr();

public:
	void		Scene_Change(SCENEID eID);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	static CSceneMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneMgr;

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
	static CSceneMgr* m_pInstance;
	CScene* m_pScene;

	SCENEID		m_ePreScene;
	SCENEID		m_eCurScene;
};

