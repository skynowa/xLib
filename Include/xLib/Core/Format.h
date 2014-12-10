/**
 * \file   Format.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

std::tstring_t
toString(int a_value)
{
    std::csize_t buffSize       = 4 * sizeof(int);
    tchar_t      buff[buffSize] = {};

    cint_t writtenSize = std::snprintf(buff, buffSize, "%d", a_value);

    return std::tstring_t(buff, buff + writtenSize);
}

std::tstring_t
toString(unsigned a_value)
{
    std::csize_t buffSize       = 4 * sizeof(unsigned);
    tchar_t      buff[buffSize] = {};

    cint_t writtenSize = std::snprintf(buff, buffSize, "%u", a_value);

    return std::tstring_t(buff, buff + writtenSize);
}

std::tstring_t
toString(long a_value)
{
    std::csize_t buffSize       = 4 * sizeof(long);
    tchar_t      buff[buffSize] = {};

    cint_t writtenSize = std::snprintf(buff, buffSize, "%ld", a_value);

    return std::tstring_t(buff, buff + writtenSize);
}

std::tstring_t
toString(unsigned long a_value)
{
    std::csize_t buffSize       = 4 * sizeof(unsigned long);
    tchar_t      buff[buffSize] = {};

    cint_t writtenSize = std::snprintf(buff, buffSize, "%lu", a_value);

    return std::tstring_t(buff, buff + writtenSize);
}

std::tstring_t
toString(long long a_value)
{
    std::csize_t buffSize       = 4 * sizeof(long long);
    tchar_t      buff[buffSize] = {};

    cint_t writtenSize = std::snprintf(buff, buffSize, "%lld", a_value);

    return std::tstring_t(buff, buff + writtenSize);
}

std::tstring_t
toString(unsigned long long a_value)
{
    std::csize_t buffSize       = 4 * sizeof(unsigned long long);
    tchar_t      buff[buffSize] = {};

    cint_t writtenSize = std::snprintf(buff, buffSize, "%llu", a_value);

    return std::tstring_t(buff, buff + writtenSize);
}

std::tstring_t
toString(float a_value)
{
    std::csize_t buffSize       = std::numeric_limits<float>::max_exponent10 + 20;
    tchar_t      buff[buffSize] = {};

    cint_t writtenSize = std::snprintf(buff, buffSize, "%f", a_value);

    return std::tstring_t(buff, buff + writtenSize);
}

std::tstring_t
toString(double a_value)
{
    std::csize_t buffSize       = std::numeric_limits<double>::max_exponent10 + 20;
    tchar_t      buff[buffSize] = {};

    cint_t writtenSize = std::snprintf(buff, buffSize, "%f", a_value);

    return std::tstring_t(buff, buff + writtenSize);
}

std::tstring_t
toString(long double a_value)
{
    std::csize_t buffSize       = std::numeric_limits<long double>::max_exponent10 + 20;
    tchar_t      buff[buffSize] = {};

    cint_t writtenSize = std::snprintf(buff, buffSize, "%Lf", a_value);

    return std::tstring_t(buff, buff + writtenSize);
}

#if 0

std::tstring_t
toString(const char *a_value)
{
}

std::tstring_t
toString(const void *a_value)
{
}

#endif
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
            case 0: sRv = toString(a_v1); break; \
            case 1: sRv = toString(a_v2); break; \
            case 2: sRv = toString(a_v3); break; \
            case 3: sRv = toString(a_v4); break; \
            case 4: sRv = toString(a_v5); break; \
            case 5: sRv = toString(a_v6); break; \
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
