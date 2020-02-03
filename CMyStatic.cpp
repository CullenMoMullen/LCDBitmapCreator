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
	HDC dc = pdi->hDC;
	CDC* pDC = CDC::FromHandle(dc);
	if (!CurrentImg.IsNull()) {
		
		
		HBITMAP hbmp = HBITMAP(CurrentImg);
		
		HDC    dcMem = ::CreateCompatibleDC(dc);
		HBITMAP hOld = (HBITMAP)::SelectObject(dcMem, hbmp);

		BITMAP bitmap = { 0 };
		::GetObject(hbmp, sizeof(BITMAP), &bitmap);

		RECT clRect{ 0 };
		this->GetClientRect(&clRect);
		
		//::BitBlt(pdi->hDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, dcMem, 0, 0, SRCCOPY);
		int destWidth = clRect.right - clRect.left;
		int destHeight = clRect.bottom - clRect.top;
		int sourceWidth = bitmap.bmWidth;
		int sourceHeight = bitmap.bmHeight;

		int maxDimension = max(sourceWidth, sourceHeight);
		int stretchWidth = destWidth * sourceWidth / maxDimension;
		int stretchHeight = destHeight * sourceHeight / maxDimension;
		int centerX = (destWidth - stretchWidth) / 2;
		int centerY = (destHeight - stretchHeight) / 2;

		HBRUSH oobBrush = ::CreateSolidBrush(GetSysColor(COLOR_INFOBK));
		HBRUSH oldbr = (HBRUSH) ::SelectObject(dc, oobBrush);

		RECT oobRect = { 0 };
		if (centerX > 0) {
			oobRect.top = 0;
			oobRect.left = 0;
			oobRect.bottom = clRect.bottom;
			oobRect.right = centerX;
			::FillRect(dc, &oobRect, oobBrush);
			oobRect.left = centerX + stretchWidth;
			oobRect.right = clRect.right;
			::FillRect(dc, &oobRect, oobBrush);
		}
		if (centerY > 0) {
			oobRect.top = 0;
			oobRect.left = 0;
			oobRect.bottom = centerY;
			oobRect.right = clRect.right;
			::FillRect(dc, &oobRect, oobBrush);
			oobRect.top = centerY + stretchHeight;
			oobRect.bottom = clRect.bottom;
			::FillRect(dc, &oobRect, oobBrush);
		}

		HBRUSH br = ::CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
		clRect.top = centerY;
		clRect.left = centerX;
		clRect.bottom = centerY + stretchHeight;
		clRect.right = centerX + stretchWidth;
		::SelectObject(dc, br);
		::DeleteObject(oobBrush);
		::FillRect(dc, &clRect, br);
		::SelectObject(dc, oldbr);
		
		::SetStretchBltMode(dc, STRETCH_DELETESCANS);
		::StretchBlt(dc, centerX, centerY, stretchWidth, stretchHeight, dcMem, 0, 0, sourceWidth, sourceHeight, SRCCOPY);
		
		/*
		HPEN pn = ::CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN) ::SelectObject(dc, pn);
		
		for (int i = 0; i < stretchHeight; i+= ((stretchHeight-1)/sourceHeight)) {
			::MoveToEx(dc, centerX, centerY+i, NULL);
			::LineTo(dc,centerX+stretchWidth,centerY+i);
		}
		for (int i = 0; i < stretchWidth; i+= ((stretchWidth-1)/sourceWidth)) {
			::MoveToEx(dc, centerX+i, centerY, NULL);
			::LineTo(dc, centerX+i, centerY+stretchHeight);
		}
		
		::SelectObject(dc, oldPen);
		::DeleteObject(pn);
		*/

		::SelectObject(dcMem, hOld);
		::DeleteObject(br);
		::ReleaseDC(HWND(pDC->GetWindow()), dcMem);
		::ReleaseDC(HWND(pDC->GetWindow()), pdi->hDC);
	}
	else {
		RECT clRect{ 0 };
		this->GetClientRect(&clRect);
		HBRUSH br = ::CreateSolidBrush(D3DCOLOR_RGBA(192,192,192,125));
		HBRUSH oldbr = (HBRUSH) ::SelectObject(dc, br);
		::FillRect(dc, &clRect, br);
		::SelectObject(dc, oldbr);
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
