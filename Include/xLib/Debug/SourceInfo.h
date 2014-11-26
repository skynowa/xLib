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
                     SourceInfo(std::ctstring_t &file, culong_t &line, std::ctstring_t &func);
        ///< constructor
    virtual         ~SourceInfo() {};
        ///< destructor

    std::ctstring_t &file() const;
        ///< file path
    culong_t        &line() const;
        ///< line number
    std::ctstring_t &func() const;
        ///< function name

private:
    std::ctstring_t &_file; ///< file path
    culong_t        &_line; ///< line number
    std::ctstring_t &_func; ///< function name

    xNO_COPY_ASSIGN(SourceInfo)
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "SourceInfo.cpp"
#endif
