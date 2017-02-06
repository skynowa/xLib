/**
 * \file  CookiePv1.inl
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "CookiePv1.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>


xNAMESPACE_BEGIN2(xl, net)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CookiePv1::CookiePv1() :
    _name    (),
    _value   (),
    _comment (),
    _domain  (),
    _path    (),
    _maxAge (- 1),
    _isSecure  (false),
    _isHttpOnly(false)
{
    init(std::tstring_t());
}
//-------------------------------------------------------------------------------------------------
xINLINE
CookiePv1::CookiePv1(
    std::ctstring_t &a_rawCookie
) :
    _name    (),
    _value   (),
    _comment (),
    _domain  (),
    _path    (),
    _maxAge (- 1),
    _isSecure  (false),
    _isHttpOnly(false)
{
    init(a_rawCookie);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv1::name() const {
    return _name;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv1::setName(
    std::ctstring_t &a_name
)
{
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv1::value() const
{
    return _value;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv1::setValue(
    std::ctstring_t &a_value
)
{
    _value = a_value;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv1::comment() const
{
    return _comment;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv1::setComment(
    std::ctstring_t &a_comment
)
{
    _comment = a_comment;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv1::domain() const
{
    return _domain;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv1::setDomain(
    std::ctstring_t &a_domain
)
{
    _domain = a_domain;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CookiePv1::path() const
{
    return _path;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv1::setPath(
    std::ctstring_t &a_path
)
{
    _path = a_path;
}
//-------------------------------------------------------------------------------------------------
xINLINE longlong_t
CookiePv1::maxAge() const
{
    return _maxAge;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv1::setMaxAge(
    clonglong_t &a_maxAge
)
{
    _maxAge = a_maxAge;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CookiePv1::secure() const
{
    return _isSecure;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv1::setSecure(
    cbool_t &a_flag
)
{
    _isSecure = a_flag;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
CookiePv1::httpOnly() const
{
    return _isHttpOnly;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv1::setHttpOnly(
    cbool_t &a_flag
)
{
    _isHttpOnly = a_flag;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CookiePv1::toString() const
{
    std::tstring_t sRv;

    sRv.append(_name);
    sRv.append(xT("="));

    sRv.append(xT("\""));
    sRv.append(_value);
    sRv.append(xT("\""));

    if (!_comment.empty()) {
        sRv.append(xT("; Comment=\""));
        sRv.append(_comment);
        sRv.append(xT("\""));
    }

    if (!_domain.empty()) {
        sRv.append(xT("; Domain=\""));
        sRv.append(_domain);
        sRv.append(xT("\""));
    }

    if (!_path.empty()) {
        sRv.append(xT("; Path=\""));
        sRv.append(_path);
        sRv.append(xT("\""));
    }

    if (_maxAge >= 0) {
        sRv.append(xT("; Max-Age=\""));
        sRv.append( String::cast(_maxAge) );
        sRv.append(xT("\""));
    }

    if (_isSecure) {
        sRv.append(xT("; Secure"));
    }

    if (_isHttpOnly) {
        sRv.append(xT("; HttpOnly"));
    }

    sRv.append(xT("; Version=\"1\""));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CookiePv1::dump() const
{
    std::tstring_t sRv;

    sRv = Format::str(
            xT("[CookiePv1 dump]\n\n")
            xT("Name: {}\n")
            xT("Value: {}\n")
            xT("Comment: {}\n")
            xT("Domain: {}\n")
            xT("Path: {}\n")
            xT("Max age: {}\n")
            xT("Secure: {}\n")
            xT("HttpOnly: {}\n\n"),
            name(),
            value(),
            comment(),
            domain(),
            path(),
            maxAge(),
            secure(),
            httpOnly()
    );

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
CookiePv1::clear()
{
    _name.clear();
    _value.clear();
    _comment.clear();
    _domain.clear();
    _path.clear();
    _maxAge     = - 1L;
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
CookiePv1::init(
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

        if (i == 0) {
            //1-st pair is "Name=Value"
            cookies.insert( TStringPair(xT("Name"),  cookieName) );
            cookies.insert( TStringPair(xT("Value"), cookieValue) );
        } else {
            cookies.insert( TStringPair(cookieName, cookieValue) );
        }
    }

    //set results
    _name     = cookies[xT("Name")];
    _value    = cookies[xT("Value")];
    _comment  = cookies[xT("Comment")];
    _domain   = cookies[xT("Domain")];
    _path     = cookies[xT("Path")];
    _maxAge  = String::cast<longlong_t>( cookies[xT("Max-Age")] );
    _isSecure   = ( cookies.end() != cookies.find(xT("Secure")) );
    _isHttpOnly = ( cookies.end() != cookies.find(xT("HttpOnly")) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, net)
