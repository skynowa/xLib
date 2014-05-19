/**
 * \file  CxBase64.inl
 * \brief Base64
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE_ANONYM_BEGIN

std::cstring_t base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

xNAMESPACE_ANONYM_END

xNAMESPACE_BEGIN2(xlib, crypt)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::string
CxBase64::encode(
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
inline std::string
CxBase64::encode(
    std::cstring_t &a_str
)
{
    xTEST_NA(a_str);

    return encode(reinterpret_cast<cuchar_t  *>( a_str.data() ), a_str.size());
}
//-------------------------------------------------------------------------------------------------
inline std::string
CxBase64::decode(
    std::cstring_t &a_str
)
{
    std::string sRv;
    int         inSize        = static_cast<int>( a_str.size() );
    int         i             = 0;
    int         j             = 0;
    int         in            = 0;
    uchar_t     charArray4[4] = {0};
    uchar_t     charArray3[3] = {0};

    while (inSize -- && (a_str[in] != '=') && _isValid( a_str[in] )) {
        charArray4[i ++] = a_str[in];
        in ++;
        if (i == 4) {
            for (i = 0; i < 4; ++ i) {
                charArray4[i] = static_cast<uchar_t>( ::base64Chars.find(charArray4[i]) );
            }

            charArray3[0] = static_cast<uchar_t>( (charArray4[0] << 2)         + ((charArray4[1] & 0x30) >> 4) );
            charArray3[1] = static_cast<uchar_t>( ((charArray4[1] & 0xF) << 4) + ((charArray4[2] & 0x3C) >> 2) );
            charArray3[2] = static_cast<uchar_t>( ((charArray4[2] & 0x3) << 6) + charArray4[3] );

            for (i = 0; (i < 3); ++ i) {
                sRv += charArray3[i];
            }

            i = 0;
        }
    }

    if (i != 0) {
        for (j = i; j < 4; ++ j) {
            charArray4[j] = 0;
        }

        for (j = 0; j < 4; ++ j) {
            charArray4[j] = static_cast<uchar_t>( ::base64Chars.find(charArray4[j]) );
        }

        charArray3[0] = static_cast<uchar_t>( (charArray4[0] << 2)         + ((charArray4[1] & 0x30) >> 4) );
        charArray3[1] = static_cast<uchar_t>( ((charArray4[1] & 0xF) << 4) + ((charArray4[2] & 0x3C) >> 2) );
        charArray3[2] = static_cast<uchar_t>( ((charArray4[2] & 0x3) << 6) + charArray4[3] );

        for (j = 0; (j < i - 1); ++ j) {
            sRv += charArray3[j];
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
inline bool
CxBase64::_isValid(
    cuchar_t &a_ch
)
{
    return std::isalnum(a_ch) || (a_ch == '+') || (a_ch == '/');
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)
