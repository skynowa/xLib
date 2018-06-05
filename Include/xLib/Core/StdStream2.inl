/**
 * \file   StdStream2.inl
 * \brief  print string
 */


#include <xLib/Core/Char.h>
#include <xLib/Algo/Algos.h>


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, std::size_t N>
inline StdStream2 &
StdStream2::operator << (
    const Array<T, N> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline StdStream2 &
StdStream2::operator << (
    const std::pair<T1, T2> &a_value   ///< value
)
{
    _os << _bracketOpen();
    _os << a_value.first;
    _os << _delimiter();
    _os << a_value.second;
    _os << _bracketClose();

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::vector<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::list<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::set<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::multiset<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::deque<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::queue<T> &a_value   ///< value
)
{
    typedef const T* const_iterator;

    const_iterator begin = &a_value.front();
    const_iterator end   = &a_value.back() + 1;

    _printRange(begin, end);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::priority_queue<T> &a_value   ///< value
)
{
    typedef const T* const_iterator;

    const_iterator begin = &a_value.top();
    const_iterator end   = &a_value.top() + a_value.size();

    _printRange(begin, end);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::stack<T> &a_value   ///< value
)
{
    typedef const T* const_iterator;

    const_iterator begin = &a_value.top() - a_value.size() + 1;
    const_iterator end   = &a_value.top() + 1;

    _printRange(begin, end);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline StdStream2 &
StdStream2::operator << (
    const std::map<T1, T2> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline StdStream2 &
StdStream2::operator << (
    const std::multimap<T1, T2> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public - xLANG_CPP11
*
**************************************************************************************************/

#if xLANG_CPP11

//-------------------------------------------------------------------------------------------------
template<typename T, std::size_t N>
inline StdStream2 &
StdStream2::operator << (
    const std::array<T, N> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::forward_list<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline StdStream2 &
StdStream2::operator << (
    const std::unordered_map<T1, T2> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
inline StdStream2 &
StdStream2::operator << (
    const std::unordered_multimap<T1, T2> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::unordered_set<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline StdStream2 &
StdStream2::operator << (
    const std::unordered_multiset<T> &a_value   ///< value
)
{
    _printContainer(a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline StdStream2 &
StdStream2::operator << (
    const std::tuple<Args...> &a_value   ///< value
)
{
    _os << _bracketOpen();
    TupleFormat<decltype(a_value), sizeof...(Args)>::print(_os, a_value);
    _os << _bracketClose();

    return *this;
}
//-------------------------------------------------------------------------------------------------

#endif // xLANG_CPP11


/**************************************************************************************************
*   public - 3-d party libs
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#if xLIB_QT

inline StdStream2 &
StdStream2::operator << (
    const QString   &a_value   ///< value
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
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename IteratorT>
inline void_t
StdStream2::_printString(
    IteratorT        a_first,  ///< first iterator
    IteratorT        a_last    ///< last iterator
)
{
    for (; a_first != a_last; ++ a_first) {
		_os << *a_first;
    }
}
//-------------------------------------------------------------------------------------------------
template<typename IteratorT>
inline void_t
StdStream2::_printRange(
    IteratorT        a_first,  ///< first iterator
    IteratorT        a_last    ///< last iterator
)
{
    if (a_first == a_last) {
        _os << _bracketOpen();
        _os << _bracketClose();
        return;
    }

    _os << _bracketOpen();
	_os << *a_first;

    for (++ a_first; a_first != a_last; ++ a_first) {
        _os << _delimiter() << *a_first;
    }

    _os << _bracketClose();
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
StdStream2::_printContainer(
    const T         &a_value   ///< value
)
{
    _printRange(a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline void_t
StdStream2::_printFloat(
    const T          a_value
)
{
    _os
        << std::setprecision( _floatPrecisionMax<T>() )
        << std::showpoint
        << a_value;

    std::tstreambuf_t *buff = _os.rdbuf();

    std::tstring_t value = std::tstring_t(
        std::istreambuf_iterator<tchar_t>(buff),
        std::istreambuf_iterator<tchar_t>());

    std::size_t i = value.find_last_not_of(xT('0'));

    if (i != std::tstring_t::npos && i != value.size() - 1) {
        if (value[i] == xT('.')) {
            ++ i;
        }

        value = value.substr(0, i + 1);
    }

    _os << value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline int_t
StdStream2::_floatPrecisionMax()
{
#if xLANG_CPP11
    return std::numeric_limits<T>::max_digits10;
#else
    return std::numeric_limits<T>::digits10 + 1;
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline std::tstring_t
StdStream2::_printUnprintableChar(
    const T a_value
)
{
   /**
    * FAQ: C documentation for isprint
    *
    * +---------+---------------------------+-------------------+
    * | ASCII   | Characters                | isprint, iswprint |
    * +---------+---------------------------+-------------------+
    * | 0 - 8   | control codes (NUL, etc.) | -                 |
    * | 9       | tab (\t)                  | -                 |
    * | 10 - 13 | whitespaces (\n,\v,\f,\r) | -                 |
    * | 14 - 31 | control codes             | -                 |
    * | 32      | space                     | +                 |
    * | 33 - 47 | !"#$%&'()*+,-./           | +                 |
    * | 48 - 57 | 123456789                 | +                 |
    * | 58 - 64 | :;<=>?@                   | +                 |
    * | 65 - 70 | ABCDEF                    | +                 |
    * | 71 - 90 | GHIJKLMNOPQRSTUVWXYZ      | +                 |
    * | 91 - 96 | [\]^_`                    | +                 |
    * | 97 -102 | abcdef                    | +                 |
    * | 103-122 | ghijklmnopqrstuvwxyz      | +                 |
    * | 123-126 | {|}~                      | +                 |
    * | 127     | backspace character (DEL) | -                 |
    * +-------------------------------------+-------------------+
    */

    Char<T> ch(a_value);
    if      ( Algos::isInBounds<T>(ch.character(), 0, 31) ) {
        return xT("<") + ch.symbol() + xT(">");
    }
    else if ( Algos::isInBounds<T>(ch.character(), 32, 126) ) {
        return ch.symbol();
    }
    else if ( Algos::isInBounds<T>(ch.character(), 127, 255) ) {
        return xT("?");
    }
    else {
        return xT("?");
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
