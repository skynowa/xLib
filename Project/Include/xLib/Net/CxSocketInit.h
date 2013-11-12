/**
 * \file  CxSocketInit.h
 * \brief initiates use of the Winsock DLL by a process
 */


#pragma once

#ifndef xLib_CxSocketInitH
#define xLib_CxSocketInitH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Core/CxNonCopyable.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSocketInit :
    public CxNonCopyable
    /// initiates use of the Winsock DLL by a process
{
public:
              CxSocketInit(cushort_t &highVersion, cushort_t &lowVersion);
        ///< constructor (init winsock DLL)
    virtual  ~CxSocketInit();
        ///< destructor  (clean winsock DLL)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Net/CxSocketInit.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSocketInitH
