// StatusBar.cpp: implementation of the StatusBar class.
//
//////////////////////////////////////////////////////////////////////

#include "StatusBar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StatusBar::StatusBar()
{
	this->strControlClass = "";
	this->dwStyle = WS_CHILD | WS_VISIBLE;
	this->dwExStyle = WS_EX_WINDOWEDGE;

	this->uPartCount = 0;
}

StatusBar::~StatusBar()
{
}

BOOL StatusBar::Create(HWND hParent, DWORD dwId, DWORD style, DWORD exStyle)
{
	if (style != 0)
		this->dwStyle = style;

	if (exStyle != 0)
		this->dwExStyle = exStyle;
	
	this->hParent = hParent;
	this->dwId = dwId;
	
	InitCommonControls();
	
	this->hWnd = CreateStatusWindow(	this->dwStyle, 
										"", 
										this->hParent,
										this->dwId);
	if (this->hWnd != NULL)
	{
		::SendMessage(this->hWnd, SB_SETPARTS, this->uPartCount, (LPARAM)this->uParts);
		return TRUE;
	}

	return FALSE;
}

BOOL StatusBar::AddPart(LPTSTR strTitle, UINT uWidth)
{
	if (uWidth < 0)
	{
		this->uParts[this->uPartCount++] = -1;

		SendMessage(this->hWnd, SB_SETPARTS, this->uPartCount, (LPARAM)this->uParts);
		SendMessage(this->hWnd, SB_SETTEXT, (WPARAM)this->uPartCount-1|0, (LPARAM)strTitle);
	}
	else
	{
		for (UINT i = 0; i < this->uPartCount; i++)
			uWidth += this->uParts[i];

		this->uParts[this->uPartCount++] = uWidth;

		SendMessage(this->hWnd, SB_SETPARTS, this->uPartCount, (LPARAM)this->uParts);
		SendMessage(this->hWnd, SB_SETTEXT, (WPARAM)this->uPartCount-1|0, (LPARAM)strTitle);
	}
	return FALSE;
}

VOID StatusBar::SetPartTitle(UINT uPart, LPTSTR strTitle)
{
	::SendMessage(this->hWnd, SB_SETTEXT, (WPARAM)uPart-1|0, (LPARAM)strTitle);
}