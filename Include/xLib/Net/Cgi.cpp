/**
 * \file  Cgi.inl
 * \brief CGI
 */


#if !xOPTION_HEADER_ONLY
    #include "Cgi.h"
#endif

#include <xLib/Core/Utils.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/System/Environment.h>
#include <xLib/IO/File.h>
#include <xLib/Net/CookiePv0.h>
#include <xLib/Net/CookiePv1.h>


xNAMESPACE_BEGIN2(xlib, net)


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Cgi::Cgi(
    std::csize_t &a_maxSize
) :
    Environment(*this),
    Cookies    (*this),
    Formdata   (*this, a_maxSize)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Cgi::dump() const
{
    std::tstring_t sRv;

    sRv = String::format(
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
xINLINE void_t
Cgi::redirect(
    std::ctstring_t &a_url
)
{
    xTEST_EQ(a_url.empty(), false)

    std::tstring_t httpResponse;

    httpResponse.append( String::format(xT("Location: %s\n"), a_url.c_str()) );
    httpResponse.append( Const::nl() );

    std::tcout << httpResponse << std::endl;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Cgi::pageShow(
    std::ctstring_t &a_filePath
)
{
    std::tstring_t fileContent;

    File::textRead(a_filePath, &fileContent);

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
xINLINE void_t
Cgi::uriEncode(
    std::ctstring_t &a_uri,
    std::ctstring_t &a_reserved,
    std::tstring_t  *a_encodedStr
)
{
    // TODO: Cgi::uriEncode()

    xFOREACH_CONST(std::tstring_t, it, a_uri) {
        tchar_t ch = *it;

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') ||
             ch == '-' || ch == '_'  || ch == '.' || ch == '~')
        {
            (*a_encodedStr) += ch;
        }
        else if (ch <= 0x20 || ch >= 0x7F || URI_ILLEGAL.find(ch) != std::tstring_t::npos ||
            a_reserved.find(ch) != std::tstring_t::npos)
        {
            (*a_encodedStr) += '%';
            //--encodedStr += NumberFormatter::formatHex((unsigned) (unsigned char) ch, 2);

            /*
                poco_assert (width > 0 && width < 64);

                char buffer[64];
                std::sprintf(buffer, "%0*X", width, value);
                str.append(buffer);
             */
            (*a_encodedStr) += String::format(xT("%0*X"), 2, (uint_t)(uchar_t)ch);
        }
        else {
            (*a_encodedStr) += ch;
        }
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Cgi::uriDecode(
    std::ctstring_t &a_uri,
    std::tstring_t  *a_decodedStr
)
{
    //TODO: Cgi::uriDecode()

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
xINLINE int_t
cgl_parsecgibuf(/*cgllist *cdata,*/ char *a_query)
{
    // TODO: Cgi::cgl_parsecgibuf()

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
//        if ((vp = strchr(np, '=')) != xPTR_NULL) {
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
//Cgi::cgl_urlencode(char *s, FILE *fw)
// {
//  // TODO: Cgi::cgl_urlencode()
//    if (!s)
//        return 0;
//
//    //--cgl_charify(s, ' ', '+');
//    std::tstring_t sRv = String::replaceAll(s, Const::space(), xT("+"));
//
//    vUrlEscape(sRv, fw);
//
//    return
//}
//-------------------------------------------------------------------------------------------------
//void_t
//Cgi::cgl_urldecode(char *s)
// {
//  // TODO: Cgi::cgl_urldecode()
//    //--cgl_charify(s, '+', ' ');
//    std::tstring_t sRv;
//
//    sRv = String::replaceAll(s, xT("+"), Const::space());
//
//    vUrlUnescape(sRv);
//}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Cgi::urlEscape(char *a_s, FILE *a_fw)
{
    // TODO: Cgi::urlEscape()

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
xINLINE void_t
Cgi::urlUnescape(char *a_s)
{
    // TODO: Cgi::urlUnescape()

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
xINLINE char
Cgi::cgl_hex2char(char *a_what)
{
    // TODO: Cgi::cgl_hex2char()

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
 * \class CgiEnvironment
 * \brief CGI environment
 */

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CgiEnvironment::CgiEnvironment(
    Cgi &a_cgi
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
xINLINE std::ctstring_t &
CgiEnvironment::authType() const
{
    return _authType;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::contentLength() const
{
    return _contentLength;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::contentType() const
{
    return _contentType;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::documentRoot() const
{
    return _documentRoot;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::gatewayInterface() const
{
    return _gatewayInterface;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::httpAccept() const
{
    return _httpAccept;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::httpCookie() const
{
    return _httpCookie;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::httpPragma() const
{
    return _httpPragma;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::httpUserAgent() const
{
    return _httpUserAgent;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::pathInfo() const
{
    return _pathInfo;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::pathTranslated() const
{
    return _pathTranslated;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::queryString() const
{
    return _queryString;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::remoteAddr() const
{
    return _remoteAddr;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::remoteHost() const
{
    return _remoteHost;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::remoteIdent() const
{
    return _remoteIdent;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::remotePort() const
{
    return _remotePort;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::remoteUser() const
{
    return _remoteUser;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::requestMethod() const
{
    return _requestMethod;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::requestUri() const
{
    return _requestUri;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::scriptFilename() const
{
    return _scriptFilename;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::scriptName() const
{
    return _scriptName;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::serverAdmin() const
{
    return _serverAdmin;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::serverName() const
{
    return _serverName;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::serverPort() const
{
    return _serverPort;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::serverProtocol() const
{
    return _serverProtocol;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::serverSoftware() const
{
    return _serverSoftware;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::httpReferer() const
{
    return _httpReferer;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::httpHost() const
{
    return _httpHost;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::httpAcceptLanguage() const
{
   return _httpAcceptLanguage;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiEnvironment::countryCode() const
{
    return _countryCode;
}
//-------------------------------------------------------------------------------------------------
xINLINE CgiEnvironment::ExRequestType
CgiEnvironment::requestType() const
{
    return _requestType;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CgiEnvironment::dump() const
{
    std::tstring_t sRv;

    sRv = String::format(
            xT("[CgiEnvironment dump]\n\n")
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
xINLINE bool_t
CgiEnvironment::_construct()
{
    _authType           = Environment::var(xT("AUTH_TYPE"));
    _contentLength      = Environment::var(xT("CONTENT_LENGTH"));
    _contentType        = Environment::var(xT("CONTENT_TYPE"));
    _documentRoot       = Environment::var(xT("DOCUMENT_ROOT"));
    _gatewayInterface   = Environment::var(xT("GATEWAY_INTERFACE"));
    _httpAccept         = Environment::var(xT("HTTP_ACCEPT"));
    _httpCookie         = Environment::var(xT("HTTP_COOKIE"));
    _httpPragma         = Environment::var(xT("HTTP_PRAGMA"));
    _httpUserAgent      = Environment::var(xT("HTTP_USER_AGENT"));
    _pathInfo           = Environment::var(xT("PATH_INFO"));
    _pathTranslated     = Environment::var(xT("PATH_TRANSLATED"));
    _queryString        = Environment::var(xT("QUERY_STRING"));
    _remoteAddr         = Environment::var(xT("REMOTE_ADDR"));
    _remoteHost         = Environment::var(xT("REMOTE_HOST"));
    _remoteIdent        = Environment::var(xT("REMOTE_IDENT"));
    _remotePort         = Environment::var(xT("REMOTE_PORT"));
    _remoteUser         = Environment::var(xT("REMOTE_USER"));
    _requestMethod      = Environment::var(xT("REQUEST_METHOD"));
    _requestUri         = Environment::var(xT("REQUEST_URI"));
    _scriptFilename     = Environment::var(xT("SCRIPT_FILENAME"));
    _scriptName         = Environment::var(xT("SCRIPT_NAME"));
    _serverAdmin        = Environment::var(xT("SERVER_ADMIN"));
    _serverName         = Environment::var(xT("SERVER_NAME"));
    _serverPort         = Environment::var(xT("SERVER_PORT"));
    _serverProtocol     = Environment::var(xT("SERVER_PROTOCOL"));
    _serverSoftware     = Environment::var(xT("SERVER_SOFTWARE"));
    _httpReferer        = Environment::var(xT("HTTP_REFERER"));
    _httpHost           = Environment::var(xT("HTTP_HOST"));
    _httpAcceptLanguage = Environment::var(xT("HTTP_ACCEPT_LANGUAGE"));
    _countryCode        = Environment::var(xT("GEOIP_COUNTRY_CODE"));

    if (_countryCode.empty()) {
        _countryCode    = Environment::var(xT("HTTP_GEOIP_COUNTRY_CODE"));
    }
    if (_countryCode.empty()) {
        _countryCode    = Environment::var(xT("HTTP_COUNTRY_CODE"));
    }

    //--------------------------------------------------
    //is data from a GET or a POST?
    if        (StringCI::compare(xT("GET"), requestMethod())) {
        _requestType = rtGet;
    } else if (StringCI::compare(xT("POST"), requestMethod())) {
        _requestType = rtPost;
    }
    else {
        _requestType = rtUknown;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------


/**
 * \class CgiCookies
 * \brief CGI cookies
 */

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CgiCookies::CgiCookies(
    Cgi &a_cgi
):
    _cgi(a_cgi)
{
    _construct();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
CgiCookies::~CgiCookies()
{
    xFOREACH(TCookies, it, items) {
        xPTR_DELETE(*it);
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CgiCookies::operator [] (
    std::ctstring_t &a_cookieName
)
{
    xFOREACH_CONST(TCookies, it, items) {
        xCHECK_DO(!StringCI::compare(a_cookieName, (*it)->value()), continue);

        return (*it)->value();
    }

    return std::tstring_t();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CgiCookies::dump() const
{
    std::tstring_t sRv;

    sRv.append(xT("[CgiCookies dump]\n\n"));

    xFOREACH_CONST(TCookies, it, items) {
        std::tstring_t itemN = String::format(
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
                String::castBool((*it)->secure()).c_str(),
                String::castBool((*it)->httpOnly()).c_str()
        );

        sRv.append( xT("[Item]:\n") );
        sRv.append(itemN);
        sRv.append(Const::nl());
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
CgiCookies::_construct()
{
    std::tstring_t     rawCookies = _cgi.Environment.httpCookie();
    std::vec_tstring_t vsRawCookies;
    TCookies           cookies;

    String::split(rawCookies, Const::semicolon(), &vsRawCookies);

    xFOREACH_CONST(std::vec_tstring_t, it, vsRawCookies) {
        CookiePv0 *pckItem = new(std::nothrow) CookiePv0(*it);
        xTEST_PTR(pckItem);

        cookies.push_back(pckItem);
    }

    cookies.swap(items);
}
//-------------------------------------------------------------------------------------------------


/**
 * \class CgiFormData
 * \brief CGI form data
 */

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CgiFormData::CgiFormData(
    Cgi        &a_cgi,
    std::csize_t &a_maxSize
) :
    _maxData(a_maxSize),
    _cgi    (a_cgi)
{
    _construct();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
CgiFormData::rawData() const
{
    return _formData;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
CgiFormData::dump() const
{
    std::tstring_t sRv;

    sRv = String::format(
            xT("[CgiFormData dump]\n\n")
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
xINLINE void_t
CgiFormData::_construct()
{
    int_t iRv = _cgi.Environment.requestType();
    switch (iRv) {
    case CgiEnvironment::rtGet:
        xTEST_EQ(_cgi.Environment.queryString().empty(), false);

        // TODO: CgiFormData::_construct() - cgl_parsecgibuf()

        _formData = _cgi.Environment.queryString();
        break;
    case CgiEnvironment::rtPost: {
        bool_t bRv = false;

        bRv = StringCI::compare(xT("application/x-www-form-urlencoded"),
            _cgi.Environment.contentType());
        xTEST_EQ(bRv, true);

        //get content length
        size_t postSize = 0;  // in bytes
        if (_cgi.Environment.contentLength().empty()) {
            postSize = 0;
        }
        else {
            postSize = String::cast<size_t>( _cgi.Environment.contentLength() );
        }
        xTEST_LESS(size_t(0U), postSize);
        xTEST_GR_EQ(_maxData, postSize);  // secure
        xTEST_EQ(_maxData <= postSize, false);

        //read, parse data
        File         file;
        std::tstring_t buff;

        file.attach(stdin, xT(""));

        buff.resize(postSize);

        size_t uiRv = file.read(&buff.at(0), buff.size());
        xTEST_EQ(uiRv, buff.size());

        // TODO: CgiFormData::_construct() - cgl_parsecgibuf()

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

xNAMESPACE_END2(xlib, net)
