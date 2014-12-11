/**
 * \file   Format.h
 * \brief  [CLASS_COMMENTS]
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

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

#define xFORMAT(n) \
    template<xVA_TYPES_##n> \
    std::tstring_t \
    format( \
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

class Format
    ///<
{
public:
                   Format() {}
        ///< constructor
                  ~Format() {}
        ///< destructor

    xFORMAT(1)
    xFORMAT(2)
    xFORMAT(3)
    xFORMAT(4)
    xFORMAT(5)
    xFORMAT(6)
    xFORMAT(7)
    xFORMAT(8)
    xFORMAT(9)
    xFORMAT(10)

    std::tstring_t toString(cbool_t &value);
    std::tstring_t toString(ctchar_t &value);
    std::tstring_t toString(cuchar_t &value);
    std::tstring_t toString(cshort_t &value);
    std::tstring_t toString(cushort_t &value);
    std::tstring_t toString(cint_t &value);
    std::tstring_t toString(cuint_t &value);
    std::tstring_t toString(clong_t &value);
    std::tstring_t toString(culong_t &value);
    std::tstring_t toString(clonglong_t &value);
    std::tstring_t toString(culonglong_t &value);
    std::tstring_t toString(cfloat_t &value);
    std::tstring_t toString(cdouble_t &value);
    std::tstring_t toString(clongdouble_t &value);
    std::tstring_t toString(cvoid_t *value);
    std::tstring_t toString(std::ctstring_t &value);
    std::tstring_t toString(ctchar_t *value);

private:
    xNO_COPY_ASSIGN(Format)

    std::tstring_t _toString(std::csize_t &buffSize, const tchar_t *format, ...);
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Format.cpp"
#endif
