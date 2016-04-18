/**
 * \file   Format_Cpp.h
 * \brief  format string
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>

#include <xLib/Core/Format.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Format_Cpp
    ///< format string
{
public:
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
    xNO_INSTANCE(Format_Cpp)
    xNO_COPY_ASSIGN(Format_Cpp)

#if 0
    static
    void _setOptions(std::tstringstream_t &ss, cbool_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, const char &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, const wchar_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, cuchar_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, cshort_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, cushort_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, cint_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, cuint_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, clong_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, culong_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, clonglong_t &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, culonglong_t &a_value) {}

    static
    void _setOptions(std::tstringstream_t &ss, cfloat_t &a_value)
    {
        ss << std::setprecision(5);
        ss << std::fixed;
    }
    static
    void _setOptions(std::tstringstream_t &ss, cdouble_t &a_value)
    {
        ss << std::setprecision(10);
        ss << std::fixed;
    }
    static
    void _setOptions(std::tstringstream_t &ss, clongdouble_t &a_value)
    {
        ss << std::setprecision(20);
        ss << std::fixed;
    }

    static
    void _setOptions(std::tstringstream_t &ss, cvoid_t * &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, const std::string &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, const std::wstring &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, const char * &a_value) {}
    static
    void _setOptions(std::tstringstream_t &ss, const wchar_t * &a_value) {}
#endif
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "Format_Cpp.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "Format_Cpp.cpp"
#endif
