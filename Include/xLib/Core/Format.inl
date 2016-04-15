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
#if xFORMAT_MODE_STD_STREAM
    #define xFORMAT_SWITCH_PRE \
                static std::tstringstream_t ss; \
                ss.str( std::tstring_t() ); \
                ss.clear()

    #define xFORMAT_SWITCH_CASE(v) \
                _setOptions(ss, v); \
                ss << v

    #define xFORMAT_SWITCH_POST \
                sRv.append( ss.str() )

#else
    #define xFORMAT_SWITCH_PRE \
                xNA

    #define xFORMAT_SWITCH_CASE(v) \
                sRv.append( toString(v) )

    #define xFORMAT_SWITCH_POST \
                xNA
#endif
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
            xFORMAT_SWITCH_PRE; \
            \
            switch (i) { \
            xFORMAT_SWITCH_CASE_##n \
            default: break; \
            } \
            \
            xFORMAT_SWITCH_POST; \
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

xNAMESPACE_END2(xlib, core)
