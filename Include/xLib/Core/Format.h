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

// http://www.cplusplus.com/reference/limits/numeric_limits/

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

#define xFORMAT_SET_MANIPULATORS_DEFAULT(t) \
    static \
    void setManipulators(std::tstringstream_t &ss, t value) {}

    static
    void setManipulators(std::tstringstream_t &ss, bool value);

    xFORMAT_SET_MANIPULATORS_DEFAULT(char)
    xFORMAT_SET_MANIPULATORS_DEFAULT(unsigned char)
    //xFORMAT_SET_MANIPULATORS_DEFAULT(wchar_t)
    //xFORMAT_SET_MANIPULATORS_DEFAULT(unsigned wchar_t)

    xFORMAT_SET_MANIPULATORS_DEFAULT(short);
    xFORMAT_SET_MANIPULATORS_DEFAULT(unsigned short);
    xFORMAT_SET_MANIPULATORS_DEFAULT(int);
    xFORMAT_SET_MANIPULATORS_DEFAULT(unsigned int);
    xFORMAT_SET_MANIPULATORS_DEFAULT(long);
    xFORMAT_SET_MANIPULATORS_DEFAULT(unsigned long);
    xFORMAT_SET_MANIPULATORS_DEFAULT(long long);
    xFORMAT_SET_MANIPULATORS_DEFAULT(unsigned long long);

    static
    void setManipulators(std::tstringstream_t &ss, float value);
    static
    void setManipulators(std::tstringstream_t &ss, double value);
    static
    void setManipulators(std::tstringstream_t &ss, long double value);

    xFORMAT_SET_MANIPULATORS_DEFAULT(void *)
    xFORMAT_SET_MANIPULATORS_DEFAULT(std::string)
    //xFORMAT_SET_MANIPULATORS_DEFAULT(std::wstring)
    xFORMAT_SET_MANIPULATORS_DEFAULT(char *)
    //xFORMAT_SET_MANIPULATORS_DEFAULT(wchar_t *)
    xFORMAT_SET_MANIPULATORS_DEFAULT(std::vec_tstring_t)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "Format.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "Format.cpp"
#endif
