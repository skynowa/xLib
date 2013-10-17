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
              CxSocketInit(cushort_t &highVersion, cushort_t &lowVersion);
        ///< constructor (init winsock DLL)
    virtual  ~CxSocketInit();
        ///< destructor  (clean winsock DLL)
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif
