/**
 * \file   Format.h
 * \brief  format string
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

#define xFORMAT_MODE_STD_STREAM 0

class Format
    ///< format string
{
public:
#define xFORMAT_DECLARE(n) \
    template<xVA_TYPES_##n> \
    static \
    std::tstring_t format(std::ctstring_t &format, xVA_VARS_##n);

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

    // FAQ: https://github.com/philsquared/Catch/blob/master/include/internal/catch_tostring.h

#if !xFORMAT_MODE_STD_STREAM
    static
    std::tstring_t    toString(cbool_t &value);
    static
    std::tstring_t    toString(ctchar_t &value);
    static
    std::tstring_t    toString(cuchar_t &value);
    static
    std::tstring_t    toString(cshort_t &value);
    static
    std::tstring_t    toString(cushort_t &value);
    static
    std::tstring_t    toString(cint_t &value);
    static
    std::tstring_t    toString(cuint_t &value);
    static
    std::tstring_t    toString(clong_t &value);
    static
    std::tstring_t    toString(culong_t &value);
    static
    std::tstring_t    toString(clonglong_t &value);
    static
    std::tstring_t    toString(culonglong_t &value);
    static
    std::tstring_t    toString(cfloat_t &value, cint_t &precision = 5, cbool_t &is_fixed = true);
    static
    std::tstring_t    toString(cdouble_t &value, cint_t &precision = 10, cbool_t &is_fixed = true);
    static
    std::tstring_t    toString(clongdouble_t &value, cint_t &a_precision = 20, cbool_t &is_fixed = true);
    static
    std::tstring_t    toString(cvoid_t *value);
    static
    std::ctstring_t & toString(std::ctstring_t &value);
    static
    std::tstring_t    toString(ctchar_t *value);
#endif

private:
    xNO_INSTANCE(Format)
    xNO_COPY_ASSIGN(Format)

#if !xFORMAT_MODE_STD_STREAM
    static
    std::tstring_t    _toString(std::csize_t &buffSize, const tchar_t *format, ...);

    template<typename T>
    static
    std::string _floatToString(const T &a_value, cint_t &a_precision, cbool_t &a_is_fixed)
    {
        std::csize_t    buffSize = std::numeric_limits<T>::max_exponent10 + 20;
        std::ctstring_t postfix  = (Type::name(a_value) == xT("long double")) ? xT("Lf") : xT("f");
        std::ctstring_t format   = xT("%0.") + toString(a_precision) + postfix;

        std::tstring_t  value = _toString(buffSize, format.c_str(), a_value);

        if ( !a_is_fixed ) {
            std::size_t i = value.find_last_not_of(xT('0'));

            if (i != std::string::npos && i != value.size() - 1) {
                if (value[i] == xT('.')) {
                    ++ i;
                }

                value = value.substr(0, i + 1);
            }
        }

        return value;
    }
#endif
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "Format.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "Format.cpp"
#endif
