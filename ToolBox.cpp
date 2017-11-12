// ToolBox.cpp: implementation of the ToolBox class.
//
//////////////////////////////////////////////////////////////////////

#include "ToolBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ToolBox::ToolBox()
{
	this->strControlClass		 = "ToolBox";
	this->dwStyle				 = WS_CHILD;
	this->pNextToolBox			 = NULL;
	this->hBackgroundColor		 = (HBRUSH)COLOR_WINDOW;
	this->nXPosition			 = 0;
	this->nYPosition			 = 0;
}

ToolBox::~ToolBox()
{
}

VOID ToolBox::Initialize(DWORD id, DWORD resource)
{
	this->dwId = id;

	if (resource != 0)
		this->dwResource = resource;

	this->dialog.Init(this->dwResource);
}

VOID ToolBox::SetTitle(LPTSTR title)
{
	Control::SetTitle(title);
}


DWORD ToolBox::GetID()
{
	return this->dwId;
}


LRESULT ToolBox::Show(HWND hParent)
{
	this->hParent = hParent;

	return CustomControl::Create(this->hParent, this->dwId);
}

LRESULT ToolBox::Close()
{
	if (this->hWnd)
	{
		::DestroyWindow(this->hWnd);
		this->hWnd = NULL;
		this->hParent = NULL;
		this->dialog.Close();
		this->button.Kill();
	}
	return TRUE;
}

UINT ToolBox::MoveToolBox(UINT x, UINT y, UINT width)
{
	this->nXPosition = x;
	this->nYPosition = y;

	::MoveWindow(this->hWnd, x, y, width, this->nCurrentHeight, true);

	if (this->pNextToolBox)
		return this->pNextToolBox->MoveToolBox(x, y + this->nCurrentHeight + 4, width);

	return y + this->nCurrentHeight;
}

LRESULT ToolBox::ObjectProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_CREATE:
		{
			this->dialog.Show(this->hWnd);
			this->nOriginalHeight = this->dialog.Height();
			this->nCurrentHeight = this->nOriginalHeight;

			this->button.Create(this->hWnd, IDM_TITLEBUTTON);
			this->button.SetTitle((LPTSTR)this->strTitle);
			break;
		}

	case WM_PAINT:
		{
			HPEN hGray, hWhite;
			HPEN tmpPen;
			HBRUSH tmpBrush;
			PAINTSTRUCT ps;

			hGray = ::CreatePen(PS_SOLID, 1, RGB(128,128,128));
			hWhite = ::CreatePen(PS_SOLID, 1, RGB(255,255,255));
			::BeginPaint(this->hWnd, &ps);

			tmpBrush = (HBRUSH)::SelectObject(ps.hdc, ::GetStockObject(HOLLOW_BRUSH));
			tmpPen = (HPEN)::SelectObject(ps.hdc, hWhite);

			::Rectangle(ps.hdc, 1, 10, Width(), this->nCurrentHeight);

			::SelectObject(ps.hdc, hGray);
			::Rectangle(ps.hdc, 0, 9, Width()-1, this->nCurrentHeight-1);

			::SelectObject(ps.hdc, tmpBrush);
			::SelectObject(ps.hdc, tmpPen);

			::EndPaint(this->hWnd, &ps);

			::DeleteObject(hGray);
			::DeleteObject(hWhite);
			break;
		}

	case WM_SIZE:
		{
			this->dialog.Resize(4, 20, Width() - 8, this->nCurrentHeight - 24);
			this->button.Move(4, 0);
			this->button.Size(Width() - 8, 17);
			break;
		}

	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_SCROLLDLGS:
	case 0x020A:
		{
			::SendMessage(this->hParent, uMsg, wParam, lParam);
			break;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDM_TITLEBUTTON:
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						{
							if (this->nCurrentHeight == 22)
							{
								this->nCurrentHeight = this->nOriginalHeight;
							}
							else
							{
								this->nOriginalHeight = this->nCurrentHeight;
								this->nCurrentHeight = 22;
							}
							MoveToolBox(this->nXPosition, this->nYPosition, Width());
							::SendMessage(this->hParent, WM_SCROLLDLGS, 0, 0);
							::SetFocus(this->hParent);
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
	return CustomControl::ObjectProc(uMsg, wParam, lParam);	
}

