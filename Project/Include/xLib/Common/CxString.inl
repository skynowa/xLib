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
template<class Traits>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &osOut,
    const std::ustring_t           &cusValue
)
{
    std::tstring_t sRv;

    sRv.assign( cusValue.begin(), cusValue.end() );

    osOut << sRv << std::flush;

    return osOut;
}
//---------------------------------------------------------------------------
template<class Traits, class T>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &osOut,
    const vector<T>                &cvValueT
)
{
    osOut << std::endl;
    osOut << xT("std::vector (") << cvValueT.size() << (" elements):") << std::endl;
    osOut << std::endl;

    typename vector<T>::const_iterator it;
    size_t                             i = 0;
    for (it = cvValueT.begin(), i = 0; it != cvValueT.end(); ++ it, ++ i) {
        osOut << xT("Value[") << i << xT("]: ") << (*it) << std::endl;
    }

    osOut << std::endl;
    osOut << std::endl;

    return osOut;
}
//---------------------------------------------------------------------------
template<class Traits, class T1, class T2>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &osOut,
    const map<T1, T2>              &cmValueT
)
{
    osOut << std::endl;
    osOut << xT("std::map (") << cmValueT.size() << (" elements):") << std::endl;
    osOut << std::endl;

    typename map<T1, T2>::const_iterator it;
    for (it = cmValueT.begin(); it != cmValueT.end(); ++ it) {
        osOut << xT("Key: ")   << (*it).first  << xT("\t\t")
              << xT("Value: ") << (*it).second << std::endl;
    }

    osOut << std::endl;
    osOut << std::endl;

    return osOut;
}
//---------------------------------------------------------------------------
template<class Traits, class T1, class T2>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &osOut,
    const multimap<T1, T2>         &cmmValueT
)
{
    osOut << std::endl;
    osOut << xT("std::multimap (") << cmmValueT.size() << (" elements):") << std::endl;
    osOut << std::endl;

    typename multimap<T1, T2>::const_iterator it;
    for (it = cmmValueT.begin(); it != cmmValueT.end(); ++ it) {
        osOut << xT("Key: ")   << (*it).first  << xT("\t\t")
              << xT("Value: ") << (*it).second << std::endl;
    }

    osOut << std::endl;
    osOut << std::endl;

    return osOut;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(std)


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   string_cast
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
CxString::string_cast(
    const T &cValueT
)
{
    //cValueT - n/a

    std::tstring_t sRv;

    try {
        std::tostringstream_t ossRes;

        ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        ossRes << cValueT;

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
template<class T>
inline std::tstring_t
CxString::string_cast(
    const T   &cValueT,
    const int  ciBase
)
{
    //cValueT - n/a
    //ciBase  - n/a

    std::tstring_t sRv;

    try {
        std::tostringstream_t ossRes;

        ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        ossRes << std::setbase(ciBase) << std::uppercase << cValueT;  //std::showbase

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
template<class T>
inline T
CxString::string_cast(
    const std::tstring_t &csStr
)
{
    //csStr - n/a

    T ResT;

    try {
        std::tistringstream_t issStream(csStr);

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
template<class T>
inline T
CxString::string_cast(
    const std::tstring_t &csStr,
    const int           ciBase
)
{
    //csStr  - n/a
    //ciBase - n/a

    T ResT;

    try {
        std::tistringstream_t issStream(csStr);

        issStream.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        issStream >> std::setbase(ciBase) >> ResT;
    } catch (const std::tistringstream_t::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
