/**
 * \file   Format.cpp
 * \brief  format string
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Format.h"
#endif

#include <xLib/Core/Char.h>
#include <xLib/Test/StdTest.h>


xNAMESPACE_BEGIN2(xlib, core)


/**************************************************************************************************
*   FormatC - public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::str(
    cptr_ctchar_t a_format, ...    ///< string format
)
{
    xTEST_NA(a_format);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    std::tstring_t sRv;

    va_list args;
    xVA_START(args, a_format);
    sRv = strV(a_format, args);
    xVA_END(args);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::strV(
    cptr_ctchar_t a_format,    ///< string format
    va_list       a_args       ///< arguments
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
        _xVERIFY(iRv == static_cast<int_t>(buffSize) - 1);

        buff.resize(iRv);
    }

    return buff;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Format - private
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
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const bool            a_value   ///< value
)
{
    a_ss << std::boolalpha;
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const char            a_value   ///< value
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
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const wchar_t         a_value   ///< value
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
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned char   a_value   ///< value
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
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const short           a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned short  a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const int             a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned int    a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long            a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned long   a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long long       a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t     &a_ss,     ///< [out]
    const unsigned long long  a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const float           a_value   ///< value
)
{
    _formatFloat(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const double          a_value   ///< value
)
{
    _formatFloat(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long double     a_value   ///< value
)
{
    _formatFloat(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
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
/* static */
xINLINE void_t
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
xINLINE void_t
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
xINLINE void_t
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
xINLINE void_t
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
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::ustring_t &a_value   ///< value
)
{
    _formatString(a_ss, a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------
#if xLANG_CPP11

/* static */
xINLINE void_t
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::nullptr_t  a_value   ///< value
)
{
    xUNUSED(a_value);

    a_ss << xT("nullptr");
}

#endif
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
