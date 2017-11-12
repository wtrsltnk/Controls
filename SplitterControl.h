// SplitterControl.h: interface for the SplitterControl class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SPLITTERCONTROL_H
#define SPLITTERCONTROL_H

#include "CustomControl.h"

#define SPLITSIZE 2

class CONTROLS_DLL SplitterControl : public CustomControl  
{
private:
	Control* pControlA;
	Control* pControlB;
	LONG lSplitPosition;
	LONG lRightMargin;
	LONG lLeftMargin;
	UINT uW, uH;

protected:
	LRESULT ObjectProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	SplitterControl();
	virtual ~SplitterControl();

	VOID Size(UINT uWidth, UINT uHeight);
	VOID SetControls(Control* a, Control* b);
	VOID SetMargin(UINT left, UINT right);
	VOID DrawXorBar(HDC hdc, int x1, int y1, int width, int height);
	
};

#endif
