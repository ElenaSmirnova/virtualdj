// SamplesVisualization.h : main header file for the SamplesVisualization application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CSamplesVisualizationApp:
// See SamplesVisualization.cpp for the implementation of this class
//

class CSamplesVisualizationApp : public CWinApp
{
public:
	CSamplesVisualizationApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSamplesVisualizationApp theApp;