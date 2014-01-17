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
xNAMESPACE_BEGIN(xlib)

class CxIpcMutex;

class CxAutoIpcMutex
    /// auto mutex
{
public:
                CxAutoIpcMutex(CxIpcMutex &mutex, std::ctstring_t &name);
    virtual    ~CxAutoIpcMutex();

private:
    CxIpcMutex &_mutex;

    xNO_COPY_ASSIGN(CxAutoIpcMutex)
};

xNAMESPACE_END(xlib)
//-------------------------------------------------------------------------------------------------
#include "CxAutoIpcMutex.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxAutoIpcMutexH
