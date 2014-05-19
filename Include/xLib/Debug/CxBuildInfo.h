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
xNAMESPACE_BEGIN2(xlib, debug)

class CxBuildInfo
    ///< build information
{
public:
                   CxBuildInfo() {}
        ///< constructor
    virtual       ~CxBuildInfo() {}
        ///< destructor

    bool_t         isRelease() const xWARN_UNUSED_RV;
        ///< is debug build (is NDEBUG macros is don't set)
    std::tstring_t datetime() const xWARN_UNUSED_RV;
        ///< date time
    std::tstring_t langStandart() const xWARN_UNUSED_RV;
        ///< C/C++ language standart
    std::tstring_t osEnvironment() const xWARN_UNUSED_RV;
        ///< OS environment
    std::tstring_t os() const xWARN_UNUSED_RV;
        ///< OS name
    std::tstring_t arch() const xWARN_UNUSED_RV;
        ///< architecture
    std::tstring_t bitsArch() const xWARN_UNUSED_RV;
        ///< bits architecture
    std::tstring_t compiler() const xWARN_UNUSED_RV;
        ///< compilier
    bool_t         isUnicodeEncoding() const xWARN_UNUSED_RV;
        ///< is Unicode character-encoding
    std::tstring_t stdLibC() const xWARN_UNUSED_RV;
        ///< C standart library
    std::tstring_t stdLibCpp() const xWARN_UNUSED_RV;
        ///< C++ standart library
    std::tstring_t xlibVersion() const xWARN_UNUSED_RV;
        ///< xLib version
    std::tstring_t binaryType() const xWARN_UNUSED_RV;
        ///< binary type

private:
    xNO_COPY_ASSIGN(CxBuildInfo)
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#include <xLib/Debug/CxBuildInfo.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxBuildInfoH
