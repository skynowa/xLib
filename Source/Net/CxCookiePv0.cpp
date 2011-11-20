/**
 * \file  CxCookiePv0.cpp
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#include <xLib/Net/CxCookiePv0.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxEnvironment.h>


xNAMESPACE_BEGIN(NxLib)

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
    _m_bSecure  (false),
    _m_bHttpOnly(false)
{
    /*DEBUG*/

    bool bRes = false;

    bRes = bInit(std::tstring());
    /*DEBUG*/xASSERT_DO(false != bRes, return);
}
//---------------------------------------------------------------------------
CxCookiePv0::CxCookiePv0(
    const std::tstring &csRawCookie
) :
    _m_sName    (),
    _m_sValue   (),
    _m_sDomain  (),
    _m_sPath    (),
    _m_sExpires (),
    _m_bSecure  (false),
    _m_bHttpOnly(false)
{
    /*DEBUG*/

    bool bRes = false;

    bRes = bInit(csRawCookie);
    /*DEBUG*/xASSERT_DO(false != bRes, return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxCookiePv0::~CxCookiePv0() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
const std::tstring &
CxCookiePv0::sGetName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetName(
    const std::tstring &csName
)
{
    /*DEBUG*/

    _m_sName = csName;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring &
CxCookiePv0::sGetValue() const {
    /*DEBUG*/

    return _m_sValue;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetValue(
    const std::tstring &csValue
)
{
    /*DEBUG*/

    _m_sValue = csValue;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring &
CxCookiePv0::sGetDomain() const {
    /*DEBUG*/

    return _m_sDomain;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetDomain(
    const std::tstring &csDomain
)
{
    /*DEBUG*/

    _m_sDomain = csDomain;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring &
CxCookiePv0::sGetPath() const {
    /*DEBUG*/

    return _m_sPath;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetPath(
    const std::tstring &csPath
)
{
    /*DEBUG*/

    _m_sPath = csPath;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring &
CxCookiePv0::sGetExpires() const {
    /*DEBUG*/

    return _m_sExpires;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetExpires(
    const std::tstring &csExpires
)
{
    /*DEBUG*/

    _m_sExpires = csExpires;

    return true;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bGetSecure() const {
    /*DEBUG*/

    return _m_bSecure;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetSecure(
    bool bFlag
)
{
    /*DEBUG*/

    _m_bSecure = bFlag;

    return true;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bGetHttpOnly() const {
    /*DEBUG*/

    return _m_bHttpOnly;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetHttpOnly(
    bool bFlag
)
{
    /*DEBUG*/

    _m_bHttpOnly = bFlag;

    return true;
}
//---------------------------------------------------------------------------
std::tstring
CxCookiePv0::sToString() const {
    /*DEBUG*/

    std::tstring sRes;

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
    if (true == _m_bSecure) {
        sRes.append(xT("; Secure"));
    }

    //HttpOmly
    if (true == _m_bHttpOnly) {
        sRes.append(xT("; HttpOnly"));
    }

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: sGetDump make tests
std::tstring
CxCookiePv0::sGetDump() const {
    /*DEBUG*/

    std::tstring sRes;

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
bool
CxCookiePv0::bClear() {
    /*DEBUG*/

    _m_sName.clear();
    _m_sValue.clear();
    _m_sDomain.clear();
    _m_sPath.clear();
    _m_sExpires.clear();
    _m_bSecure   = false;
    _m_bHttpOnly = false;

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
struct SCompareNoCase {
    bool
    operator() (const std::tstring &csStr1, const std::tstring &csStr2) const {
        return !! CxString::bCompareNoCase(csStr1, csStr2);
    }
};
//---------------------------------------------------------------------------
bool
CxCookiePv0::bInit(
    const std::tstring &csRawCookie
)
{
    /*DEBUG*/// _m_msCookie - n/a
    /*DEBUG*/// csRawCookie - n/a

    typedef std::map<std::tstring, std::tstring/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<std::tstring, std::tstring>                TStringPair;


    bool       bRes = false;
    TStringMap msCookie;
    std::tstring    sCookie;

    sCookie.assign( csRawCookie );
    sCookie.assign( CxString::sRemoveAll(sCookie, CxConst::xSQM) );
    sCookie.assign( CxString::sRemoveAll(sCookie, CxConst::xDQM) );

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vector<std::tstring> vsPairs;

    bRes = CxString::bSplit(sCookie, CxConst::xSEMICOLON, &vsPairs);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    for (size_t i = 0; i < vsPairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vector<std::tstring> vsTemp;

        bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsTemp);
        /*DEBUG*/xASSERT_RET(false != bRes, false);

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
    _m_sDomain   = msCookie[xT("Domain")];
    _m_sPath     = msCookie[xT("Path")];
    _m_sExpires  = msCookie[xT("Expires")];
    _m_bSecure   = ( msCookie.end() != msCookie.find(xT("Secure")) );
    _m_bHttpOnly = ( msCookie.end() != msCookie.find(xT("HttpOnly")) );

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
