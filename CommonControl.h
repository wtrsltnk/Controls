// CommonControl.h: interface for the CommonControl class.
//
//////////////////////////////////////////////////////////////////////

#ifndef COMMONCONTROL_H
#define COMMONCONTROL_H

#include "Control.h"
#include <commctrl.h>
#include <shlwapi.h>

class CONTROLS_DLL CommonControl : public Control
{
protected:
	CommonControl();
	virtual ~CommonControl();

public:
	BOOL Create(HWND hParent, DWORD dwId, DWORD style = 0, DWORD exStyle = 0);

};

#endif
