/**
 * \file  CxSocketInit.h
 * \brief initiates use of the Winsock DLL by a process
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSocketInit :
    private CxNonCopyable
    /// initiates use of the Winsock DLL by a process
{
public:
              CxSocketInit(cushort_t &cusHighVersion, cushort_t &cusLowVersion);
        ///< constructor (init winsock DLL)
    virtual  ~CxSocketInit();
        ///< destructor  (clean winsock DLL)
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
