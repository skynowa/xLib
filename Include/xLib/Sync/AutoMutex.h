/**
 * \file  AutoMutex.h
 * \brief auto critical section (using between threads)
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class Mutex;

class AutoMutex
    /// auto critical section
{
public:
    explicit AutoMutex(Mutex *mutex);
        ///< constructor
    virtual ~AutoMutex();
        ///< destructor

private:
    Mutex *_mutex;    ///< mutex

    xNO_COPY_ASSIGN(AutoMutex)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "AutoMutex.inl"
