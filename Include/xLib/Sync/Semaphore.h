/**
 * \file   Semaphore.h
 * \brief  semaphore
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class Semaphore
    /// semaphore
{
public:
             Semaphore();
        ///< constructor
    virtual ~Semaphore();
        ///< destructor

private:
    xNO_COPY_ASSIGN(Semaphore)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "Semaphore.inl"
