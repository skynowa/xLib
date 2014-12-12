/**
 * \file   Format.cpp
 * \brief  [CLASS_COMMENTS]
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


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(cbool_t &a_value)
{
    // Trace() << Type::name(a_value);
    return a_value ? xT("true") : xT("false");
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(ctchar_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = 4 * sizeof(tchar_t);

    return _toString(buffSize, xT("%c"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(cuchar_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = 4 * sizeof(uchar_t);

    return _toString(buffSize, xT("%hhu"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(cshort_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = 4 * sizeof(short_t);

    return _toString(buffSize, xT("%hd"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(cushort_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = 4 * sizeof(ushort_t);

    return _toString(buffSize, xT("%hu"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(cint_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(int_t);

    return _toString(buffSize, xT("%d"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(cuint_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(uint_t);

    return _toString(buffSize, xT("%u"), a_value);

}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(clong_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(long_t);

    return _toString(buffSize, xT("%ld"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(culong_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(ulong_t);

    return _toString(buffSize, xT("%lu"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(clonglong_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(longlong_t);

    return _toString(buffSize, xT("%lld"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(culonglong_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(ulonglong_t);

    return _toString(buffSize, xT("%llu"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(cfloat_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = std::numeric_limits<float_t>::max_exponent10 + 20;

    return _toString(buffSize, xT("%f"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(cdouble_t &a_value)
{
    // Trace() << Type::name(a_value);
    std::csize_t buffSize = std::numeric_limits<double>::max_exponent10 + 20;

    return _toString(buffSize, xT("%f"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(clongdouble_t &a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = std::numeric_limits<longdouble_t>::max_exponent10 + 20;

    return _toString(buffSize, xT("%Lf"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(cvoid_t *a_value)
{
    // Trace() << Type::name(a_value);

    std::csize_t buffSize = 4 * sizeof(cvoid_t *);

    return _toString(buffSize, xT("%p"), a_value);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Format::toString(std::ctstring_t &a_value)
{
    // Trace() << Type::name(a_value);

    return a_value;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Format::toString(ctchar_t *a_value)
{
    // Trace() << Type::name(a_value);

    return std::tstring_t(a_value);
}
//-------------------------------------------------------------------------------------------------
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


//-------------------------------------------------------------------------------------------------
#if 0

xINLINE std::tstring_t
Format::format(
    std::ctstring_t &a_format, xVA_VARS_6
)
{
    std::tstring_t  sRv;
    std::ctstring_t delimiter      = xT("{}");
    std::size_t     delimiter_size = delimiter.size();
    std::size_t     posPrev        = 0U; // start of string

    for (std::size_t i = 0; ; ++ i) {
        std::csize_t pos = a_format.find(delimiter, posPrev);
        xCHECK_DO(pos == std::tstring_t::npos, break);

        sRv += a_format.substr(posPrev, pos - posPrev);

    #if 0
        static std::tstringstream_t ss;
        ss.str( std::tstring_t() );
        ss.clear();

        xSWITCH_6(i)

        sRv += ss.str();
    #else
        xSWITCH_6(i)
    #endif

        posPrev = pos + delimiter_size;
    }

    sRv += a_format.substr(posPrev, a_format.size() - posPrev);

    return sRv;
}

#elif 0

xINLINE std::tstring_t
Format::format(
    ctchar_t *a_format, xVA_VARS_6
)
{
    tchar_t      szRv[2048 + 1] = {};
    ctchar_t    *delimiter      = xT("{}");
    std::size_t  delimiter_size = 2;
    std::size_t  posPrev        = 0U; // start of string

    for (std::size_t i = 0; ; ++ i) {
        // std::csize_t pos = a_format.find(delimiter, posPrev);
        // xCHECK_DO(pos == std::tstring_t::npos, break);
        ctchar_t *pos = std::strstr(a_format + posPrev, delimiter);
        xCHECK_DO(pos == xPTR_NULL, break);

        // sRv += a_format.substr(posPrev, pos - posPrev);
        std::strncat(szRv, a_format + posPrev, std::size_t(pos - a_format - posPrev));

        static std::tstringstream_t ss;
        ss.str( std::tstring_t() );
        ss.clear();

        switch (i) {
        case 0: ss << a_v1; break;
        case 1: ss << a_v2; break;
        case 2: ss << a_v3; break;
        case 3: ss << a_v4; break;
        case 4: ss << a_v5; break;
        case 5: ss << a_v6; break;
        default:            break;
        }

        // szRv += ss.str();
        std::strcat(szRv, ss.str().c_str());

        // posPrev = pos + delimiter_size;
        posPrev = pos - a_format + delimiter_size;
    }

    // sRv += a_format.substr(posPrev, a_format.size() - posPrev);
    // std::strncat(szRv, a_format + posPrev, 2048 - posPrev);
    std::strcat(szRv, a_format + posPrev);

    return szRv;
}

#endif
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
