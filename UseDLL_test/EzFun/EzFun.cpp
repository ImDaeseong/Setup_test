#include "pch.h"
#include "framework.h"
#include "EzFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
BEGIN_MESSAGE_MAP(CEzFunApp, CWinApp)
END_MESSAGE_MAP()

CEzFunApp::CEzFunApp()
{
}

CEzFunApp theApp;

BOOL CEzFunApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}
*/

bool openWebPage(char* szUrl)
{
    BOOL bNoError = TRUE;
    CInternetSession session;
    CInternetFile* file = NULL;

    try
    {
        file = (CInternetFile*)session.OpenURL(szUrl, 1, INTERNET_FLAG_TRANSFER_ASCII | INTERNET_FLAG_DONT_CACHE, NULL, 0);
    }
    catch (CInternetException* pEx)
    {
        TCHAR lpszError[256];
        pEx->GetErrorMessage(lpszError, 256, NULL);
        return false;
    }

    CString szContent = _T("");

    if (file)
    {
        file->SetReadBufferSize(4096);

        CString data;

        for (;;)
        {
            if (!file->ReadString(data))
                break;

            if (szContent.GetLength() > 0)
                szContent += "\n";
            szContent += data;
        }
        data.ReleaseBuffer();
        file->Close();
    }
    else
    {
        return false;
    }

    return true;
}


bool ConnectWebPage(char* szUrl)
{
    if (openWebPage(szUrl))
    {
        Sleep(1000);
        return true;
    }

    return false;
}

bool ShellExecuteUrl(char* szUrl)
{
    ShellExecute(NULL, _T("open"), szUrl, NULL, NULL, SW_SHOW);
    return true;
}
