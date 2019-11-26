
// LCDBitmapCreator.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "LCDBitmapCreator.h"
#include "LCDBitmapCreatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLCDBitmapCreatorApp

BEGIN_MESSAGE_MAP(CLCDBitmapCreatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLCDBitmapCreatorApp construction

CLCDBitmapCreatorApp::CLCDBitmapCreatorApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CLCDBitmapCreatorApp object

CLCDBitmapCreatorApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{0xf89b2e05,0x8fbe,0x4a73,{0x9e,0x06,0xbf,0x6e,0xdd,0x54,0x8d,0x0b}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CLCDBitmapCreatorApp initialization

BOOL CLCDBitmapCreatorApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES |
		ICC_USEREX_CLASSES | ICC_COOL_CLASSES |
		ICC_INTERNET_CLASSES | ICC_PAGESCROLLER_CLASS |
		ICC_NATIVEFNTCTL_CLASS | ICC_STANDARD_CLASSES | ICC_LINK_CLASS;
	InitCommonControlsEx(&InitCtrls);

	InitCommonControls();

	bool b = CWinApp::InitInstance();
	if (false == b) {
		AfxMessageBox(L"CWinApp::InitInstance()_FAILED");
		return FALSE;
	}
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(L"IDP_OLE_INIT_FAILED");
		return FALSE;
	}

	AfxEnableControlContainer();
	
	AfxInitRichEdit5();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("LCDBitmapCreator"));
	// Parse command line for automation or reg/unreg switches.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Register class factories via CoRegisterClassObject().
		COleTemplateServer::RegisterAll();
	}
	// App was launched with /Unregserver or /Unregister switch.  Remove
	// entries from the registry.
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// App was launched standalone or with other switches (e.g. /Register
	// or /Regserver).  Update registry entries, including typelibrary.
	else
	{
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
			return FALSE;
	}

	CLCDBitmapCreatorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
	}


#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CLCDBitmapCreatorApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
