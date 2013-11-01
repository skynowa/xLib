/**
 * \file  xStdStream.inl
 * \brief overload operators << for std::basic_ostream
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTracer.h>


/*******************************************************************************
*    overload operator << for std::basic_ostream
*
*******************************************************************************/

xNAMESPACE_BEGIN(std)

//------------------------------------------------------------------------------
template<class Traits>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_os,
    std::custring_t                &a_value
)
{
    xTEST_NA(a_os);
    xTEST_NA(a_value);

    std::tstring_t sRv;

    sRv.assign( a_value.begin(), a_value.end() );

    a_os << sRv << std::flush;

    return a_os;
}
//------------------------------------------------------------------------------
/**
 * overload operators << for std::vector
 */
template<class Traits, class T>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_os,
    const vector<T>                &a_value
)
{
    a_os << "std::vector (" << a_value.size() << " elements)";

    if (a_value.empty())  {
        return a_os;
    }

    a_os << ":" << std::endl;

    typename vector<T>::const_iterator it;
    for (it = a_value.begin(); it != a_value.end(); ++ it) {
        a_os << "    value[" << std::distance(a_value.begin(), it) << "]: " << *it;

        if (it + 1 != a_value.end()) {
             a_os << std::endl;
        }
    }

    return a_os;
}
//------------------------------------------------------------------------------
template<class Traits, class T>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_os,
    const list<T>                  &a_value
)
{
    a_os << "std::list (" << a_value.size() << " elements)";

    if (a_value.empty()) {
        return a_os;
    }

    a_os << ":" << std::endl;

    typename list<T>::const_iterator it;
    for (it = a_value.begin(); it != a_value.end(); ++ it) {
        a_os << "    value[" << std::distance(a_value.begin(), it) << "]: " << *it;

        if (++ it != a_value.end()) {
             a_os << std::endl;
        }
        -- it;
    }

    return a_os;
}
//------------------------------------------------------------------------------
template<class Traits, class T1, class T2>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_os,
    const map<T1, T2>              &a_value
)
{
    a_os << "std::map (" << a_value.size() << " elements)";

    if (a_value.empty()) {
        return a_os;
    }

    a_os << ":" << std::endl;

    typename map<T1, T2>::const_iterator it;
    for (it = a_value.begin(); it != a_value.end(); ++ it) {
        a_os << "    key: " << (*it).first  << "\t"
             << "value: "   << (*it).second;

        if (++ it != a_value.end()) {
             a_os << std::endl;
        }
        -- it;
    }

    return a_os;
}
//------------------------------------------------------------------------------
template<class Traits, class T1, class T2>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_os,
    const multimap<T1, T2>         &a_value
)
{
    xTEST_NA(a_os);
    xTEST_NA(a_value);

    a_os << std::endl;
    a_os << xT("std::multimap (") << a_value.size() << (" elements):") << std::endl;
    a_os << std::endl;

    typename multimap<T1, T2>::const_iterator it;
    for (it = a_value.begin(); it != a_value.end(); ++ it) {
        a_os << "    key: " << (*it).first  << "\t"
             << "value: "   << (*it).second;

        if (++ it != a_value.end()) {
             a_os << std::endl;
        }
        -- it;
    }

    return a_os;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(std)
