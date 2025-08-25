#include "stdafx.h"
#include "ISUser3.h"
#include <windows.h>
#include "Resource.h"
#include <afxwin.h>

static int g_result = 0;

INT_PTR CALLBACK CheckBoxDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:        

		CheckDlgButton(hDlg, IDC_RADIO1, BST_CHECKED);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED)
                g_result = 1;
            else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
                g_result = 2;
            else
                g_result = -1;

            EndDialog(hDlg, IDOK);
            return TRUE;

        case IDC_BUTTON2:
            g_result = -1;
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) int __stdcall ShowCheckBoxDialog(HWND hParent)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    g_result = 0;

    DialogBoxParam(
        AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDD_MAINDLG),
        hParent,
        CheckBoxDlgProc,
        0
    );

    return g_result;
}
