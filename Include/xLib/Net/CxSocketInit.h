/**
 * \file  CxSocketInit.h
 * \brief initiates use of the Winsock DLL by a process
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, net)

class CxSocketInit
    /// initiates use of the Winsock DLL by a process
{
public:
             CxSocketInit(cushort_t &versionMajor, cushort_t &versionMinor);
        ///< constructor (init winsock DLL)
    virtual ~CxSocketInit();
        ///< destructor  (clean winsock DLL)

    xNO_COPY_ASSIGN(CxSocketInit)

xPLATFORM:
    void_t   _construct_impl(cushort_t &versionMajor, cushort_t &versionMinor) const;
    void_t   _destruct_impl() const;
};

xNAMESPACE_END2(xlib, net)
//-------------------------------------------------------------------------------------------------
#include "CxSocketInit.inl"
