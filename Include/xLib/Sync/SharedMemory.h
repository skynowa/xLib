/**
 * \file  SharedMemory.h
 * \brief share memory
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, sync)

class SharedMemory
    /// share memory
{
public:
             SharedMemory() = default;
    virtual ~SharedMemory() = default;

private:
    xNO_COPY_ASSIGN(SharedMemory)
};

xNAMESPACE_END2(xl, sync)
//-------------------------------------------------------------------------------------------------
