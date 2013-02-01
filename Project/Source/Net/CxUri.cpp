/**
 * \file  CxUri.cpp
 * \brief URI
 */


#include <xLib/Net/CxUri.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
* public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxUri
CxUri::CxUri() :
    _m_sScheme   (),
    _m_sAuthority(),
    _m_sUserInfo (),
    _m_sHost     (),
    _m_usPort    (0),
    _m_sPath     (),
    _m_sQuery    (),
    _m_sFragment ()
{

}
//---------------------------------------------------------------------------
//DONE: CxUri
CxUri::CxUri(const std::tstring_t &a_csUri) :
    _m_sScheme   (),
    _m_sAuthority(),
    _m_sUserInfo (),
    _m_sHost     (),
    _m_usPort    (0),
    _m_sPath     (),
    _m_sQuery    (),
    _m_sFragment ()
{
    _parse(a_csUri);
}
//---------------------------------------------------------------------------
//DONE: ~CxUri
CxUri::~CxUri() {

}
//---------------------------------------------------------------------------
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
std::tstring_t
CxUri::uri() const {
    

    std::tstring_t sRv;
    std::tstring_t sTemp;

    sTemp = scheme();
    if (false == sTemp.empty()) {
        sRv += xT("");
        sRv += sTemp;
    }

    sTemp = authority();
    if (false == sTemp.empty()) {
        sRv += xT(":");
        sRv += sTemp;
    }

    sTemp = path();
    if (false == sTemp.empty()) {
        sRv += xT("");
        sRv += sTemp;
    }

    sTemp = query();
    if (false == sTemp.empty()) {
        sRv += xT("?");
        sRv += sTemp;
    }

    sTemp = fragment();
    if (false == sTemp.empty()) {
        sRv += xT("#");
        sRv += sTemp;
    }

    return sRv;
}
void
CxUri::setUri(const std::tstring_t &a_csScheme, const std::tstring_t &a_csAuthority, const std::tstring_t &a_csPath, const std::tstring_t &a_csQuery, const std::tstring_t &a_csFragment) {
    

    setScheme   (a_csScheme);
    setAuthority(a_csAuthority);
    setPath     (a_csPath);
    setQuery    (a_csQuery);
    setFragment (a_csFragment);
}
//---------------------------------------------------------------------------
//TODO: scheme
std::tstring_t
CxUri::scheme() const {
    return encodeComponent(_m_sScheme);
}
void
CxUri::setScheme(const std::tstring_t &csScheme) {
    _m_sScheme = decodeComponent(csScheme);
}
//---------------------------------------------------------------------------
//DONE: authority
std::tstring_t
CxUri::authority() const {
    std::tstring_t sTempAuthority;

    sTempAuthority += xT("//");

    if (false == _m_sUserInfo.empty()) {
        sTempAuthority += _m_sUserInfo;
        sTempAuthority += xT("@");
    }

    if (false == _m_sHost.empty()) {
        sTempAuthority += _m_sHost;
    }

    if (0 < _m_usPort && false == _isDefaultPort()) {
        sTempAuthority += xT(":");
        sTempAuthority += CxString::cast(_m_usPort);
    }

    return encodeComponent(sTempAuthority/*_m_sAuthority*/);
}
void
CxUri::setAuthority(const std::tstring_t &csAuthority) {
    _m_sAuthority = decodeComponent(csAuthority);
}
//---------------------------------------------------------------------------
//DONE: userInfo
std::tstring_t
CxUri::userInfo() const {
    return encodeComponent(_m_sUserInfo);
}
void
CxUri::setUserInfo(const std::tstring_t &csUserInfo) {
    _m_sUserInfo = decodeComponent(csUserInfo);

    //TODO: bSetAuthority
}
//---------------------------------------------------------------------------
//DONE: host
std::tstring_t
CxUri::host() const {
    return encodeComponent(_m_sHost);
}
void
CxUri::setHost(const std::tstring_t &csHost) {
    _m_sHost = decodeComponent(csHost);

    //TODO: bSetAuthority
}
//---------------------------------------------------------------------------
//DONE: port
ushort_t
CxUri::port() {
    return _m_usPort;
}
void
CxUri::setPort(const ushort_t &cusPort) {
    _m_usPort = cusPort;

    //TODO: bSetAuthority
}
//---------------------------------------------------------------------------
//DONE: path
std::tstring_t
CxUri::path() const {
    return encodeComponent(_m_sPath);
}
void
CxUri::setPath(const std::tstring_t &csPath) {
    _m_sPath = decodeComponent(csPath);
}
//---------------------------------------------------------------------------
//DONE: query
std::tstring_t
CxUri::query() const {
    return encodeComponent(_m_sQuery);
}
void
CxUri::setQuery(const std::tstring_t &csQuery) {
    _m_sQuery = decodeComponent(csQuery);
}
//---------------------------------------------------------------------------
//DONE: fragment
std::tstring_t
CxUri::fragment() const {
    return encodeComponent(_m_sFragment);
}
void
CxUri::setFragment(const std::tstring_t &csFragment) {
    _m_sFragment = decodeComponent(csFragment);
}
//---------------------------------------------------------------------------
//DONE: bClear ()
void
CxUri::clear() {
    ////bool bRv = false;

    _m_sScheme.clear();
    _m_sAuthority.clear();
    _m_sUserInfo.clear();
    _m_sHost.clear();
    _m_usPort = 0;
    _m_sPath.clear();
    _m_sQuery.clear();
    _m_sFragment.clear();
}
//---------------------------------------------------------------------------
//TODO: escape ()
/* static */
std::tstring_t
CxUri::escape(const std::tstring_t &csUri) {
    

    /*
    int    c;

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

    sRv = csUri;



    return sRv;
}
//---------------------------------------------------------------------------
//TODO: unescape ()
/* static */
std::tstring_t
CxUri::unescape(const std::tstring_t &csUri) {
    

    std::tstring_t sRv;

    //TODO: unescape

    return sRv;
}
//---------------------------------------------------------------------------
//TODO: encodeComponent
//void URI::encode(const std::tstring_t& str, const std::tstring_t& reserved, std::tstring_t& encodedStr)
/* static */
std::tstring_t
CxUri::encodeComponent(const std::tstring_t &a_csUri) {
    std::tstring_t sRv;

    xFOREACH_CONST(std::tstring_t, it, a_csUri) {
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
//---------------------------------------------------------------------------
//TODO: decodeComponent
//void URI::decode(const std::tstring_t& str, std::tstring_t& decodedStr)
/* static */
std::tstring_t
CxUri::decodeComponent(const std::tstring_t &a_csUri) {
    std::tstring_t sRv;

    std::tstring_t::const_iterator it  = a_csUri.begin();
    std::tstring_t::const_iterator end = a_csUri.end();

    while (it != end) {
        tchar_t c = *it ++;

        if (c == '%') {
            if (it == end) {
                //throw SyntaxException("URI encoding: no hex digit following percent sign", csUri);
                xTEST_FAIL;
            }

            tchar_t hi = *it ++;

            if (it == end) {
                //throw SyntaxException("URI encoding: two hex digits must follow percent sign", csUri);
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
//---------------------------------------------------------------------------



/****************************************************************************
*    private
*
*****************************************************************************/

const std::tstring_t CxUri::RESERVED_PATH     = xT("?#");
const std::tstring_t CxUri::RESERVED_QUERY    = xT("#");
const std::tstring_t CxUri::RESERVED_FRAGMENT = xT("");
const std::tstring_t CxUri::ILLEGAL           = xT("%<>{}|\\\"^`");


//---------------------------------------------------------------------------
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
void
CxUri::_parse(const std::tstring_t &a_csUri) {
    //Normilize();

    clear();

    //-------------------------------------
    //[scheme] - [foo]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiSchemeStart = 0;
    size_t uiSchemeEnd   = a_csUri.find_first_of(CxConst::xCOLON);
    xTEST_DIFF(std::tstring_t::npos, uiSchemeEnd);
    xTEST_GR(size_t(7U)/*SCHEME_MAX_SIZE + 1*/, uiSchemeEnd);

    _m_sScheme = CxString::cut(a_csUri, uiSchemeStart, uiSchemeEnd);

    //-------------------------------------
    //[authority] - [example.com:8042]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiAuthorityStart = uiSchemeEnd + 1/*":"*/;

    //���� ����� [:] ���� [//] - ����������
    size_t uiSlashCount = 0;
    while ('/' == a_csUri.at(uiAuthorityStart + uiSlashCount)) {
        uiSlashCount ++;
    }

    size_t uiAuthorityEnd = a_csUri.find_first_of(xT("/?#"), uiAuthorityStart + uiSlashCount); //or by the end

    if (std::tstring_t::npos == uiAuthorityEnd) {
        uiAuthorityEnd = a_csUri.size();
    }

    _m_sAuthority = CxString::cut(a_csUri, uiAuthorityStart /*+ uiSlashCount*/, uiAuthorityEnd);

    //-------------------------------------
    //[_m_sUserInfo] - [userinfo]
    //[INPUT]        - userinfo@example.com:8042
    size_t uiUserInfoStart = 0 + uiSlashCount;
    size_t uiUserInfoEnd   = _m_sAuthority.find_first_of(xT("@"), uiUserInfoStart);

    if (std::tstring_t::npos != uiUserInfoEnd) {
        _m_sUserInfo = CxString::cut(_m_sAuthority, uiUserInfoStart, uiUserInfoEnd);
    }

    //-------------------------------------
    //[_m_sHost] - [example.com]
    //[INPUT]    -  userinfo@example.com:8042
    size_t uiHostStart = _m_sAuthority.find_first_of(xT("@"));
    size_t uiHostEnd   = _m_sAuthority.find_first_of(xT(":"));

    if (std::tstring_t::npos != uiHostStart) {
        //���� ��� �����
        if (std::tstring_t::npos == uiHostEnd) {
            uiHostEnd = _m_sAuthority.size();
        }

        _m_sHost = CxString::cut(_m_sAuthority, uiHostStart + 1/*"@"*/, uiHostEnd);
    }

    //-------------------------------------
    //[_sPort] - [8042]
    //[INPUT]  -  userinfo@example.com:8042
    size_t uiPortStart = _m_sAuthority.find_first_of(xT(":"));
    size_t uiPortEnd   = _m_sAuthority.size();

    if (std::tstring_t::npos != uiPortStart) {
        std::tstring_t sPort = CxString::cut(_m_sAuthority, uiPortStart + 1/*":"*/, uiPortEnd);
        _m_usPort = CxString::cast<ushort_t>(sPort);
    }
    if (0 == _m_usPort) {
        _m_usPort = _defaultPort();
    }

    //-------------------------------------
    //[_m_sHost] - [example.com] - ������ ������
    //[INPUT]    -  userinfo@example.com:8042
    size_t uiAuthorityChars = _m_sAuthority.find_first_of(xT("@:"));

    //���� � Authority ��� "@:" - _m_sHost ��� Authority ��� "//"
    if (std::tstring_t::npos == uiAuthorityChars) {
        _m_sHost = CxString::trimChars(_m_sAuthority, xT("/"));
    }

    //-------------------------------------
    //[_m_sPath] - [/over/there?]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiPathStart = uiAuthorityEnd;
    size_t uiPathEnd   = a_csUri.find_first_of(xT("?#"), uiPathStart);  //or by the end

    if (std::tstring_t::npos == uiPathEnd) {
        uiPathEnd = a_csUri.size();
    }

    _m_sPath = CxString::cut(a_csUri, uiPathStart, uiPathEnd);

    //-------------------------------------
    //[_m_sQuery] - [name=ferret]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiQueryStart = uiPathEnd;
    size_t uiQueryEnd   = a_csUri.find_first_of(xT("#"), uiQueryStart);

    if (std::tstring_t::npos == uiQueryEnd) {
        uiQueryEnd = a_csUri.size();
    }

    _m_sQuery = CxString::cut(a_csUri, uiQueryStart + 1/*"?"*/, uiQueryEnd);

    //-------------------------------------
    //[_m_sFragment] - [nose]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiFragmentStart = uiQueryEnd + std::tstring_t(xT("#")).size();
    size_t uiFragmentEnd   = a_csUri.size();                        //by the end

    _m_sFragment = CxString::cut(a_csUri, uiFragmentStart, uiFragmentEnd);
}
//---------------------------------------------------------------------------
//TODO: _bNormilize ()
void
CxUri::_normilize(const std::tstring_t &a_csUri) {
    ////bool bRv = false;

    //trim
    //lowcase(_m_sScheme)
    //remove dot-segment

    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: _defaultPort ()
ushort_t
CxUri::_defaultPort() const {
    if (       xT("ftp")    == _m_sScheme) {
        return 21;
    } else if (xT("ssh")    == _m_sScheme) {
        return 22;
    } else if (xT("telnet") == _m_sScheme) {
        return 23;
    } else if (xT("gopher") == _m_sScheme) {
        return 70;
    } else if (xT("http")   == _m_sScheme) {
        return 80;
    } else if (xT("nntp")   == _m_sScheme) {
        return 119;
    } else if (xT("ldap")   == _m_sScheme) {
        return 389;
    } else if (xT("https")  == _m_sScheme) {
        return 443;
    } else {
        return 0;
    }
}
//---------------------------------------------------------------------------
//TODO: _isDefaultPort ()
bool
CxUri::_isDefaultPort() const {
    return ( _m_usPort == _defaultPort() );
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
