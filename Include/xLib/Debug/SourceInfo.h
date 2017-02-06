/**
 * \file   SourceInfo.h
 * \brief  Source info
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, debug)

struct SourceInfoData
    /// SourceInfo data
{
    std::ctstring_t filePath; ///< file path
    culong_t        lineNum;  ///< line number
    std::ctstring_t funcName; ///< function name
    culong_t        counter;  ///< counter
};
xTYPEDEF_CONST(SourceInfoData);

class SourceInfo
    ///< Source info
{
public:
    explicit          SourceInfo(cSourceInfoData &data);
        ///< constructor
    virtual          ~SourceInfo() {};
        ///< destructor

    cSourceInfoData & data() const;
        ///< data
    std::tstring_t    format() const;
        ///< format data
    std::tstring_t    at() const;
        ///< format as file and line

private:
    cSourceInfoData   _data; ///< data

    xNO_COPY_ASSIGN(SourceInfo)
};

xNAMESPACE_END2(xl, debug)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "SourceInfo.cpp"
#endif
