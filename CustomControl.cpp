// CustomControl.cpp: implementation of the CustomControl class.
//
//////////////////////////////////////////////////////////////////////

#include "CustomControl.h"

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////

LRESULT CALLBACK CustomControl::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CustomControl *pView = 0; 

	if( uMsg == WM_NCCREATE ) 
	{
		pView = reinterpret_cast<CustomControl *>( ((LPCREATESTRUCT)lParam)->lpCreateParams );
		if (pView)
			pView->hWnd = hWnd;
		
		::SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<long>( pView ));
	} 
	else
	{
		pView = reinterpret_cast<CustomControl *>( ::GetWindowLong(hWnd, GWL_USERDATA) );
	}

	if (pView)
		return pView->ObjectProc(uMsg, wParam, lParam); 

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CustomControl::CustomControl()
{
	this->hBackgroundColor = NULL;
	this->hCursor = NULL;
	this->hIcon = NULL;
	this->hSmallIcon = NULL;
}

CustomControl::~CustomControl()
{
}

BOOL CustomControl::InitCustomControl()
{
	WNDCLASSEX wsex;

	if (!::GetClassInfoEx(::GetModuleHandle(NULL), this->strControlClass, &wsex))
	{
		wsex.hbrBackground = this->hBackgroundColor;
		wsex.hCursor = this->hCursor;
		wsex.hIcon = this->hIcon;
		wsex.hIconSm = this->hSmallIcon;
		wsex.lpszClassName = this->strControlClass;

		wsex.cbClsExtra = 0;
		wsex.cbSize = sizeof(wsex);
		wsex.cbWndExtra = 0;
		wsex.hInstance = ::GetModuleHandle(NULL);
		wsex.lpfnWndProc = (WNDPROC)WindowProc;
		wsex.lpszMenuName = NULL;
		wsex.style = CS_HREDRAW | CS_VREDRAW;

		return ::RegisterClassEx(&wsex);
	}
	return TRUE;
}

BOOL CustomControl::Create(HWND hParent, DWORD dwId, DWORD style, DWORD exStyle)
{
	if (style != 0)
		this->dwStyle = style;

	if (exStyle != 0)
		this->dwExStyle = exStyle;
	
	this->hParent = hParent;
	this->dwId = dwId;
	
	if (InitCustomControl())
	{
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
			AddError("CustomControl::Create() - Aan maken van de window is niet gelukt");
		}
	}
	else
	{
		AddError("CustomControl::Create() - Registreren van de windowclass is niet gelukt");
	}
	return FALSE;
}

LRESULT CustomControl::ObjectProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(this->hWnd, uMsg, wParam, lParam);
}