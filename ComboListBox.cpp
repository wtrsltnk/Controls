// ComboListBox.cpp: implementation of the ComboListBox class.
//
//////////////////////////////////////////////////////////////////////

#include "ComboListBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ComboListBox::ComboListBox()
{
	this->dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST;
	this->strControlClass = "COMBOBOX";
}

ComboListBox::~ComboListBox()
{
}
