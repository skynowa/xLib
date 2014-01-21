/**
 * \file  CxCookiePv1.cpp
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN(xlib)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxCookiePv1::CxCookiePv1() :
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
inline
CxCookiePv1::CxCookiePv1(
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
inline std::ctstring_t &
CxCookiePv1::name() const {
    return _name;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCookiePv1::setName(
    std::ctstring_t &a_name
)
{
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCookiePv1::value() const
{
    return _value;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCookiePv1::setValue(
    std::ctstring_t &a_value
)
{
    _value = a_value;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCookiePv1::comment() const
{
    return _comment;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCookiePv1::setComment(
    std::ctstring_t &a_comment
)
{
    _comment = a_comment;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCookiePv1::domain() const
{
    return _domain;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCookiePv1::setDomain(
    std::ctstring_t &a_domain
)
{
    _domain = a_domain;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCookiePv1::path() const
{
    return _path;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCookiePv1::setPath(
    std::ctstring_t &a_path
)
{
    _path = a_path;
}
//-------------------------------------------------------------------------------------------------
inline longlong_t
CxCookiePv1::maxAge() const
{
    return _maxAge;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCookiePv1::setMaxAge(
    clonglong_t &a_maxAge
)
{
    _maxAge = a_maxAge;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxCookiePv1::secure() const
{
    return _isSecure;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCookiePv1::setSecure(
    cbool_t &a_flag
)
{
    _isSecure = a_flag;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxCookiePv1::httpOnly() const
{
    return _isHttpOnly;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCookiePv1::setHttpOnly(
    cbool_t &a_flag
)
{
    _isHttpOnly = a_flag;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxCookiePv1::toString() const
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
        sRv.append( CxString::cast(_maxAge) );
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
inline std::tstring_t
CxCookiePv1::dump() const
{
    std::tstring_t sRv;

    sRv = CxString::format(
            xT("[CxCookiePv1 dump]\n\n")
            xT("Name: %s\n")
            xT("Value: %s\n")
            xT("Comment: %s\n")
            xT("Domain: %s\n")
            xT("Path: %s\n")
            xT("Max age: %s\n")
            xT("Secure: %lld\n")
            xT("HttpOnly: %s\n\n"),
            name().c_str(),
            value().c_str(),
            comment().c_str(),
            domain().c_str(),
            path().c_str(),
            maxAge(),
            CxString::castBool( secure() ).c_str(),
            CxString::castBool( httpOnly() ).c_str()
    );

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCookiePv1::clear()
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
inline void_t
CxCookiePv1::init(
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
    cookie = CxString::removeAll(cookie, CxConst::sqm());
    cookie = CxString::removeAll(cookie, CxConst::dqm());

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vec_tstring_t pairs;

    CxString::split(cookie, CxConst::semicolon(), &pairs);

    for (size_t i = 0; i < pairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vec_tstring_t temp;

        CxString::split(pairs.at(i), CxConst::equal(), &temp);

        std::tstring_t cookieName  = CxString::trimSpace(temp.at(0));
        std::tstring_t cookieValue = ( (1 == temp.size()) ? std::tstring_t() : temp.at(1) );

        if (0 == i) {
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
    _maxAge  = CxString::cast<longlong_t>( cookies[xT("Max-Age")] );
    _isSecure   = ( cookies.end() != cookies.find(xT("Secure")) );
    _isHttpOnly = ( cookies.end() != cookies.find(xT("HttpOnly")) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)
