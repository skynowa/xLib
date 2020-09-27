/**
 * \file   Semaphore.h
 * \brief  semaphore
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class Semaphore
    /// semaphore
{
public:
             Semaphore() = default;
    virtual ~Semaphore() = default;

private:
    xNO_COPY_ASSIGN(Semaphore)
};

} // namespace
//-------------------------------------------------------------------------------------------------
