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
                CxAutoIpcMutex(CxIpcMutex &mtMutex, std::ctstring_t &csName);
    virtual    ~CxAutoIpcMutex();

private:
    CxIpcMutex &_m_mtMutex;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
