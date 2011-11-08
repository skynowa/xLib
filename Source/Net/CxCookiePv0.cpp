/**
 * \file  CxCookiePv0.cpp
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#include <xLib/Net/CxCookiePv0.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxEnvironment.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
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

    bRes = bInit(std::string_t());
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
CxCookiePv0::CxCookiePv0(
    const std::string_t &csRawCookie
) :
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
/*virtual*/
CxCookiePv0::~CxCookiePv0() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv0::sGetName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bSetName(
    const std::string_t &csName
)
{
    /*DEBUG*/

    _m_sName = csName;

    return TRUE;
}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv0::sGetValue() const {
    /*DEBUG*/

    return _m_sValue;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bSetValue(
    const std::string_t &csValue
)
{
    /*DEBUG*/

    _m_sValue = csValue;

    return TRUE;
}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv0::sGetDomain() const {
    /*DEBUG*/

    return _m_sDomain;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bSetDomain(
    const std::string_t &csDomain
)
{
    /*DEBUG*/

    _m_sDomain = csDomain;

    return TRUE;
}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv0::sGetPath() const {
    /*DEBUG*/

    return _m_sPath;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bSetPath(
    const std::string_t &csPath
)
{
    /*DEBUG*/

    _m_sPath = csPath;

    return TRUE;
}
//---------------------------------------------------------------------------
const std::string_t &
CxCookiePv0::sGetExpires() const {
    /*DEBUG*/

    return _m_sExpires;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bSetExpires(
    const std::string_t &csExpires
)
{
    /*DEBUG*/

    _m_sExpires = csExpires;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bGetSecure() const {
    /*DEBUG*/

    return _m_bSecure;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bSetSecure(
    BOOL bFlag
)
{
    /*DEBUG*/

    _m_bSecure = bFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bGetHttpOnly() const {
    /*DEBUG*/

    return _m_bHttpOnly;
}
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bSetHttpOnly(
    BOOL bFlag
)
{
    /*DEBUG*/

    _m_bHttpOnly = bFlag;

    return TRUE;
}
//---------------------------------------------------------------------------
std::string_t
CxCookiePv0::sToString() const {
    /*DEBUG*/

    std::string_t sRes;

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
//TODO: sGetDump make tests
std::string_t
CxCookiePv0::sGetDump() const {
    /*DEBUG*/

    std::string_t sRes;

    sRes = CxString::sFormat(
            xT("[CxCookiePv0 dump]\n\n")
            xT("Name: %s\n")
            xT("Value: %s\n")
            xT("Domain: %s\n")
            xT("Path: %s\n")
            xT("Expires: %s\n")
            xT("Secure: %s\n")
            xT("HttpOnly: %s\n\n"),
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
struct SCompareNoCase {
    bool
    operator() (const std::string_t &csStr1, const std::string_t &csStr2) const {
        return !! CxString::bCompareNoCase(csStr1, csStr2);
    }
};
//---------------------------------------------------------------------------
BOOL
CxCookiePv0::bInit(
    const std::string_t &csRawCookie
)
{
    /*DEBUG*/// _m_msCookie - n/a
    /*DEBUG*/// csRawCookie - n/a

    typedef std::map<std::string_t, std::string_t/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<std::string_t, std::string_t>                TStringPair;


    BOOL       bRes = FALSE;
    TStringMap msCookie;
    std::string_t    sCookie;

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
    _m_sDomain   = msCookie[xT("Domain")];
    _m_sPath     = msCookie[xT("Path")];
    _m_sExpires  = msCookie[xT("Expires")];
    _m_bSecure   = xAS_BOOL( msCookie.end() != msCookie.find(xT("Secure")) );
    _m_bHttpOnly = xAS_BOOL( msCookie.end() != msCookie.find(xT("HttpOnly")) );

    return TRUE;
}
//---------------------------------------------------------------------------
