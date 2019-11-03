
// LCDBitmapCreator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CLCDBitmapCreatorApp:
// See LCDBitmapCreator.cpp for the implementation of this class
//

class CLCDBitmapCreatorApp : public CWinApp
{
public:
	CLCDBitmapCreatorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

extern CLCDBitmapCreatorApp theApp;
