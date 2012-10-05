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
CxUri::CxUri(const std::string &a_csUri) :
    _m_sScheme   (),
    _m_sAuthority(),
    _m_sUserInfo (),
    _m_sHost     (),
    _m_usPort    (0),
    _m_sPath     (),
    _m_sQuery    (),
    _m_sFragment ()
{
    _vParse(a_csUri);
}
//---------------------------------------------------------------------------
//DONE: ~CxUri
CxUri::~CxUri() {

}
//---------------------------------------------------------------------------
//TODO: sGetUri
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
std::string
CxUri::sGetUri() const {
    /*DEBUG*/

    std::string sRv;
    std::string sTemp;

    sTemp = sGetScheme();
    if (false == sTemp.empty()) {
        sRv += "";
        sRv += sTemp;
    }

    sTemp = sGetAuthority();
    if (false == sTemp.empty()) {
        sRv += ":";
        sRv += sTemp;
    }

    sTemp = sGetPath();
    if (false == sTemp.empty()) {
        sRv += "";
        sRv += sTemp;
    }

    sTemp = sGetQuery();
    if (false == sTemp.empty()) {
        sRv += "?";
        sRv += sTemp;
    }

    sTemp = sGetFragment();
    if (false == sTemp.empty()) {
        sRv += "#";
        sRv += sTemp;
    }

    return sRv;
}
void
CxUri::vSetUri(const std::string &a_csScheme, const std::string &a_csAuthority, const std::string &a_csPath, const std::string &a_csQuery, const std::string &a_csFragment) {
    /*DEBUG*/

    vSetScheme   (a_csScheme);
    vSetAuthority(a_csAuthority);
    vSetPath     (a_csPath);
    vSetQuery    (a_csQuery);
    vSetFragment (a_csFragment);
}
//---------------------------------------------------------------------------
//TODO: sGetScheme
std::string
CxUri::sGetScheme() const {
    return sEncodeComponent(_m_sScheme);
}
void
CxUri::vSetScheme(const std::string &csScheme) {
    _m_sScheme = sDecodeComponent(csScheme);
}
//---------------------------------------------------------------------------
//DONE: sGetAuthority
std::string
CxUri::sGetAuthority() const {
    std::string sTempAuthority;

    sTempAuthority += "//";

    if (false == _m_sUserInfo.empty()) {
        sTempAuthority += _m_sUserInfo;
        sTempAuthority += "@";
    }

    if (false == _m_sHost.empty()) {
        sTempAuthority += _m_sHost;
    }

    if (0 < _m_usPort && false == _bIsDefaultPort()) {
        sTempAuthority += ":";
        sTempAuthority += CxString::string_cast(_m_usPort);
    }

    return sEncodeComponent(sTempAuthority/*_m_sAuthority*/);
}
void
CxUri::vSetAuthority(const std::string &csAuthority) {
    _m_sAuthority = sDecodeComponent(csAuthority);
}
//---------------------------------------------------------------------------
//DONE: sGetUserInfo
std::string
CxUri::sGetUserInfo() const {
    return sEncodeComponent(_m_sUserInfo);
}
void
CxUri::vSetUserInfo(const std::string &csUserInfo) {
    _m_sUserInfo = sDecodeComponent(csUserInfo);

    //TODO: bSetAuthority
}
//---------------------------------------------------------------------------
//DONE: sGetHost
std::string
CxUri::sGetHost() const {
    return sEncodeComponent(_m_sHost);
}
void
CxUri::vSetHost(const std::string &csHost) {
    _m_sHost = sDecodeComponent(csHost);

    //TODO: bSetAuthority
}
//---------------------------------------------------------------------------
//DONE: usGetPort
ushort_t
CxUri::usGetPort() {
    return _m_usPort;
}
void
CxUri::vSetPort(const ushort_t &cusPort) {
    _m_usPort = cusPort;

    //TODO: bSetAuthority
}
//---------------------------------------------------------------------------
//DONE: sGetPath
std::string
CxUri::sGetPath() const {
    return sEncodeComponent(_m_sPath);
}
void
CxUri::vSetPath(const std::string &csPath) {
    _m_sPath = sDecodeComponent(csPath);
}
//---------------------------------------------------------------------------
//DONE: sGetQuery
std::string
CxUri::sGetQuery() const {
    return sEncodeComponent(_m_sQuery);
}
void
CxUri::vSetQuery(const std::string &csQuery) {
    _m_sQuery = sDecodeComponent(csQuery);
}
//---------------------------------------------------------------------------
//DONE: sGetFragment
std::string
CxUri::sGetFragment() const {
    return sEncodeComponent(_m_sFragment);
}
void
CxUri::vSetFragment(const std::string &csFragment) {
    _m_sFragment = sDecodeComponent(csFragment);
}
//---------------------------------------------------------------------------
//DONE: bClear ()
void
CxUri::vClear() {
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
//TODO: sEscape ()
/* static */
std::string
CxUri::sEscape(const std::string &csUri) {
    /*DEBUG*/

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


    std::string sRv;

    sRv = csUri;



    return sRv;
}
//---------------------------------------------------------------------------
//TODO: sUnescape ()
/* static */
std::string
CxUri::sUnescape(const std::string &csUri) {
    /*DEBUG*/

    std::string sRv;

    //TODO: sUnescape

    return sRv;
}
//---------------------------------------------------------------------------
//TODO: sEncodeComponent
//void URI::encode(const std::string& str, const std::string& reserved, std::string& encodedStr)
/* static */
std::string
CxUri::sEncodeComponent(const std::string &a_csUri) {
    std::string sRv;

    xFOREACH_CONST(std::string, it, a_csUri) {
        char c = *it;

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
        else if (c <= 0x20 || c >= 0x7F || ILLEGAL.find(c) != std::string::npos /*|| reserved.find(c) != std::string::npos*/) {
            //� -> %FF
            sRv += CxString::sFormat(xT("%%%02X"), (uint_t)(uchar_t)c);
        }
        else {
            sRv += c;
        }
    }

    return sRv;
}
//---------------------------------------------------------------------------
//TODO: sDecodeComponent
//void URI::decode(const std::string& str, std::string& decodedStr)
/* static */
std::string
CxUri::sDecodeComponent(const std::string &a_csUri) {
    std::string sRv;

    std::string::const_iterator it  = a_csUri.begin();
    std::string::const_iterator end = a_csUri.end();

    while (it != end) {
        char c = *it ++;

        if (c == '%') {
            if (it == end) {
                //throw SyntaxException("URI encoding: no hex digit following percent sign", csUri);
                /*DEBUG*/xTEST_FAIL;
            }

            char hi = *it ++;

            if (it == end) {
                //throw SyntaxException("URI encoding: two hex digits must follow percent sign", csUri);
                /*DEBUG*/xTEST_FAIL;
            }

            char lo = *it ++;

            if (       hi >= '0' && hi <= '9') {
                c = hi - '0';
            } else if (hi >= 'A' && hi <= 'F') {
                c = hi - 'A' + 10;
            } else if (hi >= 'a' && hi <= 'f') {
                c = hi - 'a' + 10;
            } else {
                //throw SyntaxException("URI encoding: not a hex digit");
                /*DEBUG*/xTEST_FAIL;
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
                /*DEBUG*/xTEST_FAIL;
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

const std::string CxUri::RESERVED_PATH     = "?#";
const std::string CxUri::RESERVED_QUERY    = "#";
const std::string CxUri::RESERVED_FRAGMENT = "";
const std::string CxUri::ILLEGAL           = "%<>{}|\\\"^`";


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
CxUri::_vParse(const std::string &a_csUri) {
    //Normilize();

    vClear();

    //-------------------------------------
    //[scheme] - [foo]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiSchemeStart = 0;
    size_t uiSchemeEnd   = a_csUri.find_first_of(CxConst::xCOLON);
    /*DEBUG*/xTEST_DIFF(std::string::npos, uiSchemeEnd);
    /*DEBUG*/xTEST_GR(size_t(7U)/*SCHEME_MAX_SIZE + 1*/, uiSchemeEnd);

    _m_sScheme = CxString::sCut(a_csUri, uiSchemeStart, uiSchemeEnd);

    //-------------------------------------
    //[authority] - [example.com:8042]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiAuthorityStart = uiSchemeEnd + 1/*":"*/;

    //���� ����� [:] ���� [//] - ����������
    size_t uiSlashCount = 0;
    while ('/' == a_csUri.at(uiAuthorityStart + uiSlashCount)) {
        uiSlashCount ++;
    }

    size_t uiAuthorityEnd = a_csUri.find_first_of("/?#", uiAuthorityStart + uiSlashCount); //or by the end

    if (std::string::npos == uiAuthorityEnd) {
        uiAuthorityEnd = a_csUri.size();
    }

    _m_sAuthority = CxString::sCut(a_csUri, uiAuthorityStart /*+ uiSlashCount*/, uiAuthorityEnd);

    //-------------------------------------
    //[_m_sUserInfo] - [userinfo]
    //[INPUT]        - userinfo@example.com:8042
    size_t uiUserInfoStart = 0 + uiSlashCount;
    size_t uiUserInfoEnd   = _m_sAuthority.find_first_of("@", uiUserInfoStart);

    if (std::string::npos != uiUserInfoEnd) {
        _m_sUserInfo = CxString::sCut(_m_sAuthority, uiUserInfoStart, uiUserInfoEnd);
    }

    //-------------------------------------
    //[_m_sHost] - [example.com]
    //[INPUT]    -  userinfo@example.com:8042
    size_t uiHostStart = _m_sAuthority.find_first_of("@");
    size_t uiHostEnd   = _m_sAuthority.find_first_of(":");

    if (std::string::npos != uiHostStart) {
        //���� ��� �����
        if (std::string::npos == uiHostEnd) {
            uiHostEnd = _m_sAuthority.size();
        }

        _m_sHost = CxString::sCut(_m_sAuthority, uiHostStart + 1/*"@"*/, uiHostEnd);
    }

    //-------------------------------------
    //[_sPort] - [8042]
    //[INPUT]  -  userinfo@example.com:8042
    size_t uiPortStart = _m_sAuthority.find_first_of(":");
    size_t uiPortEnd   = _m_sAuthority.size();

    if (std::string::npos != uiPortStart) {
        std::string sPort = CxString::sCut(_m_sAuthority, uiPortStart + 1/*":"*/, uiPortEnd);
        _m_usPort = CxString::string_cast<ushort_t>(sPort);
    }
    if (0 == _m_usPort) {
        _m_usPort = _usGetDefaultPort();
    }

    //-------------------------------------
    //[_m_sHost] - [example.com] - ������ ������
    //[INPUT]    -  userinfo@example.com:8042
    size_t uiAuthorityChars = _m_sAuthority.find_first_of("@:");

    //���� � Authority ��� "@:" - _m_sHost ��� Authority ��� "//"
    if (std::string::npos == uiAuthorityChars) {
        _m_sHost = CxString::sTrimChars(_m_sAuthority, "/");
    }

    //-------------------------------------
    //[_m_sPath] - [/over/there?]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiPathStart = uiAuthorityEnd;
    size_t uiPathEnd   = a_csUri.find_first_of("?#", uiPathStart);  //or by the end

    if (std::string::npos == uiPathEnd) {
        uiPathEnd = a_csUri.size();
    }

    _m_sPath = CxString::sCut(a_csUri, uiPathStart, uiPathEnd);

    //-------------------------------------
    //[_m_sQuery] - [name=ferret]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiQueryStart = uiPathEnd;
    size_t uiQueryEnd   = a_csUri.find_first_of("#", uiQueryStart);

    if (std::string::npos == uiQueryEnd) {
        uiQueryEnd = a_csUri.size();
    }

    _m_sQuery = CxString::sCut(a_csUri, uiQueryStart + 1/*"?"*/, uiQueryEnd);

    //-------------------------------------
    //[_m_sFragment] - [nose]
    //[INPUT]     - foo://userinfo@example.com:8042/over/there?name=ferret#nose
    size_t uiFragmentStart = uiQueryEnd + std::string("#").size();
    size_t uiFragmentEnd   = a_csUri.size();                        //by the end

    _m_sFragment = CxString::sCut(a_csUri, uiFragmentStart, uiFragmentEnd);
}
//---------------------------------------------------------------------------
//TODO: _bNormilize ()
void
CxUri::_vNormilize(const std::string &a_csUri) {
    ////bool bRv = false;

    //trim
    //lowcase(_m_sScheme)
    //remove dot-segment

    xNOT_IMPLEMENTED;
}
//---------------------------------------------------------------------------
//TODO: _usGetDefaultPort ()
ushort_t
CxUri::_usGetDefaultPort() const {
    if (       "ftp"    == _m_sScheme) {
        return 21;
    } else if ("ssh"    == _m_sScheme) {
        return 22;
    } else if ("telnet" == _m_sScheme) {
        return 23;
    } else if ("gopher" == _m_sScheme) {
        return 70;
    } else if ("http"   == _m_sScheme) {
        return 80;
    } else if ("nntp"   == _m_sScheme) {
        return 119;
    } else if ("ldap"   == _m_sScheme) {
        return 389;
    } else if ("https"  == _m_sScheme) {
        return 443;
    } else {
        return 0;
    }
}
//---------------------------------------------------------------------------
//TODO: _bIsDefaultPort ()
bool
CxUri::_bIsDefaultPort() const {
    return ( _m_usPort == _usGetDefaultPort() );
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
