/**
 * \file   Format.h
 * \brief  format string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Format
    ///< format string
{
public:
    static std::tstring_t c_str(ctchar_t *format, ...) xWARN_UNUSED_RV;
    static std::tstring_t c_strV(ctchar_t *format, va_list args) xWARN_UNUSED_RV;

#define xFORMAT_STR_DECLARE(n) \
    template<xVA_TYPES_##n> \
    static std::tstring_t str(std::ctstring_t &format, xVA_VARS_##n) xWARN_UNUSED_RV;

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
    static
    std::ctstring_t & _specifier() xWARN_UNUSED_RV;
        ///< specifier
    static
    std::ctstring_t & _delimiter() xWARN_UNUSED_RV;
        ///< delimiter
    static
    tchar_t           _unprintableChar() xWARN_UNUSED_RV;
        ///< unprintable char

    static void _format(std::tstringstream_t &ss, const bool &value);
    static void _format(std::tstringstream_t &ss, const char &value);
    static void _format(std::tstringstream_t &ss, const wchar_t &value);
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
#if xOPTION_CPP11
    static void _format(std::tstringstream_t &ss, const std::nullptr_t value);
#endif
    static void _format(std::tstringstream_t &ss, const char * value);
    static void _format(std::tstringstream_t &ss, const wchar_t * value);
    static void _format(std::tstringstream_t &ss, const std::wstring &value);
    static void _format(std::tstringstream_t &ss, const std::string &value);
    static void _format(std::tstringstream_t &ss, const std::ustring_t &value);

#if xOPTION_CPP11
    template<typename T, std::size_t N>
    static void _format(std::tstringstream_t &ss, const std::array<T, N> &value);
#endif

    template<typename T1, class T2>
    static void _format(std::tstringstream_t &ss, const std::pair<T1, T2> &value);

    template<typename T>
    static void _format(std::tstringstream_t &ss, const std::vector<T> &value);

    template<typename T>
    static void _format(std::tstringstream_t &ss, const std::list<T> &value);

    template<typename T>
    static void _format(std::tstringstream_t &ss, const std::set<T> &value);

    template<typename T>
    static void _format(std::tstringstream_t &ss, const std::multiset<T> &value);

    template<typename T1, class T2>
    static void _format(std::tstringstream_t &ss, const std::map<T1, T2> &value);

    template<typename T1, class T2>
    static void _format(std::tstringstream_t &ss, const std::multimap<T1, T2> &value);

    template<typename T>
    static void _format(std::tstringstream_t &ss, const T &value);
        ///< format other types with overload std::tostream_t::operator <<

#if xLIB_QT
    static void _format(std::tstringstream_t &ss, const QString &value);
#endif

private:
    xNO_INSTANCE(Format)
    xNO_COPY_ASSIGN(Format)

    template<typename IteratorT>
    static void _formatString(std::tstringstream_t &ss, IteratorT first, IteratorT last);

    template<typename IteratorT>
    static void _formatRange(std::tstringstream_t &ss, IteratorT first, IteratorT last);

    template<typename T>
    static void _formatContainer(std::tstringstream_t &ss, const T &value);

    template<typename T>
    static void _formatFloat(std::tstringstream_t &ss, const T &value);

    template<typename T>
    static int  _floatPrecisionMax() xWARN_UNUSED_RV;

    template<typename T>
    static std::tstring_t _formatUnprintableChar(const T &value) xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "Format.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "Format.cpp"
#endif
