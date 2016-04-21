/**
 * \file   Format.h
 * \brief  format string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Format
    ///< format string
{
public:
#define xFORMAT_STR_DECLARE(n) \
    template<xVA_TYPES_##n> \
    static \
    std::tstring_t str(std::ctstring_t &format, xVA_VARS_##n);

    xFORMAT_STR_DECLARE(1)
    xFORMAT_STR_DECLARE(2)
    xFORMAT_STR_DECLARE(3)
    xFORMAT_STR_DECLARE(4)
    xFORMAT_STR_DECLARE(5)
    xFORMAT_STR_DECLARE(6)
    xFORMAT_STR_DECLARE(7)
    xFORMAT_STR_DECLARE(8)
    xFORMAT_STR_DECLARE(9)
    xFORMAT_STR_DECLARE(10)
    xFORMAT_STR_DECLARE(11)
    xFORMAT_STR_DECLARE(12)
    xFORMAT_STR_DECLARE(13)
    xFORMAT_STR_DECLARE(14)
    xFORMAT_STR_DECLARE(15)
    xFORMAT_STR_DECLARE(16)
    xFORMAT_STR_DECLARE(17)
    xFORMAT_STR_DECLARE(18)
    xFORMAT_STR_DECLARE(19)
    xFORMAT_STR_DECLARE(20)

private:
    static void _format(std::tstringstream_t &ss, const bool &value);
    static void _format(std::tstringstream_t &ss, const tchar_t &value);
    static void _format(std::tstringstream_t &ss, const unsigned char &value);
    static void _format(std::tstringstream_t &ss, const short &value);
    static void _format(std::tstringstream_t &ss, const unsigned short &value);
    static void _format(std::tstringstream_t &ss, const int &value);
    static void _format(std::tstringstream_t &ss, const unsigned int &value);
    static void _format(std::tstringstream_t &ss, const long &value);
    static void _format(std::tstringstream_t &ss, const unsigned long &value);
    static void _format(std::tstringstream_t &ss, const long long &value);
    static void _format(std::tstringstream_t &ss, const unsigned long long &value);
    static void _format(std::tstringstream_t &ss, const float &value);
    static void _format(std::tstringstream_t &ss, const double &value);
    static void _format(std::tstringstream_t &ss, const long double &value);
    static void _format(std::tstringstream_t &ss, const void * value);
    static void _format(std::tstringstream_t &ss, const std::tstring_t &value);
    static void _format(std::tstringstream_t &ss, const tchar_t * value);
    static void _format(std::tstringstream_t &ss, const std::vec_tstring_t &value);

private:
    xNO_INSTANCE(Format)
    xNO_COPY_ASSIGN(Format)

    template<class T>
    static
    int _floatPrecisionMax();
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "Format.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "Format.cpp"
#endif
