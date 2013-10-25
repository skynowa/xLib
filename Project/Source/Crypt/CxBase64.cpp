/**
 * \file  CxBase64.cpp
 * \brief Base64
 */


#include <xLib/Crypt/CxBase64.h>

#include <xLib/Core/CxChar.h>


xNAMESPACE_ANONYM_BEGIN

std::cstring_t g_csBase64Chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

xNAMESPACE_ANONYM_END

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::string
CxBase64::encode(
    cuchar_t     *a_bytes,
    std::csize_t &a_size
)
{
    std::string sRv;
    std::size_t uiSize = a_size;
    int         i = 0;
    int         j = 0;
    uchar_t     char_array_3[3] = {0};
    uchar_t     char_array_4[4] = {0};

    while (uiSize--) {
        char_array_3[i++] = *(a_bytes++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i ++) {
                sRv += g_csBase64Chars[char_array_4[i]];
            }

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j ++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j ++) {
            sRv += g_csBase64Chars[char_array_4[j]];
        }

        while ((i++ < 3)) {
            sRv += '=';
        }
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::string
CxBase64::encode(
    std::cstring_t &a_str
)
{
    xTEST_NA(a_str);

    return encode(reinterpret_cast<cuchar_t  *>( a_str.data() ), a_str.size());
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::string
CxBase64::decode(
    std::cstring_t &a_str
)
{
    std::string sRv;
    int         in_len = a_str.size();
    int         i = 0;
    int         j = 0;
    int         in_ = 0;
    uchar_t     char_array_4[4] = {0};
    uchar_t     char_array_3[3] = {0};

    while (in_len-- && ( a_str[in_] != '=') && _isValid(a_str[in_])) {
        char_array_4[i++] = a_str[in_]; in_++;
        if (i == 4) {
            for (i = 0; i <4; i++) {
                char_array_4[i] = g_csBase64Chars.find(char_array_4[i]);
            }

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i ++) {
                sRv += char_array_3[i];
            }

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j ++) {
            char_array_4[j] = 0;
        }

        for (j = 0; j < 4; j ++) {
            char_array_4[j] = g_csBase64Chars.find(char_array_4[j]);
        }

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j ++) {
            sRv += char_array_3[j];
        }
    }

    return sRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool
CxBase64::_isValid(
    cuchar_t &a_ch
)
{
    xTEST_NA(a_ch);

    bool_t bRv = isalnum(a_ch) || ('+' == a_ch) || ('/' == a_ch);

    return bRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
