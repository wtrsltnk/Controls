// ToolBox.h: interface for the ToolBox class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "CustomControl.h"
#include "Button.h"
#include "../Dialogs/CustomDialog.h"


#define WM_SCROLLDLGS					WM_USER + 23001

#define IDM_TITLEBUTTON					7


class CONTROLS_DLL ToolBox : public CustomControl  
{
protected:
	friend class  ToolBoxControl;

	class CONTROLS_DLL ToolBoxDlg : public CustomDialog
	{
	public:
		VOID DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		ToolBoxDlg();
		~ToolBoxDlg();

		LRESULT Init(DWORD dwResource);
		LRESULT Show(HWND hParent);
		LRESULT Close();
	};

	ToolBox* pNextToolBox;
	DWORD dwResource;
	UINT nOriginalHeight;
	UINT nCurrentHeight;
	UINT nXPosition;
	UINT nYPosition;
	
	ToolBoxDlg dialog;
	Button button;

	LRESULT Show(HWND hParent);
	LRESULT Close();
	UINT MoveToolBox(UINT x, UINT y, UINT width);

	LRESULT ObjectProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	ToolBox();
	virtual ~ToolBox();

	VOID Initialize(DWORD id, DWORD resource = 0);
	
	VOID SetTitle(LPTSTR title);
	DWORD GetID();

};

#endif
