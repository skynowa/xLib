/**
 * \file  AutoIpcMutex.h
 * \brief auto mutex
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class IpcMutex;

class AutoIpcMutex
    /// auto mutex
{
public:
                AutoIpcMutex(IpcMutex &mutex, std::ctstring_t &name);
    virtual    ~AutoIpcMutex();

private:
    IpcMutex &_mutex;

    xNO_COPY_ASSIGN(AutoIpcMutex)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "AutoIpcMutex.cpp"
#endif
