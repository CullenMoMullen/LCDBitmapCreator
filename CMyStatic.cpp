// CMyStatic.cpp : implementation file
//

#include "pch.h"
#include "LCDBitmapCreator.h"
#include "CMyStatic.h"

// CMyStatic

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

CMyStatic::CMyStatic()
{
	m_cl = RGB(0, 0, 255);
	
}

CMyStatic::~CMyStatic()
{
}

BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMyStatic message handlers
void CMyStatic::DrawItem(LPDRAWITEMSTRUCT pdi)
{

	// TODO:  Add your code to draw the specified item
	CDC* pDC = CDC::FromHandle(pdi->hDC);
	if (!CurrentImg.IsNull()) {
		
		
		HBITMAP hbmp = HBITMAP(CurrentImg);

		HDC    dcMem = ::CreateCompatibleDC(pdi->hDC);
		HBITMAP hOld = (HBITMAP)::SelectObject(dcMem, hbmp);

		BITMAP bitmap = { 0 };
		::GetObject(hbmp, sizeof(BITMAP), &bitmap);
		//::BitBlt(pdi->hDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, dcMem, 0, 0, SRCCOPY);
		int destWidth = pdi->rcItem.right - pdi->rcItem.left;
		int destHeight = pdi->rcItem.bottom - pdi->rcItem.top;
		int sourceWidth = bitmap.bmWidth;
		int sourceHeight = bitmap.bmHeight;




		int s = max(sourceWidth, sourceHeight);
		int w = destWidth * sourceWidth / s;
		int h = destHeight * sourceHeight / s;
		int x = (destWidth - w) / 2;
		int y = (destHeight - h) / 2;

		RECT clRect{ 0 };
		this->GetClientRect(&clRect);
		HBRUSH br =  ::CreateSolidBrush(RGB(0x33, 0x33, 0x33));
		HBRUSH oldbr = (HBRUSH) ::SelectObject(pdi->hDC, br);
		::FillRect(pdi->hDC, &clRect, br);
		::SelectObject(pdi->hDC, oldbr);
		
		
		::SetStretchBltMode(pdi->hDC, STRETCH_DELETESCANS);
		::StretchBlt(pdi->hDC, 0, 0, w, h, dcMem, 0, 0, sourceWidth, sourceHeight, SRCCOPY);
		//HPEN pn = ::CreatePen(PS_DASH, 1, RGB(100, 0, 0));
		//::SelectObject(pdi->hDC, pn);
		//::(pdi->hDC, 0, 8);
		//::LineTo(pdi->hDC, w - 1, 8);
		//::MoveTo(pdi->hDC, 0, 16);
		//::LineTo(pdi->hDC, w - 1, 16);
		::SelectObject(dcMem, hOld);
		::DeleteObject(br);
		::ReleaseDC(HWND(pDC->GetWindow()), dcMem);
		::ReleaseDC(HWND(pDC->GetWindow()), pdi->hDC);
	}
	else {
		RECT clRect{ 0 };
		this->GetClientRect(&clRect);
		HBRUSH br = ::CreateSolidBrush(RGB(0x33, 0x33, 0x33));
		HBRUSH oldbr = (HBRUSH) ::SelectObject(pdi->hDC, br);
		::FillRect(pdi->hDC, &clRect, br);
		::SelectObject(pdi->hDC, oldbr);
		::DeleteObject(br);
	}
}

void CMyStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	static COLORREF cl[] =
	{
		RGB(0, 0, 255),
		RGB(0, 255, 0),
		RGB(255, 0, 0)
	};
	static int idx = 0;
	m_cl = cl[idx];
	idx++;
	idx %= 3;
	Invalidate();
	//CStatic::OnLButtonUp(nFlags, point);
}
