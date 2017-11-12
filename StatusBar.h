// StatusBar.h: interface for the StatusBar class.
//
//////////////////////////////////////////////////////////////////////

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "CommonControl.h"

#define MAX_PARTS 25

class CONTROLS_DLL StatusBar : public CommonControl
{
private:
	UINT uPartCount;
	UINT uParts[MAX_PARTS];
	
public:
	StatusBar();
	virtual ~StatusBar();

	BOOL Create(HWND hParent, DWORD dwId, DWORD style = 0, DWORD exStyle = 0);

	BOOL AddPart(LPTSTR strTitle, UINT uWidth);
	VOID SetPartTitle(UINT uPart, LPTSTR strTitle);

};

#endif
