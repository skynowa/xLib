/**
 * \file   StdStream2.cpp
 * \brief  print string
 */


#include "StdStream2.h"


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
StdStream2::StdStream2()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
StdStream2::~StdStream2()
{
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
StdStream2::str() const
{
	return _os.str();
}
//-------------------------------------------------------------------------------------------------
void_t
StdStream2::str(
	std::ctstring_t &a_value
)
{
	_os.str(a_value);
}
//-------------------------------------------------------------------------------------------------
void_t
StdStream2::clear()
{
	_os.clear();
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const bool       a_value   ///< value
)
{
    _os << std::boolalpha;
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const char       a_value   ///< value
)
{
#if xANSI
    _os << a_value;
#else
    _os << static_cast<wchar_t>(a_value);
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const wchar_t    a_value   ///< value
)
{
    if ( ::iswprint(  static_cast<wint_t>(a_value) ) ) {
        _os << static_cast<tchar_t>(a_value);
    } else {
        _os << _printUnprintableChar(a_value);
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const unsigned char  a_value   ///< value
)
{
    if ( ::isprint(a_value) ) {
        _os << a_value;
    } else {
        _os << _printUnprintableChar(a_value);
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const short      a_value   ///< value
)
{
    _os << a_value;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const unsigned short  a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const int        a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const unsigned int  a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const long       a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const unsigned long  a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const long long  a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const unsigned long long  a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const float      a_value   ///< value
)
{
    _printFloat(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const double     a_value   ///< value
)
{
    _printFloat(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const long double  a_value   ///< value
)
{
    _printFloat(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const void *     a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        _os << xT("null");
    } else {
        _os << a_value;
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const char *     a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        _os << xT("null");
    } else {
        _os << std::string(a_value);
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const wchar_t *  a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        _os << xT("null");
    } else {
        /// _os << std::wstring(a_value);
        StdStream2::operator << ( std::wstring(a_value) );
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
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

    _os << sRv;

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const std::string &a_value   ///< value
)
{
#if xANSI
    _os << a_value;
#else
    _os << std::wstring(a_value.begin(), a_value.end());
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
StdStream2 &
StdStream2::operator << (
    const std::ustring_t &a_value   ///< value
)
{
    _printString(a_value.begin(), a_value.end());

    return *this;
}
//-------------------------------------------------------------------------------------------------
#if xLANG_CPP11

StdStream2 &
StdStream2::operator << (
    const std::nullptr_t  a_value   ///< value
)
{
    xUNUSED(a_value);

    _os << xT("nullptr");

    return *this;
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
StdStream2::_bracketOpen()
{
    static std::ctstring_t sRv(xT("{"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
StdStream2::_bracketClose()
{
    static std::ctstring_t sRv(xT("}"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
StdStream2::_delimiter()
{
    static std::ctstring_t sRv(xT(", "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
tchar_t
StdStream2::_unprintableChar()
{
    static tchar_t chRv(xT('?'));

    return chRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
