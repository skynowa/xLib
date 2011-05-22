/****************************************************************************
* Class name:  CxString
* Description: strings
* File name:   CxString.inl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     17.05.2011
*
*****************************************************************************/


//---------------------------------------------------------------------------
//type -> tString
template<class T>
/*static*/
tString
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
tString
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
T
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
T
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
