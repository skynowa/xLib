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
//DONE: operator << for bool
template<class Traits>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &osOut,
    bool                     cbValue
)
{
    std::tstring_t sRes;

    sRes.assign( CxString::sBoolToStr(cbValue) );

    --osOut << sRes << std::flush;

    return osOut;
}
//---------------------------------------------------------------------------
//DONE: operator << for std::ustring_t
template<class Traits>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &osOut,
    const std::ustring_t           &cusValue
)
{
    std::tstring_t sRes;

    sRes.assign( cusValue.begin(), cusValue.end() );

    osOut << sRes << std::flush;

    return osOut;
}
//---------------------------------------------------------------------------
//DONE: operator << for std::vector
template<class Traits, class T>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &osOut,
    const vector<T>              &cvValueT
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
//DONE: operator << for std::map
template<class Traits, class T1, class T2>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &osOut,
    const map<T1, T2>            &cmValueT
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
//DONE: operator << for std::multimap
template<class Traits, class T1, class T2>
inline basic_ostream<tchar_t, Traits> &
operator << (
    basic_ostream<tchar_t, Traits> &osOut,
    const multimap<T1, T2>       &cmmValueT
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
*   lexical_cast
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<class T>
/*static*/
inline std::tstring_t
CxString::lexical_cast(
    const T &cValueT
)
{
    //cValueT - n/a

    std::tstring_t sRes;

    try {
        std::tostringstream_t ossRes;

        ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        ossRes << cValueT;

        sRes.assign(ossRes.str());
    } catch (std::tostringstream_t::failure &e) {
        sRes.clear();
    } catch (...) {
        sRes.clear();
    }

    return sRes;
}
//---------------------------------------------------------------------------
template<class T>
/*static*/
inline std::tstring_t
CxString::lexical_cast(
    const T   &cValueT,
    const int  ciBase
)
{
    //cValueT - n/a
    //ciBase  - n/a

    std::tstring_t sRes;

    try {
        std::tostringstream_t ossRes;

        ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        ossRes << std::setbase(ciBase) << std::uppercase << cValueT;  //std::showbase

        sRes.assign(ossRes.str());
    } catch (std::tostringstream_t::failure &e) {
        sRes.clear();
    } catch (...) {
        sRes.clear();
    }

    return sRes;
}
//---------------------------------------------------------------------------
template<class T>
/*static*/
inline T
CxString::lexical_cast(
    const std::tstring_t &csStr
)
{
    //csStr - n/a

    T ResT;

    try {
        std::tistringstream_t issStream(csStr);

        issStream.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        issStream >> ResT;
    } catch (std::tistringstream_t::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//---------------------------------------------------------------------------
template<class T>
/*static*/
inline T
CxString::lexical_cast(
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
    } catch (std::tistringstream_t::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
