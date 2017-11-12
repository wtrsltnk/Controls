// Window.cpp: implementation of the Window class.
//
//////////////////////////////////////////////////////////////////////

#include "Window.h"

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////

LRESULT Window::StaticProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* scherm = NULL;

	if (uMsg == WM_NCCREATE)
	{
		scherm = reinterpret_cast <Window*> (((LPCREATESTRUCT)lParam)->lpCreateParams);
		
		::SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast <long> (scherm));

		if (scherm != NULL)
		{
			scherm->hWnd = hWnd;
		}
	}
	else
	{
		scherm = reinterpret_cast <Window*> (::GetWindowLong(hWnd, GWL_USERDATA));
	}

	if (scherm != NULL)
	{
		return scherm->MessageProc(uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Window::Window()
{
	this->hInstance				 = NULL;
	this->hWnd					 = NULL;
	this->hMenu					 = NULL;
	this->hIcon					 = NULL;
	this->hCursor				 = LoadCursor(NULL, IDC_ARROW);
	this->hAccelTable			 = NULL;
	this->hbrWindowColor		 = (HBRUSH)COLOR_WINDOW + 0;

	this->uCreationX			 = CW_USEDEFAULT;
	this->uCreationY			 = CW_USEDEFAULT;
	this->uCreationHeight		 = CW_USEDEFAULT;
	this->uCreationWidth		 = CW_USEDEFAULT;
 	this->dwCreationFlags		 = SW_SHOW;
	this->dwWindowStyle			 = WS_OVERLAPPEDWINDOW;
	this->dwExWindowStyle		 = WS_EX_WINDOWEDGE;
	this->strWindowTitle		 = "Hoofd Window";
	this->strWindowClass		 = "Window";
}

Window::~Window()
{
	ClearWindowClass();
}

LRESULT Window::Create(HINSTANCE hInstance)
{
	this->hInstance = hInstance;

	if (InitWindowClass() == TRUE)
	{
		this->hWnd = ::CreateWindowEx(	this->dwExWindowStyle,
											this->strWindowClass,
											this->strWindowTitle, 
											this->dwWindowStyle,
											this->uCreationX,
											this->uCreationY,
											this->uCreationWidth,
											this->uCreationHeight, 
											NULL,
											this->hMenu,
											this->hInstance,
											(VOID*)this);

		if (this->hWnd != NULL)
		{
			::ShowWindow(this->hWnd, this->dwCreationFlags);

			::UpdateWindow(this->hWnd);

			return TRUE;
		}
		else
		{
			AddError("Aan maken van de window is niet gelukt");
		}
	}
	else
	{
		AddError("Registreren van de windowclass is niet gelukt");
	}
	return FALSE;
}

LRESULT Window::RunToClose()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, this->hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return msg.wParam;
}

LRESULT Window::InitWindowClass()
{
	WNDCLASSEX wcex;

	if (::GetClassInfoEx(this->hInstance, this->strWindowClass, &wcex) == NULL)
	{
		wcex.cbSize			= sizeof(WNDCLASSEX); 
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= (WNDPROC) Window::StaticProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.lpszMenuName	= NULL;
		wcex.hIconSm		= NULL;

		wcex.hInstance		= this->hInstance;
		wcex.hIcon			= this->hIcon;
		wcex.hbrBackground	= this->hbrWindowColor;
		wcex.lpszClassName	= this->strWindowClass;
		wcex.hCursor		= this->hCursor;

		if (::RegisterClassEx(&wcex) == NULL)
		{
			return FALSE;
		}
	}

	return TRUE;
}

LRESULT Window::ClearWindowClass()
{
	if (::UnregisterClass(this->strWindowClass, this->hInstance) == NULL)
	{
		return FALSE;
	}
	return TRUE;
}

LRESULT Window::MessageProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(this->hWnd, uMsg, wParam, lParam);
}
