/**
 * \file  CxCgi.cpp
 * \brief CGI
 */


#include <xLib/Core/CxUtils.h>
#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/System/CxEnvironment.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Net/CxCookiePv0.h>
#include <xLib/Net/CxCookiePv1.h>


xNAMESPACE_BEGIN(xlib)

using namespace NxCgi;


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxCgi::CxCgi(
    std::csize_t &a_maxSize
) :
    Environment(*this),
    Cookies    (*this),
    Formdata   (*this, a_maxSize)
{
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxCgi::dump() const
{
    std::tstring_t sRv;

    sRv = CxString::format(
            xT("[CGI dump]\n\n")
            xT("%s\n")
            xT("%s\n")
            xT("%s\n"),
            Environment.dump().c_str(),
            Cookies.dump().c_str(),
            Formdata.dump().c_str()
    );

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxCgi::redirect(
    std::ctstring_t &a_url
)
{
    xTEST_EQ(false, a_url.empty())

    std::tstring_t httpResponse;

    httpResponse.append( CxString::format(xT("Location: %s\n"), a_url.c_str()) );
    httpResponse.append( CxConst::nl() );

    std::tcout << httpResponse << std::endl;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxCgi::pageShow(
    std::ctstring_t &a_filePath
)
{
    std::tstring_t fileContent;

    CxFile::textRead(a_filePath, &fileContent);

    std::tcout << fileContent << std::endl;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private: encoding, decoding
*
**************************************************************************************************/

namespace {
    std::ctstring_t URI_ILLEGAL = xT("%<>{}|\\\"^`");
    //// static std::ctstring_t ILLEGAL_CHARS = xT("()[]/|\\',;");     //for cookie
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxCgi::uriEncode(
    std::ctstring_t &a_uri,
    std::ctstring_t &a_reserved,
    std::tstring_t  *a_encodedStr
)
{
    // TODO: CxCgi::uriEncode()

    xFOREACH_CONST(std::tstring_t, it, a_uri) {
        tchar_t ch = *it;

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') ||
             ch == '-' || ch == '_'  || ch == '.' || ch == '~')
        {
            (*a_encodedStr) += ch;
        }
        else if (ch <= 0x20 || ch >= 0x7F || std::tstring_t::npos != URI_ILLEGAL.find(ch) ||
            std::tstring_t::npos != a_reserved.find(ch))
        {
            (*a_encodedStr) += '%';
            //--encodedStr += NumberFormatter::formatHex((unsigned) (unsigned char) ch, 2);

            /*
                poco_assert (width > 0 && width < 64);

                char buffer[64];
                std::sprintf(buffer, "%0*X", width, value);
                str.append(buffer);
             */
            (*a_encodedStr) += CxString::format(xT("%0*X"), 2, (uint_t)(uchar_t)ch);
        }
        else {
            (*a_encodedStr) += ch;
        }
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxCgi::uriDecode(
    std::ctstring_t &a_uri,
    std::tstring_t  *a_decodedStr
)
{
    //TODO: CxCgi::uriDecode()

    std::tstring_t::const_iterator it  = a_uri.begin();
    std::tstring_t::const_iterator end = a_uri.end();

    while (it != end) {
        tchar_t ch = *it++;

        if (ch == '%') {
            if (it == end) {
                ////throw SyntaxException("URI encoding: no hex digit following percent sign", str);
                xTEST_FAIL;
            }

            tchar_t hi = *it++;
            if (it == end) {
                ////throw SyntaxException("URI encoding: two hex digits must follow percent sign", str);
                xTEST_FAIL;
            }

            tchar_t lo = *it++;
            if (hi >= '0' && hi <= '9')
                ch = static_cast<tchar_t>(hi - '0');
            else if (hi >= 'A' && hi <= 'F')
                ch = static_cast<tchar_t>(hi - 'A' + 10);
            else if (hi >= 'a' && hi <= 'f')
                ch = static_cast<tchar_t>(hi - 'a' + 10);
            else {
                ////throw SyntaxException("URI encoding: not a hex digit");
                xTEST_FAIL;
            }

            ch = static_cast<tchar_t>(ch * 16);
            if (lo >= '0' && lo <= '9')
                ch = static_cast<tchar_t>(ch + lo - '0');
            else if (lo >= 'A' && lo <= 'F')
                ch = static_cast<tchar_t>(ch + lo - 'A' + 10);
            else if (lo >= 'a' && lo <= 'f')
                ch = static_cast<tchar_t>(ch + lo - 'a' + 10);
            else {
                ////throw SyntaxException("URI encoding: not a hex digit");
                xTEST_FAIL;
            }
        }

        (*a_decodedStr) += ch;
    }
}
//-------------------------------------------------------------------------------------------------
inline int_t
cgl_parsecgibuf(/*cgllist *cdata,*/ char *a_query)
{
    // TODO: CxCgi::cgl_parsecgibuf()

    xUNUSED(a_query);
//    char *s;
//    char *np;
//    char *vp;
//
//    if (!cdata || !query) {
//        cgl_seterrno(CGL_NULLARG);
//        return -1;
//    }
//
//    /* get rid of + signs */
//    cgl_charify(query, '+', ' ');
//
//    np = s = query;
//
//    while (*np) {
//
//        /* find name/value pairs */
//        for ( ; *s && *s != '&'; s++) ;
//
//        /* chop them up */
//        if (*s == '&') {
//            *s = '\0'; s++;
//        }
//        if ((vp = strchr(np, '=')) != NULL) {
//            *vp = '\0';
//            vp++;
//            cgl_urlunescape(np);
//            cgl_urlunescape(vp);
//            if (cgl_insertnode(cdata,
//                np, vp, CGL_INSERT_TAIL) == -1) {
//                return -1;
//            }
//        }
//
//        np = s;
//    }
    return 0;
}
//-------------------------------------------------------------------------------------------------
//int_t
//CxCgi::cgl_urlencode(char *s, FILE *fw)
// {
//  // TODO: CxCgi::cgl_urlencode()
//    if (!s)
//        return 0;
//
//    //--cgl_charify(s, ' ', '+');
//    std::tstring_t sRv = CxString::replaceAll(s, CxConst::space(), xT("+"));
//
//    vUrlEscape(sRv, fw);
//
//    return
//}
//-------------------------------------------------------------------------------------------------
//void_t
//CxCgi::cgl_urldecode(char *s)
// {
//  // TODO: CxCgi::cgl_urldecode()
//    //--cgl_charify(s, '+', ' ');
//    std::tstring_t sRv;
//
//    sRv = CxString::replaceAll(s, xT("+"), CxConst::space());
//
//    vUrlUnescape(sRv);
//}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCgi::urlEscape(char *a_s, FILE *a_fw)
{
    // TODO: CxCgi::urlEscape()

    xUNUSED(a_s);
    xUNUSED(a_fw);

//    register int_t    c;
//
//    while((c = *s++) != (char)0) {
//        switch(c) {
//            case '\0':
//                break;
//
//            case '%': case ' ': case '?': case '&':
//            case '>': case '<': case '\"': case ';':
//            case '=': case '@': case ':': case '#':
//                fprintf(fw, "%%%02x", c);
//                break;
//
//            default:
//                if (fputc(c, fw) == EOF)
//                    return EOF;
//                break;
//        }
//    }
}
//-------------------------------------------------------------------------------------------------
//modified from the Apache code. Code shrinks string, so can be done in place.
inline void_t
CxCgi::urlUnescape(char *a_s)
{
    // TODO: CxCgi::urlUnescape()

    xUNUSED(a_s);
//    int_t    error;
//    char    *p;
//
//    if (!s)
//        return 0;
//
//    error = 0;
//
//    for (p = s; *s; s++, p++) {
//        if (*s != '%') {
//            *p = *s;
//            continue;
//        } else {
//            if (!isxdigit((unsigned char)*(s+1)) || !isxdigit((unsigned char)*(s+2))) {
//                error = 1;
//                *p = '%';
//            } else {
//                *p = cgl_hex2char((s+1));
//                s++; s++;
//                if (*p == '/' || *p == (char)0)
//                    error = 1;
//            }
//        }
//    }
//
//    *p = (char)0;
//    if (error)
//        return -1;
}
//-------------------------------------------------------------------------------------------------
//ripped off from the Apache code
inline char
CxCgi::cgl_hex2char(char *a_what)
{
    // TODO: CxCgi::cgl_hex2char()

    xUNUSED(a_what);

    register char digit = '\0';

//    if (!what)
//        return (char)0;
//
//    digit = ((what[0] >= 'A') ? ((what[0] & 0xdf) - 'A')+10 : (what[0] - '0'));
//    digit *= 16;
//    digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A')+10 : (what[1] - '0'));

    return(digit);
}
//-------------------------------------------------------------------------------------------------


/**
 * \class CxCgiEnvironment
 * \brief CGI environment
 */

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxCgiEnvironment::CxCgiEnvironment(
    CxCgi &a_cgi
) :
    _cgi         (a_cgi),
    _requestType(rtUknown)
{
    // fix warning "is not used"
    std::tstring_t sRv = _cgi.dump();
    xUNUSED(sRv);

    _construct();
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::authType() const
{
    return _authType;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::contentLength() const
{
    return _contentLength;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::contentType() const
{
    return _contentType;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::documentRoot() const
{
    return _documentRoot;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::gatewayInterface() const
{
    return _gatewayInterface;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::httpAccept() const
{
    return _httpAccept;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::httpCookie() const
{
    return _httpCookie;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::httpPragma() const
{
    return _httpPragma;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::httpUserAgent() const
{
    return _httpUserAgent;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::pathInfo() const
{
    return _pathInfo;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::pathTranslated() const
{
    return _pathTranslated;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::queryString() const
{
    return _queryString;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::remoteAddr() const
{
    return _remoteAddr;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::remoteHost() const
{
    return _remoteHost;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::remoteIdent() const
{
    return _remoteIdent;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::remotePort() const
{
    return _remotePort;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::remoteUser() const
{
    return _remoteUser;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::requestMethod() const
{
    return _requestMethod;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::requestUri() const
{
    return _requestUri;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::scriptFilename() const
{
    return _scriptFilename;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::scriptName() const
{
    return _scriptName;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::serverAdmin() const
{
    return _serverAdmin;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::serverName() const
{
    return _serverName;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::serverPort() const
{
    return _serverPort;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::serverProtocol() const
{
    return _serverProtocol;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::serverSoftware() const
{
    return _serverSoftware;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::httpReferer() const
{
    return _httpReferer;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::httpHost() const
{
    return _httpHost;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::httpAcceptLanguage() const
{
   return _httpAcceptLanguage;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiEnvironment::countryCode() const
{
    return _countryCode;
}
//-------------------------------------------------------------------------------------------------
inline CxCgiEnvironment::ExRequestType
CxCgiEnvironment::requestType() const
{
    return _requestType;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxCgiEnvironment::dump() const
{
    std::tstring_t sRv;

    sRv = CxString::format(
            xT("[CxCgiEnvironment dump]\n\n")
            xT("AUTH_TYPE: %s\n")
            xT("CONTENT_LENGTH: %s\n")
            xT("CONTENT_TYPE: %s\n")
            xT("DOCUMENT_ROOT: %s\n")
            xT("GATEWAY_INTERFACE: %s\n")
            xT("HTTP_ACCEPT: %s\n")
            xT("HTTP_COOKIE: %s\n")
            xT("HTTP_PRAGMA: %s\n")
            xT("HTTP_USER_AGENT: %s\n")
            xT("PATH_INFO: %s\n")
            xT("PATH_TRANSLATED: %s\n")
            xT("QUERY_STRING: %s\n")
            xT("REMOTE_ADDR: %s\n")
            xT("REMOTE_HOST: %s\n")
            xT("REMOTE_IDENT: %s\n")
            xT("REMOTE_PORT: %s\n")
            xT("REMOTE_USER: %s\n")
            xT("REQUEST_METHOD: %s\n")
            xT("REQUEST_URI: %s\n")
            xT("SCRIPT_FILENAME: %s\n")
            xT("SCRIPT_NAME: %s\n")
            xT("SERVER_ADMIN: %s\n")
            xT("SERVER_NAME: %s\n")
            xT("SERVER_PORT: %s\n")
            xT("SERVER_PROTOCOL: %s\n")
            xT("SERVER_SOFTWARE: %s\n")
            xT("HTTP_REFERER: %s\n")
            xT("HTTP_HOST: %s\n")
            xT("HTTP_ACCEPT_LANGUAGE: %s\n")
            xT("GEOIP_COUNTRY_CODE: %s\n\n"),
            authType().c_str(),
            contentLength().c_str(),
            contentType().c_str(),
            documentRoot().c_str(),
            gatewayInterface().c_str(),
            httpAccept().c_str(),
            httpCookie().c_str(),
            httpPragma().c_str(),
            httpUserAgent().c_str(),
            pathInfo().c_str(),
            pathTranslated().c_str(),
            queryString().c_str(),
            remoteAddr().c_str(),
            remoteHost().c_str(),
            remoteIdent().c_str(),
            remotePort().c_str(),
            remoteUser().c_str(),
            requestMethod().c_str(),
            requestUri().c_str(),
            scriptFilename().c_str(),
            scriptName().c_str(),
            serverAdmin().c_str(),
            serverName().c_str(),
            serverPort().c_str(),
            serverProtocol().c_str(),
            serverSoftware().c_str(),
            httpReferer().c_str(),
            httpHost().c_str(),
            httpAcceptLanguage().c_str(),
            countryCode().c_str()
    );

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxCgiEnvironment::_construct()
{
    _authType           = CxEnvironment::var(xT("AUTH_TYPE"));
    _contentLength      = CxEnvironment::var(xT("CONTENT_LENGTH"));
    _contentType        = CxEnvironment::var(xT("CONTENT_TYPE"));
    _documentRoot       = CxEnvironment::var(xT("DOCUMENT_ROOT"));
    _gatewayInterface   = CxEnvironment::var(xT("GATEWAY_INTERFACE"));
    _httpAccept         = CxEnvironment::var(xT("HTTP_ACCEPT"));
    _httpCookie         = CxEnvironment::var(xT("HTTP_COOKIE"));
    _httpPragma         = CxEnvironment::var(xT("HTTP_PRAGMA"));
    _httpUserAgent      = CxEnvironment::var(xT("HTTP_USER_AGENT"));
    _pathInfo           = CxEnvironment::var(xT("PATH_INFO"));
    _pathTranslated     = CxEnvironment::var(xT("PATH_TRANSLATED"));
    _queryString        = CxEnvironment::var(xT("QUERY_STRING"));
    _remoteAddr         = CxEnvironment::var(xT("REMOTE_ADDR"));
    _remoteHost         = CxEnvironment::var(xT("REMOTE_HOST"));
    _remoteIdent        = CxEnvironment::var(xT("REMOTE_IDENT"));
    _remotePort         = CxEnvironment::var(xT("REMOTE_PORT"));
    _remoteUser         = CxEnvironment::var(xT("REMOTE_USER"));
    _requestMethod      = CxEnvironment::var(xT("REQUEST_METHOD"));
    _requestUri         = CxEnvironment::var(xT("REQUEST_URI"));
    _scriptFilename     = CxEnvironment::var(xT("SCRIPT_FILENAME"));
    _scriptName         = CxEnvironment::var(xT("SCRIPT_NAME"));
    _serverAdmin        = CxEnvironment::var(xT("SERVER_ADMIN"));
    _serverName         = CxEnvironment::var(xT("SERVER_NAME"));
    _serverPort         = CxEnvironment::var(xT("SERVER_PORT"));
    _serverProtocol     = CxEnvironment::var(xT("SERVER_PROTOCOL"));
    _serverSoftware     = CxEnvironment::var(xT("SERVER_SOFTWARE"));
    _httpReferer        = CxEnvironment::var(xT("HTTP_REFERER"));
    _httpHost           = CxEnvironment::var(xT("HTTP_HOST"));
    _httpAcceptLanguage = CxEnvironment::var(xT("HTTP_ACCEPT_LANGUAGE"));
    _countryCode        = CxEnvironment::var(xT("GEOIP_COUNTRY_CODE"));

    if (_countryCode.empty()) {
        _countryCode    = CxEnvironment::var(xT("HTTP_GEOIP_COUNTRY_CODE"));
    }
    if (_countryCode.empty()) {
        _countryCode    = CxEnvironment::var(xT("HTTP_COUNTRY_CODE"));
    }

    //--------------------------------------------------
    //is data from a GET or a POST?
    if        (CxString::compareNoCase(xT("GET"), requestMethod())) {
        _requestType = rtGet;
    } else if (CxString::compareNoCase(xT("POST"), requestMethod())) {
        _requestType = rtPost;
    }
    else {
        _requestType = rtUknown;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------


/**
 * \class CxCgiCookies
 * \brief CGI cookies
 */

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxCgiCookies::CxCgiCookies(
    CxCgi &a_cgi
):
    _cgi(a_cgi)
{
    _construct();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxCgiCookies::~CxCgiCookies()
{
    xFOREACH(TCookies, it, items) {
        xPTR_DELETE(*it);
    }
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxCgiCookies::operator [] (
    std::ctstring_t &a_cookieName
)
{
    xFOREACH_CONST(TCookies, it, items) {
        xCHECK_DO(!CxString::compareNoCase(a_cookieName, (*it)->value()), continue);

        return (*it)->value();
    }

    return std::tstring_t();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxCgiCookies::dump() const
{
    std::tstring_t sRv;

    sRv.append(xT("[CxCgiCookies dump]\n\n"));

    xFOREACH_CONST(TCookies, it, items) {
        std::tstring_t itemN = CxString::format(
                xT("Name: %s\n")
                xT("Value: %s\n")
                xT("Domain: %s\n")
                xT("Path: %s\n")
                xT("Expires: %s\n")
                xT("Secure: %s\n")
                xT("HttpOnly: %s\n\n"),
                (*it)->name().c_str(),
                (*it)->value().c_str(),
                (*it)->domain().c_str(),
                (*it)->path().c_str(),
                (*it)->expires().c_str(),
                CxString::boolToStr((*it)->secure()).c_str(),
                CxString::boolToStr((*it)->httpOnly()).c_str()
        );

        sRv.append( xT("[Item]:\n") );
        sRv.append(itemN);
        sRv.append(CxConst::nl());
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxCgiCookies::_construct()
{
    std::tstring_t     rawCookies = _cgi.Environment.httpCookie();
    std::vec_tstring_t vsRawCookies;
    TCookies           cookies;

    CxString::split(rawCookies, CxConst::semicolon(), &vsRawCookies);

    xFOREACH_CONST(std::vec_tstring_t, it, vsRawCookies) {
        CxCookiePv0 *pckItem = new(std::nothrow) CxCookiePv0(*it);
        xTEST_PTR(pckItem);

        cookies.push_back(pckItem);
    }

    cookies.swap(items);
}
//-------------------------------------------------------------------------------------------------


/**
 * \class CxCgiFormData
 * \brief CGI form data
 */

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxCgiFormData::CxCgiFormData(
    CxCgi        &a_cgi,
    std::csize_t &a_maxSize
) :
    _maxData(a_maxSize),
    _cgi    (a_cgi)
{
    _construct();
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxCgiFormData::rawData() const
{
    return _formData;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxCgiFormData::dump() const
{
    std::tstring_t sRv;

    sRv = CxString::format(
            xT("[CxCgiFormData dump]\n\n")
            xT("Data: %s\n\n"),
            rawData().c_str());

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxCgiFormData::_construct()
{
    int_t iRv = _cgi.Environment.requestType();
    switch (iRv) {
    case CxCgiEnvironment::rtGet:
        xTEST_EQ(false, _cgi.Environment.queryString().empty());

        // TODO: CxCgiFormData::_construct() - cgl_parsecgibuf()

        _formData = _cgi.Environment.queryString();
        break;
    case CxCgiEnvironment::rtPost: {
        bool_t bRv = false;

        bRv = CxString::compareNoCase(xT("application/x-www-form-urlencoded"),
            _cgi.Environment.contentType());
        xTEST_EQ(true, bRv);

        //get content length
        size_t postSize = 0;  // in bytes
        if (_cgi.Environment.contentLength().empty()) {
            postSize = 0;
        }
        else {
            postSize = CxString::cast<size_t>( _cgi.Environment.contentLength() );
        }
        xTEST_LESS(size_t(0U), postSize);
        xTEST_GR_EQ(_maxData, postSize);  //secure
        xTEST_EQ(false, _maxData <= postSize);

        //read, parse data
        CxFile         file;
        std::tstring_t buff;

        file.attach(stdin);

        buff.resize(postSize);

        size_t uiRv = file.read(&buff.at(0), buff.size());
        xTEST_EQ(uiRv, buff.size());

        // TODO: CxCgiFormData::_construct() - cgl_parsecgibuf()

        _formData = buff;

        FILE *f = file.detach();
        xTEST_PTR(f);
        break;
    }
    default:
        ////xTEST_FAIL;
        break;
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)
