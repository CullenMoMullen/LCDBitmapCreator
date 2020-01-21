#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

//#include "targetver.h"


///////////////////////////////
#ifndef WINVER				// Lassen Sie die Verwendung von Features spezifisch für Windows 95 und Windows NT 4 oder später zu.
#define WINVER 0x0501		// Ändern Sie den entsprechenden Wert, um auf Windows 98 und mindestens Windows 2000 abzuzielen.
#endif

#ifndef _WIN32_WINNT		// Lassen Sie die Verwendung von Features spezifisch für Windows NT 4 oder später zu.
#define _WIN32_WINNT _WIN32_WINNT_WINXP		// Ändern Sie den entsprechenden Wert, um auf Windows 98 und mindestens Windows 2000 abzuzielen.
#endif						

#ifndef _WIN32_WINDOWS		// Lassen Sie die Verwendung von Features spezifisch für Windows 98 oder später zu.
#define _WIN32_WINDOWS 0x0410 // Ändern Sie den entsprechenden Wert, um auf mindestens Windows Me abzuzielen.
#endif

#ifndef _WIN32_IE			// Lassen Sie die Verwendung von Features spezifisch für IE 4.0 oder später zu.
#define _WIN32_IE 0x0400	// Ändern Sie den entsprechenden Wert, um auf mindestens IE 5.0 abzuzielen.
#endif
////////////////////////////

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes



//#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
//#endif
//#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
//#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


