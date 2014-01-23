/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
 */


#pragma once

#ifndef xLib_CxAutoMutexH
#define xLib_CxAutoMutexH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, sync)

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

xNAMESPACE2_END(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxAutoMutex.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxAutoMutexH
