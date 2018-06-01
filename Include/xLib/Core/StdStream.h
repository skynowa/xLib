/**
 * \file   StdStream.h
 * \brief  format string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Core/Array.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class StdStream
    ///< format string
{
public:
    static
    std::ctstring_t & specifier() xWARN_UNUSED_RV;
        ///< open specifier
    static
    std::ctstring_t & specifierOpen() xWARN_UNUSED_RV;
        ///< close specifier
    static
    std::ctstring_t & specifierClose() xWARN_UNUSED_RV;
        ///< specifier
    static
    std::ctstring_t & delimiter() xWARN_UNUSED_RV;
        ///< delimiter
    static
    tchar_t           unprintableChar() xWARN_UNUSED_RV;
        ///< unprintable char

    static void_t format(std::tostream_t &os, const bool value);
    static void_t format(std::tostream_t &os, const char value);
    static void_t format(std::tostream_t &os, const wchar_t value);
    static void_t format(std::tostream_t &os, const unsigned char value);
    static void_t format(std::tostream_t &os, const short value);
    static void_t format(std::tostream_t &os, const unsigned short value);
    static void_t format(std::tostream_t &os, const int value);
    static void_t format(std::tostream_t &os, const unsigned int value);
    static void_t format(std::tostream_t &os, const long value);
    static void_t format(std::tostream_t &os, const unsigned long value);
    static void_t format(std::tostream_t &os, const long long value);
    static void_t format(std::tostream_t &os, const unsigned long long value);
    static void_t format(std::tostream_t &os, const float value);
    static void_t format(std::tostream_t &os, const double value);
    static void_t format(std::tostream_t &os, const long double value);
    static void_t format(std::tostream_t &os, const void *value);
    static void_t format(std::tostream_t &os, const char *value);
    static void_t format(std::tostream_t &os, const wchar_t *value);
    static void_t format(std::tostream_t &os, const std::wstring &value);
    static void_t format(std::tostream_t &os, const std::string &value);
    static void_t format(std::tostream_t &os, const std::ustring_t &value);

    template<typename T, std::size_t N>
    static void_t format(std::tostream_t &os, const Array<T, N> &value);

    template<typename T1, typename T2>
    static void_t format(std::tostream_t &os, const std::pair<T1, T2> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::vector<T> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::list<T> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::set<T> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::multiset<T> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::deque<T> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::queue<T> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::priority_queue<T> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::stack<T> &value);

    template<typename T1, typename T2>
    static void_t format(std::tostream_t &os, const std::map<T1, T2> &value);

    template<typename T1, typename T2>
    static void_t format(std::tostream_t &os, const std::multimap<T1, T2> &value);

#if xLANG_CPP11
    static void_t format(std::tostream_t &os, const std::nullptr_t value);

    template<typename T, std::size_t N>
    static void_t format(std::tostream_t &os, const std::array<T, N> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::forward_list<T> &value);

    template<typename T1, typename T2>
    static void_t format(std::tostream_t &os, const std::unordered_map<T1, T2> &value);

    template<typename T1, typename T2>
    static void_t format(std::tostream_t &os, const std::unordered_multimap<T1, T2> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::unordered_set<T> &value);

    template<typename T>
    static void_t format(std::tostream_t &os, const std::unordered_multiset<T> &value);

    template<typename T, std::size_t N>
    struct TupleFormat
    {
        static void_t
        format(std::tostream_t &a_ss, const T &a_value)
        {
            TupleFormat<T, N - 1>::format(a_ss, a_value);
            a_ss << delimiter() << std::get<N - 1>(a_value);
        }
    };

    template<typename T>
    struct TupleFormat<T, 1>
    {
        static void_t
        format(std::tostream_t &a_ss, const T &a_value)
        {
            a_ss << std::get<0>(a_value);
        }
    };

    template<typename... Args>
    static void_t format(std::tostream_t &os, const std::tuple<Args...> &value);
#endif

#if xLIB_QT
    static void_t format(std::tostream_t &os, const QString &value);
#endif

private:
    xNO_INSTANCE(StdStream)
    xNO_COPY_ASSIGN(StdStream)

    template<typename IteratorT>
    static void_t _formatString(std::tostream_t &os, IteratorT first, IteratorT last);

    template<typename IteratorT>
    static void_t _formatRange(std::tostream_t &os, IteratorT first, IteratorT last);

    template<typename T>
    static void_t _formatContainer(std::tostream_t &os, const T &value);

    template<typename T>
    static void_t _formatFloat(std::tostream_t &os, const T value);

    template<typename T>
    static int_t _floatPrecisionMax() xWARN_UNUSED_RV;

    template<typename T>
    static std::tstring_t _formatUnprintableChar(const T value) xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "StdStream.inl"
