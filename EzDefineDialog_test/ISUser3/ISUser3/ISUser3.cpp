#include "stdafx.h"
#include "ISUser3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CISUser3App, CWinApp)
END_MESSAGE_MAP()

CISUser3App::CISUser3App()
{
}

CISUser3App theApp;

BOOL CISUser3App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
