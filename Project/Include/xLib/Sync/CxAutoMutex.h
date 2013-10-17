/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMutex;

class CxAutoMutex :
    private CxNonCopyable
    /// auto critical section
{
public:
    explicit CxAutoMutex(CxMutex *mutex);
        ///< constructor
    virtual ~CxAutoMutex();
        ///< destructor

private:
    CxMutex *_mutex;    ///< mutex
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Sync/CxAutoMutex.cpp>
#endif
