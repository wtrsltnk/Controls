// ListView.cpp: implementation of the ListView class.
//
//////////////////////////////////////////////////////////////////////

#include "ListView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListView::ListView()
{
	this->strControlClass = "SysListView32";
	this->dwStyle = WS_CHILD | WS_VISIBLE;
	this->dwExStyle = WS_EX_WINDOWEDGE;
}

ListView::~ListView()
{
}

BOOL ListView::Create(HWND parent, DWORD id, DWORD style, DWORD exStyle)
{	
	if (CommonControl::Create(parent, id, style, exStyle))
	{
		this->hHeader = ::CreateWindow(	WC_HEADER,
										"", 
										HDS_HORZ|HDS_BUTTONS, 
										0,
										0,
										100,
										100,
										this->hWnd,
										NULL,
										GetModuleHandle(NULL),
										NULL);

		if (this->hHeader == NULL)
		{
			AddError("Aanmaken van de header is niet gelukt");
			return false;
		}
		return true;
	}

	return false;
}

LPLVITEM ListView::GetItem(UINT index)
{
	LVITEM *lvi;
	lvi = new LVITEM;

	lvi->mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_FMT | LVIF_PARAM;
	lvi->iItem = index;
	lvi->iSubItem = 0;

	ListView_GetItem(this->hWnd, lvi);
	return lvi;
}

VOID ListView::AddColumn(LPTSTR title, UINT width, UINT index)
{
	LV_COLUMN lvc;

	lvc.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	lvc.fmt = LVCFMT_LEFT ;
	lvc.cchTextMax = 300;
	lvc.cx = width;
	lvc.pszText = title;
	lvc.iSubItem = index;

	ListView_InsertColumn(this->hWnd, index, &lvc);
}

VOID ListView::RemoveColumn(UINT index)
{
	ListView_DeleteColumn(this->hWnd, index);
}

VOID ListView::ClearColumns()
{
	DWORD result = 1;

	while (result)
	{
		result = ListView_DeleteColumn(this->hWnd, 0);
	}
}

VOID ListView::AddItem(LPTSTR text, UINT index, DWORD image, LPARAM data)
{
	LV_ITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
	lvi.state = 0;
	lvi.stateMask = -1;
	lvi.iItem = index;
	lvi.iSubItem = 0;
	lvi.pszText = text;
	lvi.iImage = image;
	lvi.lParam = data;

	ListView_InsertItem(this->hWnd, &lvi );
}

VOID ListView::AddSubitem(LPTSTR text, UINT index, UINT subindex, LPARAM data)
{
	ListView_SetItemText(this->hWnd, index, subindex, text);
}

VOID ListView::RemoveItem(UINT index)
{
	ListView_DeleteItem(this->hWnd, index);
}

VOID ListView::ClearItems()
{
	ListView_DeleteAllItems(this->hWnd);
}

VOID ListView::GetItemText(UINT index, LPTSTR text, UINT size)
{
	ListView_GetItemText(this->hWnd, index, 0, text, size);
}

VOID ListView::GetSubItemText(UINT index, UINT subindex, LPTSTR text, UINT size)
{
	ListView_GetItemText(this->hWnd, index, subindex, text, size);
}

LPARAM ListView::GetItemData(UINT index)
{
	LPARAM p = NULL;
	LVITEM lvi;

	lvi.mask = LVIF_PARAM;
	lvi.iItem = index;
	lvi.iSubItem = 0;

	ListView_GetItem(this->hWnd, &lvi);
	return lvi.lParam;
}

UINT ListView::GetSelectedItemIndex()
{
	return ListView_GetSelectionMark(this->hWnd);
}

HIMAGELIST ListView::SetNormalImageList(HIMAGELIST himl)
{
	return ListView_SetImageList(this->hWnd, himl, LVSIL_NORMAL);
}

HIMAGELIST ListView::SetSmallImageList(HIMAGELIST himl)
{
	return ListView_SetImageList(this->hWnd, himl, LVSIL_SMALL);
}
