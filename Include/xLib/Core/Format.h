/**
 * \file   Format.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

#define xARG_TYPES_1  class T1
#define xARG_TYPES_2  class T1, class T2
#define xARG_TYPES_3  class T1, class T2, class T3
#define xARG_TYPES_4  class T1, class T2, class T3, class T4
#define xARG_TYPES_5  class T1, class T2, class T3, class T4, class T5
#define xARG_TYPES_6  class T1, class T2, class T3, class T4, class T5, class T6
#define xARG_TYPES_7  class T1, class T2, class T3, class T4, class T5, class T6, class T7
#define xARG_TYPES_8  class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8
#define xARG_TYPES_9  class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9
#define xARG_TYPES_10 class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10

#define xARG_VARS_1  const T1& a_v1
#define xARG_VARS_2  const T1& a_v1, const T2& a_v2
#define xARG_VARS_3  const T1& a_v1, const T2& a_v2, const T3& a_v3
#define xARG_VARS_4  const T1& a_v1, const T2& a_v2, const T3& a_v3, const T4& a_v4
#define xARG_VARS_5  const T1& a_v1, const T2& a_v2, const T3& a_v3, const T4& a_v4, const T5& a_v5
#define xARG_VARS_6  const T1& a_v1, const T2& a_v2, const T3& a_v3, const T4& a_v4, const T5& a_v5, const T6& a_v6
#define xARG_VARS_7  const T1& a_v1, const T2& a_v2, const T3& a_v3, const T4& a_v4, const T5& a_v5, const T6& a_v6, const T7& a_v7
#define xARG_VARS_8  const T1& a_v1, const T2& a_v2, const T3& a_v3, const T4& a_v4, const T5& a_v5, const T6& a_v6, const T7& a_v7, const T8& a_v8
#define xARG_VARS_9  const T1& a_v1, const T2& a_v2, const T3& a_v3, const T4& a_v4, const T5& a_v5, const T6& a_v6, const T7& a_v7, const T8& a_v8, const T9& a_v9
#define xARG_VARS_10 const T1& a_v1, const T2& a_v2, const T3& a_v3, const T4& a_v4, const T5& a_v5, const T6& a_v6, const T7& a_v7, const T8& a_v8, const T9& a_v9, const T10& a_v10

#define xARGS_1 v1
#define xARGS_2 v1, v2
#define xARGS_3 v1, v2, v3
#define xARGS_4 v1, v2, v3, v4
#define xARGS_5 v1, v2, v3, v4, v5
#define xARGS_6 v1, v2, v3, v4, v5, v6
#define xARGS_7 v1, v2, v3, v4, v5, v6, v7
#define xARGS_8 v1, v2, v3, v4, v5, v6, v7, v8
#define xARGS_9 v1, v2, v3, v4, v5, v6, v7, v8, v9
#define xARGS_10 v1, v2, v3, v4, v5, v6, v7, v8, v9, v10

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
        template<xARG_TYPES_##n> \
        std::tstring_t \
        Format( \
            std::ctstring_t &a_format, xARG_VARS_##n \
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
        template<xARG_TYPES_##n> \
        std::tstring_t \
        Format( \
            std::ctstring_t &a_format, xARG_VARS_##n \
        ) \
        { \
            std::tstring_t       sRv; \
            std::ctstring_t      delimiter      = xT("{}"); \
            std::size_t          delimiter_size = delimiter.size(); \
            std::size_t          posPrev        = 0U; \
            std::tstringstream_t ss; \
            \
            for (std::size_t i = 0; ; ++ i) { \
                std::csize_t pos = a_format.find(delimiter, posPrev); \
                xCHECK_DO(pos == std::tstring_t::npos, break); \
                \
                sRv += a_format.substr(posPrev, pos - posPrev); \
                \
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
#if 0

template<xARG_TYPES_6>
std::tstring_t
Format(
    std::ctstring_t &a_format, xARG_VARS_6
)
{
    std::tstring_t       sRv;
    std::ctstring_t      delimiter      = xT("{}");
    std::size_t          delimiter_size = delimiter.size();
    std::size_t          posPrev        = 0U; // start of string
    std::tstringstream_t ss;

    for (std::size_t i = 0; ; ++ i) {
        std::csize_t pos = a_format.find(delimiter, posPrev);
        xCHECK_DO(pos == std::tstring_t::npos, break);

        sRv += a_format.substr(posPrev, pos - posPrev);

        ss.str( std::tstring_t() );
        ss.clear();

        xSWITCH_6(i)

        sRv += ss.str();

        posPrev = pos + delimiter_size;
    }

    sRv += a_format.substr(posPrev, a_format.size() - posPrev);

    return sRv;
}

#else

template<xARG_TYPES_6>
std::tstring_t
Format(
    ctchar_t *a_format, xARG_VARS_6
)
{
    tchar_t              szRv[2048 + 1] = {};
    ctchar_t            *delimiter      = xT("{}");
    std::size_t          delimiter_size = 2;
    std::size_t          posPrev        = 0U; // start of string
    std::tstringstream_t ss;

    for (std::size_t i = 0; ; ++ i) {
        // std::csize_t pos = a_format.find(delimiter, posPrev);
        // xCHECK_DO(pos == std::tstring_t::npos, break);
        ctchar_t *pos = std::strstr(a_format + posPrev, delimiter);
        xCHECK_DO(pos == xPTR_NULL, break);

        // sRv += a_format.substr(posPrev, pos - posPrev);
        std::strncat(szRv, a_format + posPrev, std::size_t(pos - a_format - posPrev));

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
