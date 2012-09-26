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

    bool bRv = false;

    bRv = bInit(std::tstring_t());
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxCookiePv0::CxCookiePv0(
    const std::tstring_t &a_csRawCookie
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

    bool bRv = false;

    bRv = bInit(a_csRawCookie);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxCookiePv0::~CxCookiePv0() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::sGetName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetName(
    const std::tstring_t &a_csName
)
{
    /*DEBUG*/

    _m_sName = a_csName;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::sGetValue() const {
    /*DEBUG*/

    return _m_sValue;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetValue(
    const std::tstring_t &a_csValue
)
{
    /*DEBUG*/

    _m_sValue = a_csValue;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::sGetDomain() const {
    /*DEBUG*/

    return _m_sDomain;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetDomain(
    const std::tstring_t &a_csDomain
)
{
    /*DEBUG*/

    _m_sDomain = a_csDomain;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::sGetPath() const {
    /*DEBUG*/

    return _m_sPath;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetPath(
    const std::tstring_t &a_csPath
)
{
    /*DEBUG*/

    _m_sPath = a_csPath;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::sGetExpires() const {
    /*DEBUG*/

    return _m_sExpires;
}
//---------------------------------------------------------------------------
bool
CxCookiePv0::bSetExpires(
    const std::tstring_t &a_csExpires
)
{
    /*DEBUG*/

    _m_sExpires = a_csExpires;

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
    bool a_bFlag
)
{
    /*DEBUG*/

    _m_bSecure = a_bFlag;

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
    bool a_bFlag
)
{
    /*DEBUG*/

    _m_bHttpOnly = a_bFlag;

    return true;
}
//---------------------------------------------------------------------------
std::tstring_t
CxCookiePv0::sToString() const {
    /*DEBUG*/

    std::tstring_t sRv;

    //name
    sRv.append(_m_sName);
    sRv.append(xT("="));
    sRv.append(_m_sValue);

    //domain
    if (false == _m_sDomain.empty()) {
        sRv.append(xT("; Domain="));
        sRv.append(_m_sDomain);
    }

    //path
    if (false == _m_sPath.empty()) {
        sRv.append(xT("; Path="));
        sRv.append(_m_sPath);
    }

    //expires
    if (false == _m_sExpires.empty()) {
        //[Wdy, DD-Mon-YYYY HH:MM:SS GMT]
        sRv.append(xT("; Expires="));
        sRv.append(_m_sExpires);
    }

    //secure
    if (true == _m_bSecure) {
        sRv.append(xT("; Secure"));
    }

    //HttpOmly
    if (true == _m_bHttpOnly) {
        sRv.append(xT("; HttpOnly"));
    }

    return sRv;
}
//---------------------------------------------------------------------------
//TODO: sGetDump make tests
std::tstring_t
CxCookiePv0::sGetDump() const {
    /*DEBUG*/

    std::tstring_t sRv;

    sRv = CxString::sFormat(
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

    return sRv;
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
    operator() (const std::tstring_t &csStr1, const std::tstring_t &csStr2) const {
        return !! CxString::bCompareNoCase(csStr1, csStr2);
    }
};
//---------------------------------------------------------------------------
bool
CxCookiePv0::bInit(
    const std::tstring_t &a_csRawCookie
)
{
    /*DEBUG*/// _m_msCookie - n/a
    /*DEBUG*/// csRawCookie - n/a

    typedef std::map<std::tstring_t, std::tstring_t/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<std::tstring_t, std::tstring_t>                TStringPair;


    bool       bRv = false;
    TStringMap msCookie;
    std::tstring_t    sCookie;

    sCookie = a_csRawCookie;
    sCookie = CxString::sRemoveAll(sCookie, CxConst::xSQM);
    sCookie = CxString::sRemoveAll(sCookie, CxConst::xDQM);

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vec_tstring_t vsPairs;

    bRv = CxString::bSplit(sCookie, CxConst::xSEMICOLON, &vsPairs);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    for (size_t i = 0; i < vsPairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vec_tstring_t vsTemp;

        bRv = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsTemp);
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        std::tstring_t sCookieName  = CxString::sTrimSpace(vsTemp.at(0));
        std::tstring_t sCookieValue = ( (1 == vsTemp.size()) ? std::tstring_t() : vsTemp.at(1) );

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
