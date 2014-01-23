/**
 * \file  CxSharedMemory.h
 * \brief share memory
 */


#pragma once

#ifndef xLib_CxSharedMemoryH
#define xLib_CxSharedMemoryH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, sync)

class CxSharedMemory
    /// share memory
{
public:
             CxSharedMemory();
    virtual ~CxSharedMemory();

private:
    xNO_COPY_ASSIGN(CxSharedMemory)
};

xNAMESPACE2_END(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxSharedMemory.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSharedMemoryH
