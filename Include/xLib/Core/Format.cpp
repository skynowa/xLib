/**
 * \file   Format.cpp
 * \brief  format string
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Format.h"
#endif

#include <xLib/Core/Char.h>
#include <xLib/Core/Algos.h>


xNAMESPACE_BEGIN2(xlib, core)


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::c_str(
    ctchar_t *a_format, ...    ///< string format
)
{
    xTEST_NA(a_format);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    std::tstring_t sRv;

    va_list args;
    xVA_START(args, a_format);
    sRv = c_strV(a_format, args);
    xVA_END(args);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::c_strV(
    ctchar_t *a_format,    ///< string format
    va_list   a_args       ///< arguments
)
{
    xTEST_NA(a_format);
    xTEST_NA(a_args);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    std::size_t buffSize = 0;
    {
        va_list args;
        xVA_COPY(args, a_args);
        cint_t iRv = xTVSNPRINTF(xPTR_NULL, 0, a_format, args);
        xVA_END(args);

        _xVERIFY(iRv != - 1);
        _xVERIFY(iRv > - 1);

        if (iRv <= - 1) {
            buffSize = 0;
        } else {
            buffSize = static_cast<std::size_t>(iRv) + 1;  // + 1 for '\0'
        }

        // std::tcout << xTRACE_VAR(buffSize) << std::endl;

        xCHECK_RET(buffSize == 0, std::tstring_t());
    }

    // write to buffer
    std::tstring_t buff(buffSize, xT('\0'));
    {
        va_list args;
        xVA_COPY(args, a_args);
        cint_t iRv = xTVSNPRINTF(&buff.at(0), buffSize, a_format, args);
        xVA_END(args);

        _xVERIFY(iRv != - 1);
        _xVERIFY(iRv > - 1);
        _xVERIFY(iRv == buffSize - 1);

        buff.resize(iRv);
    }

    return buff;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::ctstring_t &
Format::_specifier()
{
    static std::ctstring_t sRv(xT("{}"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::ctstring_t &
Format::_delimiter()
{
    static std::ctstring_t sRv(xT(", "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE tchar_t
Format::_unprintableChar()
{
    static tchar_t chRv(xT('?'));

    return chRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const bool           &a_value   ///< value
)
{
    a_ss << std::boolalpha;
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const char           &a_value   ///< value
)
{
#if xANSI
    a_ss << a_value;
#else
    a_ss << static_cast<wchar_t>(a_value);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const wchar_t        &a_value   ///< value
)
{
    if ( ::iswprint(a_value) ) {
        a_ss << static_cast<tchar_t>(a_value);
    } else {
        a_ss << _formatUnprintableChar(a_value);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned char  &a_value   ///< value
)
{
    if ( ::isprint(a_value) ) {
        a_ss << a_value;
    } else {
        a_ss << _formatUnprintableChar(a_value);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const short          &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned short &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const int            &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned int   &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long           &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned long  &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long long      &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t     &a_ss,     ///< [out]
    const unsigned long long &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const float          &a_value   ///< value
)
{
    _formatFloat(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const double         &a_value   ///< value
)
{
    _formatFloat(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long double    &a_value   ///< value
)
{
    _formatFloat(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const void *          a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_ss << xT("null");
    } else {
        a_ss << a_value;
    }
}
//-------------------------------------------------------------------------------------------------
#if xOPTION_CPP11

/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::nullptr_t  a_value   ///< value
)
{
    a_ss << xT("nullptr");
}

#endif
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const char *          a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_ss << xT("null");
    } else {
        _format(a_ss, std::string(a_value));
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const wchar_t *       a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_ss << xT("null");
    } else {
        _format(a_ss, std::wstring(a_value));
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::wstring   &a_value   ///< value
)
{
    std::tstring_t sRv;
    sRv.reserve( a_value.size() );

    for (size_t i = 0; i < a_value.size(); ++ i) {
        if ( ::iswprint(a_value[i]) ) {
            sRv += static_cast<tchar_t>( a_value[i] );
        } else {
            sRv += _formatUnprintableChar( a_value[i] );
        }
    }

    a_ss << sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::string    &a_value   ///< value
)
{
#if xANSI
    a_ss << a_value;
#else
    a_ss << std::wstring(a_value.begin(), a_value.end());
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::ustring_t &a_value   ///< value
)
{
    _formatString(a_ss, a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------
#if xOPTION_CPP11

template<typename T, std::size_t N>
/* static */
inline void
Format::_format(
    std::tstringstream_t   &a_ss,     ///< [out]
    const std::array<T, N> &a_value   ///< value
)
{
    _formatContainer(a_ss, a_value);
}

#endif
//-------------------------------------------------------------------------------------------------
template<typename T1, class T2>
/* static */
inline void
Format::_format(
    std::tstringstream_t    &a_ss,     ///< [out]
    const std::pair<T1, T2> &a_value   ///< value
)
{
    _format(a_ss, xT("{"));
    _format(a_ss, a_value.first);
    _format(a_ss, _delimiter());
    _format(a_ss, a_value.second);
    _format(a_ss, xT("}"));
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::vector<T> &a_value   ///< value
)
{
    _formatContainer(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::list<T>   &a_value   ///< value
)
{
    _formatContainer(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::set<T>    &a_value   ///< value
)
{
    _formatContainer(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void
Format::_format(
    std::tstringstream_t   &a_ss,     ///< [out]
    const std::multiset<T> &a_value   ///< value
)
{
    _formatContainer(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T1, class T2>
/* static */
inline void
Format::_format(
    std::tstringstream_t   &a_ss,     ///< [out]
    const std::map<T1, T2> &a_value   ///< value
)
{
    _formatContainer(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T1, class T2>
/* static */
inline void
Format::_format(
    std::tstringstream_t        &a_ss,     ///< [out]
    const std::multimap<T1, T2> &a_value   ///< value
)
{
    _formatContainer(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const T              &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
#if xLIB_QT

/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const QString        &a_value   ///< value
)
{
#if xANSI
    a_ss << a_value.toStdString();
#else
    a_ss << a_value.toStdWString();
#endif
}

#endif
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void
Format::_formatFloat(
    std::tstringstream_t &a_ss,
    const T              &a_value
)
{
    a_ss
        << std::setprecision( _floatPrecisionMax<T>() )
        << std::showpoint
        << a_value;

    std::tstring_t value = a_ss.str();
    std::size_t    i     = value.find_last_not_of(xT('0'));

    if (i != std::tstring_t::npos && i != value.size() - 1) {
        if (value[i] == xT('.')) {
            ++ i;
        }

        value = value.substr(0, i + 1);
    }

    a_ss.str(value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline int
Format::_floatPrecisionMax()
{
#if xOPTION_CPP11
    return std::numeric_limits<T>::max_digits10;
#else
    return std::numeric_limits<T>::digits10 + 1;
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline std::tstring_t
Format::_formatUnprintableChar(
    const T &a_value
)
{
   /**
    * FAQ: C documentation for isprint
    *
    * +---------+---------------------------+-------------------+
    * | ASCII   | Characters                | isprint, iswprint |
    * +---------+---------------------------+-------------------+
    * | 0 - 8   | control codes (NUL, etc.) | -                 |
    * | 9       | tab (\t)                  | -                 |
    * | 10 - 13 | whitespaces (\n,\v,\f,\r) | -                 |
    * | 14 - 31 | control codes             | -                 |
    * | 32      | space                     | +                 |
    * | 33 - 47 | !"#$%&'()*+,-./           | +                 |
    * | 48 - 57 | 123456789                 | +                 |
    * | 58 - 64 | :;<=>?@                   | +                 |
    * | 65 - 70 | ABCDEF                    | +                 |
    * | 71 - 90 | GHIJKLMNOPQRSTUVWXYZ      | +                 |
    * | 91 - 96 | [\]^_`                    | +                 |
    * | 97 -102 | abcdef                    | +                 |
    * | 103-122 | ghijklmnopqrstuvwxyz      | +                 |
    * | 123-126 | {|}~                      | +                 |
    * | 127     | backspace character (DEL) | -                 |
    * +-------------------------------------+-------------------+
    */

    Char<T> ch(a_value);
    if      ( Algos::isInBounds<T>(ch.character(), 0, 31) ) {
        return xT("<") + ch.symbol() + xT(">");
    }
    else if ( Algos::isInBounds<T>(ch.character(), 32, 126) ) {
        return ch.symbol();
    }
    else if ( Algos::isInBounds<T>(ch.character(), 127, 255) ) {
        return xT("?");
    }
    else {
        return xT("?");
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
