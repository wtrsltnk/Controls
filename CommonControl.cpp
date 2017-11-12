// CommonControl.cpp: implementation of the CommonControl class.
//
//////////////////////////////////////////////////////////////////////

#include "CommonControl.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CommonControl::CommonControl()
{
}

CommonControl::~CommonControl()
{
}

BOOL CommonControl::Create(HWND hParent, DWORD dwId, DWORD style, DWORD exStyle)
{
	if (style != 0)
		this->dwStyle = style;

	if (exStyle != 0)
		this->dwExStyle = exStyle;
	
	this->hParent = hParent;
	this->dwId = dwId;

	InitCommonControls();
	
	this->hWnd = ::CreateWindowEx(	this->dwExStyle,
									this->strControlClass, 
									this->strTitle,
									this->dwStyle,
									CW_USEDEFAULT,
									CW_USEDEFAULT,
									CW_USEDEFAULT,
									CW_USEDEFAULT,
									this->hParent,
							(HMENU)	this->dwId,
									GetModuleHandle(NULL),
									this);

	if (this->hWnd)
	{
		::ShowWindow(this->hWnd, SW_SHOW);
		::UpdateWindow(this->hWnd);
		return TRUE;
	}
	else
	{
		AddError("CommonControl::Create() - Aan maken van de window is niet gelukt", 0);
	}
	
	return FALSE;
}