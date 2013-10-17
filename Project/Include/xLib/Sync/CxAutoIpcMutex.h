/**
 * \file  CxAutoIpcMutex.h
 * \brief auto mutex
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxIpcMutex;

class CxAutoIpcMutex :
    private CxNonCopyable
    /// auto mutex
{
public:
                CxAutoIpcMutex(CxIpcMutex &mutex, std::ctstring_t &name);
    virtual    ~CxAutoIpcMutex();

private:
    CxIpcMutex &_mutex;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif
