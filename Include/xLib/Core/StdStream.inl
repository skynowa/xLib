/**
 * \file  StdStream.inl
 * \brief overload operators << for std::std::basic_ostream
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   Sequence containers
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class Traits, class T1, class T2>
xINLINE std::basic_ostream<tchar_t, Traits> &
operator << (
    std::basic_ostream<tchar_t, Traits> &a_os,
    const std::pair<T1, T2>             &a_value
)
{
    a_os << xT("std::pair: (") << a_value.first << xT(",") << a_value.second << ")";

    return a_os;
}
//-------------------------------------------------------------------------------------------------
template<class Traits, class T>
xINLINE std::basic_ostream<tchar_t, Traits> &
operator << (
    std::basic_ostream<tchar_t, Traits> &a_os,
    const std::vector<T>                &a_value
)
{
    a_os << xT("std::vector (") << a_value.size() << xT(" elements)");

    if (a_value.empty())  {
        return a_os;
    }

    a_os << xT(":") << std::endl;

    typename std::vector<T>::const_iterator it;
    for (it = a_value.begin(); it != a_value.end(); ++ it) {
        a_os << xT("    value[") << std::distance(a_value.begin(), it) << xT("]: ") << *it;

        if (it + 1 != a_value.end()) {
             a_os << std::endl;
        }
    }

    return a_os;
}
//-------------------------------------------------------------------------------------------------
template<class Traits, class T>
xINLINE std::basic_ostream<tchar_t, Traits> &
operator << (
    std::basic_ostream<tchar_t, Traits> &a_os,
    const std::list<T>                  &a_value
)
{
    a_os << xT("std::list (") << a_value.size() << xT(" elements)");

    if (a_value.empty()) {
        return a_os;
    }

    a_os << xT(":") << std::endl;

    typename std::list<T>::const_iterator it;
    for (it = a_value.begin(); it != a_value.end(); ++ it) {
        a_os << xT("    value[") << std::distance(a_value.begin(), it) << xT("]: ") << *it;

        if (++ it != a_value.end()) {
             a_os << std::endl;
        }

        -- it;
    }

    return a_os;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Container adaptors
*
**************************************************************************************************/


/**************************************************************************************************
*   Associative containers
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class Traits, class T1, class T2>
xINLINE std::basic_ostream<tchar_t, Traits> &
operator << (
    std::basic_ostream<tchar_t, Traits> &a_os,
    const std::map<T1, T2>              &a_value
)
{
    a_os << xT("std::map (") << a_value.size() << xT(" elements)");

    if (a_value.empty()) {
        return a_os;
    }

    a_os << xT(":") << std::endl;

    typename std::map<T1, T2>::const_iterator it;
    for (it = a_value.begin(); it != a_value.end(); ++ it) {
        a_os << xT("    key: ") << it->first  << xT("\t")
             << xT("value: ")   << it->second;

        if (++ it != a_value.end()) {
             a_os << std::endl;
        }

        -- it;
    }

    return a_os;
}
//-------------------------------------------------------------------------------------------------
template<class Traits, class T1, class T2>
xINLINE std::basic_ostream<tchar_t, Traits> &
operator << (
    std::basic_ostream<tchar_t, Traits> &a_os,
    const std::multimap<T1, T2>         &a_value
)
{
    a_os << std::endl;
    a_os << xT("std::multimap (") << a_value.size() << xT(" elements):") << std::endl;
    a_os << std::endl;

    typename std::multimap<T1, T2>::const_iterator it;
    for (it = a_value.begin(); it != a_value.end(); ++ it) {
        a_os << xT("    key: ") << it->first  << xT("\t")
             << xT("value: ")   << it->second;

        if (++ it != a_value.end()) {
             a_os << std::endl;
        }

        -- it;
    }

    return a_os;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Unordered associative containers
*
**************************************************************************************************/


/**************************************************************************************************
*   Etc
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class Traits>
xINLINE std::basic_ostream<tchar_t, Traits> &
operator << (
    std::basic_ostream<tchar_t, Traits> &a_os,
    std::custring_t                     &a_value
)
{
    std::tstring_t sRv;

    sRv.assign( a_value.begin(), a_value.end() );

    a_os << sRv << std::flush;

    return a_os;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
