/**
 * \file   OStream.h
 * \brief  print string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class OStream
    ///< print string
{
public:
                   OStream() = default;
    virtual       ~OStream() = default;

    std::tstring_t str() const;
    void_t         str(std::ctstring_t &value);
    void_t         clear();

	// operators <<
	// TODO: [skynowa] more overload methods
    OStream & operator << (const bool value);
    OStream & operator << (const char value);
    OStream & operator << (const wchar_t value);
    OStream & operator << (const unsigned char value);
    OStream & operator << (const short value);
    OStream & operator << (const unsigned short value);
    OStream & operator << (const int value);
    OStream & operator << (const unsigned int value);
    OStream & operator << (const long value);
    OStream & operator << (const unsigned long value);
    OStream & operator << (const long long value);
    OStream & operator << (const unsigned long long value);
    OStream & operator << (const float value);
    OStream & operator << (const double value);
    OStream & operator << (const long double value);
    OStream & operator << (const void *value);
    OStream & operator << (const char *value);
    OStream & operator << (const wchar_t *value);
    OStream & operator << (const std::wstring &value);
    OStream & operator << (const std::string &value);
    OStream & operator << (const std::ustring_t &value);

    template<typename T1, typename T2>
    OStream & operator << (const std::pair<T1, T2> &value);

    template<typename T>
    OStream & operator << (const std::vector<T> &value);

    template<typename T>
    OStream & operator << (const std::list<T> &value);

    template<typename T>
    OStream & operator << (const std::set<T> &value);

    template<typename T>
    OStream & operator << (const std::multiset<T> &value);

    template<typename T>
    OStream & operator << (const std::deque<T> &value);

    template<typename T>
    OStream & operator << (const std::queue<T> &value);

    template<typename T>
    OStream & operator << (const std::priority_queue<T> &value);

    template<typename T>
    OStream & operator << (const std::stack<T> &value);

    template<typename T1, typename T2>
    OStream & operator << (const std::map<T1, T2> &value);

    template<typename T1, typename T2>
    OStream & operator << (const std::multimap<T1, T2> &value);

    OStream & operator << (const std::nullptr_t value);

    template<typename T, std::size_t N>
    OStream & operator << (const std::array<T, N> &value);

    template<typename T>
    OStream & operator << (const std::forward_list<T> &value);

    template<typename T1, typename T2>
    OStream & operator << (const std::unordered_map<T1, T2> &value);

    template<typename T1, typename T2>
    OStream & operator << (const std::unordered_multimap<T1, T2> &value);

    template<typename T>
    OStream & operator << (const std::unordered_set<T> &value);

    template<typename T>
    OStream & operator << (const std::unordered_multiset<T> &value);

    template<typename... Args>
    OStream & operator << (const std::tuple<Args...> &value);

#if xLIB_QT
    OStream & operator << (const QString &value);
#endif

	OStream & operator << (std::tostream_t& (*a_os)(std::tostream_t &))
	{
		this->_os << a_os;

		return *this;
	}
        ///< print std::endl

protected:
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

    template<typename T>
    void_t _printContainerTitle(const T &a_value);

    template<typename T>
    void_t _printValue(const T &value);

    template<typename IteratorT>
    void_t _printString(IteratorT first, IteratorT last);

    template<typename IteratorT>
    void_t _printRange(IteratorT first, IteratorT last);

    template<typename IteratorT>
    void_t _printRangeMap(IteratorT first, IteratorT last);

    template<typename T>
    void_t _printContainer(const T &value);

    template<typename T>
    void_t _printMap(const T &value);

    template<typename T>
    void_t _printFloat(const T value);

    template<typename T>
    std::tstring_t _unprintableChar(const T value) xWARN_UNUSED_RV;

	// std::tuple
	template<typename T, std::csize_t N>
	struct TuplePrint;

	template<typename T>
	struct TuplePrint<T, 1>;

    xNO_COPY_ASSIGN(OStream)
};
//-------------------------------------------------------------------------------------------------
class Cout :
	public OStream
    /// print std::cout
{
public:
             Cout() = default;
    virtual ~Cout() = default;

    xNO_COPY_ASSIGN(Cout)

	template<typename T>
	Cout & operator << (const T a_value)
	{
		OStream::operator << (a_value);

		std::tcout << OStream::str();

		OStream::str({});
		OStream::clear();

		return *this;
	}

	Cout & operator << (std::tostream_t& (*a_os)(std::tostream_t &))
	{
		/// this->_os << a_os;
		a_os(std::tcout);

		return *this;
	}
        ///< print std::endl
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "OStream.inl"
//-------------------------------------------------------------------------------------------------
