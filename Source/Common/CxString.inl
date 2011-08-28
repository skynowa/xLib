/**
 * \file  CxString.inl
 * \brief string utils
 */


/****************************************************************************
*	overload operator << for std::basic_ostream
*
*****************************************************************************/

namespace std {

//---------------------------------------------------------------------------
//DONE: operator << for std::ustring
template<class Traits>
inline basic_ostream<TCHAR, Traits> &
operator << (
    basic_ostream<TCHAR, Traits> &osOut,
    const std::ustring           &cusValue
)
{
    std::tstring sRes;

    sRes.assign( cusValue.begin(), cusValue.end() );

    osOut << sRes.data() << std::flush;

    return osOut;
}
//---------------------------------------------------------------------------
//DONE: operator << for std::vector
template<class Traits, class T>
inline basic_ostream<TCHAR, Traits> &
operator << (
    basic_ostream<TCHAR, Traits> &osOut,
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
inline basic_ostream<TCHAR, Traits> &
operator << (
    basic_ostream<TCHAR, Traits> &osOut,
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
inline basic_ostream<TCHAR, Traits> &
operator << (
    basic_ostream<TCHAR, Traits> &osOut,
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

} //namespace std


/****************************************************************************
*   lexical_cast
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<class T>
/*static*/
inline std::tstring
CxString::lexical_cast(
    const T &cValueT
)
{
    //cValueT - n/a

    std::tstring sRes;

    try {
        std::tostringstream ossRes;

        ossRes.exceptions(std::tostringstream::failbit | std::tostringstream::badbit);
        ossRes << cValueT;

        sRes.assign(ossRes.str());
    } catch (std::tostringstream::failure &e) {
        sRes.clear();
    } catch (...) {
        sRes.clear();
    }

    return sRes;
}
//---------------------------------------------------------------------------
template<class T>
/*static*/
inline std::tstring
CxString::lexical_cast(
    const T   &cValueT,
    const INT  ciBase
)
{
    //cValueT - n/a
    //ciBase  - n/a

    std::tstring sRes;

    try {
        std::tostringstream ossRes;

        ossRes.exceptions(std::tostringstream::failbit | std::tostringstream::badbit);
        ossRes << std::setbase(ciBase) << std::uppercase << cValueT;  //std::showbase

        sRes.assign(ossRes.str());
    } catch (std::tostringstream::failure &e) {
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
    const std::tstring &csStr
)
{
    //csStr - n/a

    T ResT;

    try {
        std::tistringstream issStream(csStr);

        issStream.exceptions(std::tistringstream::failbit | std::tistringstream::badbit);
        issStream >> ResT;
    } catch (std::tistringstream::failure &e) {
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
    const std::tstring &csStr,
    const INT           ciBase
)
{
    //csStr  - n/a
    //ciBase - n/a

    T ResT;

    try {
        std::tistringstream issStream(csStr);

        issStream.exceptions(std::tistringstream::failbit | std::tistringstream::badbit);
        issStream >> std::setbase(ciBase) >> ResT;
    } catch (std::tistringstream::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//---------------------------------------------------------------------------
