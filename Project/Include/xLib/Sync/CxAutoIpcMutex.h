/**
 * \file  CxAutoIpcMutex.h
 * \brief auto mutex
 */


#pragma once

#ifndef xLib_CxAutoIpcMutexH
#define xLib_CxAutoIpcMutexH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxIpcMutex;

class CxAutoIpcMutex :
    public CxNonCopyable
    /// auto mutex
{
public:
                CxAutoIpcMutex(CxIpcMutex &mutex, std::ctstring_t &name);
    virtual    ~CxAutoIpcMutex();

private:
    CxIpcMutex &_mutex;
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Sync/CxAutoIpcMutex.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxAutoIpcMutexH
