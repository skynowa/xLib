/**
 * \file  CxConst.h
 * \brief constants
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxConst
    /// constants
{
public:
    // xSTR_EMPTY
    static std::cstring_t  xSTR_EMPTY_A;
        ///< empty string (ansi)
    static std::cwstring_t xSTR_EMPTY_W;
        ///< empty string (unicode)
    static std::ctstring_t xSTR_EMPTY;
        ///< empty string (ansi or unicode)

    // xCR
    static std::cstring_t  xCR_A;
        ///< carriage return (ansi)
    static std::cwstring_t xCR_W;
        ///< carriage return (unicode)
    static std::ctstring_t xCR;
        ///< carriage return (ansi or unicode)

    // xNL
    static std::cstring_t  xNL_A;
        ///< newline (ansi)
    static std::cwstring_t xNL_W;
        ///< newline (unicode)
    static std::ctstring_t xNL;
        ///< newline (ansi or unicode)

    // xCRNL
    static std::cstring_t  xCRNL_A;
        ///< carriage return + newline (ansi)
    static std::cwstring_t xCRNL_W;
        ///< carriage return + newline (unicode)
    static std::ctstring_t xCRNL;
        ///< carriage return + newline (ansi or unicode)

    // xCOLON
    static std::cstring_t  xCOLON_A;
        ///< colon (ansi)
    static std::cwstring_t xCOLON_W;
        ///< colon (unicode)
    static std::ctstring_t xCOLON;
        ///< colon (ansi or unicode)

    // xWIN_SLASH
    static std::cstring_t  xWIN_SLASH_A;
        ///< windows backslash (ansi)
    static std::cwstring_t xWIN_SLASH_W;
        ///< windows backslash (unicode)
    static std::ctstring_t xWIN_SLASH;
        ///< windows backslash (ansi or unicode)

    // xUNIX_SLASH
    static std::cstring_t  xUNIX_SLASH_A;
        ///< nix backslash (ansi)
    static std::cwstring_t xUNIX_SLASH_W;
        ///< nix backslash (unicode)
    static std::ctstring_t xUNIX_SLASH;
        ///< nix backslash (ansi or unicode)

    // xSLASH
    static std::cstring_t  xSLASH_A;
        ///< backslash for specific OS (ansi)
    static std::cwstring_t xSLASH_W;
        ///< backslash for specific OS (unicode)
    static std::ctstring_t xSLASH;
        ///< backslash for specific OS (ansi or unicode)

    // xEOL
    static std::cstring_t  xEOL_A;
        ///< end of line (ansi)
    static std::cwstring_t xEOL_W;
        ///< end of line (unicode)
    static std::ctstring_t xEOL;
        ///< end of line (ansi or unicode)

    // xSEMICOLON
    static std::cstring_t  xSEMICOLON_A;
        ///< path separator (ansi)
    static std::cwstring_t xSEMICOLON_W;
        ///< path separator (unicode)
    static std::ctstring_t xSEMICOLON;
        ///< path separator (ansi or unicode)

    // xDOT
    static std::cstring_t  xDOT_A;
        ///< 1 dot (ansi)
    static std::cwstring_t xDOT_W;
        ///< 1 dot (unicode)
    static std::ctstring_t xDOT;
        ///< 1 dot (ansi or unicode)

    // x2DOT
    static std::cstring_t  x2DOT_A;
        ///< 2 dots (ansi)
    static std::cwstring_t x2DOT_W;
        ///< 2 dots (unicode)
    static std::ctstring_t x2DOT;
        ///< 2 dots

    // x3DOT
    static std::cstring_t  x3DOT_A;
        ///< 3 dots (ansi)
    static std::cwstring_t x3DOT_W;
        ///< 3 dots (unicode)
    static std::ctstring_t x3DOT;
        ///< 3 dots (ansi or unicode)

    // xMASK_ALL
    static std::cstring_t  xMASK_ALL_A;
        ///< all files mask (ansi)
    static std::cwstring_t xMASK_ALL_W;
        ///< all files mask (unicode)
    static std::ctstring_t xMASK_ALL;
        ///< all files mask (ansi or unicode)

    // xHT
    static std::cstring_t  xHT_A;
        ///< horizontal tab (ansi)
    static std::cwstring_t xHT_W;
        ///< horizontal tab (unicode)
    static std::ctstring_t xHT;
        ///< horizontal tab (ansi or unicode)

    // xVT
    static std::cstring_t  xVT_A;
        ///< vertical tab (ansi)
    static std::cwstring_t xVT_W;
        ///< vertical tab (unicode)
    static std::ctstring_t xVT;
        ///< vertical tab (ansi or unicode)

    // xSPACE
    static std::cstring_t  xSPACE_A;
        ///< space (ansi)
    static std::cwstring_t xSPACE_W;
        ///< space (unicode)
    static std::ctstring_t xSPACE;
        ///< space (ansi or unicode)

    // xBELL
    static std::cstring_t  xBELL_A;
        ///< alert (ansi)
    static std::cwstring_t xBELL_W;
        ///< alert (unicode)
    static std::ctstring_t xBELL;
        ///< alert (ansi or unicode)

    // xBS
    static std::cstring_t  xBS_A;
        ///< backspace (ansi)
    static std::cwstring_t xBS_W;
        ///< backspace (unicode)
    static std::ctstring_t xBS;
        ///< backspace (ansi or unicode)

    // xFF
    static std::cstring_t  xFF_A;
        ///< formfeed (ansi)
    static std::cwstring_t xFF_W;
        ///< formfeed (unicode)
    static std::ctstring_t xFF;
        ///< formfeed (ansi or unicode)

    // xQM
    static std::cstring_t  xQM_A;
        ///< question mark (ansi)
    static std::cwstring_t xQM_W;
        ///< question mark (unicode)
    static std::ctstring_t xQM;
        ///< question mark (ansi or unicode)

    // xSQM
    static std::cstring_t  xSQM_A;
        ///< single quotation mark (ansi)
    static std::cwstring_t xSQM_W;
        ///< single quotation mark (unicode)
    static std::ctstring_t xSQM;
        ///< single quotation mark (ansi or unicode)

    // xDQM
    static std::cstring_t  xDQM_A;
        ///< double quotation mark (ansi)
    static std::cwstring_t xDQM_W;
        ///< double quotation mark (unicode)
    static std::ctstring_t xDQM;
        ///< double quotation mark (ansi or unicode)

    // xWHITE_SPACES
    static std::cstring_t  xWHITE_SPACES_A;
        ///< white spaces (ansi)
    static std::cwstring_t xWHITE_SPACES_W;
        ///< white spaces (unicode)
    static std::ctstring_t xWHITE_SPACES;
        ///< white spaces (ansi or unicode)

    // xEQUAL
    static std::cstring_t  xEQUAL_A;
        ///< equal sign (ansi)
    static std::cwstring_t xEQUAL_W;
        ///< equal sign (unicode)
    static std::ctstring_t xEQUAL;
        ///< equal sign (ansi or unicode)

    // xHYPHEN
    static std::cstring_t  xHYPHEN_A;
        ///< hyphen (ansi)
    static std::cwstring_t xHYPHEN_W;
        ///< hyphen (unicode)
    static std::ctstring_t xHYPHEN;
        ///< hyphen (ansi or unicode)

    // xUNKNOWN_STRING
    static std::cstring_t  xUNKNOWN_STRING_A;
        ///< unknown string value (ansi)
    static std::cwstring_t xUNKNOWN_STRING_W;
        ///< unknown string value (unicode)
    static std::ctstring_t xUNKNOWN_STRING;
        ///< unknown string value (ansi or unicode)

private:
             CxConst();
    virtual ~CxConst();
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Core/CxConst.cpp>
#endif
