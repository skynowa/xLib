/**
 * \file  OStream.cpp
 * \brief print string
 */


#include "OStream.h"


namespace xl::core
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
OStream::str() const /* final */
{
	return _os.str();
}
//-------------------------------------------------------------------------------------------------
void_t
OStream::str(
	std::ctstring_t &a_value
)
{
	_os.str(a_value);
}
//-------------------------------------------------------------------------------------------------
void_t
OStream::clear()
{
	_os.clear();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public / operators <<
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const bool a_value   ///< value
)
{
    _os << (a_value ? xT("true") : xT("false"));

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const char a_value   ///< value
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
OStream &
OStream::operator << (
    const wchar_t a_value   ///< value
)
{
    if ( ::iswprint(  static_cast<wint_t>(a_value) ) ) {
        _os << static_cast<tchar_t>(a_value);
    } else {
        _os << CharW(a_value).symbol();
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const unsigned char a_value   ///< value
)
{
    if ( ::isprint(a_value) ) {
        _os << a_value;
    } else {
        _os << CharU(a_value).symbol();
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const short a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const unsigned short a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const int a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const unsigned int a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const long a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const unsigned long a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const long long a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const unsigned long long a_value   ///< value
)
{
    _os << a_value;

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const float a_value   ///< value
)
{
    _printFloat(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const double a_value   ///< value
)
{
    _printFloat(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const long double a_value   ///< value
)
{
    _printFloat(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const void *a_value   ///< value
)
{
    if (a_value == nullptr) {
        _os << xT("null");
    } else {
        _os << a_value;
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const char *a_value   ///< value
)
{
    if (a_value == nullptr) {
        _os << xT("null");
    } else {
        _os << std::string(a_value);
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const wchar_t *a_value   ///< value
)
{
    if (a_value == nullptr) {
        _os << xT("null");
    } else {
        _printValue( std::wstring(a_value) );
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const std::wstring &a_value   ///< value
)
{
    std::tstring_t sRv;
    sRv.reserve( a_value.size() );

    for (size_t i = 0; i < a_value.size(); ++ i) {
        if ( ::iswprint( static_cast<wint_t>(a_value[i])) ) {
            sRv += static_cast<tchar_t>( a_value[i] );
        } else {
            sRv += CharW( a_value[i] ).symbol();
        }
    }

    _os << sRv;

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const std::string &a_value   ///< value
)
{
#if xANSI
    _os << a_value;
#else
    _os << std::wstring(a_value.cbegin(), a_value.cend());
#endif

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const std::ustring_t &a_value   ///< value
)
{
    _printString(a_value.cbegin(), a_value.cend());

    return *this;
}
//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
    const std::nullptr_t a_value   ///< value
)
{
    xUNUSED(a_value);

    _os << xT("nullptr");

    return *this;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   LibC
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
OStream &
OStream::operator << (
	const std::tm &a_value   ///< value
)
{
	_os
		<< "std::tm (sizeof=" << sizeof(a_value) << xT("):") << "\n"
		<< xT("    tm_sec:   ") << a_value.tm_sec            << "\n"
		<< xT("    tm_min:   ") << a_value.tm_min            << "\n"
		<< xT("    tm_hour:  ") << a_value.tm_hour           << "\n"
		<< xT("    tm_mday:  ") << a_value.tm_mday           << "\n"
		<< xT("    tm_mon:   ") << (a_value.tm_mon  + 1)     << "\n"
		<< xT("    tm_year:  ") << (a_value.tm_year + 1900)  << "\n"
		<< xT("    tm_wday:  ") << a_value.tm_wday           << "\n"
		<< xT("    tm_yday:  ") << a_value.tm_yday           << "\n"
		<< xT("    tm_isdst: ") << a_value.tm_isdst;

    return *this;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
OStream::_bracketOpen()
{
    static std::ctstring_t sRv(xT("{"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
OStream::_bracketClose()
{
    static std::ctstring_t sRv(xT("}"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::ctstring_t &
OStream::_delimiter()
{
    static std::ctstring_t sRv(xT(", "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
