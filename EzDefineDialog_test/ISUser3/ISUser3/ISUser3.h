#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

class CISUser3App : public CWinApp
{
public:
	CISUser3App();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
