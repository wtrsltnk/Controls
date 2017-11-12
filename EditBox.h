// EditBox.h: interface for the EditBox class.
//
//////////////////////////////////////////////////////////////////////

#ifndef EDITBOX_H
#define EDITBOX_H

#include "CommonControl.h"

class CONTROLS_DLL EditBox : public CommonControl  
{
public:
	EditBox();
	virtual ~EditBox();

	BOOL Append(LPTSTR text);

};

#endif
