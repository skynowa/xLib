/**
 * \file  Uri.inl
 * \brief URI (RFC 3986)
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Uri.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
* public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Uri::Uri() :
    _scheme   (),
    _authority(),
    _userInfo (),
    _host     (),
    _port     (0),
    _path     (),
    _query    (),
    _fragment ()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE
Uri::Uri(
    std::ctstring_t &a_uri
) :
    _scheme   (),
    _authority(),
    _userInfo (),
    _host     (),
    _port     (0),
    _path     (),
    _query    (),
    _fragment ()
{
    _parse(a_uri);
}
//-------------------------------------------------------------------------------------------------
// TODO: Uri::uri()
/**
 * URI = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
 *
 * foo://userinfo@example.com:8042/over/there?name=ferret#nose
 * \_/   \_______________________/\_________/ \_________/ \__/
 * |                |                |            |       |
 * scheme        authority           path        query   fragment
 */
xINLINE std::tstring_t
Uri::uri() const
{
    std::tstring_t sRv;
    std::tstring_t temp;

    temp = scheme();
    if (!temp.empty()) {
        sRv += xT("");
        sRv += temp;
    }

    temp = authority();
    if (!temp.empty()) {
        sRv += xT(":");
        sRv += temp;
    }

    temp = path();
    if (!temp.empty()) {
        sRv += xT("");
        sRv += temp;
    }

    temp = query();
    if (!temp.empty()) {
        sRv += xT("?");
        sRv += temp;
    }

    temp = fragment();
    if (!temp.empty()) {
        sRv += xT("#");
        sRv += temp;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::setUri(
    std::ctstring_t &a_scheme,
    std::ctstring_t &a_authority,
    std::ctstring_t &a_path,
    std::ctstring_t &a_query,
    std::ctstring_t &a_fragment
)
{
    setScheme   (a_scheme);
    setAuthority(a_authority);
    setPath     (a_path);
    setQuery    (a_query);
    setFragment (a_fragment);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Uri::scheme() const
{
    return encodeComponent(_scheme);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::setScheme(
    std::ctstring_t &a_scheme
)
{
    _scheme = decodeComponent(a_scheme);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Uri::authority() const
{
    std::tstring_t tempAuthority;

    tempAuthority += xT("//");

    if (!_userInfo.empty()) {
        tempAuthority += _userInfo;
        tempAuthority += xT("@");
    }

    if (!_host.empty()) {
        tempAuthority += _host;
    }

    if (0 < _port && !_isDefaultPort()) {
        tempAuthority += xT(":");
        tempAuthority += String::cast(_port);
    }

    return encodeComponent(tempAuthority/*_authority*/);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::setAuthority(
    std::ctstring_t &a_authority
)
{
    _authority = decodeComponent(a_authority);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Uri::userInfo() const
{
    return encodeComponent(_userInfo);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::setUserInfo(
    std::ctstring_t &a_userInfo
)
{
    _userInfo = decodeComponent(a_userInfo);

    // TODO: setAuthority
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Uri::host() const
{
    return encodeComponent(_host);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::setHost(
    std::ctstring_t &a_host
)
{
    _host = decodeComponent(a_host);

    // TODO: setAuthority
}
//-------------------------------------------------------------------------------------------------
xINLINE ushort_t
Uri::port()
{
    return _port;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::setPort(
    cushort_t &a_port
)
{
    _port = a_port;

    // TODO: Uri::setPort() - setAuthority
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Uri::path() const
{
    return encodeComponent(_path);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::setPath(
    std::ctstring_t &a_path
)
{
    _path = decodeComponent(a_path);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Uri::query() const
{
    return encodeComponent(_query);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::setQuery(
    std::ctstring_t &a_query
)
{
    _query = decodeComponent(a_query);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Uri::fragment() const
{
    return encodeComponent(_fragment);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::setFragment(
    std::ctstring_t &a_fragment
)
{
    _fragment = decodeComponent(a_fragment);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::clear()
{
    _scheme.clear();
    _authority.clear();
    _userInfo.clear();
    _host.clear();
    _port = 0;
    _path.clear();
    _query.clear();
    _fragment.clear();
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Uri::escape(
    std::ctstring_t &a_uri
)
{
#if 0
    int_t    c;

    while((c = *s++) != (char)0) {
        switch(c) {
        case '\0':
            break;
        case '%': case ' ': case '?': case '&':
        case '>': case '<': case '\"': case ';':
        case '=': case '@': case ':': case '#':
            fprintf(fw, "%%%02x", c);
            break;
        default:
            if (fputc(c, fw) == EOF) {
                return EOF;
            }
            break;
        }
    }

    return 0;
#endif

    std::tstring_t sRv;

    sRv = a_uri;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Uri::unescape(
    std::ctstring_t &a_uri
)
{
    xUNUSED(a_uri);

    std::tstring_t sRv;

    // TODO: unescape

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Uri::encodeComponent(
    std::ctstring_t &a_uri
)
{
    // TODO: Uri::encodeComponent()

    std::tstring_t sRv;

    xFOR_EACH_CONST(std::tstring_t, it, a_uri) {
        tchar_t c = *it;

        if (
            (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            c == '-' ||
            c == '_' ||
            c == '.' ||
            c == '~')
        {
            sRv += c;
        }
        /*
        _reservedPath     = "?#";
        _reservedQuery    = "#";
        _reservedFragment = "";
        _illegal          = "%<>{}|\\\"^`";
        */
        else if (c <= 0x20 || c >= 0x7F || _illegal().find(c) != std::tstring_t::npos
            /*|| reserved.find(c) != std::tstring_t::npos*/)
        {
            //� -> %FF
            sRv += Format::c_str(xT("%%%02X"), (uint_t)(uchar_t)c);
        }
        else {
            sRv += c;
        }
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Uri::decodeComponent(
    std::ctstring_t &a_uri
)
{
    // TODO: Uri::decodeComponent()

    std::tstring_t sRv;

    std::tstring_t::const_iterator it  = a_uri.begin();
    std::tstring_t::const_iterator end = a_uri.end();

    while (it != end) {
        tchar_t c = *it ++;

        if (c == '%') {
            if (it == end) {
                //throw SyntaxException("URI encoding: no hex digit following percent sign", uri);
                xTEST_FAIL;
            }

            tchar_t hi = *it ++;

            if (it == end) {
                // throw SyntaxException("URI encoding: two hex digits must follow percent sign",
                // uri);
                xTEST_FAIL;
            }

            tchar_t lo = *it ++;

            if (       hi >= '0' && hi <= '9') {
                c = static_cast<tchar_t>(hi - '0');
            } else if (hi >= 'A' && hi <= 'F') {
                c = static_cast<tchar_t>(hi - 'A' + 10);
            } else if (hi >= 'a' && hi <= 'f') {
                c = static_cast<tchar_t>(hi - 'a' + 10);
            } else {
                //throw SyntaxException("URI encoding: not a hex digit");
                xTEST_FAIL;
            }

            c = static_cast<tchar_t>(c * 16);

            if (       lo >= '0' && lo <= '9') {
                c = static_cast<tchar_t>(c + lo - '0');
            } else if (lo >= 'A' && lo <= 'F') {
                c = static_cast<tchar_t>(c + lo - 'A' + 10);
            } else if (lo >= 'a' && lo <= 'f') {
                c = static_cast<tchar_t>(c + lo - 'a' + 10);
            } else {
                //throw SyntaxException("URI encoding: not a hex digit");
                xTEST_FAIL;
            }
        }

        sRv += c;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Uri::_reservedPath()
{
    static std::ctstring_t sRv(xT("?#"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Uri::_reservedQuery()
{
    static std::ctstring_t sRv(xT("#"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Uri::_reservedFragment()
{
    static std::ctstring_t sRv(xT(""));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Uri::_illegal()
{
    static std::ctstring_t sRv(xT("%<>{}|\\\"^`"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/**
 * URI = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
 *
 * foo://userinfo@example.com:8042/over/there?name=ferret#nose
 * \_/   \_______________________/\_________/ \_________/ \__/
 * |                |                |            |       |
 * scheme        authority           path        query   fragment
 */
xINLINE void_t
Uri::_parse(
    std::ctstring_t &a_uri
)
{
    // TODO: Uri::_parse()

    // normilize();

    clear();

    // [scheme] - [foo]
    // [INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t schemeStart = 0;
    size_t schemeEnd   = a_uri.find_first_of(Const::colon());
    xTEST_DIFF(schemeEnd, std::tstring_t::npos);
    xTEST_GR(size_t(7U)/*SCHEME_MAX_SIZE + 1*/, schemeEnd);

    _scheme = String::cut(a_uri, schemeStart, schemeEnd);

    // [authority] - [example.com:8042]
    // [INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t authorityStart = schemeEnd + 1/*":"*/;

    size_t slashCount = 0;
    while (a_uri.at(authorityStart + slashCount) == '/') {
        slashCount ++;
    }

    size_t authorityEnd = a_uri.find_first_of(xT("/?#"), authorityStart + slashCount); // or by the end

    if (authorityEnd == std::tstring_t::npos) {
        authorityEnd = a_uri.size();
    }

    _authority = String::cut(a_uri, authorityStart /*+ slashCount*/, authorityEnd);

    // [_userInfo] - [userinfo]
    // [INPUT]     - userinfo@example.com:8042
    size_t userInfoStart = 0 + slashCount;
    size_t userInfoEnd   = _authority.find_first_of(xT("@"), userInfoStart);

    if (userInfoEnd != std::tstring_t::npos) {
        _userInfo = String::cut(_authority, userInfoStart, userInfoEnd);
    }

    // [_host] - [example.com]
    // [INPUT] -  userinfo@example.com:8042
    size_t hostStart = _authority.find_first_of(xT("@"));
    size_t hostEnd   = _authority.find_first_of(xT(":"));

    if (hostStart != std::tstring_t::npos) {
        if (hostEnd == std::tstring_t::npos) {
            hostEnd = _authority.size();
        }

        _host = String::cut(_authority, hostStart + 1/*"@"*/, hostEnd);
    }

    // [_sPort] - [8042]
    // [INPUT]  -  userinfo@example.com:8042
    size_t portStart = _authority.find_first_of(xT(":"));
    size_t portEnd   = _authority.size();

    if (portStart != std::tstring_t::npos) {
        std::tstring_t sRv = String::cut(_authority, portStart + 1/*":"*/, portEnd);
        _port = String::cast<ushort_t>(sRv);
    }
    if (0 == _port) {
        _port = _defaultPort();
    }

    // [_host] - [example.com]
    // [INPUT] -  userinfo@example.com:8042
    size_t authorityChars = _authority.find_first_of(xT("@:"));

    //���� � Authority ��� "@:" - _host ��� Authority ��� "//"
    if (authorityChars == std::tstring_t::npos) {
        _host = String::trimChars(_authority, xT("/"));
    }

    // [_path] - [/over/there?]
    // [INPUT] - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t pathStart = authorityEnd;
    size_t pathEnd   = a_uri.find_first_of(xT("?#"), pathStart);  // or by the end

    if (pathEnd == std::tstring_t::npos) {
        pathEnd = a_uri.size();
    }

    _path = String::cut(a_uri, pathStart, pathEnd);

    // [_query] - [name=ferret]
    // [INPUT]  - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t queryStart = pathEnd;
    size_t queryEnd   = a_uri.find_first_of(xT("#"), queryStart);

    if (queryEnd == std::tstring_t::npos) {
        queryEnd = a_uri.size();
    }

    _query = String::cut(a_uri, queryStart + 1/*"?"*/, queryEnd);

    // [_fragment] - [nose]
    // [INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t fragmentStart = queryEnd + std::tstring_t(xT("#")).size();
    size_t fragmentEnd   = a_uri.size();    // by the end

    _fragment = String::cut(a_uri, fragmentStart, fragmentEnd);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Uri::_normilize(
    std::ctstring_t &a_uri
)
{
    xUNUSED(a_uri);

    // TODO: Uri::_normilize()

    // trim
    // lowcase(_scheme)
    // remove dot-segment

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE ushort_t
Uri::_defaultPort() const
{
    if      (_scheme == xT("ftp")) {
        return 21;
    }
    else if (_scheme == xT("ssh")) {
        return 22;
    }
    else if (_scheme == xT("telnet")) {
        return 23;
    }
    else if (_scheme == xT("gopher")) {
        return 70;
    }
    else if (_scheme == xT("http")) {
        return 80;
    }
    else if (_scheme == xT("nntp")) {
        return 119;
    }
    else if (_scheme == xT("ldap")) {
        return 389;
    }
    else if (_scheme == xT("https")) {
        return 443;
    }
    else {
        return 0;
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Uri::_isDefaultPort() const
{
    return ( _port == _defaultPort() );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
