/**
 * \file   Format.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

//-------------------------------------------------------------------------------------------------
template<typename StringT, typename CharT /* = typename StringT::value_type */>
inline StringT
_toString(
    std::csize_t &a_buffSize,
    const CharT  *a_format, ...
)
{
    tchar_t buff[a_buffSize * sizeof(CharT)];

    va_list args;
    xVA_START(args, a_format);

    cint_t writtenSize = xTVSNPRINTF(buff, a_buffSize, a_format, args);

    xVA_END(args);

    return StringT(buff, buff + writtenSize);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(cbool_t &a_value)
{
    return a_value ? xT("true") : xT("false");
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(ctchar_t &a_value)
{
    std::csize_t buffSize = 4 * sizeof(tchar_t);

    return _toString<std::tstring_t>(buffSize, xT("%c"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(cshort_t &a_value)
{
    std::csize_t buffSize = 4 * sizeof(short_t);

    return _toString<std::tstring_t>(buffSize, xT("%h"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(cushort_t &a_value)
{
    std::csize_t buffSize = 4 * sizeof(ushort_t);

    return _toString<std::tstring_t>(buffSize, xT("%hu"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(cint_t &a_value)
{
    std::csize_t buffSize = 4 * sizeof(int_t);

    return _toString<std::tstring_t>(buffSize, xT("%d"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(cuint_t &a_value)
{
    std::csize_t buffSize = 4 * sizeof(uint_t);

    return _toString<std::tstring_t>(buffSize, xT("%u"), a_value);

}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(clong_t &a_value)
{
    std::csize_t buffSize = 4 * sizeof(long_t);

    return _toString<std::tstring_t>(buffSize, xT("%ld"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(culong_t &a_value)
{
    std::csize_t buffSize = 4 * sizeof(ulong_t);

    return _toString<std::tstring_t>(buffSize, xT("%lu"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(clonglong_t &a_value)
{
    std::csize_t buffSize = 4 * sizeof(longlong_t);

    return _toString<std::tstring_t>(buffSize, xT("%lld"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(culonglong_t &a_value)
{
    std::csize_t buffSize = 4 * sizeof(ulonglong_t);

    return _toString<std::tstring_t>(buffSize, xT("%llu"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(cfloat_t &a_value)
{
    std::csize_t buffSize = std::numeric_limits<float_t>::max_exponent10 + 20;

    return _toString<std::tstring_t>(buffSize, xT("%f"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(cdouble_t &a_value)
{
    std::csize_t buffSize = std::numeric_limits<double>::max_exponent10 + 20;

    return _toString<std::tstring_t>(buffSize, xT("%f"), a_value);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(clongdouble_t &a_value)
{
    std::csize_t buffSize = std::numeric_limits<longdouble_t>::max_exponent10 + 20;

    return _toString<std::tstring_t>(buffSize, xT("%Lf"), a_value);
}
//-------------------------------------------------------------------------------------------------
#if 0
void *
#endif
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
toString(std::ctstring_t &a_value)
{
    return a_value;
}
//-------------------------------------------------------------------------------------------------
#if 0
char *
#endif
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
toString(ctchar_t *a_value)
{
    std::csize_t buffSize = 4 * sizeof(ctchar_t *);

    return _toString<std::tstring_t>(buffSize, xT("%s"), a_value);
}
//-------------------------------------------------------------------------------------------------
#define xSWITCH_1(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            default:            break; \
            }

#define xSWITCH_2(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            case 1: ss << a_v2; break; \
            default:            break; \
            }

#define xSWITCH_3(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            case 1: ss << a_v2; break; \
            case 2: ss << a_v3; break; \
            default:            break; \
            }

#define xSWITCH_4(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            case 1: ss << a_v2; break; \
            case 2: ss << a_v3; break; \
            case 3: ss << a_v4; break; \
            default:            break; \
            }

#define xSWITCH_5(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            case 1: ss << a_v2; break; \
            case 2: ss << a_v3; break; \
            case 3: ss << a_v4; break; \
            case 4: ss << a_v5; break; \
            default:            break; \
            }

        #if 0
    #define xSWITCH_6(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            case 1: ss << a_v2; break; \
            case 2: ss << a_v3; break; \
            case 3: ss << a_v4; break; \
            case 4: ss << a_v5; break; \
            case 5: ss << a_v6; break; \
            default:            break; \
            }
        #else
    #define xSWITCH_6(v) \
            switch (v) { \
            case 0: sRv += toString(a_v1); break; \
            case 1: sRv += toString(a_v2); break; \
            case 2: sRv += toString(a_v3); break; \
            case 3: sRv += toString(a_v4); break; \
            case 4: sRv += toString(a_v5); break; \
            case 5: sRv += toString(a_v6); break; \
            default:                      break; \
            }
        #endif

#define xSWITCH_7(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            case 1: ss << a_v2; break; \
            case 2: ss << a_v3; break; \
            case 3: ss << a_v4; break; \
            case 4: ss << a_v5; break; \
            case 5: ss << a_v6; break; \
            case 6: ss << a_v7; break; \
            default:            break; \
            }

#define xSWITCH_8(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            case 1: ss << a_v2; break; \
            case 2: ss << a_v3; break; \
            case 3: ss << a_v4; break; \
            case 4: ss << a_v5; break; \
            case 5: ss << a_v6; break; \
            case 6: ss << a_v7; break; \
            case 7: ss << a_v8; break; \
            default:            break; \
            }

#define xSWITCH_9(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            case 1: ss << a_v2; break; \
            case 2: ss << a_v3; break; \
            case 3: ss << a_v4; break; \
            case 4: ss << a_v5; break; \
            case 5: ss << a_v6; break; \
            case 6: ss << a_v7; break; \
            case 7: ss << a_v8; break; \
            case 8: ss << a_v9; break; \
            default:            break; \
            }

#define xSWITCH_10(v) \
            switch (v) { \
            case 0: ss << a_v1; break; \
            case 1: ss << a_v2; break; \
            case 2: ss << a_v3; break; \
            case 3: ss << a_v4; break; \
            case 4: ss << a_v5; break; \
            case 5: ss << a_v6; break; \
            case 6: ss << a_v7; break; \
            case 7: ss << a_v8; break; \
            case 8: ss << a_v9; break; \
            case 9: ss << a_v10; break; \
            default:            break; \
            }
//-------------------------------------------------------------------------------------------------
#if 0
    #define xFORMAT(n) \
        template<xVA_TYPES_##n> \
        std::tstring_t \
        Format( \
            std::ctstring_t &a_format, xVA_VARS_##n \
        ) \
        { \
            std::tstring_t       sRv; \
            std::tstringstream_t ss; \
            std::ctstring_t      delimiter = "{}"; \
            std::vec_tstring_t   vec_format; \
            \
            String::split(a_format, delimiter, &vec_format); \
            \
            const std::size_t vec_format_size = vec_format.size(); \
            \
            for (std::size_t i = 0; i < vec_format_size; ++ i) { \
                sRv += vec_format[i]; \
                ss.str( std::tstring_t() ); \
                ss.clear(); \
                \
                xSWITCH_##n(i) \
                \
                sRv += ss.str(); \
            } \
            \
            return sRv; \
        }
#else
    #define xFORMAT(n) \
        template<xVA_TYPES_##n> \
        std::tstring_t \
        Format( \
            std::ctstring_t &a_format, xVA_VARS_##n \
        ) \
        { \
            std::tstring_t  sRv; \
            std::ctstring_t delimiter      = xT("{}"); \
            std::size_t     delimiter_size = delimiter.size(); \
            std::size_t     posPrev        = 0U; \
            \
            for (std::size_t i = 0; ; ++ i) { \
                std::csize_t pos = a_format.find(delimiter, posPrev); \
                xCHECK_DO(pos == std::tstring_t::npos, break); \
                \
                sRv += a_format.substr(posPrev, pos - posPrev); \
                \
                static std::tstringstream_t ss; \
                ss.str( std::tstring_t() ); \
                ss.clear(); \
                \
                xSWITCH_##n(i) \
                \
                sRv += ss.str(); \
                 \
                posPrev = pos + delimiter_size; \
            } \
            \
            sRv += a_format.substr(posPrev, a_format.size() - posPrev); \
            \
            return sRv; \
        }
#endif
//-------------------------------------------------------------------------------------------------
#if 1

template<xVA_TYPES_6>
std::tstring_t
Format(
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

template<xVA_TYPES_6>
std::tstring_t
Format(
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
xFORMAT(1)
xFORMAT(2)
xFORMAT(3)
xFORMAT(4)
xFORMAT(5)
// xFORMAT(6)
xFORMAT(7)
xFORMAT(8)
xFORMAT(9)
xFORMAT(10)

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    // #include "Format.cpp"
#endif
