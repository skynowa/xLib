/**
 * \file   FormatC.cpp
 * \brief  format string
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "FormatC.h"
#endif

#include <xLib/Core/Type.h>


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

#if !xFORMAT_MODE_STD_STREAM

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    cbool_t &a_value
)
{
    return a_value ? xT("1") : xT("0");
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    ctchar_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(tchar_t);

    return _toString(buffSize, xT("%c"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    cuchar_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(uchar_t);

    return _toString(buffSize, xT("%c"), a_value);    // %hhu
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    cshort_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(short_t);

    return _toString(buffSize, xT("%hd"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    cushort_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(ushort_t);

    return _toString(buffSize, xT("%hu"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    cint_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(int_t);

    return _toString(buffSize, xT("%d"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    cuint_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(uint_t);

    return _toString(buffSize, xT("%u"), a_value);

}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    clong_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(long_t);

    return _toString(buffSize, xT("%ld"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    culong_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(ulong_t);

    return _toString(buffSize, xT("%lu"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    clonglong_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(longlong_t);

    return _toString(buffSize, xT("%lld"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    culonglong_t &a_value
)
{
    std::csize_t buffSize = 4 * sizeof(ulonglong_t);

    return _toString(buffSize, xT("%llu"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    cfloat_t &a_value,
    cint_t   &a_precision,
    cbool_t  &a_is_fixed
)
{
    return _floatToString(a_value, a_precision, a_is_fixed);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    cdouble_t &a_value,
    cint_t    &a_precision,
    cbool_t   &a_is_fixed
)
{
    return _floatToString(a_value, a_precision, a_is_fixed);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    clongdouble_t &a_value,
    cint_t        &a_precision,
    cbool_t       &a_is_fixed)
{
    return _floatToString(a_value, a_precision, a_is_fixed);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    cvoid_t *a_value
)
{
    std::csize_t buffSize = 4 * sizeof(cvoid_t *);

    return _toString(buffSize, xT("%p"), a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::ctstring_t &
FormatC::toString(
    std::ctstring_t &a_value
)
{
    return a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::toString(
    ctchar_t *a_value
)
{
    return std::tstring_t(a_value);
}
//-------------------------------------------------------------------------------------------------

#endif


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#if !xFORMAT_MODE_STD_STREAM

/* static */
xINLINE std::tstring_t
FormatC::_toString(
    std::csize_t  &a_buffSize,
    ctchar_t      *a_format, ...
)
{
    tchar_t buff[a_buffSize * sizeof(std::tstring_t::value_type)];

    va_list args;
    xVA_START(args, a_format);
    cint_t writtenSize = xTVSNPRINTF(buff, a_buffSize, a_format, args);
    xVA_END(args);

    xTEST_GR(writtenSize, 0);

    return std::tstring_t(buff, buff + writtenSize);
}

#endif
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
