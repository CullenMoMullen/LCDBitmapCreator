#pragma once
#include <wincodec.h>

// CMyStatic

class CMyStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyStatic)

public:
	CMyStatic();
	virtual ~CMyStatic();
	CImage CurrentImg;
	virtual void DrawItem(LPDRAWITEMSTRUCT pdi/*lpDrawItemStruct*/);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()

private:
	COLORREF m_cl;
};


