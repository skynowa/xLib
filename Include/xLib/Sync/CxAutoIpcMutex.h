/**
 * \file  CxAutoIpcMutex.h
 * \brief auto mutex
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

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

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxAutoIpcMutex.inl"
