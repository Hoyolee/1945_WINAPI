#pragma once

#include "Define.h"

class CKeyMgr
{
private:
	CKeyMgr();
	CKeyMgr& operator=(CKeyMgr&) = delete;
	CKeyMgr(const CKeyMgr& rhs) = delete;
	~CKeyMgr();

public:
	void		Update();

	bool		Key_Pressing(int _iKey);

	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);
	void		Release();


public:
	static CKeyMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyMgr;

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
	static CKeyMgr* m_pInstance;
	bool		m_bKeyState[VK_MAX];
};

