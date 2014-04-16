/**
 * \file  CxSocketInit.h
 * \brief initiates use of the Winsock DLL by a process
 */


#pragma once

#ifndef xLib_CxSocketInitH
#define xLib_CxSocketInitH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, net)

class CxSocketInit
    /// initiates use of the Winsock DLL by a process
{
public:
              CxSocketInit(cushort_t &versionMajor, cushort_t &versionMinor);
        ///< constructor (init winsock DLL)
    virtual  ~CxSocketInit();
        ///< destructor  (clean winsock DLL)

    xNO_COPY_ASSIGN(CxSocketInit)
};

xNAMESPACE2_END(xlib, net)
//-------------------------------------------------------------------------------------------------
#include "CxSocketInit.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSocketInitH
