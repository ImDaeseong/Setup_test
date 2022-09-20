#include "pch.h"
#include "framework.h"
#include "VrFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char* GetFileVersion(char* pFilePath)
{
	DWORD dwSize;
	DWORD dwMajorVer, dwMinorVer;
	CString strVersion = _T("");
	CString strFilePath = CString(pFilePath);

	dwSize = GetFileVersionInfoSize(strFilePath, 0);
	if (dwSize)
	{
		TCHAR* buffer = new TCHAR[dwSize];
		memset(buffer, 0, dwSize);

		if (GetFileVersionInfo(strFilePath, 0, dwSize, buffer))
		{
			VS_FIXEDFILEINFO* pInfo;

			UINT uLen;
			BOOL bResult;

			bResult = VerQueryValue(buffer, _T("\\"), (void**)&pInfo, &uLen);
			if (bResult)
			{
				dwMajorVer = pInfo->dwFileVersionMS; // 주버전
				dwMinorVer = pInfo->dwFileVersionLS; // 보조버전

				DWORD dwMinorVer1, dwMinorVer2, dwMajorVer1, dwMajorVer2;

				dwMajorVer1 = (dwMajorVer / 65536);
				dwMajorVer2 = (dwMajorVer % 65536);
				dwMinorVer1 = (dwMinorVer / 65536);
				dwMinorVer2 = (dwMinorVer % 65536);
				strVersion.Format(_T("%d.%d.%d.%d"), dwMajorVer1, dwMajorVer2, dwMinorVer1, dwMinorVer2);
			}
		}
		delete[] buffer;
	}

	char* szVersion = (LPSTR)(LPCTSTR)strVersion;
	return szVersion;
}

char* GetNowTime()
{
	COleDateTime tNow = COleDateTime::GetCurrentTime();

	CString strTime;
	strTime.Format(_T("%.4d%.2d%.2d%.2d%.2d%.2d"), tNow.GetYear(), tNow.GetMonth(), tNow.GetDay(), tNow.GetHour(), tNow.GetMinute(), tNow.GetSecond());

	char* szTime = (LPSTR)(LPCTSTR)strTime;
	return szTime;
}

char* GetUrlInfo(char* szUrl)
{
	CString strUrl = CString(szUrl);
	CInternetSession session;
	CInternetFile* pFile = NULL;

	try
	{
		pFile = (CInternetFile*)session.OpenURL(strUrl, 1, INTERNET_FLAG_TRANSFER_ASCII | INTERNET_FLAG_DONT_CACHE, NULL, 0);
	}
	catch (CInternetException* pEx)
	{
		pFile = NULL;
		pEx->Delete();
		return false;
	}

	CString strContent = _T("");

	if (pFile)
	{
		CString strData;
		pFile->SetReadBufferSize(4096);
		while (pFile->ReadString(strData))
		{
			strContent = strContent + CA2W((LPCSTR)strData.GetBuffer(), CP_UTF8) + _T("\r\n");
		}
		pFile->Close();
		session.Close();
	}

	char* szContent = (LPSTR)(LPCTSTR)strContent;
	return szContent;
}
