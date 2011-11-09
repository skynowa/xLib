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

    bRes = bInit(std::string_t());
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
CxCookiePv1::CxCookiePv1(
    const std::string_t &csRawCookie
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
/*virtual*/
CxCookiePv1::~CxCookiePv1() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv1::sGetName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv1::bSetName(
    const std::string_t &csName
)
{
    /*DEBUG*/

    _m_sName = csName;

    return TRUE;
}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv1::sGetValue() const {
    /*DEBUG*/

    return _m_sValue;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv1::bSetValue(
    const std::string_t &csValue
)
{
    /*DEBUG*/

    _m_sValue = csValue;

    return TRUE;
}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv1::sGetComment() const {
    /*DEBUG*/

    return _m_sComment;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv1::bSetComment(
    const std::string_t &csComment
)
{
    /*DEBUG*/

    _m_sComment = csComment;

    return TRUE;
}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv1::sGetDomain() const {
    /*DEBUG*/

    return _m_sDomain;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv1::bSetDomain(
    const std::string_t &csDomain
)
{
    /*DEBUG*/

    _m_sDomain = csDomain;

    return TRUE;
}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv1::sGetPath() const {
    /*DEBUG*/

    return _m_sPath;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv1::bSetPath(
    const std::string_t &csPath
)
{
    /*DEBUG*/

    _m_sPath = csPath;

    return TRUE;
}
//---------------------------------------------------------------------------
LONGLONG
CxCookiePv1::liGetMaxAge() const {
    /*DEBUG*/

    return _m_liMaxAge;
}
//---------------------------------------------------------------------------
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
BOOL
CxCookiePv1::bGetSecure() const {
    /*DEBUG*/

    return _m_bSecure;
}
//---------------------------------------------------------------------------
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
BOOL
CxCookiePv1::bGetHttpOnly() const {
    /*DEBUG*/

    return _m_bHttpOnly;
}
//---------------------------------------------------------------------------
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
std::string_t
CxCookiePv1::sToString() const {
    /*DEBUG*/

    std::string_t sRes;

    sRes.append(_m_sName);
    sRes.append(xT("="));

    sRes.append(xT("\""));
    sRes.append(_m_sValue);
    sRes.append(xT("\""));

    if (false == _m_sComment.empty()) {
        sRes.append(xT("; Comment=\""));
        sRes.append(_m_sComment);
        sRes.append(xT("\""));
    }

    if (false == _m_sDomain.empty()) {
        sRes.append(xT("; Domain=\""));
        sRes.append(_m_sDomain);
        sRes.append(xT("\""));
    }

    if (false == _m_sPath.empty()) {
        sRes.append(xT("; Path=\""));
        sRes.append(_m_sPath);
        sRes.append(xT("\""));
    }

    if (_m_liMaxAge >= 0) {
        sRes.append(xT("; Max-Age=\""));
        sRes.append( CxString::lexical_cast(_m_liMaxAge) );
        sRes.append(xT("\""));
    }

    if (TRUE == _m_bSecure) {
        sRes.append(xT("; Secure"));
    }

    if (TRUE == _m_bHttpOnly) {
        sRes.append(xT("; HttpOnly"));
    }

    sRes.append(xT("; Version=\"1\""));

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: sGetDump
std::string_t
CxCookiePv1::sGetDump() const {
    std::string_t sRes;

    xNOT_IMPLEMENTED_RET(std::string_t());

    return sRes;
}
//---------------------------------------------------------------------------
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
struct SCompareNoCase {
    bool
    operator() (const std::string_t &csStr1, const std::string_t &csStr2) const {
        return !! CxString::bCompareNoCase(csStr1, csStr2);
    }
};
//---------------------------------------------------------------------------
BOOL
CxCookiePv1::bInit(
    const std::string_t &csRawCookie
)
{
    /*DEBUG*/// _m_msCookie - n/a
    /*DEBUG*/// csRawCookie - n/a

    typedef std::map<std::string_t, std::string_t/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<std::string_t, std::string_t>                TStringPair;


    BOOL         bRes = FALSE;
    TStringMap   msCookie;
    std::string_t sCookie;

    sCookie.assign( csRawCookie );
    sCookie.assign( CxString::sRemoveAll(sCookie, CxConst::xSQM) );
    sCookie.assign( CxString::sRemoveAll(sCookie, CxConst::xDQM) );

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vector<std::string_t> vsPairs;

    bRes = CxString::bSplit(sCookie, CxConst::xSEMICOLON, &vsPairs);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    for (size_t i = 0; i < vsPairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vector<std::string_t> vsTemp;

        bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsTemp);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        std::string_t sCookieName  = CxString::sTrimSpace(vsTemp.at(0));
        std::string_t sCookieValue = ( (1 == vsTemp.size()) ? std::string_t() : vsTemp.at(1) );

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
