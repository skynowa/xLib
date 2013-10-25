/**
 * \file  CxCookiePv1.cpp
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#include <xLib/Net/CxCookiePv1.h>

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
xINLINE_HO
CxCookiePv1::CxCookiePv1() :
    _name    (),
    _value   (),
    _m_sComment (),
    _domain  (),
    _path    (),
    _maxAge (- 1),
    _isSecure  (false),
    _isHttpOnly(false)
{
    init(std::tstring_t());
}
//------------------------------------------------------------------------------
xINLINE_HO
CxCookiePv1::CxCookiePv1(
    std::ctstring_t &a_rawCookie
) :
    _name    (),
    _value   (),
    _m_sComment (),
    _domain  (),
    _path    (),
    _maxAge (- 1),
    _isSecure  (false),
    _isHttpOnly(false)
{
    init(a_rawCookie);
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxCookiePv1::name() const {
    return _name;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::setName(
    std::ctstring_t &a_name
)
{
    _name = a_name;
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxCookiePv1::value() const
{
    return _value;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::setValue(
    std::ctstring_t &a_value
)
{
    _value = a_value;
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxCookiePv1::comment() const
{
    return _m_sComment;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::setComment(
    std::ctstring_t &a_comment
)
{
    _m_sComment = a_comment;
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxCookiePv1::domain() const
{
    return _domain;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::setDomain(
    std::ctstring_t &a_domain
)
{
    _domain = a_domain;
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxCookiePv1::path() const
{
    return _path;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::setPath(
    std::ctstring_t &a_path
)
{
    _path = a_path;
}
//------------------------------------------------------------------------------
xINLINE_HO longlong_t
CxCookiePv1::maxAge() const
{
    return _maxAge;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::setMaxAge(
    clonglong_t &a_maxAge
)
{
    _maxAge = a_maxAge;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxCookiePv1::secure() const
{
    return _isSecure;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::setSecure(
    cbool_t &a_flag
)
{
    _isSecure = a_flag;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxCookiePv1::httpOnly() const
{
    return _isHttpOnly;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::setHttpOnly(
    cbool_t &a_flag
)
{
    _isHttpOnly = a_flag;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxCookiePv1::toString() const
{
    std::tstring_t sRv;

    sRv.append(_name);
    sRv.append(xT("="));

    sRv.append(xT("\""));
    sRv.append(_value);
    sRv.append(xT("\""));

    if (!_m_sComment.empty()) {
        sRv.append(xT("; Comment=\""));
        sRv.append(_m_sComment);
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
//------------------------------------------------------------------------------
// TODO: dump
xINLINE_HO std::tstring_t
CxCookiePv1::dump() const
{
    std::tstring_t sRv;

    xNOT_IMPLEMENTED;

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::clear()
{
    _name.clear();
    _value.clear();
    _m_sComment.clear();
    _domain.clear();
    _path.clear();
    _maxAge  = - 1L;
    _isSecure   = false;
    _isHttpOnly = false;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxCookiePv1::init(
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
    sCookie = CxString::removeAll(sCookie, CxConst::xSQM());
    sCookie = CxString::removeAll(sCookie, CxConst::xDQM());

    //split into pairs (name1=value1; name2=value2; nameN=valueN)
    std::vec_tstring_t vsPairs;

    CxString::split(sCookie, CxConst::xSEMICOLON(), &vsPairs);

    for (size_t i = 0; i < vsPairs.size(); ++ i) {
        //split into name, value (name=value)
        std::vec_tstring_t vsTemp;

        CxString::split(vsPairs.at(i), CxConst::xEQUAL(), &vsTemp);

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
    _m_sComment  = msCookie[xT("Comment")];
    _domain   = msCookie[xT("Domain")];
    _path     = msCookie[xT("Path")];
    _maxAge  = CxString::cast<longlong_t>( msCookie[xT("Max-Age")] );
    _isSecure   = ( msCookie.end() != msCookie.find(xT("Secure")) );
    _isHttpOnly = ( msCookie.end() != msCookie.find(xT("HttpOnly")) );
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
