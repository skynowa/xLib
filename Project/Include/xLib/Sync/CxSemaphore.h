/**
 * \file   CxSemaphore.h
 * \brief  semaphore (user space)
 */


#pragma once

#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSemaphore :
    public CxNonCopyable
    /// semaphore
{
public:
             CxSemaphore();
        ///< constructor
    virtual ~CxSemaphore();
        ///< destructor

private:

};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
