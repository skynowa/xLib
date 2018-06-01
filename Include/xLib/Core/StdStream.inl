/**
 * \file   StdStream.inl
 * \brief  format string
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
/* static */
inline void_t
StdStream::format(
    std::tostream_t   &a_os,     ///< [out]
    const Array<T, N> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
/* static */
inline void_t
StdStream::format(
    std::tostream_t         &a_os,     ///< [out]
    const std::pair<T1, T2> &a_value   ///< value
)
{
    format(a_os, specifierOpen());
    format(a_os, a_value.first);
    format(a_os, delimiter());
    format(a_os, a_value.second);
    format(a_os, specifierClose());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t      &a_os,     ///< [out]
    const std::vector<T> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t    &a_os,     ///< [out]
    const std::list<T> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t   &a_os,     ///< [out]
    const std::set<T> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t        &a_os,     ///< [out]
    const std::multiset<T> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t     &a_os,     ///< [out]
    const std::deque<T> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t     &a_os,     ///< [out]
    const std::queue<T> &a_value   ///< value
)
{
    typedef const T* const_iterator;

    const_iterator begin = &a_value.front();
    const_iterator end   = &a_value.back() + 1;

    _formatRange(a_os, begin, end);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t              &a_os,     ///< [out]
    const std::priority_queue<T> &a_value   ///< value
)
{
    typedef const T* const_iterator;

    const_iterator begin = &a_value.top();
    const_iterator end   = &a_value.top() + a_value.size();

    _formatRange(a_os, begin, end);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t     &a_os,     ///< [out]
    const std::stack<T> &a_value   ///< value
)
{
    typedef const T* const_iterator;

    const_iterator begin = &a_value.top() - a_value.size() + 1;
    const_iterator end   = &a_value.top() + 1;

    _formatRange(a_os, begin, end);
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
/* static */
inline void_t
StdStream::format(
    std::tostream_t        &a_os,     ///< [out]
    const std::map<T1, T2> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
/* static */
inline void_t
StdStream::format(
    std::tostream_t             &a_os,     ///< [out]
    const std::multimap<T1, T2> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public - xLANG_CPP11
*
**************************************************************************************************/

#if xLANG_CPP11

//-------------------------------------------------------------------------------------------------
template<typename T, std::size_t N>
/* static */
inline void_t
StdStream::format(
    std::tostream_t        &a_os,     ///< [out]
    const std::array<T, N> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t            &a_os,     ///< [out]
    const std::forward_list<T> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
/* static */
inline void_t
StdStream::format(
    std::tostream_t                  &a_os,     ///< [out]
    const std::unordered_map<T1, T2> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T1, typename T2>
/* static */
inline void_t
StdStream::format(
    std::tostream_t                       &a_os,     ///< [out]
    const std::unordered_multimap<T1, T2> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t             &a_os,     ///< [out]
    const std::unordered_set<T> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::format(
    std::tostream_t                  &a_os,     ///< [out]
    const std::unordered_multiset<T> &a_value   ///< value
)
{
    _formatContainer(a_os, a_value);
}
//-------------------------------------------------------------------------------------------------
template<typename... Args>
inline void_t
StdStream::format(
    std::tostream_t           &a_os,     ///< [out]
    const std::tuple<Args...> &a_value   ///< value
)
{
    a_os << specifierOpen();
    TupleFormat<decltype(a_value), sizeof...(Args)>::format(a_os, a_value);
    a_os << specifierClose();
}
//-------------------------------------------------------------------------------------------------

#endif // xLANG_CPP11


/**************************************************************************************************
*   public - 3-d party libs
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#if xLIB_QT

/* static */
inline void_t
StdStream::format(
    std::tostream_t &a_os,     ///< [out]
    const QString   &a_value   ///< value
)
{
#if xANSI
    a_os << a_value.toStdString();
#else
    a_os << a_value.toStdWString();
#endif
}

#endif
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename IteratorT>
/* static */
inline void_t
StdStream::_formatString(
    std::tostream_t &a_os,     ///< [out]
    IteratorT        a_first,  ///< first iterator
    IteratorT        a_last    ///< last iterator
)
{
    for (; a_first != a_last; ++ a_first) {
		a_os << *a_first;
    }
}
//-------------------------------------------------------------------------------------------------
template<typename IteratorT>
/* static */
inline void_t
StdStream::_formatRange(
    std::tostream_t &a_os,     ///< [out]
    IteratorT        a_first,  ///< first iterator
    IteratorT        a_last    ///< last iterator
)
{
    if (a_first == a_last) {
        a_os << specifier();
        return;
    }

    a_os << specifierOpen();
	a_os << *a_first;

    for (++ a_first; a_first != a_last; ++ a_first) {
        a_os << delimiter() << *a_first;
    }

    a_os << specifierClose();
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::_formatContainer(
    std::tostream_t &a_os,     ///< [out]
    const T         &a_value   ///< value
)
{
    _formatRange(a_os, a_value.begin(), a_value.end());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline void_t
StdStream::_formatFloat(
    std::tostream_t &a_os,
    const T          a_value
)
{
    a_os
        << std::setprecision( _floatPrecisionMax<T>() )
        << std::showpoint
        << a_value;

    std::tstreambuf_t *buff = a_os.rdbuf();

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

    a_os << value;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline int_t
StdStream::_floatPrecisionMax()
{
#if xLANG_CPP11
    return std::numeric_limits<T>::max_digits10;
#else
    return std::numeric_limits<T>::digits10 + 1;
#endif
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
inline std::tstring_t
StdStream::_formatUnprintableChar(
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
