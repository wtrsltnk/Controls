// ListBox.cpp: implementation of the ListBox class.
//
//////////////////////////////////////////////////////////////////////

#include "ListBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListBox::ListBox()
{
	this->strControlClass = "LISTBOX";
}

ListBox::~ListBox()
{
}

DWORD ListBox::AddItem(LPTSTR item, UINT index, DWORD data)
{
	UINT i = ::SendMessage(this->hWnd, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)item);
	
	::SendMessage(this->hWnd, LB_SETITEMDATA, (WPARAM)i, (LPARAM)data);

	return i;
}

BOOL ListBox::RemoveItem(UINT index)
{
	return ::SendMessage(this->hWnd, LB_DELETESTRING, (WPARAM)index, 0) != CB_ERR;
}

UINT ListBox::Count()
{
	return ::SendMessage(this->hWnd, LB_GETCOUNT, 0, 0);
}

UINT ListBox::GetTextLength(UINT index)
{
	return ::SendMessage(this->hWnd, LB_GETTEXTLEN, 0, 0);
}

BOOL ListBox::GetText(UINT index, LPTSTR text)
{
	return ::SendMessage(this->hWnd, LB_GETTEXT, (WPARAM)index, (LPARAM)(LPCTSTR)text);
}

DWORD ListBox::GetData(UINT index)
{
	return (DWORD)::SendMessage(this->hWnd, LB_GETITEMDATA, (WPARAM)index, 0);
}

UINT ListBox::GetSelectedIndex()
{
	return ::SendMessage(this->hWnd, LB_GETCURSEL, 0, 0);
}

VOID ListBox::Clear()
{
	::SendMessage(this->hWnd, LB_RESETCONTENT, 0, 0);
}

VOID ListBox::Select(UINT index)
{
	::SendMessage(this->hWnd, LB_SETCURSEL, (WPARAM)index, 0);
}
