/**
 * \file  SharedMemory.h
 * \brief share memory
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class SharedMemory
    /// share memory
{
public:
             SharedMemory() = default;
    virtual ~SharedMemory() = default;

private:
    xNO_COPY_ASSIGN(SharedMemory)
};

} // namespace
//-------------------------------------------------------------------------------------------------
