/**
 * \file   SourceInfo.h
 * \brief  [CLASS_COMMENTS]
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class SourceInfo
    ///<
{
public:
                     SourceInfo(std::ctstring_t &filePath, culong_t &lineNum,
                         std::ctstring_t &funcName);
        ///< constructor
    virtual         ~SourceInfo() {};
        ///< destructor

    std::tstring_t   filePath() const;
        ///< file path
    ulong_t          lineNum() const;
        ///< line number
    std::tstring_t   funcName() const;
        ///< function name

private:
    std::ctstring_t &_filePath; ///< file path
    culong_t        &_lineNum;  ///< line number
    std::ctstring_t &_funcName; ///< function name

    xNO_COPY_ASSIGN(SourceInfo)
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "SourceInfo.cpp"
#endif
