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
xNAMESPACE_BEGIN(xlib)

class CxSharedMemory
    /// share memory
{
public:
             CxSharedMemory();
    virtual ~CxSharedMemory();

private:
    xNO_COPY_ASSIGN(CxSharedMemory)
};

xNAMESPACE_END(xlib)
//-------------------------------------------------------------------------------------------------
#include "CxSharedMemory.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSharedMemoryH
