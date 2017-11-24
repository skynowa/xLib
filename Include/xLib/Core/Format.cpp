/**
 * \file   Format.cpp
 * \brief  format string
 */


#include "Format.h"

#include <xLib/Core/Char.h>


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   Format - private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
Format::_specifier()
{
    static std::ctstring_t sRv(_specifierOpen() + _specifierClose());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
Format::_specifierOpen()
{
    static std::ctstring_t sRv(xT("{"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
Format::_specifierClose()
{
    static std::ctstring_t sRv(xT("}"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
Format::_delimiter()
{
    static std::ctstring_t sRv(xT(", "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
tchar_t
Format::_unprintableChar()
{
    static tchar_t chRv(xT('?'));

    return chRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const bool       a_value   ///< value
)
{
    a_os << std::boolalpha;
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const char       a_value   ///< value
)
{
#if xANSI
    a_os << a_value;
#else
    a_os << static_cast<wchar_t>(a_value);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const wchar_t    a_value   ///< value
)
{
    if ( ::iswprint(  static_cast<wint_t>(a_value) ) ) {
        a_os << static_cast<tchar_t>(a_value);
    } else {
        a_os << _formatUnprintableChar(a_value);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t     &a_os,     ///< [out]
    const unsigned char  a_value   ///< value
)
{
    if ( ::isprint(a_value) ) {
        a_os << a_value;
    } else {
        a_os << _formatUnprintableChar(a_value);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const short      a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t      &a_os,     ///< [out]
    const unsigned short  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const int        a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t    &a_os,     ///< [out]
    const unsigned int  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const long       a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t     &a_os,     ///< [out]
    const unsigned long  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const long long  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t          &a_os,     ///< [out]
    const unsigned long long  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const float      a_value   ///< value
)
{
    _formatFloat(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const double     a_value   ///< value
)
{
    _formatFloat(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t   &a_os,     ///< [out]
    const long double  a_value   ///< value
)
{
    _formatFloat(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const void *     a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_os << xT("null");
    } else {
        a_os << a_value;
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const char *     a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_os << xT("null");
    } else {
        _format(a_os, std::string(a_value));
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t &a_os,     ///< [out]
    const wchar_t *  a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_os << xT("null");
    } else {
        _format(a_os, std::wstring(a_value));
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t    &a_os,     ///< [out]
    const std::wstring &a_value   ///< value
)
{
    std::tstring_t sRv;
    sRv.reserve( a_value.size() );

    for (size_t i = 0; i < a_value.size(); ++ i) {
        if ( ::iswprint( static_cast<wint_t>(a_value[i])) ) {
            sRv += static_cast<tchar_t>( a_value[i] );
        } else {
            sRv += _formatUnprintableChar( a_value[i] );
        }
    }

    a_os << sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t   &a_os,     ///< [out]
    const std::string &a_value   ///< value
)
{
#if xANSI
    a_os << a_value;
#else
    a_os << std::wstring(a_value.begin(), a_value.end());
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Format::_format(
    std::tostream_t      &a_os,     ///< [out]
    const std::ustring_t &a_value   ///< value
)
{
    _formatString(a_os, a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------
#if xLANG_CPP11

/* static */
void_t
Format::_format(
    std::tostream_t      &a_os,     ///< [out]
    const std::nullptr_t  a_value   ///< value
)
{
    xUNUSED(a_value);

    a_os << xT("nullptr");
}

#endif
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
