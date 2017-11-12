// Window.h: interface for the Window class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BASISSCHERM_H
#define BASISSCHERM_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Controls.h"
#include "ControlError.h"

class CONTROLS_DLL Window : public ControlError
{
private:
	static LRESULT StaticProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HINSTANCE hInstance;
	HWND hWnd;
	HMENU hMenu;
	HICON  hIcon;
	HCURSOR hCursor;
	HACCEL hAccelTable;

	UINT uCreationX;
	UINT uCreationY;
	UINT uCreationHeight;
	UINT uCreationWidth;
 	DWORD dwCreationFlags;
	DWORD dwWindowStyle;
	DWORD dwExWindowStyle;
	LPTSTR strWindowTitle;
	LPTSTR strWindowClass;
	HBRUSH hbrWindowColor;

	LRESULT InitWindowClass();
	LRESULT ClearWindowClass();
	virtual LRESULT MessageProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	Window();
	virtual ~Window();

	LRESULT Create(HINSTANCE hInstance);
	LRESULT RunToClose();

};

#endif
