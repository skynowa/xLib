/**
 * \file   Format.h
 * \brief  format string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
#define xFORMAT_SWITCH_CASE(v) \
            _setOptions(ss, v); \
            ss << v
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
    Format::str( \
        std::ctstring_t &a_format, xVA_VARS_##n \
    ) \
    { \
        std::tstring_t  sRv; \
        std::ctstring_t delimiter      = xT("{}"); \
        std::csize_t    delimiter_size = delimiter.size(); \
        std::size_t     posPrev        = 0U; \
        \
        for (std::size_t param = 1; ; ++ param) { \
            std::csize_t pos = a_format.find(delimiter, posPrev); \
            xCHECK_DO(pos == std::tstring_t::npos, break); \
            \
            sRv += a_format.substr(posPrev, pos - posPrev); \
            \
            static std::tstringstream_t ss; \
            ss.str( std::tstring_t() ); \
            ss.clear(); \
            \
            switch (param) { \
            xFORMAT_SWITCH_CASE_##n \
            default: break; \
            } \
            \
            sRv.append( ss.str() ); \
            \
            posPrev = pos + delimiter_size; \
        } \
        \
        sRv += a_format.substr(posPrev, a_format.size() - posPrev); \
        \
        return sRv; \
    }
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Format
    ///< format string
{
public:
    #define xFORMAT_DECLARE(n) \
        template<xVA_TYPES_##n> \
        static \
        std::tstring_t str(std::ctstring_t &format, xVA_VARS_##n);

    xFORMAT_DECLARE(1)
    xFORMAT_DECLARE(2)
    xFORMAT_DECLARE(3)
    xFORMAT_DECLARE(4)
    xFORMAT_DECLARE(5)
    xFORMAT_DECLARE(6)
    xFORMAT_DECLARE(7)
    xFORMAT_DECLARE(8)
    xFORMAT_DECLARE(9)
    xFORMAT_DECLARE(10)
    xFORMAT_DECLARE(11)
    xFORMAT_DECLARE(12)
    xFORMAT_DECLARE(13)
    xFORMAT_DECLARE(14)
    xFORMAT_DECLARE(15)
    xFORMAT_DECLARE(16)
    xFORMAT_DECLARE(17)
    xFORMAT_DECLARE(18)
    xFORMAT_DECLARE(19)
    xFORMAT_DECLARE(20)

private:
    xNO_INSTANCE(Format)
    xNO_COPY_ASSIGN(Format)

    #define xFORMAT_SET_OPTIONS_DEFAULT(t) \
        static \
        void _setOptions(std::tstringstream_t &ss, t value) {}

    static
    void _setOptions(std::tstringstream_t &ss, bool value);

    xFORMAT_SET_OPTIONS_DEFAULT(char)
    xFORMAT_SET_OPTIONS_DEFAULT(unsigned char)
    //xFORMAT_SET_OPTIONS_DEFAULT(wchar_t)
    //xFORMAT_SET_OPTIONS_DEFAULT(unsigned wchar_t)

    xFORMAT_SET_OPTIONS_DEFAULT(short);
    xFORMAT_SET_OPTIONS_DEFAULT(unsigned short);
    xFORMAT_SET_OPTIONS_DEFAULT(int);
    xFORMAT_SET_OPTIONS_DEFAULT(unsigned int);
    xFORMAT_SET_OPTIONS_DEFAULT(long);
    xFORMAT_SET_OPTIONS_DEFAULT(unsigned long);
    xFORMAT_SET_OPTIONS_DEFAULT(long long);
    xFORMAT_SET_OPTIONS_DEFAULT(unsigned long long);

    static
    void _setOptions(std::tstringstream_t &ss, float value);
    static
    void _setOptions(std::tstringstream_t &ss, double value);
    static
    void _setOptions(std::tstringstream_t &ss, long double value);

    xFORMAT_SET_OPTIONS_DEFAULT(void *)
    xFORMAT_SET_OPTIONS_DEFAULT(std::string)
    //xFORMAT_SET_OPTIONS_DEFAULT(std::wstring)
    xFORMAT_SET_OPTIONS_DEFAULT(char *)
    //xFORMAT_SET_OPTIONS_DEFAULT(wchar_t *)
    xFORMAT_SET_OPTIONS_DEFAULT(std::vec_tstring_t)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "Format.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "Format.cpp"
#endif
