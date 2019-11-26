
// DlgProxy.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "LCDBitmapCreator.h"
#include "DlgProxy.h"
#include "LCDBitmapCreatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2DlgAutoProxy

IMPLEMENT_DYNCREATE(CLCDBitmapCreatorDlgAutoProxy, CCmdTarget)

CLCDBitmapCreatorDlgAutoProxy::CLCDBitmapCreatorDlgAutoProxy()
{
	EnableAutomation();

	// To keep the application running as long as an automation
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CLCDBitmapCreatorDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CLCDBitmapCreatorDlg)))
		{
			m_pDialog = reinterpret_cast<CLCDBitmapCreatorDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CLCDBitmapCreatorDlgAutoProxy::~CLCDBitmapCreatorDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CLCDBitmapCreatorDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CLCDBitmapCreatorDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLCDBitmapCreatorDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_ILCDBitmapCreator to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {77099c85-7691-42d3-97b6-caf25e2211f5}
static const IID IID_ILCDBitmapCreator =
{0x77099c85,0x7691,0x42d3,{0x97,0xb6,0xca,0xf2,0x5e,0x22,0x11,0xf5}};

BEGIN_INTERFACE_MAP(CLCDBitmapCreatorDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CLCDBitmapCreatorDlgAutoProxy, IID_ILCDBitmapCreator, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in pch.h of this project
// {cd87f916-60b9-472d-8ef4-cce030eb61c6}
IMPLEMENT_OLECREATE2(CLCDBitmapCreatorDlgAutoProxy, "LCDBitmapCreator.Application", 0xcd87f916,0x60b9,0x472d,0x8e,0xf4,0xcc,0xe0,0x30,0xeb,0x61,0xc6)


// CLCDBitmapCreatorDlgAutoProxy message handlers
