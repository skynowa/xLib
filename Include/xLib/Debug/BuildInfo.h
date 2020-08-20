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
                   BuildInfo() = default;
    virtual       ~BuildInfo() = default;

    bool_t         isRelease() const;
        ///< is debug build (is NDEBUG macros is don't set)
    std::tstring_t datetime() const;
        ///< date time
    std::tstring_t langStandart() const;
        ///< C/C++ language standart
    std::tstring_t osEnvironment() const;
        ///< OS environment
    std::tstring_t os() const;
        ///< OS name
    std::tstring_t arch() const;
        ///< architecture
    std::tstring_t bitsArch() const;
        ///< bits architecture
    std::tstring_t compiler() const;
        ///< compilier
    std::tstring_t compilerFlags() const;
        ///< compilier flags
    std::tstring_t libs() const;
        ///< linked libraries
    bool_t         isUnicodeEncoding() const;
        ///< is Unicode character-encoding
    std::tstring_t stdLibC() const;
        ///< C standart library
    std::tstring_t stdLibCpp() const;
        ///< C++ standart library
    std::tstring_t qt() const;
        ///< Qt library
    std::tstring_t xlibVersion() const;
        ///< xLib library
    std::tstring_t xlibBinaryType() const;
        ///< binary type
    std::tstring_t xlibBuildType() const;
        ///< build type
    std::tstring_t cmake() const;
        ///< cmake

private:
    xNO_COPY_ASSIGN(BuildInfo)
};

xNAMESPACE_END2(xl, debug)
//-------------------------------------------------------------------------------------------------
#include "BuildInfo.inl"
