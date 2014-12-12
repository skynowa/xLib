/**
 * \file   Format.cpp
 * \brief  format string
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Format.h"
#endif

#include <xLib/Core/Type.h>
// #include <xLib/Log/Trace.h>


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(cbool_t &a_value)
{
    // Trace() << Type::name(a_value);
    return a_value ? xT("true") : xT("false");
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(ctchar_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = 4 * sizeof(tchar_t);

    return _toString(buffSize, xT("%c"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(cuchar_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = 4 * sizeof(uchar_t);

    return _toString(buffSize, xT("%hhu"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(cshort_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = 4 * sizeof(short_t);

    return _toString(buffSize, xT("%hd"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(cushort_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = 4 * sizeof(ushort_t);

    return _toString(buffSize, xT("%hu"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(cint_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(int_t);

    return _toString(buffSize, xT("%d"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(cuint_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(uint_t);

    return _toString(buffSize, xT("%u"), a_value);

}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(clong_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(long_t);

    return _toString(buffSize, xT("%ld"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(culong_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(ulong_t);

    return _toString(buffSize, xT("%lu"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(clonglong_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(longlong_t);

    return _toString(buffSize, xT("%lld"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(culonglong_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(ulonglong_t);

    return _toString(buffSize, xT("%llu"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(cfloat_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = std::numeric_limits<float_t>::max_exponent10 + 20;

    return _toString(buffSize, xT("%f"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(cdouble_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = std::numeric_limits<double>::max_exponent10 + 20;

    return _toString(buffSize, xT("%f"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(clongdouble_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = std::numeric_limits<longdouble_t>::max_exponent10 + 20;

    return _toString(buffSize, xT("%Lf"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(cvoid_t *a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(cvoid_t *);

    return _toString(buffSize, xT("%p"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::ctstring_t &
Format::toString(std::ctstring_t &a_value)
{
    // Trace() << Type::name(a_value);

    return a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::toString(ctchar_t *a_value)
{
    // Trace() << Type::name(a_value);

    return std::tstring_t(a_value);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::_toString(
    std::csize_t  &a_buffSize,
    const tchar_t *a_format, ...
)
{
    tchar_t buff[a_buffSize * sizeof(std::tstring_t::value_type)];

    va_list args;
    xVA_START(args, a_format);

    cint_t writtenSize = xTVSNPRINTF(buff, a_buffSize, a_format, args);
    xTEST_GR(writtenSize, 0);

    xVA_END(args);

    return std::tstring_t(buff, buff + writtenSize);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
