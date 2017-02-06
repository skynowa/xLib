/**
 * \file  SocketInit.h
 * \brief initiates use of the Winsock DLL by a process
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, net)

class SocketInit
    /// initiates use of the Winsock DLL by a process
{
public:
             SocketInit(cushort_t &versionMajor, cushort_t &versionMinor);
        ///< constructor (init winsock DLL)
    virtual ~SocketInit();
        ///< destructor  (clean winsock DLL)

    xNO_COPY_ASSIGN(SocketInit)

xPLATFORM_IMPL:
    void_t   _construct_impl(cushort_t &versionMajor, cushort_t &versionMinor) const;
    void_t   _destruct_impl() const;
};

xNAMESPACE_END2(xl, net)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "SocketInit.cpp"
#endif
