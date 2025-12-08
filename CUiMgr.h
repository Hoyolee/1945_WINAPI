#pragma once

#include "Define.h"

class CUIMgr 
{
public:
  CUIMgr();
	CUIMgr& operator=(CUIMgr&) = delete;
	CUIMgr(const CUIMgr& rhs) = delete;
  ~CUIMgr();
public:
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();
public:
	static 
		CUIMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CUIMgr;

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
  static CUIMgr* m_pInstance;
};

