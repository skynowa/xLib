/**
 * \file   BuildInfo.h (header only)
 * \brief  build information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, debug)

class BuildInfo
    ///< build information
{
public:
                   BuildInfo() {}
        ///< constructor
    virtual       ~BuildInfo() {}
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
    std::tstring_t compilerFlags() const xWARN_UNUSED_RV;
        ///< compilier flags
    std::tstring_t libs() const xWARN_UNUSED_RV;
        ///< linked libraries
    bool_t         isUnicodeEncoding() const xWARN_UNUSED_RV;
        ///< is Unicode character-encoding
    std::tstring_t stdLibC() const xWARN_UNUSED_RV;
        ///< C standart library
    std::tstring_t stdLibCpp() const xWARN_UNUSED_RV;
        ///< C++ standart library
    std::tstring_t qt() const xWARN_UNUSED_RV;
        ///< Qt library
    std::tstring_t xlibVersion() const xWARN_UNUSED_RV;
        ///< xLib library
    std::tstring_t xlibBinaryType() const xWARN_UNUSED_RV;
        ///< binary type
    std::tstring_t xlibBuildType() const xWARN_UNUSED_RV;
        ///< build type
    std::tstring_t cmake() const xWARN_UNUSED_RV;
        ///< cmake

private:
    xNO_COPY_ASSIGN(BuildInfo)
};

xNAMESPACE_END2(xl, debug)
//-------------------------------------------------------------------------------------------------
#include "BuildInfo.inl"
