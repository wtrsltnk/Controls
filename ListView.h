// ListView.h: interface for the ListView class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "CommonControl.h"

class CONTROLS_DLL ListView : public CommonControl  
{
protected:
	HWND hHeader;
	
public:
	ListView();
	virtual ~ListView();

	BOOL Create(HWND parent, DWORD id, DWORD style = 0, DWORD exStyle = 0);

	LPLVITEM GetItem(UINT index);

	VOID AddColumn(LPTSTR title, UINT width, UINT index);
	VOID RemoveColumn(UINT index);
	VOID ClearColumns();

	VOID AddItem(LPTSTR text, UINT index, DWORD image, LPARAM data);
	VOID AddSubitem(LPTSTR text, UINT index, UINT subindex, LPARAM data);
	VOID RemoveItem(UINT index);
	VOID ClearItems();

	VOID GetItemText(UINT index, LPTSTR text, UINT size);
	VOID GetSubItemText(UINT index, UINT subindex, LPTSTR text, UINT size);
	LPARAM GetItemData(UINT index);
	UINT GetSelectedItemIndex();
	
	HIMAGELIST SetNormalImageList(HIMAGELIST himl);
	HIMAGELIST SetSmallImageList(HIMAGELIST himl);

};

#endif
