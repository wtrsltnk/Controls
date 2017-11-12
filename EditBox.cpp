// EditBox.cpp: implementation of the EditBox class.
//
//////////////////////////////////////////////////////////////////////

#include "EditBox.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EditBox::EditBox()
{
	this->strControlClass = "EDIT";
}

EditBox::~EditBox()
{
}

BOOL EditBox::Append(LPTSTR text)
{
	DWORD lenght = ::SendMessage(this->hWnd, WM_GETTEXTLENGTH, 0, 0);

	if (lenght <= 0)
	{
		::SendMessage(this->hWnd, WM_SETTEXT, 0, (LPARAM)(LPTSTR)text);
		return TRUE;
	}

	DWORD newlenght = lenght + strlen(text);

	LPTSTR tmp = new CHAR[lenght + 1];
	LPTSTR newtext = new CHAR[newlenght + 1];


	if (tmp != NULL && newtext != NULL)
	{
		::SendMessage(this->hWnd, WM_GETTEXT, lenght, (LPARAM)(LPTSTR)tmp);

		sprintf(newtext, "%s%s", tmp, text);

		::SendMessage(this->hWnd, WM_SETTEXT, 0, (LPARAM)(LPTSTR)newtext);

		delete [] tmp;
		delete [] newtext;

		return TRUE;
	}
	else
	{
		AddError("Buffers voor het toevoegen van de tekst is niet gelukt");
	}
	return FALSE;
}