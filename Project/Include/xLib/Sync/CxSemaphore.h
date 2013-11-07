/**
 * \file   CxSemaphore.h
 * \brief  semaphore (user space)
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Sync/CxSemaphore.cpp>
#endif
