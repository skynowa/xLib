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
                         std::ctstring_t &funcName, culong_t &counter);
        ///< constructor
    virtual         ~SourceInfo() {};
        ///< destructor

    std::ctstring_t &filePath() const;
        ///< file path
    culong_t        &lineNum() const;
        ///< line number
    std::ctstring_t &funcName() const;
        ///< function name
    culong_t        &counter() const;
        ///< counter

private:
    std::ctstring_t  _filePath; ///< file path
    culong_t         _lineNum;  ///< line number
    std::ctstring_t  _funcName; ///< function name
    culong_t         _counter;  ///< counter

    xNO_COPY_ASSIGN(SourceInfo)
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "SourceInfo.cpp"
#endif
