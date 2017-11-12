// Control.h: interface for the Control class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CONTROL_H
#define CONTROL_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "ControlError.h"

#define MAX_TITLE 256

class CONTROLS_DLL Control : public ControlError
{
protected:
	HWND hWnd;
	HWND hParent;
	DWORD dwId;
	LPVOID lpTag;

	LPTSTR strControlClass;
	LPTSTR strTitle;
	DWORD dwStyle;
	DWORD dwExStyle;

protected:
	Control();
	virtual ~Control();

public:
	virtual BOOL Create(HWND hParent, DWORD dwId, DWORD style = 0, DWORD exStyle = 0) = 0;
	virtual VOID Size(UINT uWidth, UINT uHeight);
	virtual VOID Move(UINT uX, UINT uY);
	virtual VOID Kill();

	virtual UINT XPosition();
	virtual UINT YPosition();
	virtual UINT Width();
	virtual UINT Height();

	virtual VOID Show();
	virtual VOID Hide();

	virtual VOID Enable();
	virtual VOID Disable();

	virtual VOID SetParent(HWND hParent);
	virtual HWND GetParent();

	virtual VOID SetTag(LPVOID tag);
	virtual LPVOID GetTag();

	virtual VOID SetTitle(LPTSTR title);
	virtual LPTSTR GetTitle();

	virtual VOID SetFont(HFONT font);
	virtual HFONT GetFont();
	
};

#endif
