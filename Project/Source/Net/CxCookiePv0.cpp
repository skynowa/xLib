/**
 * \file  CxCookiePv0.cpp
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#include <xLib/Net/CxCookiePv0.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxEnvironment.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxCookiePv0::CxCookiePv0() :
    _m_sName    (),
    _m_sValue   (),
    _m_sDomain  (),
    _m_sPath    (),
    _m_sExpires (),
    _m_bSecure  (false),
    _m_bHttpOnly(false)
{
    init(std::tstring_t());
}
//------------------------------------------------------------------------------
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
    init(a_csRawCookie);
}
//------------------------------------------------------------------------------
/* virtual */
CxCookiePv0::~CxCookiePv0() {

}
//------------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::name() const {
    return _m_sName;
}
//------------------------------------------------------------------------------
void
CxCookiePv0::setName(
    const std::tstring_t &a_csName
)
{
    _m_sName = a_csName;
}
//------------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::value() const {
    return _m_sValue;
}
//------------------------------------------------------------------------------
void
CxCookiePv0::setValue(
    const std::tstring_t &a_csValue
)
{
    _m_sValue = a_csValue;
}
//------------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::domain() const {
    return _m_sDomain;
}
//------------------------------------------------------------------------------
void
CxCookiePv0::setDomain(
    const std::tstring_t &a_csDomain
)
{
    _m_sDomain = a_csDomain;
}
//------------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::path() const {
    return _m_sPath;
}
//------------------------------------------------------------------------------
void
CxCookiePv0::setPath(
    const std::tstring_t &a_csPath
)
{
    _m_sPath = a_csPath;
}
//------------------------------------------------------------------------------
const std::tstring_t &
CxCookiePv0::expires() const {
    return _m_sExpires;
}
//------------------------------------------------------------------------------
void
CxCookiePv0::setExpires(
    const std::tstring_t &a_csExpires
)
{
    _m_sExpires = a_csExpires;
}
//------------------------------------------------------------------------------
bool
CxCookiePv0::secure() const {
    return _m_bSecure;
}
//------------------------------------------------------------------------------
void
CxCookiePv0::setSecure(
    const bool &a_cbFlag
)
{
    _m_bSecure = a_cbFlag;
}
//------------------------------------------------------------------------------
bool
CxCookiePv0::httpOnly() const {
    return _m_bHttpOnly;
}
//------------------------------------------------------------------------------
void
CxCookiePv0::setHttpOnly(
    const bool &a_cbFlag
)
{
    _m_bHttpOnly = a_cbFlag;
}
//------------------------------------------------------------------------------
std::tstring_t
CxCookiePv0::toString() const {
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
//------------------------------------------------------------------------------
//TODO: sDump make tests
std::tstring_t
CxCookiePv0::dump() const {
    std::tstring_t sRv;

    sRv = CxString::format(
            xT("[CxCookiePv0 dump]\n\n")
            xT("Name: %s\n")
            xT("Value: %s\n")
            xT("Domain: %s\n")
            xT("Path: %s\n")
            xT("Expires: %s\n")
            xT("Secure: %s\n")
            xT("HttpOnly: %s\n\n"),
            name().c_str(),
            value().c_str(),
            domain().c_str(),
            path().c_str(),
            expires().c_str(),
            CxString::boolToStr(secure()).c_str(),
            CxString::boolToStr(httpOnly()).c_str()
    );

    return sRv;
}
//------------------------------------------------------------------------------
void
CxCookiePv0::clear() {
    _m_sName.clear();
    _m_sValue.clear();
    _m_sDomain.clear();
    _m_sPath.clear();
    _m_sExpires.clear();
    _m_bSecure   = false;
    _m_bHttpOnly = false;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
struct SCompareNoCase {
    bool
    operator() (const std::tstring_t &csStr1, const std::tstring_t &csStr2) const {
        return !! CxString::compareNoCase(csStr1, csStr2);
    }
};
//------------------------------------------------------------------------------
void
CxCookiePv0::init(
    const std::tstring_t &a_csRawCookie
)
{
    // _m_msCookie - n/a
    // csRawCookie - n/a

    typedef std::map<std::tstring_t, std::tstring_t/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<std::tstring_t, std::tstring_t>                TStringPair;

    TStringMap     msCookie;
    std::tstring_t sCookie;

    sCookie = a_csRawCookie;
    sCookie = CxString::removeAll(sCookie, CxConst::xSQM);
    sCookie = CxString::removeAll(sCookie, CxConst::xDQM);

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vec_tstring_t vsPairs;

    CxString::split(sCookie, CxConst::xSEMICOLON, &vsPairs);

    for (size_t i = 0; i < vsPairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vec_tstring_t vsTemp;

        CxString::split(vsPairs.at(i), CxConst::xEQUAL, &vsTemp);

        std::tstring_t sCookieName  = CxString::trimSpace(vsTemp.at(0));
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
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
