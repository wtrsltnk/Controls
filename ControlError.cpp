// ControlError.cpp: implementation of the ControlError class.
//
//////////////////////////////////////////////////////////////////////

#include "ControlError.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ControlError::ControlError()
{
	this->first = 0;
}

ControlError::~ControlError()
{
	while (this->first != 0)
	{
		control_error* tmp = this->first;
		this->first = this->first->pNext;

		delete tmp;
	}
}

bool ControlError::AddError(char* err, int id)
{
	if (err)
	{
		control_error* newerr = new control_error;

		newerr->strErr = err;
		newerr->iErrID = id;

		newerr->pNext = this->first;
		this->first = newerr;

		return false;
	}

	return true;
}

bool ControlError::AddErrors(control_error* first)
{
	if (first != 0)
	{
		if (this->first != 0)
		{
			control_error* tmp = this->first;
			
			while (tmp->pNext != 0)
				tmp = tmp->pNext;

			tmp->pNext = first;
		}
		else
		{
			this->first = first;
		}
		return false;
	}
	
	return true;
}

bool ControlError::GetLastError(control_error &err)
{
	if (this->first != 0)
	{
		err = *this->first;

		control_error* tmp = this->first;
		this->first = this->first->pNext;

		delete tmp;

		return true;
	}
	return false;
}

control_error* ControlError::GetErrors()
{
	control_error* tmp = this->first;

	this->first = 0;

	return tmp;
}

bool ControlError::HasErrors()
{
	return this->first != 0;
}
