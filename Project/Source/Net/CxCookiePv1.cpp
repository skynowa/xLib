/**
 * \file  CxCookiePv1.cpp
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#include <xLib/Net/CxCookiePv1.h>

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

    bool bRv = false;

    bRv = bInit(std::tstring_t());
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
CxCookiePv1::CxCookiePv1(
    const std::tstring_t &csRawCookie
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

    bool bRv = false;

    bRv = bInit(csRawCookie);
    /*DEBUG*/xASSERT_DO(true == bRv, return);
}
//---------------------------------------------------------------------------
/*virtual*/
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
bool
CxCookiePv1::bSetName(
    const std::tstring_t &csName
)
{
    /*DEBUG*/

    _m_sName = csName;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv1::sGetValue() const {
    /*DEBUG*/

    return _m_sValue;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bSetValue(
    const std::tstring_t &csValue
)
{
    /*DEBUG*/

    _m_sValue = csValue;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv1::sGetComment() const {
    /*DEBUG*/

    return _m_sComment;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bSetComment(
    const std::tstring_t &csComment
)
{
    /*DEBUG*/

    _m_sComment = csComment;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv1::sGetDomain() const {
    /*DEBUG*/

    return _m_sDomain;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bSetDomain(
    const std::tstring_t &csDomain
)
{
    /*DEBUG*/

    _m_sDomain = csDomain;

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv1::sGetPath() const {
    /*DEBUG*/

    return _m_sPath;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bSetPath(
    const std::tstring_t &csPath
)
{
    /*DEBUG*/

    _m_sPath = csPath;

    return true;
}
//---------------------------------------------------------------------------
longlong_t
CxCookiePv1::liGetMaxAge() const {
    /*DEBUG*/

    return _m_liMaxAge;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bSetMaxAge(
    longlong_t liMaxAge
)
{
    /*DEBUG*/

    _m_liMaxAge = liMaxAge;

    return true;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bGetSecure() const {
    /*DEBUG*/

    return _m_bSecure;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bSetSecure(
    bool bFlag
)
{
    /*DEBUG*/

    _m_bSecure = bFlag;

    return true;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bGetHttpOnly() const {
    /*DEBUG*/

    return _m_bHttpOnly;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bSetHttpOnly(
    bool bFlag
)
{
    /*DEBUG*/

    _m_bHttpOnly = bFlag;

    return true;
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
        sRv.append( CxString::lexical_cast(_m_liMaxAge) );
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

    xNOT_IMPLEMENTED_RET(CxConst::xSTR_EMPTY);

    return sRv;
}
//---------------------------------------------------------------------------
bool
CxCookiePv1::bClear() {
    /*DEBUG*/

    _m_sName.clear();
    _m_sValue.clear();
    _m_sComment.clear();
    _m_sDomain.clear();
    _m_sPath.clear();
    _m_liMaxAge  = - 1;
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
CxCookiePv1::bInit(
    const std::tstring_t &csRawCookie
)
{
    /*DEBUG*/// _m_msCookie - n/a
    /*DEBUG*/// csRawCookie - n/a

    typedef std::map<std::tstring_t, std::tstring_t/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<std::tstring_t, std::tstring_t>                TStringPair;


    bool           bRv = false;
    TStringMap     msCookie;
    std::tstring_t sCookie;

    sCookie = csRawCookie;
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
    _m_sComment  = msCookie[xT("Comment")];
    _m_sDomain   = msCookie[xT("Domain")];
    _m_sPath     = msCookie[xT("Path")];
    _m_liMaxAge  = CxString::lexical_cast<longlong_t>( msCookie[xT("Max-Age")] );
    _m_bSecure   = ( msCookie.end() != msCookie.find(xT("Secure")) );
    _m_bHttpOnly = ( msCookie.end() != msCookie.find(xT("HttpOnly")) );

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
