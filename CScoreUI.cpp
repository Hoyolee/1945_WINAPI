#include "pch.h"
#include "CScoreUI.h"

CScoreUI::CScoreUI()
{
}

CScoreUI::~CScoreUI()
{
	Release();
}

void CScoreUI::Initialize()
{
	m_iScore = 0;

	int nFonts = AddFontResourceExW(
		L"Font/strikers-1945-extended.otf"
		, FR_PRIVATE
		, 0);

}

int CScoreUI::Update()
{
	return 0;
}

void CScoreUI::Late_Update()
{
}

void CScoreUI::Render(HDC hDC)
{
	int size = 32;

	HFONT hFont = CreateFontW(
		32,                
		0, 0, 0,
		FW_BOLD,            
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH,
		L"Strikers 1945 Extended"   

	);

	HFONT old = (HFONT)SelectObject(hDC, hFont);

	COLORREF clr = RGB(255, 255, 255);

	SetTextColor(hDC, clr);
	SetBkMode(hDC, TRANSPARENT);

	WCHAR buf[64];
	wsprintfW(buf, L"SCORE: %d", m_iScore);
	TextOutW(hDC, 25, 50, buf, lstrlenW(buf));

	SelectObject(hDC, old);
	DeleteObject(hFont);
}

void CScoreUI::Release()
{
	RemoveFontResourceExW(L"Font/strikers-1945-extended.otf", FR_PRIVATE, 0);
}
