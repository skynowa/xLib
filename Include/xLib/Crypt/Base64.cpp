/**
 * \file  Base64.inl
 * \brief Base64
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Base64.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>


xNAMESPACE_ANONYM_BEGIN

std::cstring_t base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

xNAMESPACE_ANONYM_END

xNAMESPACE_BEGIN2(xl, crypt)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::string
Base64::encode(
    cuchar_t     *a_bytes,
    std::csize_t &a_size
)
{
    std::string sRv;
    std::size_t inSize        = a_size;
    int         i             = 0;
    int         j             = 0;
    uchar_t     charArray3[3] = {0};
    uchar_t     charArray4[4] = {0};

    while (inSize --) {
        charArray3[i ++] = *(a_bytes ++);
        if (i == 3) {
            charArray4[0] = (charArray3[0] & 0xFC) >> 2;
            charArray4[1] = static_cast<uchar_t>( ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xF0) >> 4) );
            charArray4[2] = static_cast<uchar_t>( ((charArray3[1] & 0x0F) << 2) + ((charArray3[2] & 0xC0) >> 6) );
            charArray4[3] = charArray3[2] & 0x3F;

            for (i = 0; i < 4; ++ i) {
                sRv += ::base64Chars[ charArray4[i] ];
            }

            i = 0;
        }
    }

    if (i != 0) {
        for (j = i; j < 3; ++ j) {
            charArray3[j] = '\0';
        }

        charArray4[0] = (charArray3[0] & 0xFC) >> 2;
        charArray4[1] = static_cast<uchar_t>( ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xF0) >> 4) );
        charArray4[2] = static_cast<uchar_t>( ((charArray3[1] & 0x0F) << 2) + ((charArray3[2] & 0xC0) >> 6) );
        charArray4[3] = charArray3[2] & 0x3F;

        for (j = 0; (j < i + 1); j ++) {
            sRv += ::base64Chars[ charArray4[j] ];
        }

        while (i ++ < 3) {
            sRv += '=';
        }
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::string
Base64::encode(
    std::cstring_t &a_str
)
{
    xTEST_NA(a_str);

    return encode(reinterpret_cast<cuchar_t  *>( a_str.data() ), a_str.size());
}
//-------------------------------------------------------------------------------------------------
xINLINE std::string
Base64::decode(
    std::cstring_t &a_str
)
{
    std::string sRv;
    int         inSize        = static_cast<int>( a_str.size() );
    int         i             = 0;
    int         j             = 0;
    std::size_t in            = 0;
    uchar_t     charArray4[4] = {0};
    uchar_t     charArray3[3] = {0};

    while (inSize -- && (a_str[in] != '=') && _isValid( static_cast<cuchar_t>( a_str[in] ) )) {
        charArray4[i ++] = static_cast<cuchar_t>( a_str[in] );
        in ++;
        if (i == 4) {
            for (i = 0; i < 4; ++ i) {
                charArray4[i] = static_cast<uchar_t>( ::base64Chars.find( static_cast<ctchar_t>(charArray4[i]) ) );
            }

            charArray3[0] = static_cast<uchar_t>( (charArray4[0] << 2)         + ((charArray4[1] & 0x30) >> 4) );
            charArray3[1] = static_cast<uchar_t>( ((charArray4[1] & 0xF) << 4) + ((charArray4[2] & 0x3C) >> 2) );
            charArray3[2] = static_cast<uchar_t>( ((charArray4[2] & 0x3) << 6) + charArray4[3] );

            for (i = 0; (i < 3); ++ i) {
                sRv += static_cast<ctchar_t>( charArray3[i] );
            }

            i = 0;
        }
    }

    if (i != 0) {
        for (j = i; j < 4; ++ j) {
            charArray4[j] = 0;
        }

        for (j = 0; j < 4; ++ j) {
            charArray4[j] = static_cast<uchar_t>( ::base64Chars.find( static_cast<ctchar_t>( charArray4[j] )) );
        }

        charArray3[0] = static_cast<uchar_t>( (charArray4[0] << 2)         + ((charArray4[1] & 0x30) >> 4) );
        charArray3[1] = static_cast<uchar_t>( ((charArray4[1] & 0xF) << 4) + ((charArray4[2] & 0x3C) >> 2) );
        charArray3[2] = static_cast<uchar_t>( ((charArray4[2] & 0x3) << 6) + charArray4[3] );

        for (j = 0; (j < i - 1); ++ j) {
            sRv += static_cast<ctchar_t>( charArray3[j] );
        }
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Base64::_isValid(
    cuchar_t &a_ch
)
{
    return std::isalnum(a_ch) || (a_ch == '+') || (a_ch == '/');
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, crypt)
