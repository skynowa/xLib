/**
 * \file  CxBase64.cpp
 * \brief Base64
 */


#include <xLib/Crypt/CxBase64.h>

#include <xLib/Common/CxChar.h>


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
std::string
CxBase64::encode(
    cuchar_t     *a_cucBytes,
    std::csize_t &a_cuiSize
)
{
    std::string sRv;
    std::size_t uiSize = a_cuiSize;
    int         i = 0;
    int         j = 0;
    uchar_t     char_array_3[3] = {0};
    uchar_t     char_array_4[4] = {0};

    while (uiSize--) {
        char_array_3[i++] = *(a_cucBytes++);
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
std::string 
CxBase64::encode(
    std::cstring_t &a_csStr
)
{
    xTEST_NA(a_csStr);

    return encode(reinterpret_cast<cuchar_t  *>( a_csStr.data() ), a_csStr.size());
}
//------------------------------------------------------------------------------
/* static */
std::string
CxBase64::decode(
    std::cstring_t &a_csStr
)
{
    std::string sRv;
    int         in_len = a_csStr.size();
    int         i = 0;
    int         j = 0;
    int         in_ = 0;
    uchar_t     char_array_4[4] = {0};
    uchar_t     char_array_3[3] = {0};

    while (in_len-- && ( a_csStr[in_] != '=') && _isValid(a_csStr[in_])) {
        char_array_4[i++] = a_csStr[in_]; in_++;
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
CxBase64::CxBase64() {

}
//------------------------------------------------------------------------------
/* virtual */
CxBase64::~CxBase64() {

}
//------------------------------------------------------------------------------
/* static */
bool
CxBase64::_isValid(
    cuchar_t &a_cchChar
)
{
    xTEST_NA(a_cchChar);

    bool_t bRv = isalnum(a_cchChar) || ('+' == a_cchChar) || ('/' == a_cchChar);

    return bRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
