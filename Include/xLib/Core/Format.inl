/**
 * \file   Format.inl
 * \brief  format string
 */


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#if xFORMAT_MODE
    #define xFORMAT_SWITCH_PRE_IMPL \
                static std::tstringstream_t ss; \
                ss.str( std::tstring_t() ); \
                ss.clear()

    #define xFORMAT_CASE_IMPL(v) \
                ss << v

    #define xFORMAT_SWITCH_POST_IMPL \
                sRv.append( ss.str() )

#else
    #define xFORMAT_SWITCH_PRE_IMPL \
                xNA

    #define xFORMAT_CASE_IMPL(v) \
                sRv.append( toString(v) )

    #define xFORMAT_SWITCH_POST_IMPL \
                xNA
#endif
//-------------------------------------------------------------------------------------------------
#define xFORMAT_SWITCH_1 \
            case 1: xFORMAT_CASE_IMPL(a_v1); break;

#define xFORMAT_SWITCH_2 \
            xFORMAT_SWITCH_1 \
            case 2: xFORMAT_CASE_IMPL(a_v2); break;

#define xFORMAT_SWITCH_3 \
            xFORMAT_SWITCH_2 \
            case 3: xFORMAT_CASE_IMPL(a_v3); break;

#define xFORMAT_SWITCH_4 \
            xFORMAT_SWITCH_3 \
            case 4: xFORMAT_CASE_IMPL(a_v4); break;

#define xFORMAT_SWITCH_5 \
            xFORMAT_SWITCH_4 \
            case 5: xFORMAT_CASE_IMPL(a_v5); break;

#define xFORMAT_SWITCH_6 \
            xFORMAT_SWITCH_5 \
            case 6: xFORMAT_CASE_IMPL(a_v6); break;

#define xFORMAT_SWITCH_7 \
            xFORMAT_SWITCH_6 \
            case 7: xFORMAT_CASE_IMPL(a_v7); break;

#define xFORMAT_SWITCH_8 \
            xFORMAT_SWITCH_7 \
            case 8: xFORMAT_CASE_IMPL(a_v8); break;

#define xFORMAT_SWITCH_9 \
            xFORMAT_SWITCH_8 \
            case 9: xFORMAT_CASE_IMPL(a_v9); break;

#define xFORMAT_SWITCH_10 \
            xFORMAT_SWITCH_9 \
            case 10: xFORMAT_CASE_IMPL(a_v10); break;

#define xFORMAT_SWITCH_11 \
            xFORMAT_SWITCH_10 \
            case 11: xFORMAT_CASE_IMPL(a_v11); break;

#define xFORMAT_SWITCH_12 \
            xFORMAT_SWITCH_11 \
            case 12: xFORMAT_CASE_IMPL(a_v12); break;

#define xFORMAT_SWITCH_13 \
            xFORMAT_SWITCH_12 \
            case 13: xFORMAT_CASE_IMPL(a_v13); break;

#define xFORMAT_SWITCH_14 \
            xFORMAT_SWITCH_13 \
            case 14: xFORMAT_CASE_IMPL(a_v14); break;

#define xFORMAT_SWITCH_15 \
            xFORMAT_SWITCH_14 \
            case 15: xFORMAT_CASE_IMPL(a_v15); break;

#define xFORMAT_SWITCH_16 \
            xFORMAT_SWITCH_15 \
            case 16: xFORMAT_CASE_IMPL(a_v16); break;

#define xFORMAT_SWITCH_17 \
            xFORMAT_SWITCH_16 \
            case 17: xFORMAT_CASE_IMPL(a_v17); break;

#define xFORMAT_SWITCH_18 \
            xFORMAT_SWITCH_17 \
            case 18: xFORMAT_CASE_IMPL(a_v18); break;

#define xFORMAT_SWITCH_19 \
            xFORMAT_SWITCH_18 \
            case 19: xFORMAT_CASE_IMPL(a_v19); break;

#define xFORMAT_SWITCH_20 \
            xFORMAT_SWITCH_19 \
            case 20: xFORMAT_CASE_IMPL(a_v20); break;
//-------------------------------------------------------------------------------------------------
#define xFORMAT(n) \
    template<xVA_TYPES_##n> \
    std::tstring_t \
    Format::format( \
        std::ctstring_t &a_format, xVA_VARS_##n \
    ) \
    { \
        std::tstring_t  sRv; \
        std::ctstring_t delimiter      = xT("{}"); \
        std::csize_t    delimiter_size = delimiter.size(); \
        std::size_t     posPrev        = 0U; \
        \
        for (std::size_t i = 1; ; ++ i) { \
            std::csize_t pos = a_format.find(delimiter, posPrev); \
            xCHECK_DO(pos == std::tstring_t::npos, break); \
            \
            sRv += a_format.substr(posPrev, pos - posPrev); \
            \
            xFORMAT_SWITCH_PRE_IMPL; \
            \
            switch (i) { \
            xFORMAT_SWITCH_##n \
            default: break; \
            } \
            \
            xFORMAT_SWITCH_POST_IMPL; \
            \
            posPrev = pos + delimiter_size; \
        } \
        \
        sRv += a_format.substr(posPrev, a_format.size() - posPrev); \
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
xFORMAT(11)
xFORMAT(12)
xFORMAT(13)
xFORMAT(14)
xFORMAT(15)
xFORMAT(16)
xFORMAT(17)
xFORMAT(18)
xFORMAT(19)
xFORMAT(20)
//-------------------------------------------------------------------------------------------------
#if 0

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
