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
    explicit AutoMutex(Mutex *mutex);
    virtual ~AutoMutex();

private:
    Mutex *_mutex {};    ///< mutex

    xNO_COPY_ASSIGN(AutoMutex)
};

} // namespace
//-------------------------------------------------------------------------------------------------
