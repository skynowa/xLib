/**
 * \file  CxSharedMemory.h
 * \brief share memory
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Sync/CxSharedMemory.cpp>
#endif
