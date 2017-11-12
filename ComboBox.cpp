// omboBox.cpp: implementation of the ComboBox class.
//
//////////////////////////////////////////////////////////////////////

#include "ComboBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ComboBox::ComboBox()
{
	this->dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWN;
	this->strControlClass = "COMBOBOX";
}

ComboBox::~ComboBox()
{
}
