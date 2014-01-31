/**
 * \file   CxBuildInfo.h
 * \brief  build information
 */


#pragma once

#ifndef xLib_CxBuildInfoH
#define xLib_CxBuildInfoH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, debug)

class CxBuildInfo
    ///< build information
{
public:
             CxBuildInfo() {}
        ///< constructor
    virtual ~CxBuildInfo() {}
        ///< destructor

    bool_t   isDebugBuild() const xWARN_UNUSED_RV;
        ///< is debug build (is NDEBUG macros is don't set)

private:
    xNO_COPY_ASSIGN(CxBuildInfo)
};

xNAMESPACE2_END(xlib, debug)
//-------------------------------------------------------------------------------------------------
#include <xLib/Debug/CxBuildInfo.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxBuildInfoH
