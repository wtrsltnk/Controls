// ToolBoxDlg.cpp: implementation of the ToolBoxDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "ToolBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ToolBox::ToolBoxDlg::ToolBoxDlg()
{
}

ToolBox::ToolBoxDlg::~ToolBoxDlg()
{
}

LRESULT ToolBox::ToolBoxDlg::Init(DWORD dwResource)
{
	this->dwResourceDlg = dwResource;
	return TRUE;
}

LRESULT ToolBox::ToolBoxDlg::Show(HWND hParent)
{
	this->hParent = hParent;

	return CustomDialog::ShowModalless(this->hInstance, this->hParent);
}

LRESULT ToolBox::ToolBoxDlg::Close()
{
	if (this->hDlg)
	{
		::EndDialog(this->hDlg, 0);
		this->hDlg = NULL;
		this->hParent = NULL;
	}
	return TRUE;
}

VOID ToolBox::ToolBoxDlg::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	case WM_COMMAND:
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_SCROLLDLGS:
	case 0x020A:
		{
			::SendMessage(this->hParent, uMsg, wParam, lParam);
			break;
		}
	}
	CustomDialog::DlgProc(uMsg, wParam, lParam);
}