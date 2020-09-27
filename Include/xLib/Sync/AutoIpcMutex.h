/**
 * \file  AutoIpcMutex.h
 * \brief auto mutex
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class IpcMutex;

class AutoIpcMutex
    /// auto mutex
{
public:
///@name ctors, dtor
///@{
			 AutoIpcMutex(IpcMutex &mutex, std::ctstring_t &name);
	virtual ~AutoIpcMutex();

	xNO_COPY_ASSIGN(AutoIpcMutex)
///@}

private:
    IpcMutex &_mutex;
};

} // namespace
//-------------------------------------------------------------------------------------------------
