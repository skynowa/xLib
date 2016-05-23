/**
 * \file   Format.inl
 * \brief  format string
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>

xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#define xFORMAT_SWITCH_CASE(a_v) \
            _format(ss, a_v)
//-------------------------------------------------------------------------------------------------
#define xFORMAT_SWITCH_CASE_1 \
            case 1: xFORMAT_SWITCH_CASE(a_v1); break;

#define xFORMAT_SWITCH_CASE_2 \
            xFORMAT_SWITCH_CASE_1 \
            case 2: xFORMAT_SWITCH_CASE(a_v2); break;

#define xFORMAT_SWITCH_CASE_3 \
            xFORMAT_SWITCH_CASE_2 \
            case 3: xFORMAT_SWITCH_CASE(a_v3); break;

#define xFORMAT_SWITCH_CASE_4 \
            xFORMAT_SWITCH_CASE_3 \
            case 4: xFORMAT_SWITCH_CASE(a_v4); break;

#define xFORMAT_SWITCH_CASE_5 \
            xFORMAT_SWITCH_CASE_4 \
            case 5: xFORMAT_SWITCH_CASE(a_v5); break;

#define xFORMAT_SWITCH_CASE_6 \
            xFORMAT_SWITCH_CASE_5 \
            case 6: xFORMAT_SWITCH_CASE(a_v6); break;

#define xFORMAT_SWITCH_CASE_7 \
            xFORMAT_SWITCH_CASE_6 \
            case 7: xFORMAT_SWITCH_CASE(a_v7); break;

#define xFORMAT_SWITCH_CASE_8 \
            xFORMAT_SWITCH_CASE_7 \
            case 8: xFORMAT_SWITCH_CASE(a_v8); break;

#define xFORMAT_SWITCH_CASE_9 \
            xFORMAT_SWITCH_CASE_8 \
            case 9: xFORMAT_SWITCH_CASE(a_v9); break;

#define xFORMAT_SWITCH_CASE_10 \
            xFORMAT_SWITCH_CASE_9 \
            case 10: xFORMAT_SWITCH_CASE(a_v10); break;

#define xFORMAT_SWITCH_CASE_11 \
            xFORMAT_SWITCH_CASE_10 \
            case 11: xFORMAT_SWITCH_CASE(a_v11); break;

#define xFORMAT_SWITCH_CASE_12 \
            xFORMAT_SWITCH_CASE_11 \
            case 12: xFORMAT_SWITCH_CASE(a_v12); break;

#define xFORMAT_SWITCH_CASE_13 \
            xFORMAT_SWITCH_CASE_12 \
            case 13: xFORMAT_SWITCH_CASE(a_v13); break;

#define xFORMAT_SWITCH_CASE_14 \
            xFORMAT_SWITCH_CASE_13 \
            case 14: xFORMAT_SWITCH_CASE(a_v14); break;

#define xFORMAT_SWITCH_CASE_15 \
            xFORMAT_SWITCH_CASE_14 \
            case 15: xFORMAT_SWITCH_CASE(a_v15); break;

#define xFORMAT_SWITCH_CASE_16 \
            xFORMAT_SWITCH_CASE_15 \
            case 16: xFORMAT_SWITCH_CASE(a_v16); break;

#define xFORMAT_SWITCH_CASE_17 \
            xFORMAT_SWITCH_CASE_16 \
            case 17: xFORMAT_SWITCH_CASE(a_v17); break;

#define xFORMAT_SWITCH_CASE_18 \
            xFORMAT_SWITCH_CASE_17 \
            case 18: xFORMAT_SWITCH_CASE(a_v18); break;

#define xFORMAT_SWITCH_CASE_19 \
            xFORMAT_SWITCH_CASE_18 \
            case 19: xFORMAT_SWITCH_CASE(a_v19); break;

#define xFORMAT_SWITCH_CASE_20 \
            xFORMAT_SWITCH_CASE_19 \
            case 20: xFORMAT_SWITCH_CASE(a_v20); break;

#define xFORMAT_SWITCH_CASE_21 \
            xFORMAT_SWITCH_CASE_20 \
            case 21: xFORMAT_SWITCH_CASE(a_v21); break;
//-------------------------------------------------------------------------------------------------
#define xFORMAT_STR(n) \
    template<xVA_TYPES_##n> \
    inline std::tstring_t \
    Format::str( \
        std::ctstring_t &a_format, xVA_VARS_##n \
    ) \
    { \
        std::tstring_t sRv; \
        std::size_t    posPrev = 0U; \
        \
        static std::tstringstream_t ss; \
        static std::ctstring_t      emptyString; \
        \
        std::size_t param = 1; \
        for ( ; ; ++ param) { \
            std::csize_t pos = a_format.find(_specifier(), posPrev); \
            if (pos == std::tstring_t::npos) { \
                break; \
            } \
            \
            sRv += a_format.substr(posPrev, pos - posPrev); \
            \
            ss.str( emptyString ); \
            ss.clear(); \
            \
            switch (param) { \
            xFORMAT_SWITCH_CASE_##n \
            default: break; \
            } \
            \
            sRv.append( ss.str() ); \
            \
            posPrev = pos + _specifier().size(); \
        } \
        \
        sRv += a_format.substr(posPrev, a_format.size() - posPrev); \
        \
        xTEST_EQ_MSG(param - 1, static_cast<std::size_t>(n), xT("Invalid params")); \
        \
        return sRv; \
    }
//-------------------------------------------------------------------------------------------------
xFORMAT_STR(1)
xFORMAT_STR(2)
xFORMAT_STR(3)
xFORMAT_STR(4)
xFORMAT_STR(5)
xFORMAT_STR(6)
xFORMAT_STR(7)
xFORMAT_STR(8)
xFORMAT_STR(9)
xFORMAT_STR(10)
xFORMAT_STR(11)
xFORMAT_STR(12)
xFORMAT_STR(13)
xFORMAT_STR(14)
xFORMAT_STR(15)
xFORMAT_STR(16)
xFORMAT_STR(17)
xFORMAT_STR(18)
xFORMAT_STR(19)
xFORMAT_STR(20)
xFORMAT_STR(21)
//-------------------------------------------------------------------------------------------------
template<class IteratorT>
/* static */
inline void
Format::_formatString(
    std::tstringstream_t &a_ss,     ///< [out]
    IteratorT             a_first,  ///< first iterator
    IteratorT             a_last    ///< last iterator
)
{
    for (; a_first != a_last; ++ a_first) {
        a_ss << str(_specifier(), *a_first);
    }
}
//-------------------------------------------------------------------------------------------------
template<class IteratorT>
/* static */
inline void
Format::_formatRange(
    std::tstringstream_t &a_ss,     ///< [out]
    IteratorT             a_first,  ///< first iterator
    IteratorT             a_last    ///< last iterator
)
{
    if (a_first == a_last) {
        a_ss << xT("{}");
        return;
    }

    a_ss << xT("{");
    a_ss << str(_specifier(), *a_first);

    for (++ a_first; a_first != a_last; ++ a_first) {
        a_ss << str(_delimiter() + _specifier(), *a_first);
    }

    a_ss << xT("}");
}
//-------------------------------------------------------------------------------------------------
template<class T>
/* static */
inline void
Format::_formatContainer(
    std::tstringstream_t &a_ss,     ///< [out]
    const T              &a_value   ///< value
)
{
    _formatRange(a_ss, a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
