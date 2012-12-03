/**
 * \file  CxString.inl
 * \brief string utils
 */


/****************************************************************************
*    overload operator << for std::basic_ostream
*
*****************************************************************************/

xNAMESPACE_BEGIN(std)

//---------------------------------------------------------------------------
template<typename Traits>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_osOut,
    const std::ustring_t           &a_cusValue
)
{
    xTEST_NA(a_osOut);
    xTEST_NA(a_cusValue);

    std::tstring_t sRv;

    sRv.assign( a_cusValue.begin(), a_cusValue.end() );

    a_osOut << sRv << std::flush;

    return a_osOut;
}
//---------------------------------------------------------------------------
template<typename Traits, typename T>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_osOut,
    const vector<T>                &a_cvValueT
)
{
    xTEST_NA(a_osOut);
    xTEST_NA(a_cvValueT);

    a_osOut << std::endl;
    a_osOut << xT("std::vector (") << a_cvValueT.size() << (" elements):") << std::endl;
    a_osOut << std::endl;

    typename vector<T>::const_iterator it;
    size_t                             i = 0;
    for (it = a_cvValueT.begin(), i = 0; it != a_cvValueT.end(); ++ it, ++ i) {
        a_osOut << xT("Value[") << i << xT("]: ") << (*it) << std::endl;
    }

    a_osOut << std::endl;
    a_osOut << std::endl;

    return a_osOut;
}
//---------------------------------------------------------------------------
template<typename Traits, typename T1, typename T2>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_osOut,
    const map<T1, T2>              &a_cmValueT
)
{
    xTEST_NA(a_osOut);
    xTEST_NA(a_cmValueT);

    a_osOut << std::endl;
    a_osOut << xT("std::map (") << a_cmValueT.size() << (" elements):") << std::endl;
    a_osOut << std::endl;

    typename map<T1, T2>::const_iterator it;
    for (it = a_cmValueT.begin(); it != a_cmValueT.end(); ++ it) {
        a_osOut << xT("Key: ")   << (*it).first  << xT("\t\t")
                << xT("Value: ") << (*it).second << std::endl;
    }

    a_osOut << std::endl;
    a_osOut << std::endl;

    return a_osOut;
}
//---------------------------------------------------------------------------
template<typename Traits, typename T1, typename T2>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &a_osOut,
    const multimap<T1, T2>         &a_cmmValueT
)
{
    xTEST_NA(a_osOut);
    xTEST_NA(a_cmmValueT);

    a_osOut << std::endl;
    a_osOut << xT("std::multimap (") << a_cmmValueT.size() << (" elements):") << std::endl;
    a_osOut << std::endl;

    typename multimap<T1, T2>::const_iterator it;
    for (it = a_cmmValueT.begin(); it != a_cmmValueT.end(); ++ it) {
        a_osOut << xT("Key: ")   << (*it).first  << xT("\t\t")
                << xT("Value: ") << (*it).second << std::endl;
    }

    a_osOut << std::endl;
    a_osOut << std::endl;

    return a_osOut;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(std)


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   casting
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
template<typename T>
inline std::tstring_t
CxString::cast(
    const T &a_cValueT
)
{
    xTEST_NA(a_cValueT);

    std::tstring_t sRv;

    try {
        std::tostringstream_t ossRes;

        ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        ossRes << a_cValueT;

        sRv = ossRes.str();
    } catch (const std::tostringstream_t::failure &e) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
template<typename T>
inline std::tstring_t
CxString::cast(
    const T   &a_cValueT,
    const int &a_ciBase
)
{
    xTEST_NA(a_cValueT);
    xTEST_NA(a_ciBase);

    std::tstring_t sRv;

    try {
        std::tostringstream_t ossRes;

        ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        ossRes << std::setbase(a_ciBase) << std::uppercase << a_cValueT;  // std::showbase

        sRv = ossRes.str();
    } catch (const std::tostringstream_t::failure &e) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
template<typename T>
inline T
CxString::cast(
    const std::tstring_t &a_csStr
)
{
    xTEST_NA(a_csStr);

    T ResT;

    try {
        std::tistringstream_t issStream(a_csStr);

        issStream.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        issStream >> ResT;
    } catch (const std::tistringstream_t::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//---------------------------------------------------------------------------
/* static */
template<typename T>
inline T
CxString::cast(
    const std::tstring_t &a_csStr,
    const int            &a_ciBase
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_ciBase);

    T ResT;

    try {
        std::tistringstream_t issStream(a_csStr);

        issStream.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        issStream >> std::setbase(a_ciBase) >> ResT;
    } catch (const std::tistringstream_t::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//---------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

struct SNarrow {
    std::string::value_type
    operator () (const std::wstring::value_type &a_cchChar) {
        return std::use_facet< std::ctype<std::wstring::value_type> >( std::locale() ).narrow(a_cchChar, '@');
    }
};

xNAMESPACE_ANONYM_END

/* static */
inline std::string
CxString::castA(
    const std::wstring &a_csStr
)
{
    xTEST_NA(a_csStr);

    std::string asRv;

    std::transform(a_csStr.begin(), a_csStr.end(), std::back_inserter(asRv), SNarrow());

    return asRv;
}
//---------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

struct SWiden {
    std::wstring::value_type
    operator () (const std::string::value_type &a_cchChar) {
        return std::use_facet< std::ctype<std::string::value_type> >( std::locale() ).widen(a_cchChar);
    }
};

xNAMESPACE_ANONYM_END

/* static */
inline std::wstring
CxString::castW(
    const std::string &a_csStr
)
{
    xTEST_NA(a_csStr);

    std::wstring wsRv;

    std::transform(a_csStr.begin(), a_csStr.end(), std::back_inserter(wsRv), SWiden());

    return wsRv;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
