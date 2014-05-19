/**
 * \file  CxUri.inl
 * \brief URI (RFC 3986)
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
* public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxUri::CxUri() :
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
inline
CxUri::CxUri(
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
// TODO: CxUri::uri()
/**
 * URI = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
 *
 * foo://userinfo@example.com:8042/over/there?name=ferret#nose
 * \_/   \_______________________/\_________/ \_________/ \__/
 * |                |                |            |       |
 * scheme        authority           path        query   fragment
 */
inline std::tstring_t
CxUri::uri() const
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
inline void_t
CxUri::setUri(
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
inline std::tstring_t
CxUri::scheme() const
{
    return encodeComponent(_scheme);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::setScheme(
    std::ctstring_t &a_scheme
)
{
    _scheme = decodeComponent(a_scheme);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxUri::authority() const
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
        tempAuthority += CxString::cast(_port);
    }

    return encodeComponent(tempAuthority/*_authority*/);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::setAuthority(
    std::ctstring_t &a_authority
)
{
    _authority = decodeComponent(a_authority);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxUri::userInfo() const
{
    return encodeComponent(_userInfo);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::setUserInfo(
    std::ctstring_t &a_userInfo
)
{
    _userInfo = decodeComponent(a_userInfo);

    // TODO: setAuthority
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxUri::host() const
{
    return encodeComponent(_host);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::setHost(
    std::ctstring_t &a_host
)
{
    _host = decodeComponent(a_host);

    // TODO: setAuthority
}
//-------------------------------------------------------------------------------------------------
inline ushort_t
CxUri::port()
{
    return _port;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::setPort(
    cushort_t &a_port
)
{
    _port = a_port;

    // TODO: CxUri::setPort() - setAuthority
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxUri::path() const
{
    return encodeComponent(_path);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::setPath(
    std::ctstring_t &a_path
)
{
    _path = decodeComponent(a_path);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxUri::query() const
{
    return encodeComponent(_query);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::setQuery(
    std::ctstring_t &a_query
)
{
    _query = decodeComponent(a_query);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxUri::fragment() const
{
    return encodeComponent(_fragment);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::setFragment(
    std::ctstring_t &a_fragment
)
{
    _fragment = decodeComponent(a_fragment);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::clear()
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
inline std::tstring_t
CxUri::escape(
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
inline std::tstring_t
CxUri::unescape(
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
inline std::tstring_t
CxUri::encodeComponent(
    std::ctstring_t &a_uri
)
{
    // TODO: CxUri::encodeComponent()

    std::tstring_t sRv;

    xFOREACH_CONST(std::tstring_t, it, a_uri) {
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
            sRv += CxString::format(xT("%%%02X"), (uint_t)(uchar_t)c);
        }
        else {
            sRv += c;
        }
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxUri::decodeComponent(
    std::ctstring_t &a_uri
)
{
    // TODO: CxUri::decodeComponent()

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
inline std::ctstring_t &
CxUri::_reservedPath()
{
    static std::ctstring_t sRv(xT("?#"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxUri::_reservedQuery()
{
    static std::ctstring_t sRv(xT("#"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxUri::_reservedFragment()
{
    static std::ctstring_t sRv(xT(""));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxUri::_illegal()
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
inline void_t
CxUri::_parse(
    std::ctstring_t &a_uri
)
{
    // TODO: CxUri::_parse()

    // normilize();

    clear();

    // [scheme] - [foo]
    // [INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t schemeStart = 0;
    size_t schemeEnd   = a_uri.find_first_of(CxConst::colon());
    xTEST_DIFF(schemeEnd, std::tstring_t::npos);
    xTEST_GR(size_t(7U)/*SCHEME_MAX_SIZE + 1*/, schemeEnd);

    _scheme = CxString::cut(a_uri, schemeStart, schemeEnd);

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

    _authority = CxString::cut(a_uri, authorityStart /*+ slashCount*/, authorityEnd);

    // [_userInfo] - [userinfo]
    // [INPUT]     - userinfo@example.com:8042
    size_t userInfoStart = 0 + slashCount;
    size_t userInfoEnd   = _authority.find_first_of(xT("@"), userInfoStart);

    if (userInfoEnd != std::tstring_t::npos) {
        _userInfo = CxString::cut(_authority, userInfoStart, userInfoEnd);
    }

    // [_host] - [example.com]
    // [INPUT] -  userinfo@example.com:8042
    size_t hostStart = _authority.find_first_of(xT("@"));
    size_t hostEnd   = _authority.find_first_of(xT(":"));

    if (hostStart != std::tstring_t::npos) {
        if (hostEnd == std::tstring_t::npos) {
            hostEnd = _authority.size();
        }

        _host = CxString::cut(_authority, hostStart + 1/*"@"*/, hostEnd);
    }

    // [_sPort] - [8042]
    // [INPUT]  -  userinfo@example.com:8042
    size_t portStart = _authority.find_first_of(xT(":"));
    size_t portEnd   = _authority.size();

    if (portStart != std::tstring_t::npos) {
        std::tstring_t sRv = CxString::cut(_authority, portStart + 1/*":"*/, portEnd);
        _port = CxString::cast<ushort_t>(sRv);
    }
    if (0 == _port) {
        _port = _defaultPort();
    }

    // [_host] - [example.com]
    // [INPUT] -  userinfo@example.com:8042
    size_t authorityChars = _authority.find_first_of(xT("@:"));

    //���� � Authority ��� "@:" - _host ��� Authority ��� "//"
    if (authorityChars == std::tstring_t::npos) {
        _host = CxString::trimChars(_authority, xT("/"));
    }

    // [_path] - [/over/there?]
    // [INPUT] - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t pathStart = authorityEnd;
    size_t pathEnd   = a_uri.find_first_of(xT("?#"), pathStart);  // or by the end

    if (pathEnd == std::tstring_t::npos) {
        pathEnd = a_uri.size();
    }

    _path = CxString::cut(a_uri, pathStart, pathEnd);

    // [_query] - [name=ferret]
    // [INPUT]  - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t queryStart = pathEnd;
    size_t queryEnd   = a_uri.find_first_of(xT("#"), queryStart);

    if (queryEnd == std::tstring_t::npos) {
        queryEnd = a_uri.size();
    }

    _query = CxString::cut(a_uri, queryStart + 1/*"?"*/, queryEnd);

    // [_fragment] - [nose]
    // [INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t fragmentStart = queryEnd + std::tstring_t(xT("#")).size();
    size_t fragmentEnd   = a_uri.size();    // by the end

    _fragment = CxString::cut(a_uri, fragmentStart, fragmentEnd);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxUri::_normilize(
    std::ctstring_t &a_uri
)
{
    xUNUSED(a_uri);

    // TODO: CxUri::_normilize()

    // trim
    // lowcase(_scheme)
    // remove dot-segment

    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
inline ushort_t
CxUri::_defaultPort() const
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
inline bool_t
CxUri::_isDefaultPort() const
{
    return ( _port == _defaultPort() );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
