/**
 * \file  CxSharedMemory.h
 * \brief share memory
 */


#pragma once

#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSharedMemory :
    private CxNonCopyable
    /// share memory
{
public:
             CxSharedMemory();
    virtual ~CxSharedMemory();

private:

};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
