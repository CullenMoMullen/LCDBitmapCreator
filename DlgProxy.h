
// DlgProxy.h: header file
//

#pragma once

class CLCDBitmapCreatorDlg;


// LCDBitmapCreatorDlgAutoProxy command target

class CLCDBitmapCreatorDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CLCDBitmapCreatorDlgAutoProxy)

	CLCDBitmapCreatorDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CLCDBitmapCreatorDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CLCDBitmapCreatorDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLCDBitmapCreatorDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

