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
xNAMESPACE_BEGIN(NxLib)

class CxSharedMemory :
    public CxNonCopyable
    /// share memory
{
public:
             CxSharedMemory();
    virtual ~CxSharedMemory();

private:

};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Sync/CxSharedMemory.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSharedMemoryH
