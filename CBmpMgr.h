#pragma once

#include "CMyBitmap.h"

class CBmpMgr
{
private:
	CBmpMgr();
	CBmpMgr& operator=(CBmpMgr&) = delete;
	CBmpMgr(const CBmpMgr& rhs) = delete;
	~CBmpMgr();

public:
	HDC			Find_Image(const TCHAR* pImgKey);

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void		Release();

public:
	static CBmpMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBmpMgr;

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
	static CBmpMgr* m_pInstance;

	map<const TCHAR*, CMyBitmap*>		m_mapBit;

};

