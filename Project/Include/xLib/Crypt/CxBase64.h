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
xNAMESPACE_BEGIN(NxLib)

class CxBase64 :
    public CxNonCopyable
    /// Base64
{
public:
    static std::string encode(cuchar_t *bytes, std::csize_t &size) xWARN_UNUSED_RV;
        ///< encoding
    static std::string encode(std::cstring_t &str) xWARN_UNUSED_RV;
        ///< encoding
    static std::string decode(std::cstring_t &str) xWARN_UNUSED_RV;
        ///< decoding
private:
                       CxBase64();
        ///< constructor
    virtual           ~CxBase64();
        ///< destructor

    static bool        _isValid(cuchar_t &ch) xWARN_UNUSED_RV;
        ///< check char for validness
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Crypt/CxBase64.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxBase64H
