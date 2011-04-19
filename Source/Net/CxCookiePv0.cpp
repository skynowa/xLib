/****************************************************************************
* Class name:  CxCookiePv0
* Description: cookie (http://www.ietf.org/rfc/rfc2109.txt)
* File name:   CxCookiePv0.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     26.01.2011 0:04:44
*
*****************************************************************************/


#include <xLib/Net/CxCookiePv0.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxEnvironment.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCookiePv0 (constructor)
CxCookiePv0::CxCookiePv0() :
    _m_sName    (),
    _m_sValue   (),
    _m_sDomain  (),
    _m_sPath    (),
    _m_sExpires (),
    _m_bSecure  (FALSE),
    _m_bHttpOnly(FALSE)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = bInit(tString());
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: CxCookiePv0 (constructor)
CxCookiePv0::CxCookiePv0(const tString &csRawCookie) :
    _m_sName    (),
    _m_sValue   (),
    _m_sDomain  (),
    _m_sPath    (),
    _m_sExpires (),
    _m_bSecure  (FALSE),
    _m_bHttpOnly(FALSE)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = bInit(csRawCookie);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxCookiePv0 (destructor)
/*virtual*/
CxCookiePv0::~CxCookiePv0() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
//DONE: sGetName ()
const tString &
CxCookiePv0::sGetName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
//DONE: bSetName ()
BOOL
CxCookiePv0::bSetName(const tString &csName) {
    /*DEBUG*/

    _m_sName = csName;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetValue ()
const tString &
CxCookiePv0::sGetValue() const {
    /*DEBUG*/

    return _m_sValue;
}
//---------------------------------------------------------------------------
//DONE: bSetValue ()
BOOL
CxCookiePv0::bSetValue(const tString &csValue) {
    /*DEBUG*/

    _m_sValue = csValue;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetDomain ()
const tString &
CxCookiePv0::sGetDomain() const {
    /*DEBUG*/

    return _m_sDomain;
}
//---------------------------------------------------------------------------
//DONE: bSetDomain ()
BOOL
CxCookiePv0::bSetDomain(const tString &csDomain) {
    /*DEBUG*/

    _m_sDomain = csDomain;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetPath ()
const tString &
CxCookiePv0::sGetPath() const {
    /*DEBUG*/

    return _m_sPath;
}
//---------------------------------------------------------------------------
//DONE: bSetPath ()
BOOL
CxCookiePv0::bSetPath(const tString &csPath) {
    /*DEBUG*/

    _m_sPath = csPath;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetExpires ()
const tString &
CxCookiePv0::sGetExpires() const {
    /*DEBUG*/

    return _m_sExpires;
}
//---------------------------------------------------------------------------
//DONE: bSetExpires ()
BOOL
CxCookiePv0::bSetExpires(const tString &csExpires) {
    /*DEBUG*/

    _m_sExpires = csExpires;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetSecure ()
BOOL
CxCookiePv0::bGetSecure() const {
    /*DEBUG*/

    return _m_bSecure;
}
//---------------------------------------------------------------------------
//DONE: bSetSecure ()
BOOL
CxCookiePv0::bSetSecure(BOOL bFlag) {
    /*DEBUG*/

    _m_bSecure = bFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetHttpOnly ()
BOOL
CxCookiePv0::bGetHttpOnly() const {
    /*DEBUG*/

    return _m_bHttpOnly;
}
//---------------------------------------------------------------------------
//DONE: bSetHttpOnly ()
BOOL
CxCookiePv0::bSetHttpOnly(BOOL bFlag) {
    /*DEBUG*/

    _m_bHttpOnly = bFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sToString ()
tString
CxCookiePv0::sToString() const {
    /*DEBUG*/

    tString sRes;

    //name
    sRes.append(_m_sName);
    sRes.append(xT("="));
    sRes.append(_m_sValue);

    //domain
    if (false == _m_sDomain.empty()) {
        sRes.append(xT("; Domain="));
        sRes.append(_m_sDomain);
    }

    //path
    if (false == _m_sPath.empty()) {
        sRes.append(xT("; Path="));
        sRes.append(_m_sPath);
    }

    //expires
    if (false == _m_sExpires.empty()) {
        //[Wdy, DD-Mon-YYYY HH:MM:SS GMT]
        sRes.append(xT("; Expires="));
        sRes.append(_m_sExpires);
    }

    //secure
    if (TRUE == _m_bSecure) {
        sRes.append(xT("; Secure"));
    }

    //HttpOmly
    if (TRUE == _m_bHttpOnly) {
        sRes.append(xT("; HttpOnly"));
    }

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: sGetDump ()
//TODO: TEST
tString
CxCookiePv0::sGetDump() const {
    /*DEBUG*/

    tString sRes;

    sRes = CxString::sFormat(
            xT("[CxCookiePv0 dump]\n\n"
            "Name: %s\n"
            "Value: %s\n"
            "Domain: %s\n"
            "Path: %s\n"
            "Expires: %s\n"
            "Secure: %s\n"
            "HttpOnly: %s\n\n"),
            sGetName().c_str(),
            sGetValue().c_str(),
            sGetDomain().c_str(),
            sGetPath().c_str(),
            sGetExpires().c_str(),
            CxString::sBoolToStr(bGetSecure()).c_str(),
            CxString::sBoolToStr(bGetHttpOnly()).c_str()
    );

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bClear ()
BOOL
CxCookiePv0::bClear() {
    /*DEBUG*/

    _m_sName.clear();
    _m_sValue.clear();
    _m_sDomain.clear();
    _m_sPath.clear();
    _m_sExpires.clear();
    _m_bSecure   = FALSE;
    _m_bHttpOnly = FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: SCompareNoCase
struct SCompareNoCase {
    bool
    operator() (const tString &csStr1, const tString &csStr2) const {
        return !! CxString::bCompareNoCase(csStr1, csStr2);
    }
};
//---------------------------------------------------------------------------
//DONE: bInit (parsing raw cookie string)
BOOL
CxCookiePv0::bInit(const tString &csRawCookie) {
    /*DEBUG*/// _m_msCookie - n/a
    /*DEBUG*/// csRawCookie - n/a

    typedef std::map<tString, tString/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<tString, tString>                TStringPair;


    BOOL       bRes = FALSE;
    TStringMap msCookie;
    tString    sCookie;

    sCookie.assign( csRawCookie );
    sCookie.assign( CxString::sRemoveAll(sCookie, CxConst::xSQM) );
    sCookie.assign( CxString::sRemoveAll(sCookie, CxConst::xDQM) );

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vector<tString> vecsPairs;

    bRes = CxString::bSplit(sCookie, CxConst::xSEMICOLON, &vecsPairs);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    for (size_t i = 0; i < vecsPairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vector<tString> vecsTemp;

        bRes = CxString::bSplit(vecsPairs.at(i), CxConst::xEQUAL, &vecsTemp);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        tString sCookieName  = CxString::sTrimSpace(vecsTemp.at(0));
        tString sCookieValue = ( (1 == vecsTemp.size()) ? tString() : vecsTemp.at(1) );

        if (0 == i) {
            //1-st pair is "Name=Value"
            msCookie.insert( TStringPair(xT("Name"),  sCookieName) );
            msCookie.insert( TStringPair(xT("Value"), sCookieValue) );
        } else {
            msCookie.insert( TStringPair(sCookieName, sCookieValue) );
        }
    }

    //set results
    _m_sName     = msCookie[xT("Name")];
    _m_sValue    = msCookie[xT("Value")];
    _m_sDomain   = msCookie[xT("Domain")];
    _m_sPath     = msCookie[xT("Path")];
    _m_sExpires  = msCookie[xT("Expires")];
    _m_bSecure   = xTO_BOOL( msCookie.end() != msCookie.find(xT("Secure")) );
    _m_bHttpOnly = xTO_BOOL( msCookie.end() != msCookie.find(xT("HttpOnly")) );

    return TRUE;
}
//---------------------------------------------------------------------------
