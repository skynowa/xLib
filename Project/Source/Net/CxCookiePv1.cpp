/**
 * \file  CxCookiePv1.cpp
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#include <xLib/Net/CxCookiePv1.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxEnvironment.h>


xNAMESPACE_BEGIN(NxLib)

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
    _m_bSecure  (false),
    _m_bHttpOnly(false)
{
    /*DEBUG*/

    vInit(std::tstring_t());
}
//---------------------------------------------------------------------------
CxCookiePv1::CxCookiePv1(
    const std::tstring_t &a_csRawCookie
) :
    _m_sName    (),
    _m_sValue   (),
    _m_sComment (),
    _m_sDomain  (),
    _m_sPath    (),
    _m_liMaxAge (- 1),
    _m_bSecure  (false),
    _m_bHttpOnly(false)
{
    /*DEBUG*/

    vInit(a_csRawCookie);
}
//---------------------------------------------------------------------------
/* virtual */
CxCookiePv1::~CxCookiePv1() {
    /*DEBUG*/

}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv1::sGetName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
void
CxCookiePv1::vSetName(
    const std::tstring_t &a_csName
)
{
    /*DEBUG*/

    _m_sName = a_csName;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv1::sGetValue() const {
    /*DEBUG*/

    return _m_sValue;
}
//---------------------------------------------------------------------------
void
CxCookiePv1::vSetValue(
    const std::tstring_t &a_csValue
)
{
    /*DEBUG*/

    _m_sValue = a_csValue;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv1::sGetComment() const {
    /*DEBUG*/

    return _m_sComment;
}
//---------------------------------------------------------------------------
void
CxCookiePv1::vSetComment(
    const std::tstring_t &a_csComment
)
{
    /*DEBUG*/

    _m_sComment = a_csComment;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv1::sGetDomain() const {
    /*DEBUG*/

    return _m_sDomain;
}
//---------------------------------------------------------------------------
void
CxCookiePv1::vSetDomain(
    const std::tstring_t &a_csDomain
)
{
    /*DEBUG*/

    _m_sDomain = a_csDomain;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv1::sGetPath() const {
    /*DEBUG*/

    return _m_sPath;
}
//---------------------------------------------------------------------------
void
CxCookiePv1::vSetPath(
    const std::tstring_t &a_csPath
)
{
    /*DEBUG*/

    _m_sPath = a_csPath;
}
//---------------------------------------------------------------------------
longlong_t
CxCookiePv1::liGetMaxAge() const {
    /*DEBUG*/

    return _m_liMaxAge;
}
//---------------------------------------------------------------------------
void
CxCookiePv1::vSetMaxAge(
    const longlong_t &a_cliMaxAge
)
{
    /*DEBUG*/

    _m_liMaxAge = a_cliMaxAge;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bGetSecure() const {
    /*DEBUG*/

    return _m_bSecure;
}
//---------------------------------------------------------------------------
void
CxCookiePv1::vSetSecure(
    const bool &a_cbFlag
)
{
    /*DEBUG*/

    _m_bSecure = a_cbFlag;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bGetHttpOnly() const {
    /*DEBUG*/

    return _m_bHttpOnly;
}
//---------------------------------------------------------------------------
void
CxCookiePv1::vSetHttpOnly(
    const bool &a_cbFlag
)
{
    /*DEBUG*/

    _m_bHttpOnly = a_cbFlag;
}
//---------------------------------------------------------------------------
std::tstring_t
CxCookiePv1::sToString() const {
    /*DEBUG*/

    std::tstring_t sRv;

    sRv.append(_m_sName);
    sRv.append(xT("="));

    sRv.append(xT("\""));
    sRv.append(_m_sValue);
    sRv.append(xT("\""));

    if (false == _m_sComment.empty()) {
        sRv.append(xT("; Comment=\""));
        sRv.append(_m_sComment);
        sRv.append(xT("\""));
    }

    if (false == _m_sDomain.empty()) {
        sRv.append(xT("; Domain=\""));
        sRv.append(_m_sDomain);
        sRv.append(xT("\""));
    }

    if (false == _m_sPath.empty()) {
        sRv.append(xT("; Path=\""));
        sRv.append(_m_sPath);
        sRv.append(xT("\""));
    }

    if (_m_liMaxAge >= 0) {
        sRv.append(xT("; Max-Age=\""));
        sRv.append( CxString::string_cast(_m_liMaxAge) );
        sRv.append(xT("\""));
    }

    if (true == _m_bSecure) {
        sRv.append(xT("; Secure"));
    }

    if (true == _m_bHttpOnly) {
        sRv.append(xT("; HttpOnly"));
    }

    sRv.append(xT("; Version=\"1\""));

    return sRv;
}
//---------------------------------------------------------------------------
//TODO: sGetDump
std::tstring_t
CxCookiePv1::sGetDump() const {
    std::tstring_t sRv;

    xNOT_IMPLEMENTED;

    return sRv;
}
//---------------------------------------------------------------------------
void
CxCookiePv1::vClear() {
    /*DEBUG*/

    _m_sName.clear();
    _m_sValue.clear();
    _m_sComment.clear();
    _m_sDomain.clear();
    _m_sPath.clear();
    _m_liMaxAge  = - 1L;
    _m_bSecure   = false;
    _m_bHttpOnly = false;
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
void
CxCookiePv1::vInit(
    const std::tstring_t &a_csRawCookie
)
{
    /*DEBUG*/// _m_msCookie - n/a
    /*DEBUG*/// csRawCookie - n/a

    typedef std::map<std::tstring_t, std::tstring_t/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<std::tstring_t, std::tstring_t>                TStringPair;

    TStringMap     msCookie;
    std::tstring_t sCookie;

    sCookie = a_csRawCookie;
    sCookie = CxString::sRemoveAll(sCookie, CxConst::xSQM);
    sCookie = CxString::sRemoveAll(sCookie, CxConst::xDQM);

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vec_tstring_t vsPairs;

    CxString::vSplit(sCookie, CxConst::xSEMICOLON, &vsPairs);

    for (size_t i = 0; i < vsPairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vec_tstring_t vsTemp;

        CxString::vSplit(vsPairs.at(i), CxConst::xEQUAL, &vsTemp);

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
    _m_sComment  = msCookie[xT("Comment")];
    _m_sDomain   = msCookie[xT("Domain")];
    _m_sPath     = msCookie[xT("Path")];
    _m_liMaxAge  = CxString::string_cast<longlong_t>( msCookie[xT("Max-Age")] );
    _m_bSecure   = ( msCookie.end() != msCookie.find(xT("Secure")) );
    _m_bHttpOnly = ( msCookie.end() != msCookie.find(xT("HttpOnly")) );
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
