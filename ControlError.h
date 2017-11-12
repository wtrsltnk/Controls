// ControlError.h: interface for the ControlError class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CONTROLERROR_H
#define CONTROLERROR_H

#include "Controls.h"

struct control_error
{
	char* strErr;
	int iErrID;
	control_error* pNext;
};

#define CONTROL_ERROR_ID_UNKNOWN 2300
#define CONTROL_ERROR_NAME_UNKNOWN "Unknown"

class CONTROLS_DLL ControlError  
{
private:
	control_error* first;
	
public:
	ControlError();
	virtual ~ControlError();
	
	bool AddError(char* err, int id = CONTROL_ERROR_ID_UNKNOWN);
	bool AddErrors(control_error* first);

public:
	bool GetLastError(control_error &err);
	control_error* GetErrors();
	bool HasErrors();

};

#endif
