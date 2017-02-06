/**
 * \file   ApplicationInfo.h
 * \brief  ApplicationInfo money
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

struct ApplicationInfoData
    /// SourceInfo data
{
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
};
xTYPEDEF_CONST(ApplicationInfoData);

class ApplicationInfo
    ///< Application information
{
public:
                 ApplicationInfo();
    explicit     ApplicationInfo(cApplicationInfoData &data);
        ///< constructor
    virtual     ~ApplicationInfo();
        ///< destructor

    xPROPERTY(ApplicationInfoData, data);

private:
    // xNO_COPY_ASSIGN(ApplicationInfo)
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "ApplicationInfo.cpp"
#endif
