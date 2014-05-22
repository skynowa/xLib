/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class CxMutex;

class CxAutoMutex
    /// auto critical section
{
public:
    explicit CxAutoMutex(CxMutex *mutex);
        ///< constructor
    virtual ~CxAutoMutex();
        ///< destructor

private:
    CxMutex *_mutex;    ///< mutex

    xNO_COPY_ASSIGN(CxAutoMutex)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxAutoMutex.inl"
