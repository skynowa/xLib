/**
 * \file   StdStream.cpp
 * \brief  print string
 */


#include "StdStream.h"


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
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
StdStream::print(
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
StdStream::print(
    std::tostream_t &a_os,     ///< [out]
    const wchar_t    a_value   ///< value
)
{
    if ( ::iswprint(  static_cast<wint_t>(a_value) ) ) {
        a_os << static_cast<tchar_t>(a_value);
    } else {
        a_os << _printUnprintableChar(a_value);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t     &a_os,     ///< [out]
    const unsigned char  a_value   ///< value
)
{
    if ( ::isprint(a_value) ) {
        a_os << a_value;
    } else {
        a_os << _printUnprintableChar(a_value);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t &a_os,     ///< [out]
    const short      a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t      &a_os,     ///< [out]
    const unsigned short  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t &a_os,     ///< [out]
    const int        a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t    &a_os,     ///< [out]
    const unsigned int  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t &a_os,     ///< [out]
    const long       a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t     &a_os,     ///< [out]
    const unsigned long  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t &a_os,     ///< [out]
    const long long  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t          &a_os,     ///< [out]
    const unsigned long long  a_value   ///< value
)
{
    a_os << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t &a_os,     ///< [out]
    const float      a_value   ///< value
)
{
    _printFloat(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t &a_os,     ///< [out]
    const double     a_value   ///< value
)
{
    _printFloat(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t   &a_os,     ///< [out]
    const long double  a_value   ///< value
)
{
    _printFloat(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
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
StdStream::print(
    std::tostream_t &a_os,     ///< [out]
    const char *     a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_os << xT("null");
    } else {
        print(a_os, std::string(a_value));
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
    std::tostream_t &a_os,     ///< [out]
    const wchar_t *  a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_os << xT("null");
    } else {
        print(a_os, std::wstring(a_value));
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
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
            sRv += _printUnprintableChar( a_value[i] );
        }
    }

    a_os << sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StdStream::print(
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
StdStream::print(
    std::tostream_t      &a_os,     ///< [out]
    const std::ustring_t &a_value   ///< value
)
{
    _printString(a_os, a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------
#if xLANG_CPP11

/* static */
void_t
StdStream::print(
    std::tostream_t      &a_os,     ///< [out]
    const std::nullptr_t  a_value   ///< value
)
{
    xUNUSED(a_value);

    a_os << xT("nullptr");
}

#endif
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
StdStream::_bracketOpen()
{
    static std::ctstring_t sRv(xT("{"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
StdStream::_bracketClose()
{
    static std::ctstring_t sRv(xT("}"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
StdStream::_delimiter()
{
    static std::ctstring_t sRv(xT(", "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
tchar_t
StdStream::_unprintableChar()
{
    static tchar_t chRv(xT('?'));

    return chRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
