// TreeView.h: interface for the TreeView class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "CommonControl.h"

class CONTROLS_DLL TreeView : public CommonControl  
{
public:
	TreeView();
	virtual ~TreeView();

	HTREEITEM AddItem(LPTSTR text, HTREEITEM parent, DWORD image = 0, DWORD selimage = 0, LPARAM data = 0);
	VOID RemoveItem(HTREEITEM item);

	VOID ClearItems();
	VOID ClearChilds(HTREEITEM item);

	BOOL HasChilds(HTREEITEM item);

	BOOL GetItemText(HTREEITEM item, LPTSTR text, UINT size);
	DWORD GetItemData(HTREEITEM item);
	HTREEITEM GetSelectedItem();
	HTREEITEM GetParentItem(HTREEITEM item);
	HTREEITEM GetChild(HTREEITEM parent, UINT index);
	HTREEITEM GetFirstChild(HTREEITEM parent);
	HTREEITEM GetNextSibling(HTREEITEM item);

	VOID Expand(HTREEITEM item);
	VOID Collapse(HTREEITEM item);

	HIMAGELIST SetNormalImageList(HIMAGELIST himl);

	VOID SetCheckState(HTREEITEM item, BOOL state);
	BOOL GetCheckState(HTREEITEM item);
	
	HTREEITEM HitTestCursor();

};

#endif
