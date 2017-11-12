// TreeView.cpp: implementation of the TreeView class.
//
//////////////////////////////////////////////////////////////////////

#include "TreeView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TreeView::TreeView()
{
	this->strControlClass = "SysTreeView32";
	this->dwStyle = WS_CHILD | WS_VISIBLE;
}

TreeView::~TreeView()
{
}

HTREEITEM TreeView::AddItem(LPTSTR text, HTREEITEM parent, DWORD image, DWORD selimage, LPARAM data)
{
	TV_INSERTSTRUCT tvins;
	TV_ITEM tvi;

	tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvi.pszText = text;
	tvi.iImage = image;
	tvi.iSelectedImage = selimage;
	tvi.lParam = data;

	tvins.hParent = parent;
	tvins.hInsertAfter = TVI_LAST;
	tvins.item = tvi;

	return TreeView_InsertItem(this->hWnd, &tvins);
}

VOID TreeView::RemoveItem(HTREEITEM item)
{
	TreeView_DeleteItem(this->hWnd, item);
}

VOID TreeView::ClearItems()
{
	TreeView_DeleteAllItems(this->hWnd);
}

VOID TreeView::ClearChilds(HTREEITEM item)
{
	HTREEITEM child = TreeView_GetChild(this->hWnd, item);

	while (child)
	{
		TreeView_DeleteItem(this->hWnd, child);

		child = TreeView_GetChild(this->hWnd, item);
	}
}

BOOL TreeView::HasChilds(HTREEITEM item)
{
	return TreeView_GetChild(this->hWnd, item) != NULL;
}

BOOL TreeView::GetItemText(HTREEITEM item, LPTSTR text, UINT size)
{
	TVITEM tvi;

	tvi.hItem		=	item;
	tvi.cchTextMax	=	size;
	tvi.pszText		=	text;
	tvi.mask		=	TVIF_TEXT;

	return ::SendMessage(this->hWnd, TVM_GETITEM, 0, (LPARAM)&tvi);
}

DWORD TreeView::GetItemData(HTREEITEM item)
{
	TVITEM tvi;

	tvi.hItem		=	item;
	tvi.mask		=	TVIF_PARAM;

	::SendMessage(this->hWnd, TVM_GETITEM, 0, (LPARAM)&tvi);
	
	return tvi.lParam;
}

HTREEITEM TreeView::GetSelectedItem()
{
	return TreeView_GetSelection(this->hWnd);
}

HTREEITEM TreeView::GetParentItem(HTREEITEM item)
{
	return TreeView_GetParent(this->hWnd, item);
}

HTREEITEM TreeView::GetChild(HTREEITEM parent, UINT index)
{
	HTREEITEM firstChild = TreeView_GetChild(this->hWnd, parent);

	if (index == 0)
	{
		return firstChild;
	}
	else
	{
		HTREEITEM child = firstChild;
		
		for (DWORD i = 0; i < index; i++)
		{
			child = GetNextSibling(child);
		}
		return child;
	}
}

HTREEITEM TreeView::GetFirstChild(HTREEITEM parent)
{
	return TreeView_GetChild(this->hWnd, parent);
}

HTREEITEM TreeView::GetNextSibling(HTREEITEM item)
{
	return TreeView_GetNextSibling(this->hWnd, item);
}

VOID TreeView::Expand(HTREEITEM item)
{
	TreeView_Expand(this->hWnd, item, TVE_EXPAND);
}

VOID TreeView::Collapse(HTREEITEM item)
{
	TreeView_Expand(this->hWnd, item, TVE_COLLAPSE);
}

HIMAGELIST TreeView::SetNormalImageList(HIMAGELIST himl)
{
	return TreeView_SetImageList(this->hWnd, himl, LVSIL_NORMAL);
}

VOID TreeView::SetCheckState(HTREEITEM item, BOOL state)
{
	TVITEM tvItem;

    tvItem.mask = TVIF_HANDLE | TVIF_STATE;
    tvItem.hItem = item;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

    /*
    Since state images are one-based, 1 in this macro turns the check off, and 
    2 turns it on.
    */
    tvItem.state = INDEXTOSTATEIMAGEMASK((state ? 2 : 1));

    TreeView_SetItem(this->hWnd, &tvItem);

}

BOOL TreeView::GetCheckState(HTREEITEM item)
{
	TVITEM tvItem;

    // Prepare to receive the desired information.
    tvItem.mask = TVIF_HANDLE | TVIF_STATE;
    tvItem.hItem = item;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

    // Request the information.
    TreeView_GetItem(this->hWnd, &tvItem);

    // Return zero if it's not checked, or nonzero otherwise.
    return ((tvItem.state >> 12) -1) == 0;
}

HTREEITEM TreeView::HitTestCursor()
{
	POINT pt;
	TVHITTESTINFO htinfo;

	GetCursorPos(&pt);
	ScreenToClient(this->hWnd, &pt);

	htinfo.pt.x = pt.x;
	htinfo.pt.y = pt.y;
	htinfo.flags = TVHT_ONITEM;

	TreeView_HitTest(this->hWnd, &htinfo);

	return htinfo.hItem;
}
