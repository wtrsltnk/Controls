// ToolBoxControl.cpp: implementation of the ToolBoxControl class.
//
//////////////////////////////////////////////////////////////////////

#include "ToolBoxControl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ToolBoxControl::ToolBoxControl()
{
	this->strControlClass		 = "ToolBoxContainer";
	this->dwStyle				 = WS_CHILD;
	this->dwExStyle				 = WS_EX_STATICEDGE;
	this->hBackgroundColor		 = (HBRUSH)COLOR_WINDOW;
	this->hHand					 = ::LoadCursor(GetModuleHandle(DLL_FILE_NAME), MAKEINTRESOURCE(IDC_HAND));
	this->bDrag				 	 = false;
	this->nScrollAmount			 = 0;
	this->nTotalHeight			 = 0;
	this->nScrollBarWidth		 = 4;
}

ToolBoxControl::~ToolBoxControl()
{
}

LRESULT ToolBoxControl::Scroll(UINT amount)
{
	UINT oldamount = this->nScrollAmount;

	if (this->rcClientArea.bottom - this->rcClientArea.top < (int)this->layer.Height())
	{
		int newAmount = this->nScrollAmount + amount;
		int maxAmount = this->rcClientArea.bottom - this->rcClientArea.top - this->layer.Height();

		if (newAmount <= 0)
		{
			if (newAmount <= maxAmount)
				this->nScrollAmount = maxAmount;
			else
				this->nScrollAmount = newAmount;
		}
		else
		{
			if (this->nScrollAmount != 0)
				this->nScrollAmount = 0;
		}
	}
	else
	{
		if (this->nScrollAmount != 0)
			this->nScrollAmount = 0;
	}

	if (oldamount != (UINT)this->nScrollAmount)
	{
		this->layer.Move(this->layer.XPosition(), 2 + this->rcClientArea.top + this->nScrollAmount);
	}

	RECT rc = { Width()-this->nScrollBarWidth, 0, Width(), Height() };
	::InvalidateRect(this->hWnd, &rc, FALSE);
	return TRUE;
}

void ToolBoxControl::UpdateBoxes()
{
	if (this->headToolBox.pNextToolBox)
	{
		this->nTotalHeight = this->headToolBox.pNextToolBox->MoveToolBox(2, 2, this->layer.Width()-2) + 2;
		this->layer.Size(this->layer.Width(), this->nTotalHeight);
	}
}

LRESULT ToolBoxControl::ObjectProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT pt = {0};
	switch (uMsg)
	{
	case WM_CREATE:
		{
			layer.Create(this->hWnd, 5);
			break;
		}

	case WM_SIZE:
		{
			::GetClientRect(this->hWnd, &this->rcClientArea);
			this->layer.Size(LOWORD(lParam) - this->nScrollBarWidth, this->layer.Height());

			this->layer.Move(0, this->nScrollAmount);
			UpdateBoxes();
			Scroll(0);
			break;
		}

	case 0x020A:
		{
			Scroll((short) HIWORD(wParam) / 4);
			break;
		}

	case WM_LBUTTONDOWN:
		{
			::GetCursorPos(&pt);
			::SetCapture(this->hWnd);
			::SetFocus(this->hWnd);

			::SetCursor(this->hHand);

			this->bDrag = true;
			break;
		}

	case WM_MOUSEMOVE:
		{
			if (this->bDrag)
			{
				POINT newpt;

				::GetCursorPos(&newpt);

				if (newpt.y - pt.y != 0)
				{
					if (Scroll(newpt.y - pt.y))
					{
						::GetCursorPos(&pt);
					}
				}
			}
			break;
		}

	case WM_LBUTTONUP:
		{
			::ReleaseCapture();

			this->bDrag = false;
			break;
		}

	case WM_SCROLLDLGS:
		{
			UpdateBoxes();
			Scroll(0);
			break;
		}

	case WM_PAINT:
		{
			int cntrl_height = this->rcClientArea.bottom;
			int ttl_height = this->nTotalHeight;
			float tmp = (float)cntrl_height / ttl_height;
			int scrllbr_height = (int)(tmp * (cntrl_height));
			int scrll_amount = (int)(tmp * this->nScrollAmount);
			
			HPEN hBackgroundPen;
			HBRUSH hBackgroundBrush;
			HPEN hForegroundPen;
			HBRUSH hForegroundBrush;

			HPEN tmpPen;
			HBRUSH tmpBrush;

			PAINTSTRUCT ps;

			hBackgroundPen = ::CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			hBackgroundBrush = ::CreateSolidBrush(RGB(0, 0, 0));
			hForegroundPen = ::CreatePen(PS_SOLID, 1, RGB(110, 110, 110));
			hForegroundBrush = ::CreateSolidBrush(RGB(110, 110, 110));

			::BeginPaint(this->hWnd, &ps);

			tmpBrush = (HBRUSH)::SelectObject(ps.hdc, hBackgroundPen);
			tmpPen = (HPEN)::SelectObject(ps.hdc, hBackgroundBrush);

			::Rectangle(ps.hdc, Width()-this->nScrollBarWidth, 0, Width(), Height());

			::SelectObject(ps.hdc, hForegroundPen);
			::SelectObject(ps.hdc, hForegroundBrush);

			::Rectangle(ps.hdc, Width()-this->nScrollBarWidth, -scrll_amount, Width(), scrllbr_height - scrll_amount + 2);

			::SelectObject(ps.hdc, tmpPen);
			::SelectObject(ps.hdc, tmpBrush);

			::EndPaint(this->hWnd, &ps);

			::DeleteObject(hBackgroundPen);
			::DeleteObject(hBackgroundBrush);
			::DeleteObject(hForegroundPen);
			::DeleteObject(hForegroundBrush);
			break;
		}
	}
	return CustomControl::ObjectProc(uMsg, wParam, lParam);
}

LRESULT ToolBoxControl::AddToolBox(ToolBox* toolBox)
{
	ToolBox* tmp = &this->headToolBox;

	while (tmp->pNextToolBox)
	{
		tmp = tmp->pNextToolBox;
	}
	tmp->pNextToolBox = toolBox;

	toolBox->pNextToolBox = NULL;
	toolBox->Show(this->layer.HWND());

	UpdateBoxes();

	return TRUE;
}

LRESULT ToolBoxControl::RemoveToolBox(DWORD id)
{
	ToolBox* tmp = &this->headToolBox;
	ToolBox* tl = 0;

	while (tmp->pNextToolBox)
	{
		if (tmp->pNextToolBox->GetID() == id)
		{
			tl = tmp->pNextToolBox;
			if (tl)
			{
				tl->Close();
			}
			tmp->pNextToolBox = tmp->pNextToolBox->pNextToolBox;
		}
		else
			tmp = tmp->pNextToolBox;
	}

	UpdateBoxes();

	return TRUE;
}

void ToolBoxControl::ClearToolBoxes()
{
	ToolBox* tmp = &this->headToolBox;
	ToolBox* tl = 0;

	while (tmp->pNextToolBox)
	{
		tmp->Close();
		tl = tmp;
		tmp = tmp->pNextToolBox;

		delete tl;
	}

	UpdateBoxes();
}













ToolBoxControl::Layer::Layer()
{
	this->strControlClass		 = "Layer";
	this->dwStyle				 = WS_CHILD;
	this->hBackgroundColor		 = (HBRUSH)COLOR_WINDOW;
}


ToolBoxControl::Layer::~Layer()
{
}

LRESULT ToolBoxControl::Layer::ObjectProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
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
	return CustomControl::ObjectProc(uMsg, wParam, lParam);
}

HWND ToolBoxControl::Layer::HWND()
{
	return this->hWnd;
}