/**
 * \file   OStream.inl
 * \brief  print string
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/Char.h>
#include <xLib/Core/Type/Type.h>
#include <xLib/Algo/Algos.h>


namespace xl::core
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline OStream &
OStream::operator << (
    const std::pair<T1, T2> &a_value   ///< value
)
{
    _os << _bracketOpen();
    _printValue(a_value.first);
    _os << _delimiter();
    _printValue(a_value.second);
    _os << _bracketClose();

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::vector<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::list<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::set<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::multiset<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::deque<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::queue<T> &a_value   ///< value
)
{
	using const_iterator = const T *;

    const_iterator begin = &a_value.front();
    const_iterator end   = &a_value.back() + 1;

    _printRange(begin, end);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::priority_queue<T> &a_value   ///< value
)
{
    using const_iterator = const T *;

    const_iterator begin = &a_value.top();
    const_iterator end   = &a_value.top() + a_value.size();

    _printRange(begin, end);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::stack<T> &a_value   ///< value
)
{
    using const_iterator = const T *;

    const_iterator begin = &a_value.top() - a_value.size() + 1;
    const_iterator end   = &a_value.top() + 1;

    _printRange(begin, end);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline OStream &
OStream::operator << (
    const std::map<T1, T2> &a_value   ///< value
)
{
    _printMap(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline OStream &
OStream::operator << (
    const std::multimap<T1, T2> &a_value   ///< value
)
{
    _printMap(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T, std::size_t N>
inline OStream &
OStream::operator << (
    const std::array<T, N> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::forward_list<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline OStream &
OStream::operator << (
    const std::unordered_map<T1, T2> &a_value   ///< value
)
{
    _printMap(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline OStream &
OStream::operator << (
    const std::unordered_multimap<T1, T2> &a_value   ///< value
)
{
    _printMap(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::unordered_set<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
    const std::unordered_multiset<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline OStream &
OStream::operator << (
    const std::tuple<Args...> &a_value   ///< value
)
{
    _os << _bracketOpen();
    TuplePrint<decltype(a_value), sizeof...(Args)>::print(_os, a_value);
    _os << _bracketClose();

    return *this;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public - 3-d party libs
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#if xLIB_QT

inline OStream &
OStream::operator << (
    const QString &a_value   ///< value
)
{
#if xANSI
    _os << a_value.toStdString();
#else
    _os << a_value.toStdWString();
#endif

    return *this;
}

#endif
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   xLib
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline OStream &
OStream::operator << (
	const Float<T> &a_value ///< value
)
{
	_printFloat( a_value.get() );

	return *this;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
OStream::_printContainerTitle(
	const T &a_value   ///< value
)
{
    // TODO: std::forward_list - max_size()
	xUNUSED(a_value);

    /// _os << TypeName<T>::get() << xT(" (size=") /*<< a_value.size()*/ << xT("):") << std::endl;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
OStream::_printValue(
    const T &a_value   ///< value
)
{
    OStream::operator << (a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename IteratorT>
inline void_t
OStream::_printString(
    IteratorT a_first,    ///< first iterator
    IteratorT a_last      ///< last iterator
)
{
    for (; a_first != a_last; ++ a_first) {
		_printValue(*a_first);
    }
}
//-------------------------------------------------------------------------------------------------
template<typename IteratorT>
inline void_t
OStream::_printRange(
    IteratorT a_first,    ///< first iterator
    IteratorT a_last      ///< last iterator
)
{
    if (a_first == a_last) {
        _os << _bracketOpen();
        _os << _bracketClose();
        return;
    }

    _os << _bracketOpen();
	_printValue(*a_first);

    for (++ a_first; a_first != a_last; ++ a_first) {
        _os << _delimiter();
        _printValue(*a_first);
    }

    _os << _bracketClose();
}
//-------------------------------------------------------------------------------------------------
template<typename IteratorT>
inline void_t
OStream::_printRangeMap(
    IteratorT a_first,    ///< first iterator
    IteratorT a_last      ///< last iterator
)
{
    if (a_first == a_last) {
        _os << _bracketOpen();
        _os << _bracketClose();
        return;
    }

    _os << _bracketOpen();
	_printValue(*a_first);

    for (++ a_first; a_first != a_last; ++ a_first) {
        _os << Const::nl();
        _printValue(*a_first);
    }

    _os << _bracketClose();
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
OStream::_printContainer(
    const T &a_value   ///< value
)
{
	_printContainerTitle(a_value);
    _printRange(a_value.cbegin(), a_value.cend());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
OStream::_printMap(
    const T &a_value   ///< value
)
{
	_printContainerTitle(a_value);
    _printRangeMap(a_value.cbegin(), a_value.cend());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
OStream::_printFloat(
    const T a_value
)
{
	std::tstring_t value = std::to_string(a_value);

   /**
    * Skip extras '0' from end:
    *
    * - 15.000   -> 15.0
    * - 12.99000 -> 12.99
    */

	std::size_t pos = value.find_last_not_of(xT('0'));
	if (pos != std::tstring_t::npos &&
		pos != value.size() - 1)
	{
		if (value[pos] == xT('.')) {
			++ pos;
		}

		value = value.substr(0, pos + 1);
	}

	_os << value;
}
//-------------------------------------------------------------------------------------------------
template<typename T, std::csize_t N>
struct OStream::TuplePrint
{
    static void_t
    print(std::tostream_t &a_ss, const T &a_value)
    {
        TuplePrint<T, N - 1>::print(a_ss, a_value);
        a_ss << _delimiter() << std::get<N - 1>(a_value);
    }
};
//-------------------------------------------------------------------------------------------------
template<typename T>
struct OStream::TuplePrint<T, 1>
{
    static void_t
    print(std::tostream_t &a_ss, const T &a_value)
    {
        a_ss << std::get<0>(a_value);
    }
};
//-------------------------------------------------------------------------------------------------

} // namespace
