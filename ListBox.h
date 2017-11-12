// ListBox.h: interface for the ListBox class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LISTBOX_H
#define LISTBOX_H

#include "CommonControl.h"

class CONTROLS_DLL ListBox : public CommonControl  
{
public:
	ListBox();
	virtual ~ListBox();

	DWORD AddItem(LPTSTR item, UINT index, DWORD data);
	BOOL RemoveItem(UINT index);

	UINT Count();

	UINT GetTextLength(UINT index);
	BOOL GetText(UINT index, LPTSTR text);

	DWORD GetData(UINT index);

	VOID Select(UINT index);
	UINT GetSelectedIndex();

	VOID Clear();

};

#endif
