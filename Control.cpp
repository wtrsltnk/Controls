// Control.cpp: implementation of the Control class.
//
//////////////////////////////////////////////////////////////////////

#include "Control.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Control::Control()
{
	this->hWnd = NULL;
	this->hParent = NULL;
	this->dwId = 0;
	this->lpTag = NULL;

	this->strControlClass = "Control";
	this->strTitle = "Title";
	this->dwStyle = WS_CHILD | WS_VISIBLE;
	this->dwExStyle = WS_EX_WINDOWEDGE;
}

Control::~Control()
{
}

VOID Control::SetParent(HWND hParent)
{
	::SetParent(this->hWnd, hParent);
}

HWND Control::GetParent()
{
	return ::GetParent(this->hWnd);
}

VOID Control::Size(UINT uWidth, UINT uHeight)
{
	::SetWindowPos(this->hWnd, NULL, 0, 0, uWidth, uHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

VOID Control::Move(UINT uX, UINT uY)
{
	::SetWindowPos(this->hWnd, NULL, uX, uY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

UINT Control::XPosition()
{
	RECT rc;

	::GetClientRect(this->hWnd, &rc);

	return rc.left;
}

UINT Control::YPosition()
{
	RECT rc;

	::GetClientRect(this->hWnd, &rc);

	return rc.top;
}

UINT Control::Width()
{
	RECT rc;

	::GetClientRect(this->hWnd, &rc);

	return (rc.right - rc.left);
}

UINT Control::Height()
{
	RECT rc;

	::GetClientRect(this->hWnd, &rc);

	return (rc.bottom - rc.top);
}

VOID Control::Kill()
{
	::DestroyWindow(this->hWnd);
}

VOID Control::Show()
{
	::ShowWindow(this->hWnd, SW_SHOW);
}

VOID Control::Hide()
{
	::ShowWindow(this->hWnd, SW_HIDE);
}

VOID Control::Enable()
{
	::EnableWindow(this->hWnd, TRUE);
}

VOID Control::Disable()
{
	::EnableWindow(this->hWnd, FALSE);
}

VOID Control::SetTag(LPVOID tag)
{
	this->lpTag = tag;
}

LPVOID Control::GetTag()
{
	return this->lpTag;
}

VOID Control::SetTitle(LPTSTR title)
{
	this->strTitle = title;

	::SetWindowText(this->hWnd, this->strTitle);
}

LPTSTR Control::GetTitle()
{
	::GetWindowText(this->hWnd, this->strTitle, MAX_TITLE);

	return this->strTitle;
}

VOID Control::SetFont(HFONT font)
{
	::SendMessage(this->hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
}

HFONT Control::GetFont()
{
	return (HFONT)SendMessage(this->hWnd, WM_GETFONT, 0, 0);
}