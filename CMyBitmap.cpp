#include "pch.h"
#include "CMyBitmap.h"

CMyBitmap::CMyBitmap()
{
}

CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::Load_Bmp(const TCHAR* pFilePath)
{
	HDC	hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : 매개 변수로 전달한 DC와 호환되는 DC를 생성하여 반환

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL, // 프로그램의 인스턴스 핸들
		pFilePath, // 파일의 경로
		IMAGE_BITMAP,	// 파일의 유형(이미지 파일 형식)
		0, 0,		// 읽어들이는 파일의 가로, 세로 사이즈
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	//	LR_LOADFROMFILE : 파일로부터 이미지를 불러들임
	//	LR_CREATEDIBSECTION : 읽어온 파일을 dib 형태로 변환


//SelectObject : 준비한 DC의 GDI 오브젝트로 불러온 비트맵을 선택
// - GDI 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환
	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
