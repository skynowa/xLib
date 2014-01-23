/**
 * \file   CxSemaphore.h
 * \brief  semaphore (user space)
 */


#pragma once

#ifndef xLib_CxSemaphoreH
#define xLib_CxSemaphoreH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, sync)

class CxSemaphore
    /// semaphore
{
public:
             CxSemaphore();
        ///< constructor
    virtual ~CxSemaphore();
        ///< destructor

private:
    xNO_COPY_ASSIGN(CxSemaphore)
};

xNAMESPACE2_END(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxSemaphore.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSemaphoreH
