/****************************************************************************
* Class name:  CxString
* Description: strings
* File name:   CxString.inl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     17.05.2011
*
*****************************************************************************/


/****************************************************************************
*	overload operator << for std::basic_ostream
*
*****************************************************************************/

namespace std {

//---------------------------------------------------------------------------
//DONE: operator << for uString
template<class Traits>
inline basic_ostream<TCHAR, Traits> &
operator << (
    basic_ostream<TCHAR, Traits> &osOut,
    const uString                &cusValue
)
{
    tString sRes;

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
    osOut << tendl;
    osOut << xT("std::vector (") << cvValueT.size() << (" elements):") << tendl;
    osOut << tendl;

    typename vector<T>::const_iterator it;
    size_t                             i = 0;
    for (it = cvValueT.begin(), i = 0; it != cvValueT.end(); ++ it, ++ i) {
        osOut << xT("Value[") << i << xT("]: ") << (*it) << tendl;
    }

    osOut << tendl;
    osOut << tendl;

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
    osOut << tendl;
    osOut << xT("std::map (") << cmValueT.size() << (" elements):") << tendl;
    osOut << tendl;

    typename map<T1, T2>::const_iterator it;
    for (it = cmValueT.begin(); it != cmValueT.end(); ++ it) {
        osOut << xT("Key: ")   << (*it).first  << xT("\t\t")
              << xT("Value: ") << (*it).second << tendl;
    }

    osOut << tendl;
    osOut << tendl;

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
    osOut << tendl;
    osOut << xT("std::multimap (") << cmmValueT.size() << (" elements):") << tendl;
    osOut << tendl;

    typename multimap<T1, T2>::const_iterator it;
    for (it = cmmValueT.begin(); it != cmmValueT.end(); ++ it) {
        osOut << xT("Key: ")   << (*it).first  << xT("\t\t")
              << xT("Value: ") << (*it).second << tendl;
    }

    osOut << tendl;
    osOut << tendl;

    return osOut;
}
//---------------------------------------------------------------------------

} //namespace std


/****************************************************************************
*   lexical_cast
*
*****************************************************************************/

//---------------------------------------------------------------------------
//type -> tString
template<class T>
/*static*/
inline tString
CxString::lexical_cast(
    const T &cValueT
)
{
    //cValueT - n/a

    tString sRes;

    try {
        tostringstream ossRes;

        ossRes.exceptions(tostringstream::failbit | tostringstream::badbit);
        ossRes << cValueT;

        sRes.assign(ossRes.str());
    } catch (tostringstream::failure &e) {
        sRes.clear();
    } catch (...) {
        sRes.clear();
    }

    return sRes;
}
//---------------------------------------------------------------------------
//type -> tString by base
template<class T>
/*static*/
inline tString
CxString::lexical_cast(
    const T   &cValueT,
    const INT  ciBase
)
{
    //cValueT - n/a
    //ciBase  - n/a

    tString sRes;

    try {
        tostringstream ossRes;

        ossRes.exceptions(tostringstream::failbit | tostringstream::badbit);
        ossRes << std::setbase(ciBase) << std::uppercase << cValueT;  //std::showbase

        sRes.assign(ossRes.str());
    } catch (tostringstream::failure &e) {
        sRes.clear();
    } catch (...) {
        sRes.clear();
    }

    return sRes;
}
//---------------------------------------------------------------------------
//tString -> type
template<class T>
/*static*/
inline T
CxString::lexical_cast(
    const tString &csStr
)
{
    //csStr - n/a

    T ResT;

    try {
        tistringstream issStream(csStr);

        issStream.exceptions(tistringstream::failbit | tistringstream::badbit);
        issStream >> ResT;
    } catch (tistringstream::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//---------------------------------------------------------------------------
//tString by base (8, 10, 16) -> type
template<class T>
/*static*/
inline T
CxString::lexical_cast(
    const tString &csStr,
    const INT      ciBase
)
{
    //csStr  - n/a
    //ciBase - n/a

    T ResT;

    try {
        tistringstream issStream(csStr);

        issStream.exceptions(tistringstream::failbit | tistringstream::badbit);
        issStream >> std::setbase(ciBase) >> ResT;
    } catch (tistringstream::failure &e) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//---------------------------------------------------------------------------
