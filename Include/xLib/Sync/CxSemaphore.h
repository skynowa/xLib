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
xNAMESPACE_BEGIN(NxLib)

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

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxSemaphore.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSemaphoreH
