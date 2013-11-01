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
template<class Traits, class T>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_os,
    const vector<T>                &a_value
)
{
    xTEST_NA(a_os);
    xTEST_NA(a_value);

    a_os << std::endl;
    a_os << xT("std::vector (") << a_value.size() << (" elements):") << std::endl;
    a_os << std::endl;

    typename vector<T>::const_iterator it;
    size_t                             i = 0;
    for (it = a_value.begin(), i = 0; it != a_value.end(); ++ it, ++ i) {
        a_os << xT("Value[") << i << xT("]: ") << (*it) << std::endl;
    }

    a_os << std::endl;
    a_os << std::endl;

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
    xTEST_NA(a_os);
    xTEST_NA(a_value);

    a_os << std::endl;
    a_os << xT("std::map (") << a_value.size() << (" elements):") << std::endl;
    a_os << std::endl;

    typename map<T1, T2>::const_iterator it;
    for (it = a_value.begin(); it != a_value.end(); ++ it) {
        a_os << xT("Key: ")   << (*it).first  << xT("\t\t")
                << xT("Value: ") << (*it).second << std::endl;
    }

    a_os << std::endl;
    a_os << std::endl;

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
        a_os << xT("Key: ")   << (*it).first  << xT("\t\t")
                << xT("Value: ") << (*it).second << std::endl;
    }

    a_os << std::endl;
    a_os << std::endl;

    return a_os;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(std)


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   casting
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
CxString::cast(
    const T &a_value
)
{
    xTEST_NA(a_value);

    std::tstring_t sRv;

    try {
        std::tostringstream_t ossRes;

        ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        ossRes << a_value;

        sRv = ossRes.str();
    } catch (std::ctostringstream_t::failure &e) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
CxString::cast(
    const T &a_value,
    cint_t  &a_base
)
{
    xTEST_NA(a_value);
    xTEST_NA(a_base);

    std::tstring_t sRv;

    try {
        std::tostringstream_t ossRes;

        ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        ossRes << std::setbase(a_base) << std::uppercase << a_value;  // std::showbase

        sRv = ossRes.str();
    } catch (std::ctostringstream_t::failure &e) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
template<class T>
inline T
CxString::cast(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    T ResT;

    try {
        std::tistringstream_t issStream(a_str);

        issStream.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        issStream >> ResT;
    } catch (std::ctistringstream_t::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//------------------------------------------------------------------------------
/* static */
template<class T>
inline T
CxString::cast(
    std::ctstring_t &a_str,
    cint_t          &a_base
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_base);

    T ResT;

    try {
        std::tistringstream_t issStream(a_str);

        issStream.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        issStream >> std::setbase(a_base) >> ResT;
    } catch (std::ctistringstream_t::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

struct SNarrow {
    std::string::value_type
    operator () (
        const std::wstring::value_type &a_char
    )
    {
        return std::use_facet< std::ctype<std::wstring::value_type> >( std::locale() )
                    .narrow(a_char, '@');
    }
};

xNAMESPACE_ANONYM_END

/* static */
inline std::string
CxString::castA(
    std::cwstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::string asRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(asRv), SNarrow());

    return asRv;
}
//------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

struct SWiden {
    std::wstring::value_type
    operator () (
        const std::string::value_type &a_char
    )
    {
        return std::use_facet< std::ctype<std::string::value_type> >( std::locale() )
                    .widen(a_char);
    }
};

xNAMESPACE_ANONYM_END

/* static */
inline std::wstring
CxString::castW(
    std::cstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::wstring wsRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(wsRv), SWiden());

    return wsRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
