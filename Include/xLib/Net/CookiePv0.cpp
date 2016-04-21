/**
 * \file  CookiePv0.inl
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "CookiePv0.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CookiePv0::CookiePv0() :
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
//-------------------------------------------------------------------------------------------------
xINLINE
CookiePv0::CookiePv0(
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
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv0::name() const
{
    return _name;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv0::setName(
    std::ctstring_t &a_name
)
{
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv0::value() const
{
    return _value;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv0::setValue(
    std::ctstring_t &a_value
)
{
    _value = a_value;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv0::domain() const
{
    return _domain;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv0::setDomain(
    std::ctstring_t &a_domain
)
{
    _domain = a_domain;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv0::path() const
{
    return _path;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv0::setPath(
    std::ctstring_t &a_path
)
{
    _path = a_path;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv0::expires() const
{
    return _expires;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv0::setExpires(
    std::ctstring_t &a_expires
)
{
    _expires = a_expires;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CookiePv0::secure() const
{
    return _isSecure;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv0::setSecure(
    cbool_t &a_flag
)
{
    _isSecure = a_flag;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CookiePv0::httpOnly() const
{
    return _isHttpOnly;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv0::setHttpOnly(
    cbool_t &a_flag
)
{
    _isHttpOnly = a_flag;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CookiePv0::toString() const
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
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CookiePv0::dump() const
{
    std::tstring_t sRv;

    sRv = Format::str(
            xT("[CookiePv0 dump]\n\n")
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
            String::castBool(secure()).c_str(),
            String::castBool(httpOnly()).c_str()
    );

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv0::clear()
{
    _name.clear();
    _value.clear();
    _domain.clear();
    _path.clear();
    _expires.clear();
    _isSecure   = false;
    _isHttpOnly = false;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv0::init(
    std::ctstring_t &a_rawCookie
)
{
    // _m_msCookie - n/a
    // rawCookie - n/a

    typedef std::map<std::tstring_t, std::tstring_t/*, SCompareCI*/> TStringMap;
    typedef std::pair<std::tstring_t, std::tstring_t>                TStringPair;

    TStringMap     cookies;
    std::tstring_t cookie;

    cookie = a_rawCookie;
    cookie = String::removeAll(cookie, Const::sqm());
    cookie = String::removeAll(cookie, Const::dqm());

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vec_tstring_t pairs;

    String::split(cookie, Const::semicolon(), &pairs);

    for (size_t i = 0; i < pairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vec_tstring_t temp;

        String::split(pairs.at(i), Const::equal(), &temp);

        std::tstring_t cookieName  = String::trimSpace(temp.at(0));
        std::tstring_t cookieValue = ( (temp.size() == 1) ? std::tstring_t() : temp.at(1) );

        if (0 == i) {
            //1-st pair is "Name=Value"
            cookies.insert( TStringPair(xT("Name"),  cookieName) );
            cookies.insert( TStringPair(xT("Value"), cookieValue) );
        } else {
            cookies.insert( TStringPair(cookieName, cookieValue) );
        }
    }

    //set results
    _name       = cookies[xT("Name")];
    _value      = cookies[xT("Value")];
    _domain     = cookies[xT("Domain")];
    _path       = cookies[xT("Path")];
    _expires    = cookies[xT("Expires")];
    _isSecure   = ( cookies.end() != cookies.find(xT("Secure")) );
    _isHttpOnly = ( cookies.end() != cookies.find(xT("HttpOnly")) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
