#include "pch.h"
#include "CScoreUI.h"

CScoreUI::CScoreUI()
{
}

CScoreUI::~CScoreUI()
{
}

void CScoreUI::Initialize()
{
	m_iScore = 0;
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
	HFONT hFont = CreateFontW(
		35, 0, 0, 0, 0, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
		VARIABLE_PITCH, NULL);


	HFONT old = (HFONT)SelectObject(hDC, hFont);

	WCHAR title[1024];
	int iTitle = 1946;

	wsprintfW(title, L"160기 화이팅");
	TextOutW(hDC, 25, 50, title, lstrlen(title));

}

void CScoreUI::Release()
{
}
