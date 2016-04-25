/**
 * \file   Format.cpp
 * \brief  format string
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Format.h"
#endif

#include <xLib/Core/Type.h>


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

    std::tstring_t buff(64, 0);
    int_t          writtenSize = - 1;

    for ( ; ; ) {
        va_list args;
        xVA_COPY(args, a_args);
        writtenSize = xTVSNPRINTF(&buff.at(0), buff.size(), a_format, args);
        xVA_END(args);

        _xVERIFY(writtenSize > - 1);
        xCHECK_DO(static_cast<size_t>( writtenSize ) < buff.size(), break);

        buff.resize(buff.size() * 2);
    }

    buff.resize(writtenSize);

    return buff;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
// strEmpty
xINLINE std::cstring_t &
Format::specifier()
{
    static std::cstring_t sRv(xT("{}"));

    return sRv;
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
    const tchar_t        &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned char  &a_value   ///< value
)
{
    a_ss << a_value;
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
    a_ss << std::setprecision( _floatPrecisionMax<float>() );
    a_ss << std::fixed;
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const double         &a_value   ///< value
)
{
    a_ss << std::setprecision( _floatPrecisionMax<double>() );
    a_ss << std::fixed;
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long double    &a_value   ///< value
)
{
    a_ss << std::setprecision( _floatPrecisionMax<long double>() );
    a_ss << std::fixed;
    a_ss << a_value;
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
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::tstring_t &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::ustring_t &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const tchar_t *       a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t      &a_ss,     ///< [out]
    const std::pair_tstring_t &a_value   ///< value
)
{
    _format(a_ss, xT("{") + a_value.first + xT(", ") + a_value.second + xT("}"));
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t     &a_ss,     ///< [out]
    const std::vec_tstring_t &a_value   ///< value
)
{
    _formatRange(a_ss, a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t      &a_ss,     ///< [out]
    const std::list_tstring_t &a_value   ///< value
)
{
    _formatRange(a_ss, a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t     &a_ss,     ///< [out]
    const std::map_tstring_t &a_value   ///< value
)
{
    _formatRange(a_ss, a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
xINLINE int
Format::_floatPrecisionMax()
{
#if xOPTION_CPP11
    return std::numeric_limits<T>::max_digits10;
#else
    return std::numeric_limits<T>::digits10 + 1;
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
