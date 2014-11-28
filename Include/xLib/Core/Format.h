/**
 * \file   Format.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

#define xARGTYPES_1  class T1
#define xARGTYPES_2  class T1, class T2
#define xARGTYPES_3  class T1, class T2, class T3
#define xARGTYPES_4  class T1, class T2, class T3, class T4
#define xARGTYPES_5  class T1, class T2, class T3, class T4, class T5
#define xARGTYPES_6  class T1, class T2, class T3, class T4, class T5, class T6
#define xARGTYPES_7  class T1, class T2, class T3, class T4, class T5, class T6, class T7
#define xARGTYPES_8  class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8
#define xARGTYPES_9  class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9
#define xARGTYPES_10 class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10

#define xVARARGS_1  const T1& a_t1
#define xVARARGS_2  const T1& a_t1, const T2& a_t2
#define xVARARGS_3  const T1& a_t1, const T2& a_t2, const T3& a_t3
#define xVARARGS_4  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4
#define xVARARGS_5  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5
#define xVARARGS_6  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6
#define xVARARGS_7  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6, const T7& a_t7
#define xVARARGS_8  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6, const T7& a_t7, const T8& a_t8
#define xVARARGS_9  const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6, const T7& a_t7, const T8& a_t8, const T9& a_t9
#define xVARARGS_10 const T1& a_t1, const T2& a_t2, const T3& a_t3, const T4& a_t4, const T5& a_t5, const T6& a_t6, const T7& a_t7, const T8& a_t8, const T9& a_t9, const T10& a_t10


#define xSWITCH_1(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            default:            break; \
            }

#define xSWITCH_2(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            case 1: ss << a_t2; break; \
            default:            break; \
            }

#define xSWITCH_3(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            case 1: ss << a_t2; break; \
            case 2: ss << a_t3; break; \
            default:            break; \
            }

#define xSWITCH_4(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            case 1: ss << a_t2; break; \
            case 2: ss << a_t3; break; \
            case 3: ss << a_t4; break; \
            default:            break; \
            }

#define xSWITCH_5(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            case 1: ss << a_t2; break; \
            case 2: ss << a_t3; break; \
            case 3: ss << a_t4; break; \
            case 4: ss << a_t5; break; \
            default:            break; \
            }

#define xSWITCH_6(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            case 1: ss << a_t2; break; \
            case 2: ss << a_t3; break; \
            case 3: ss << a_t4; break; \
            case 4: ss << a_t5; break; \
            case 5: ss << a_t6; break; \
            default:            break; \
            }

#define xSWITCH_7(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            case 1: ss << a_t2; break; \
            case 2: ss << a_t3; break; \
            case 3: ss << a_t4; break; \
            case 4: ss << a_t5; break; \
            case 5: ss << a_t6; break; \
            case 6: ss << a_t7; break; \
            default:            break; \
            }

#define xSWITCH_8(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            case 1: ss << a_t2; break; \
            case 2: ss << a_t3; break; \
            case 3: ss << a_t4; break; \
            case 4: ss << a_t5; break; \
            case 5: ss << a_t6; break; \
            case 6: ss << a_t7; break; \
            case 7: ss << a_t8; break; \
            default:            break; \
            }

#define xSWITCH_9(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            case 1: ss << a_t2; break; \
            case 2: ss << a_t3; break; \
            case 3: ss << a_t4; break; \
            case 4: ss << a_t5; break; \
            case 5: ss << a_t6; break; \
            case 6: ss << a_t7; break; \
            case 7: ss << a_t8; break; \
            case 8: ss << a_t9; break; \
            default:            break; \
            }

#define xSWITCH_10(v) \
            switch (v) { \
            case 0: ss << a_t1; break; \
            case 1: ss << a_t2; break; \
            case 2: ss << a_t3; break; \
            case 3: ss << a_t4; break; \
            case 4: ss << a_t5; break; \
            case 5: ss << a_t6; break; \
            case 6: ss << a_t7; break; \
            case 7: ss << a_t8; break; \
            case 8: ss << a_t9; break; \
            case 9: ss << a_t10; break; \
            default:            break; \
            }
//-------------------------------------------------------------------------------------------------
#define xFORMAT(n) \
    template<xARGTYPES_##n> \
    std::tstring_t \
    Format( \
        std::ctstring_t &a_format, xVARARGS_##n \
    ) \
    { \
        std::tstring_t sRv; \
        \
        std::vec_tstring_t vec_format; \
        String::split(a_format, "{}", &vec_format); \
        \
        for (std::size_t i = 0; i < vec_format.size(); ++ i) { \
            sRv += vec_format[i]; \
            \
            std::tstringstream_t ss; \
            \
            xSWITCH_##n(i) \
            \
            sRv += ss.str(); \
        } \
        \
        return sRv; \
    }

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

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    // #include "Format.cpp"
#endif
