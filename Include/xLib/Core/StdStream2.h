/**
 * \file   StdStream2.h
 * \brief  print string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Core/Array.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class StdStream2
    ///< print string
{
public:
                   StdStream2();
    virtual       ~StdStream2();

    std::tstring_t str() const;
    void_t         str(std::ctstring_t &value);
    void_t         clear();

    StdStream2 & operator << (const bool value);
    StdStream2 & operator << (const char value);
    StdStream2 & operator << (const wchar_t value);
    StdStream2 & operator << (const unsigned char value);
    StdStream2 & operator << (const short value);
    StdStream2 & operator << (const unsigned short value);
    StdStream2 & operator << (const int value);
    StdStream2 & operator << (const unsigned int value);
    StdStream2 & operator << (const long value);
    StdStream2 & operator << (const unsigned long value);
    StdStream2 & operator << (const long long value);
    StdStream2 & operator << (const unsigned long long value);
    StdStream2 & operator << (const float value);
    StdStream2 & operator << (const double value);
    StdStream2 & operator << (const long double value);
    StdStream2 & operator << (const void *value);
    StdStream2 & operator << (const char *value);
    StdStream2 & operator << (const wchar_t *value);
    StdStream2 & operator << (const std::wstring &value);
    StdStream2 & operator << (const std::string &value);
    StdStream2 & operator << (const std::ustring_t &value);

    template<typename T, std::size_t N>
    StdStream2 & operator << (const Array<T, N> &value);

    template<typename T1, typename T2>
    StdStream2 & operator << (const std::pair<T1, T2> &value);

    template<typename T>
    StdStream2 & operator << (const std::vector<T> &value);

    template<typename T>
    StdStream2 & operator << (const std::list<T> &value);

    template<typename T>
    StdStream2 & operator << (const std::set<T> &value);

    template<typename T>
    StdStream2 & operator << (const std::multiset<T> &value);

    template<typename T>
    StdStream2 & operator << (const std::deque<T> &value);

    template<typename T>
    StdStream2 & operator << (const std::queue<T> &value);

    template<typename T>
    StdStream2 & operator << (const std::priority_queue<T> &value);

    template<typename T>
    StdStream2 & operator << (const std::stack<T> &value);

    template<typename T1, typename T2>
    StdStream2 & operator << (const std::map<T1, T2> &value);

    template<typename T1, typename T2>
    StdStream2 & operator << (const std::multimap<T1, T2> &value);

#if xLANG_CPP11
    StdStream2 & operator << (const std::nullptr_t value);

    template<typename T, std::size_t N>
    StdStream2 & operator << (const std::array<T, N> &value);

    template<typename T>
    StdStream2 & operator << (const std::forward_list<T> &value);

    template<typename T1, typename T2>
    StdStream2 & operator << (const std::unordered_map<T1, T2> &value);

    template<typename T1, typename T2>
    StdStream2 & operator << (const std::unordered_multimap<T1, T2> &value);

    template<typename T>
    StdStream2 & operator << (const std::unordered_set<T> &value);

    template<typename T>
    StdStream2 & operator << (const std::unordered_multiset<T> &value);

    template<typename T, std::size_t N>
    struct TupleFormat
    {
        static void_t
        print(std::tostream_t &a_ss, const T &a_value)
        {
            TupleFormat<T, N - 1>::print(a_ss, a_value);
            a_ss << _delimiter() << std::get<N - 1>(a_value);
        }
    };

    template<typename T>
    struct TupleFormat<T, 1>
    {
        static void_t
        print(std::tostream_t &a_ss, const T &a_value)
        {
            a_ss << std::get<0>(a_value);
        }
    };

    template<typename... Args>
    StdStream2 & operator << (const std::tuple<Args...> &value);
#endif

#if xLIB_QT
    StdStream2 & operator << (const QString &value);
#endif

private:
    std::tstringstream_t _os;

    static
    std::ctstring_t & _bracketOpen() xWARN_UNUSED_RV;
        ///< open bracket
    static
    std::ctstring_t & _bracketClose() xWARN_UNUSED_RV;
        ///< close bracket
    static
    std::ctstring_t & _delimiter() xWARN_UNUSED_RV;
        ///< _delimiter
    static
    tchar_t           _unprintableChar() xWARN_UNUSED_RV;
        ///< unprintable char

    template<typename IteratorT>
    void_t _printString(IteratorT first, IteratorT last);

    template<typename IteratorT>
    void_t _printRange(IteratorT first, IteratorT last);

    template<typename T>
    void_t _printContainer(const T &value);

    template<typename T>
    void_t _printFloat(const T value);

    template<typename T>
    int_t _floatPrecisionMax() xWARN_UNUSED_RV;

    template<typename T>
    std::tstring_t _printUnprintableChar(const T value) xWARN_UNUSED_RV;

    xNO_COPY_ASSIGN(StdStream2)
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "StdStream2.inl"
