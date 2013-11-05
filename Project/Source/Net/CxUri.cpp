/**
 * \file  CxUri.cpp
 * \brief URI
 */


#include <xLib/Net/CxUri.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
* public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxUri::CxUri() :
    _scheme   (),
    _authority(),
    _userInfo (),
    _host     (),
    _port    (0),
    _path     (),
    _query    (),
    _fragment ()
{
}
//------------------------------------------------------------------------------
xINLINE_HO
CxUri::CxUri(
    std::ctstring_t &a_uri
) :
    _scheme   (),
    _authority(),
    _userInfo (),
    _host     (),
    _port    (0),
    _path     (),
    _query    (),
    _fragment ()
{
    _parse(a_uri);
}
//------------------------------------------------------------------------------
//TODO: uri
/*
URI = scheme ":" hier-part [ "?" query ] [ "#" fragment ]

foo://userinfo@example.com:8042/over/there?name=ferret#nose
\_/   \_______________________/\_________/ \_________/ \__/
|                |                |            |       |
scheme        authority           path        query   fragment
*/

/*
http   : //ru.wikipedia.org/wiki/URI
ftp    : //ftp.is.co.za/rfc/rfc1808.txt
file   : //C:\UserName.HostName\Projects\Wikipedia_Articles\URI.xml
ldap   : //[2001:db8::7]/c=GB                                       ? objectClass?one

mailto : John.Doe@example.com
sip    : 911@pbx.mycompany.com
news   : comp.infosystems.www.servers.unix
data   : text/plain;charset=iso-8859-7,%be%fg%be
tel    : +1-816-555-1212
telnet : //192.0.2.16:80/
*/
xINLINE_HO std::tstring_t
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
xINLINE_HO void_t
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
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxUri::scheme() const
{
    return encodeComponent(_scheme);
}
void_t
CxUri::setScheme(
    std::ctstring_t &scheme
)
{
    _scheme = decodeComponent(scheme);
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
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
xINLINE_HO void_t
CxUri::setAuthority(
    std::ctstring_t &authority
)
{
    _authority = decodeComponent(authority);
}
//------------------------------------------------------------------------------
//DONE: userInfo
std::tstring_t
CxUri::userInfo() const
{
    return encodeComponent(_userInfo);
}
xINLINE_HO void_t
CxUri::setUserInfo(
    std::ctstring_t &userInfo
)
{
    _userInfo = decodeComponent(userInfo);

    //TODO: bSetAuthority
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxUri::host() const
{
    return encodeComponent(_host);
}
xINLINE_HO void_t
CxUri::setHost(
    std::ctstring_t &host
)
{
    _host = decodeComponent(host);

    //TODO: bSetAuthority
}
//------------------------------------------------------------------------------
xINLINE_HO ushort_t
CxUri::port()
{
    return _port;
}
xINLINE_HO void_t
CxUri::setPort(
    cushort_t &port
)
{
    _port = port;

    //TODO: bSetAuthority
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxUri::path() const
{
    return encodeComponent(_path);
}
xINLINE_HO void_t
CxUri::setPath(
    std::ctstring_t &path
)
{
    _path = decodeComponent(path);
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxUri::query() const
{
    return encodeComponent(_query);
}
xINLINE_HO void_t
CxUri::setQuery(
    std::ctstring_t &query
)
{
    _query = decodeComponent(query);
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxUri::fragment() const
{
    return encodeComponent(_fragment);
}
xINLINE_HO void_t
CxUri::setFragment(
    std::ctstring_t &fragment
)
{
    _fragment = decodeComponent(fragment);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxUri::clear()
{
    ////bool_t bRv = false;

    _scheme.clear();
    _authority.clear();
    _userInfo.clear();
    _host.clear();
    _port = 0;
    _path.clear();
    _query.clear();
    _fragment.clear();
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxUri::escape(
    std::ctstring_t &uri
)
{


    /*
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
                if (fputc(c, fw) == EOF)
                    return EOF;
                break;
        }
    }

    return 0;
    */


    std::tstring_t sRv;

    sRv = uri;



    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxUri::unescape(
    std::ctstring_t &uri
)
{


    std::tstring_t sRv;

    //TODO: unescape

    return sRv;
}
//------------------------------------------------------------------------------
//TODO: encodeComponent
//void_t URI::encode(std::ctstring_t& str, std::ctstring_t& reserved, std::tstring_t& encodedStr)
/* static */
xINLINE_HO std::tstring_t
CxUri::encodeComponent(
    std::ctstring_t &a_uri
)
{
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
        RESERVED_PATH     = "?#";
        RESERVED_QUERY    = "#";
        RESERVED_FRAGMENT = "";
        ILLEGAL           = "%<>{}|\\\"^`";
        */
        else if (c <= 0x20 || c >= 0x7F || ILLEGAL.find(c) != std::tstring_t::npos /*|| reserved.find(c) != std::tstring_t::npos*/) {
            //� -> %FF
            sRv += CxString::format(xT("%%%02X"), (uint_t)(uchar_t)c);
        }
        else {
            sRv += c;
        }
    }

    return sRv;
}
//------------------------------------------------------------------------------
//TODO: decodeComponent
//void_t URI::decode(std::ctstring_t& str, std::tstring_t& decodedStr)
/* static */
xINLINE_HO std::tstring_t
CxUri::decodeComponent(
    std::ctstring_t &a_uri
)
{
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
                //throw SyntaxException("URI encoding: two hex digits must follow percent sign", uri);
                xTEST_FAIL;
            }

            tchar_t lo = *it ++;

            if (       hi >= '0' && hi <= '9') {
                c = hi - '0';
            } else if (hi >= 'A' && hi <= 'F') {
                c = hi - 'A' + 10;
            } else if (hi >= 'a' && hi <= 'f') {
                c = hi - 'a' + 10;
            } else {
                //throw SyntaxException("URI encoding: not a hex digit");
                xTEST_FAIL;
            }

            c *= 16;

            if (       lo >= '0' && lo <= '9') {
                c += lo - '0';
            } else if (lo >= 'A' && lo <= 'F') {
                c += lo - 'A' + 10;
            } else if (lo >= 'a' && lo <= 'f') {
                c += lo - 'a' + 10;
            } else {
                //throw SyntaxException("URI encoding: not a hex digit");
                xTEST_FAIL;
            }
        }

        sRv += c;
    }

    return sRv;
}
//------------------------------------------------------------------------------



/*******************************************************************************
*    private
*
*******************************************************************************/

std::ctstring_t CxUri::RESERVED_PATH     = xT("?#");
std::ctstring_t CxUri::RESERVED_QUERY    = xT("#");
std::ctstring_t CxUri::RESERVED_FRAGMENT = xT("");
std::ctstring_t CxUri::ILLEGAL           = xT("%<>{}|\\\"^`");


//------------------------------------------------------------------------------
//TODO: bParse (������ URI)
/*
URI = scheme ":" hier-part [ "?" query ] [ "#" fragment ]

foo://userinfo@example.com:8042/over/there?name=ferret#nose
\_/   \_______________________/\_________/ \_________/ \__/
|                |                |            |       |
scheme        authority           path        query   fragment
*/

/*
http   : //ru.wikipedia.org/wiki/URI
ftp    : //ftp.is.co.za/rfc/rfc1808.txt
file   : //C:\UserName.HostName\Projects\Wikipedia_Articles\URI.xml
ldap   : //[2001:db8::7]/c=GB                                       ? objectClass?one

mailto : John.Doe@example.com
sip    : 911@pbx.mycompany.com
news   : comp.infosystems.www.servers.unix
data   : text/plain;charset=iso-8859-7,%be%fg%be
tel    : +1-816-555-1212
telnet : //192.0.2.16:80/
*/
xINLINE_HO void_t
CxUri::_parse(
    std::ctstring_t &a_uri
)
{
    //Normilize();

    clear();

    //-------------------------------------
    //[scheme] - [foo]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t schemeStart = 0;
    size_t schemeEnd   = a_uri.find_first_of(CxConst::xCOLON());
    xTEST_DIFF(std::tstring_t::npos, schemeEnd);
    xTEST_GR(size_t(7U)/*SCHEME_MAX_SIZE + 1*/, schemeEnd);

    _scheme = CxString::cut(a_uri, schemeStart, schemeEnd);

    //-------------------------------------
    //[authority] - [example.com:8042]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t authorityStart = schemeEnd + 1/*":"*/;

    //���� ����� [:] ���� [//] - ����������
    size_t slashCount = 0;
    while ('/' == a_uri.at(authorityStart + slashCount)) {
        slashCount ++;
    }

    size_t authorityEnd = a_uri.find_first_of(xT("/?#"), authorityStart + slashCount); //or by the end

    if (std::tstring_t::npos == authorityEnd) {
        authorityEnd = a_uri.size();
    }

    _authority = CxString::cut(a_uri, authorityStart /*+ slashCount*/, authorityEnd);

    //-------------------------------------
    //[_userInfo] - [userinfo]
    //[INPUT]        - userinfo@example.com:8042
    size_t uiUserInfoStart = 0 + slashCount;
    size_t uiUserInfoEnd   = _authority.find_first_of(xT("@"), uiUserInfoStart);

    if (std::tstring_t::npos != uiUserInfoEnd) {
        _userInfo = CxString::cut(_authority, uiUserInfoStart, uiUserInfoEnd);
    }

    //-------------------------------------
    //[_host] - [example.com]
    //[INPUT]    -  userinfo@example.com:8042
    size_t hostStart = _authority.find_first_of(xT("@"));
    size_t hostEnd   = _authority.find_first_of(xT(":"));

    if (std::tstring_t::npos != hostStart) {
        //���� ��� �����
        if (std::tstring_t::npos == hostEnd) {
            hostEnd = _authority.size();
        }

        _host = CxString::cut(_authority, hostStart + 1/*"@"*/, hostEnd);
    }

    //-------------------------------------
    //[_sPort] - [8042]
    //[INPUT]  -  userinfo@example.com:8042
    size_t portStart = _authority.find_first_of(xT(":"));
    size_t portEnd   = _authority.size();

    if (std::tstring_t::npos != portStart) {
        std::tstring_t sPort = CxString::cut(_authority, portStart + 1/*":"*/, portEnd);
        _port = CxString::cast<ushort_t>(sPort);
    }
    if (0 == _port) {
        _port = _defaultPort();
    }

    //-------------------------------------
    //[_host] - [example.com] - ������ ������
    //[INPUT]    -  userinfo@example.com:8042
    size_t authorityChars = _authority.find_first_of(xT("@:"));

    //���� � Authority ��� "@:" - _host ��� Authority ��� "//"
    if (std::tstring_t::npos == authorityChars) {
        _host = CxString::trimChars(_authority, xT("/"));
    }

    //-------------------------------------
    //[_path] - [/over/there?]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t pathStart = authorityEnd;
    size_t pathEnd   = a_uri.find_first_of(xT("?#"), pathStart);  //or by the end

    if (std::tstring_t::npos == pathEnd) {
        pathEnd = a_uri.size();
    }

    _path = CxString::cut(a_uri, pathStart, pathEnd);

    //-------------------------------------
    //[_query] - [name=ferret]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t queryStart = pathEnd;
    size_t queryEnd   = a_uri.find_first_of(xT("#"), queryStart);

    if (std::tstring_t::npos == queryEnd) {
        queryEnd = a_uri.size();
    }

    _query = CxString::cut(a_uri, queryStart + 1/*"?"*/, queryEnd);

    //-------------------------------------
    //[_fragment] - [nose]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t fragmentStart = queryEnd + std::tstring_t(xT("#")).size();
    size_t fragmentEnd   = a_uri.size();                        //by the end

    _fragment = CxString::cut(a_uri, fragmentStart, fragmentEnd);
}
//------------------------------------------------------------------------------
//TODO: _bNormilize ()
xINLINE_HO void_t
CxUri::_normilize(
    std::ctstring_t &a_uri
)
{
    ////bool_t bRv = false;

    //trim
    //lowcase(_scheme)
    //remove dot-segment

    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: _defaultPort ()
xINLINE_HO ushort_t
CxUri::_defaultPort() const
{
    if (       xT("ftp")    == _scheme) {
        return 21;
    } else if (xT("ssh")    == _scheme) {
        return 22;
    } else if (xT("telnet") == _scheme) {
        return 23;
    } else if (xT("gopher") == _scheme) {
        return 70;
    } else if (xT("http")   == _scheme) {
        return 80;
    } else if (xT("nntp")   == _scheme) {
        return 119;
    } else if (xT("ldap")   == _scheme) {
        return 389;
    } else if (xT("https")  == _scheme) {
        return 443;
    } else {
        return 0;
    }
}
//------------------------------------------------------------------------------
//TODO: _isDefaultPort ()
xINLINE_HO bool_t
CxUri::_isDefaultPort() const
{
    return ( _port == _defaultPort() );
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
