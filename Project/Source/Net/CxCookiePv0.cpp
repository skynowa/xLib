/**
 * \file  CxCookiePv0.cpp
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#include <xLib/Net/CxCookiePv0.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxDateTime.h>
#include <xLib/System/CxEnvironment.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxCookiePv0::CxCookiePv0() :
    _name    (),
    _value   (),
    _domain  (),
    _path    (),
    _expires (),
    _isSecure  (false),
    _isHttpOnly(false)
{
    init(std::tstring_t());
}
//------------------------------------------------------------------------------
CxCookiePv0::CxCookiePv0(
    std::ctstring_t &a_rawCookie
) :
    _name    (),
    _value   (),
    _domain  (),
    _path    (),
    _expires (),
    _isSecure  (false),
    _isHttpOnly(false)
{
    init(a_rawCookie);
}
//------------------------------------------------------------------------------
/* virtual */
CxCookiePv0::~CxCookiePv0()
{
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxCookiePv0::name() const
{
    return _name;
}
//------------------------------------------------------------------------------
void_t
CxCookiePv0::setName(
    std::ctstring_t &a_name
)
{
    _name = a_name;
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxCookiePv0::value() const
{
    return _value;
}
//------------------------------------------------------------------------------
void_t
CxCookiePv0::setValue(
    std::ctstring_t &a_value
)
{
    _value = a_value;
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxCookiePv0::domain() const
{
    return _domain;
}
//------------------------------------------------------------------------------
void_t
CxCookiePv0::setDomain(
    std::ctstring_t &a_domain
)
{
    _domain = a_domain;
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxCookiePv0::path() const
{
    return _path;
}
//------------------------------------------------------------------------------
void_t
CxCookiePv0::setPath(
    std::ctstring_t &a_path
)
{
    _path = a_path;
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxCookiePv0::expires() const
{
    return _expires;
}
//------------------------------------------------------------------------------
void_t
CxCookiePv0::setExpires(
    std::ctstring_t &a_expires
)
{
    _expires = a_expires;
}
//------------------------------------------------------------------------------
bool_t
CxCookiePv0::secure() const
{
    return _isSecure;
}
//------------------------------------------------------------------------------
void_t
CxCookiePv0::setSecure(
    cbool_t &a_flag
)
{
    _isSecure = a_flag;
}
//------------------------------------------------------------------------------
bool_t
CxCookiePv0::httpOnly() const
{
    return _isHttpOnly;
}
//------------------------------------------------------------------------------
void_t
CxCookiePv0::setHttpOnly(
    cbool_t &a_flag
)
{
    _isHttpOnly = a_flag;
}
//------------------------------------------------------------------------------
std::tstring_t
CxCookiePv0::toString() const
{
    std::tstring_t sRv;

    //name
    sRv.append(_name);
    sRv.append(xT("="));
    sRv.append(_value);

    //domain
    if (!_domain.empty()) {
        sRv.append(xT("; Domain="));
        sRv.append(_domain);
    }

    //path
    if (!_path.empty()) {
        sRv.append(xT("; Path="));
        sRv.append(_path);
    }

    //expires
    if (!_expires.empty()) {
        //[Wdy, DD-Mon-YYYY HH:MM:SS GMT]
        sRv.append(xT("; Expires="));
        sRv.append(_expires);
    }

    //secure
    if (_isSecure) {
        sRv.append(xT("; Secure"));
    }

    //HttpOmly
    if (_isHttpOnly) {
        sRv.append(xT("; HttpOnly"));
    }

    return sRv;
}
//------------------------------------------------------------------------------
//TODO: sDump make tests
std::tstring_t
CxCookiePv0::dump() const
{
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
void_t
CxCookiePv0::clear()
{
    _name.clear();
    _value.clear();
    _domain.clear();
    _path.clear();
    _expires.clear();
    _isSecure   = false;
    _isHttpOnly = false;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
struct SCompareNoCase
{
    bool_t
    operator() (std::ctstring_t &a_str1, std::ctstring_t &a_str2) const
    {
        return !! CxString::compareNoCase(a_str1, a_str2);
    }
};
//------------------------------------------------------------------------------
void_t
CxCookiePv0::init(
    std::ctstring_t &a_rawCookie
)
{
    // _m_msCookie - n/a
    // rawCookie - n/a

    typedef std::map<std::tstring_t, std::tstring_t/*, SCompareNoCase*/> TStringMap;
    typedef std::pair<std::tstring_t, std::tstring_t>                TStringPair;

    TStringMap     msCookie;
    std::tstring_t sCookie;

    sCookie = a_rawCookie;
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
    _name     = msCookie[xT("Name")];
    _value    = msCookie[xT("Value")];
    _domain   = msCookie[xT("Domain")];
    _path     = msCookie[xT("Path")];
    _expires  = msCookie[xT("Expires")];
    _isSecure   = ( msCookie.end() != msCookie.find(xT("Secure")) );
    _isHttpOnly = ( msCookie.end() != msCookie.find(xT("HttpOnly")) );
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
