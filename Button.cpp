// Button.cpp: implementation of the Button class.
//
//////////////////////////////////////////////////////////////////////

#include "Button.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Button::Button()
{
	this->dwStyle = WS_CHILD | WS_VISIBLE | BS_NOTIFY | BS_PUSHBUTTON;
	this->strControlClass = "BUTTON";
}

Button::~Button()
{
}
