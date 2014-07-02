/**
 * \file  SharedMemory.h
 * \brief share memory
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class SharedMemory
    /// share memory
{
public:
             SharedMemory();
    virtual ~SharedMemory();

private:
    xNO_COPY_ASSIGN(SharedMemory)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "SharedMemory.inl"
