/**
 * \file  CxCookiePv1.cpp
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#include <xLib/Net/CxCookiePv1.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxEnvironment.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCookiePv1
CxCookiePv1::CxCookiePv1() :
    _m_sName    (),
    _m_sValue   (),
    _m_sComment (),
    _m_sDomain  (),
    _m_sPath    (),
    _m_liMaxAge (- 1),
    _m_bSecure  (FALSE),
    _m_bHttpOnly(FALSE)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = bInit(std::tstring());
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: CxCookiePv1
CxCookiePv1::CxCookiePv1(
    const std::tstring &csRawCookie
) :
    _m_sName    (),
    _m_sValue   (),
    _m_sComment (),
    _m_sDomain  (),
    _m_sPath    (),
    _m_liMaxAge (- 1),
    _m_bSecure  (FALSE),
    _m_bHttpOnly(FALSE)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = bInit(csRawCookie);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxCookiePv1
/*virtual*/
CxCookiePv1::~CxCookiePv1() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
//DONE: sGetName ()
const std::tstring &
CxCookiePv1::sGetName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
//DONE: bSetName ()
BOOL
CxCookiePv1::bSetName(
    const std::tstring &csName
)
{
    /*DEBUG*/

    _m_sName = csName;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetValue ()
const std::tstring &
CxCookiePv1::sGetValue() const {
    /*DEBUG*/

    return _m_sValue;
}
//---------------------------------------------------------------------------
//DONE: bSetValue ()
BOOL
CxCookiePv1::bSetValue(
    const std::tstring &csValue
)
{
    /*DEBUG*/

    _m_sValue = csValue;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetComment ()
const std::tstring &
CxCookiePv1::sGetComment() const {
    /*DEBUG*/

    return _m_sComment;
}
//---------------------------------------------------------------------------
//DONE: bSetComment ()
BOOL
CxCookiePv1::bSetComment(
    const std::tstring &csComment
)
{
    /*DEBUG*/

    _m_sComment = csComment;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetDomain ()
const std::tstring &
CxCookiePv1::sGetDomain() const {
    /*DEBUG*/

    return _m_sDomain;
}
//---------------------------------------------------------------------------
//DONE: bSetDomain ()
BOOL
CxCookiePv1::bSetDomain(
    const std::tstring &csDomain
)
{
    /*DEBUG*/

    _m_sDomain = csDomain;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetPath ()
const std::tstring &
CxCookiePv1::sGetPath() const {
    /*DEBUG*/

    return _m_sPath;
}
//---------------------------------------------------------------------------
//DONE: bSetPath ()
BOOL
CxCookiePv1::bSetPath(
    const std::tstring &csPath
)
{
    /*DEBUG*/

    _m_sPath = csPath;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: liGetMaxAge ()
LONGLONG
CxCookiePv1::liGetMaxAge() const {
    /*DEBUG*/

    return _m_liMaxAge;
}
//---------------------------------------------------------------------------
//DONE: bSetMaxAge ()
BOOL
CxCookiePv1::bSetMaxAge(
    LONGLONG liMaxAge
)
{
    /*DEBUG*/

    _m_liMaxAge = liMaxAge;

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
CxCookiePv1::bSetSecure(
    BOOL bFlag
)
{
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
CxCookiePv1::bSetHttpOnly(
    BOOL bFlag
)
{
    /*DEBUG*/

    _m_bHttpOnly = bFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sToString ()
std::tstring
CxCookiePv1::sToString() const {
    /*DEBUG*/

    std::tstring sRes;

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

    if (_m_liMaxAge >= 0) {
        sRes.append("; Max-Age=\"");
        sRes.append( CxString::lexical_cast(_m_liMaxAge) );
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
    _m_liMaxAge  = - 1;
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
    operator() (const std::tstring &csStr1, const std::tstring &csStr2) const {
        return !! CxString::bCompareNoCase(csStr1, csStr2);
    }
};
//---------------------------------------------------------------------------
//DONE: bInit (parsing raw cookie string pv0)
BOOL
CxCookiePv1::bInit(
    const std::tstring &csRawCookie
)
{
    /*DEBUG*/// _m_msCookie - n/a
    /*DEBUG*/// csRawCookie - n/a

    typedef std::map<std::tstring, std::tstring/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<std::tstring, std::tstring>                TStringPair;


    BOOL       bRes = FALSE;
    TStringMap msCookie;
    std::tstring    sCookie;

    sCookie.assign( csRawCookie );
    sCookie.assign( CxString::sRemoveAll(sCookie, CxConst::xSQM) );
    sCookie.assign( CxString::sRemoveAll(sCookie, CxConst::xDQM) );

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vector<std::tstring> vsPairs;

    bRes = CxString::bSplit(sCookie, CxConst::xSEMICOLON, &vsPairs);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    for (size_t i = 0; i < vsPairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vector<std::tstring> vsTemp;

        bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsTemp);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        std::tstring sCookieName  = CxString::sTrimSpace(vsTemp.at(0));
        std::tstring sCookieValue = ( (1 == vsTemp.size()) ? std::tstring() : vsTemp.at(1) );

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
    _m_liMaxAge  = CxString::lexical_cast<LONGLONG>( msCookie[xT("Max-Age")] );
    _m_bSecure   = xAS_BOOL( msCookie.end() != msCookie.find(xT("Secure")) );
    _m_bHttpOnly = xAS_BOOL( msCookie.end() != msCookie.find(xT("HttpOnly")) );

    return TRUE;
}
//---------------------------------------------------------------------------
