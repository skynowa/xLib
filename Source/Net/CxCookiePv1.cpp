/****************************************************************************
* Class name:  CxCookiePv1
* Description: cookie (http://www.ietf.org/rfc/rfc2109.txt)
* File name:   CxCookiePv1.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     26.01.2011 0:04:44
*
*****************************************************************************/


#include <xLib/Net/CxCookiePv1.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxEnvironment.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCookiePv1 (constructor)
CxCookiePv1::CxCookiePv1() :
    _m_sName    (),
    _m_sValue   (),
    _m_sComment (),
    _m_sDomain  (),
    _m_sPath    (),
    _m_iMaxAge  (- 1),
    _m_bSecure  (FALSE),
    _m_bHttpOnly(FALSE)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = bInit(tString());
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: CxCookiePv1 (constructor)
CxCookiePv1::CxCookiePv1(const tString &csRawCookie) :
    _m_sName    (),
    _m_sValue   (),
    _m_sComment (),
    _m_sDomain  (),
    _m_sPath    (),
    _m_iMaxAge  (- 1),
    _m_bSecure  (FALSE),
    _m_bHttpOnly(FALSE)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = bInit(csRawCookie);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxCookiePv1 (destructor)
/*virtual*/
CxCookiePv1::~CxCookiePv1() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
//DONE: sGetName ()
const tString &
CxCookiePv1::sGetName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
//DONE: bSetName ()
BOOL
CxCookiePv1::bSetName(const tString &csName) {
    /*DEBUG*/

    _m_sName = csName;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetValue ()
const tString &
CxCookiePv1::sGetValue() const {
    /*DEBUG*/

    return _m_sValue;
}
//---------------------------------------------------------------------------
//DONE: bSetValue ()
BOOL
CxCookiePv1::bSetValue(const tString &csValue) {
    /*DEBUG*/

    _m_sValue = csValue;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetComment ()
const tString &
CxCookiePv1::sGetComment() const {
    /*DEBUG*/

    return _m_sComment;
}
//---------------------------------------------------------------------------
//DONE: bSetComment ()
BOOL
CxCookiePv1::bSetComment(const tString &csComment) {
    /*DEBUG*/

    _m_sComment = csComment;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetDomain ()
const tString &
CxCookiePv1::sGetDomain() const {
    /*DEBUG*/

    return _m_sDomain;
}
//---------------------------------------------------------------------------
//DONE: bSetDomain ()
BOOL
CxCookiePv1::bSetDomain(const tString &csDomain) {
    /*DEBUG*/

    _m_sDomain = csDomain;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetPath ()
const tString &
CxCookiePv1::sGetPath() const {
    /*DEBUG*/

    return _m_sPath;
}
//---------------------------------------------------------------------------
//DONE: bSetPath ()
BOOL
CxCookiePv1::bSetPath(const tString &csPath) {
    /*DEBUG*/

    _m_sPath = csPath;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetMaxAge ()
ULONGLONG
CxCookiePv1::iGetMaxAge() const {
    /*DEBUG*/

    return _m_iMaxAge;
}
//---------------------------------------------------------------------------
//DONE: bSetMaxAge ()
BOOL
CxCookiePv1::bSetMaxAge(ULONGLONG iMaxAge) {
    /*DEBUG*/

    _m_iMaxAge = iMaxAge;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetSecure ()
BOOL
CxCookiePv1::bGetSecure() const {
    /*DEBUG*/

    return _m_bSecure;
}
//---------------------------------------------------------------------------
//DONE: bSetSecure ()
BOOL
CxCookiePv1::bSetSecure(BOOL bFlag) {
    /*DEBUG*/

    _m_bSecure = bFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetHttpOnly ()
BOOL
CxCookiePv1::bGetHttpOnly() const {
    /*DEBUG*/

    return _m_bHttpOnly;
}
//---------------------------------------------------------------------------
//DONE: bSetHttpOnly ()
BOOL
CxCookiePv1::bSetHttpOnly(BOOL bFlag) {
    /*DEBUG*/

    _m_bHttpOnly = bFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sToString ()
tString
CxCookiePv1::sToString() const {
    /*DEBUG*/

    tString sRes;

    sRes.append(_m_sName);
    sRes.append("=");

    sRes.append("\"");
    sRes.append(_m_sValue);
    sRes.append("\"");

    if (false == _m_sComment.empty()) {
        sRes.append("; Comment=\"");
        sRes.append(_m_sComment);
        sRes.append("\"");
    }

    if (false == _m_sDomain.empty()) {
        sRes.append("; Domain=\"");
        sRes.append(_m_sDomain);
        sRes.append("\"");
    }

    if (false == _m_sPath.empty()) {
        sRes.append("; Path=\"");
        sRes.append(_m_sPath);
        sRes.append("\"");
    }

    if (_m_iMaxAge >= 0) {
        sRes.append("; Max-Age=\"");
        sRes.append( CxString::lexical_cast(_m_iMaxAge) );
        sRes.append("\"");
    }

    if (TRUE == _m_bSecure) {
        sRes.append("; Secure");
    }

    if (TRUE == _m_bHttpOnly) {
        sRes.append("; HttpOnly");
    }

    sRes.append("; Version=\"1\"");

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bClear ()
BOOL
CxCookiePv1::bClear() {
    /*DEBUG*/

    _m_sName.clear();
    _m_sValue.clear();
    _m_sComment.clear();
    _m_sDomain.clear();
    _m_sPath.clear();
    _m_iMaxAge   = - 1;
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
//DONE: bInit (parsing raw cookie string pv0)
BOOL
CxCookiePv1::bInit(const tString &csRawCookie) {
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
    _m_sComment  = msCookie[xT("Comment")];
    _m_sDomain   = msCookie[xT("Domain")];
    _m_sPath     = msCookie[xT("Path")];
    _m_iMaxAge   = CxString::lexical_cast<INT>( msCookie[xT("Max-Age")] );
    _m_bSecure   = xTO_BOOL( msCookie.end() != msCookie.find(xT("Secure")) );
    _m_bHttpOnly = xTO_BOOL( msCookie.end() != msCookie.find(xT("HttpOnly")) );

    return TRUE;
}
//---------------------------------------------------------------------------
