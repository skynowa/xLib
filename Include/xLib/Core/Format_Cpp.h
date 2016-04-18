/**
 * \file   Format_Cpp.h
 * \brief  format string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Format
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
    xNO_INSTANCE(Format)
    xNO_COPY_ASSIGN(Format)

#if 1
    #define xFORMAT_SET_OPTIONS_DEFAULT(t) \
        static \
        void _setOptions(std::tstringstream_t &ss, t &a_value) {}

    xFORMAT_SET_OPTIONS_DEFAULT(cbool_t)
    xFORMAT_SET_OPTIONS_DEFAULT(const char)
    xFORMAT_SET_OPTIONS_DEFAULT(const wchar_t)
    xFORMAT_SET_OPTIONS_DEFAULT(cuchar_t)
    xFORMAT_SET_OPTIONS_DEFAULT(cshort_t)
    xFORMAT_SET_OPTIONS_DEFAULT(cushort_t)
    xFORMAT_SET_OPTIONS_DEFAULT(cint_t)
    xFORMAT_SET_OPTIONS_DEFAULT(cuint_t)
    xFORMAT_SET_OPTIONS_DEFAULT(clong_t)
    xFORMAT_SET_OPTIONS_DEFAULT(culong_t)
    xFORMAT_SET_OPTIONS_DEFAULT(clonglong_t)
    xFORMAT_SET_OPTIONS_DEFAULT(culonglong_t)
    xFORMAT_SET_OPTIONS_DEFAULT(cvoid_t *)
    xFORMAT_SET_OPTIONS_DEFAULT(const std::string)
    xFORMAT_SET_OPTIONS_DEFAULT(const std::wstring)
    xFORMAT_SET_OPTIONS_DEFAULT(const char *)
    xFORMAT_SET_OPTIONS_DEFAULT(const wchar_t *)
    xFORMAT_SET_OPTIONS_DEFAULT(std::cvec_tstring_t)

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
#endif
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "Format_Cpp.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "Format_Cpp.cpp"
#endif
