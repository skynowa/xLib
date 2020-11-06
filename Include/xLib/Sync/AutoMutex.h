/**
 * \file  AutoMutex.h
 * \brief auto critical section (using between threads)
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class Mutex;

class AutoMutex
    /// auto critical section
{
public:
///@name ctors, dtor
///@{
	explicit AutoMutex(Mutex *mutex);
	virtual ~AutoMutex();

	xNO_COPY_ASSIGN(AutoMutex)
///@}

private:
    Mutex *_mutex {};    ///< mutex
};

} // namespace
//-------------------------------------------------------------------------------------------------
