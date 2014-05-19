/**
 * \file  CxBase64.h
 * \brief base64
 */


#pragma once

#ifndef xLib_CxBase64H
#define xLib_CxBase64H
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, crypt)

class CxBase64
    /// Base64
{
public:
                CxBase64() {};
        ///< constructor
    virtual    ~CxBase64() {};
        ///< destructor

    std::string encode(cuchar_t *bytes, std::csize_t &size) xWARN_UNUSED_RV;
        ///< encoding
    std::string encode(std::cstring_t &str) xWARN_UNUSED_RV;
        ///< encoding
    std::string decode(std::cstring_t &str) xWARN_UNUSED_RV;
        ///< decoding
private:
    bool        _isValid(cuchar_t &ch) xWARN_UNUSED_RV;
        ///< check char for validness

    xNO_COPY_ASSIGN(CxBase64)
};

xNAMESPACE_END2(xlib, crypt)
//-------------------------------------------------------------------------------------------------
#include "CxBase64.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxBase64H
