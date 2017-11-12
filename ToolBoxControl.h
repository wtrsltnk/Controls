// ToolBoxControl.h: interface for the ToolBoxControl class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TOOLBOXCONTROL_H
#define TOOLBOXCONTROL_H

#include "CustomControl.h"
#include "ToolBox.h"
#include "resource/resource.h"

class CONTROLS_DLL ToolBoxControl : public CustomControl
{
private:
	class CONTROLS_DLL Layer : public CustomControl
	{
	public:
		Layer();
		virtual ~Layer();

		HWND HWND();

		LRESULT ObjectProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	};

private:
	ToolBox headToolBox;
	Layer layer;
	BOOL bDrag;
	HCURSOR hHand;
	INT nScrollAmount;
	UINT nTotalHeight;
	INT nScrollBarWidth;
	RECT rcClientArea;

	LRESULT Scroll(UINT amount);
	LRESULT ObjectProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void UpdateBoxes();

public:
	ToolBoxControl();
	virtual ~ToolBoxControl();

	LRESULT AddToolBox(ToolBox* toolBox);
	LRESULT RemoveToolBox(DWORD id);
	VOID ClearToolBoxes();

};

#endif
