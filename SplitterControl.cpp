// SplitterControl.cpp: implementation of the SplitterControl class.
//
//////////////////////////////////////////////////////////////////////

#include "SplitterControl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SplitterControl::SplitterControl()
{
	this->dwStyle = WS_CHILD | WS_VISIBLE;
	this->strControlClass = "SplitterControl";
	
	this->hBackgroundColor = (HBRUSH)COLOR_WINDOW;
	this->hCursor = LoadCursor(NULL, IDC_SIZEWE);
	this->hIcon = LoadIcon(NULL, IDI_APPLICATION);
	this->hSmallIcon = this->hIcon;

	this->pControlA = NULL;
	this->pControlB = NULL;
	this->lSplitPosition = 200;
	this->lRightMargin = 200;
	this->lLeftMargin = 400;
}

SplitterControl::~SplitterControl()
{
}

LRESULT SplitterControl::ObjectProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int  oldy = -4;
	static BOOL fMoved = FALSE;
	static BOOL bDrag = FALSE;

	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			HDC hdc;
			RECT rect;

			pt.x = (short)LOWORD(lParam);  // horizontal position of cursor 
			pt.y = (short)HIWORD(lParam);

			GetWindowRect(this->hWnd, &rect);

			//convert the mouse coordinates relative to the top-left of
			//the window
			ClientToScreen(this->hWnd, &pt);
			pt.y -= rect.top;
			pt.x -= rect.left;

			//same for the window coordinates - make them relative to 0,0
			OffsetRect(&rect, -rect.left, -rect.top);

			if (pt.x > rect.right-this->lRightMargin)
				pt.x = rect.right-this->lRightMargin;

			if (pt.x < this->lLeftMargin)
				pt.x = this->lLeftMargin;

			bDrag = TRUE;

			SetCapture(this->hWnd);
	
			hdc = GetWindowDC(this->hWnd);
			DrawXorBar(hdc, pt.x - 2, 1, 4, rect.bottom-2);
			ReleaseDC(this->hWnd, hdc);

			oldy = pt.x;
			break;
		}
	case WM_MOUSEMOVE:
		{
			HDC hdc;
			RECT rect;

			POINT pt;

			if(bDrag == TRUE)
			{
				pt.x = (short)LOWORD(lParam);  // horizontal position of cursor 
				pt.y = (short)HIWORD(lParam);

				GetWindowRect(hWnd, &rect);

				ClientToScreen(hWnd, &pt);
				pt.y -= rect.top;
				pt.x -= rect.left;

				OffsetRect(&rect, -rect.left, -rect.top);

				if (pt.x > rect.right-this->lRightMargin)
					pt.x = rect.right-this->lRightMargin;

				if (pt.x < this->lLeftMargin)
					pt.x = this->lLeftMargin;

				if(pt.x != oldy && wParam & MK_LBUTTON)
				{
					hdc = GetWindowDC(hWnd);
					DrawXorBar(hdc, oldy - 2, 1, 4, rect.bottom-2);
					DrawXorBar(hdc, pt.x - 2, 1, 4, rect.bottom-2);
						
					ReleaseDC(hWnd, hdc);

					oldy = pt.x;
				}
			}
			break;
		}
	case WM_LBUTTONUP:
		{
			HDC hdc;
			RECT rect;

			POINT pt;
			pt.x = (short)LOWORD(lParam);  // horizontal position of cursor 
			pt.y = (short)HIWORD(lParam);

			if(bDrag == TRUE)
			{
				GetWindowRect(this->hWnd, &rect);

				ClientToScreen(this->hWnd, &pt);
				pt.y -= rect.top;
				pt.x -= rect.left;

				OffsetRect(&rect, -rect.left, -rect.top);

				if (pt.x > rect.right-this->lRightMargin)
					pt.x = rect.right-this->lRightMargin;

				if (pt.x < this->lLeftMargin)
					pt.x = this->lLeftMargin;

				hdc = GetWindowDC(this->hWnd);
				DrawXorBar(hdc, oldy - 2, 1, 4, rect.bottom-2);			
				ReleaseDC(this->hWnd, hdc);

				oldy = pt.x;

				bDrag = FALSE;

				//convert the splitter position back to screen coords.
				GetWindowRect(this->hWnd, &rect);
				pt.y += rect.top;
				pt.x += rect.left;

				//now convert into CLIENT coordinates
				ScreenToClient(this->hWnd, &pt);
				GetClientRect(this->hWnd, &rect);
				this->lSplitPosition = pt.x;

				//position the child controls
				Size(rect.right,rect.bottom);

				ReleaseCapture();
			}
			break;
		}
	}
	return CustomControl::ObjectProc(uMsg, wParam, lParam);
}

VOID SplitterControl::Size(UINT uWidth, UINT uHeight)
{
	this->uW = uWidth;
	this->uH = uHeight;
	
	if (this->pControlA != NULL)
	{
		this->pControlA->Move(0, 0);
		this->pControlA->Size(this->lSplitPosition - SPLITSIZE, uHeight);
	}

	if (this->pControlB != NULL)
	{
		this->pControlB->Move(this->lSplitPosition + SPLITSIZE, 0);
		this->pControlB->Size(uWidth - this->lSplitPosition - SPLITSIZE, uHeight);
	}
	CustomControl::Size(uWidth, uHeight);
}

VOID SplitterControl::SetControls(Control* a, Control* b)
{
	this->pControlA = a;
	this->pControlA->SetParent(this->hWnd);
	this->pControlA->Move(0, 0);
	
	this->pControlB = b;
	this->pControlB->SetParent(this->hWnd);
	this->pControlB->Move(this->lSplitPosition, 0);
}

VOID SplitterControl::SetMargin(UINT left, UINT right)
{
	this->lLeftMargin = left;
	if (this->lLeftMargin > this->lSplitPosition)
		this->lSplitPosition = this->lLeftMargin;

	this->lRightMargin = right;
	if (this->lRightMargin > this->lSplitPosition)
		this->lSplitPosition = this->lRightMargin;
}

VOID SplitterControl::DrawXorBar(HDC hdc, int x1, int y1, int width, int height)
{
	static WORD _dotPatternBmp[8] = { 0x00aa, 0x0055, 0x00aa, 0x0055, 
									0x00aa, 0x0055, 0x00aa, 0x0055};

	HBITMAP hbm;
	HBRUSH  hbr, hbrushOld;

	/* create a monochrome checkered pattern */
	hbm = CreateBitmap(8, 8, 1, 1, _dotPatternBmp);

	hbr = CreatePatternBrush(hbm);

	SetBrushOrgEx(hdc, x1, y1, 0);
	hbrushOld = (HBRUSH)SelectObject(hdc, hbr);

	/* draw the checkered rectangle to the screen */
	PatBlt(hdc, x1, y1, width, height, PATINVERT);

	SelectObject(hdc, hbrushOld);

	DeleteObject(hbr);
	DeleteObject(hbm);
}