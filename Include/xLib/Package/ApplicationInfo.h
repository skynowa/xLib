/**
 * \file   ApplicationInfo.h
 * \brief  ApplicationInfo money
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class ApplicationInfo
    /// Application information
{
public:
    std::tstring_t name;
    std::tstring_t decription;
    std::tstring_t copyrightYears;
    std::tstring_t usage;
    std::tstring_t help;
    std::tstring_t versionMajor;
    std::tstring_t versionMinor;
    std::tstring_t versionPatch;
    std::tstring_t versionType;
    std::tstring_t versionRevision;
    std::tstring_t vendorName;
    std::tstring_t vendorDomain;
    std::tstring_t vendorAuthor;
    std::tstring_t vendorUrl;
    std::tstring_t vendorEmail;
    std::tstring_t vendorSkype;
    std::tstring_t vendorJabber;
    std::tstring_t vendorIcq;

    std::tstring_t versionFull() const;

             ApplicationInfo() = default;
    virtual ~ApplicationInfo() = default;
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
