/**
 * \file  Cgi.inl
 * \brief CGI
 */


#include "Cgi.h"

#include <xLib/Core/Utils.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
#include <xLib/System/Environment.h>
#include <xLib/Fs/File.h>
#include <xLib/Net/CookiePv0.h>
#include <xLib/Net/CookiePv1.h>


xNAMESPACE_BEGIN2(xl, net)


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Cgi::Cgi(
    std::csize_t &a_maxSize
) :
    Environment(*this),
    Cookies    (*this),
    Formdata   (*this, a_maxSize)
{
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Cgi::dump() const
{
    std::tstring_t sRv;

    sRv = Format::str(
            xT("[CGI dump]\n\n")
            xT("{}\n")
            xT("{}\n")
            xT("{}\n"),
            Environment.dump(),
            Cookies.dump(),
            Formdata.dump()
    );

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Cgi::redirect(
    std::ctstring_t &a_url
)
{
    xTEST_EQ(a_url.empty(), false)

    std::tstring_t httpResponse;

    httpResponse.append( Format::str(xT("Location: {}\n"), a_url) );
    httpResponse.append( Const::nl() );

    std::tcout << httpResponse << std::endl;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Cgi::pageShow(
    std::ctstring_t &a_filePath
)
{
    std::tstring_t fileContent;

    File::textRead(a_filePath, &fileContent);

    std::tcout << fileContent << std::endl;
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
CgiEnvironment::CgiEnvironment(
    Cgi &a_cgi
) :
    _cgi(a_cgi)
{
    // fix warning "is not used"
    std::tstring_t sRv = _cgi.dump();
    xUNUSED(sRv);

    _construct();
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::authType() const
{
    return _authType;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::contentLength() const
{
    return _contentLength;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::contentType() const
{
    return _contentType;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::documentRoot() const
{
    return _documentRoot;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::gatewayInterface() const
{
    return _gatewayInterface;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::httpAccept() const
{
    return _httpAccept;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::httpCookie() const
{
    return _httpCookie;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::httpPragma() const
{
    return _httpPragma;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::httpUserAgent() const
{
    return _httpUserAgent;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::pathInfo() const
{
    return _pathInfo;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::pathTranslated() const
{
    return _pathTranslated;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::queryString() const
{
    return _queryString;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::remoteAddr() const
{
    return _remoteAddr;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::remoteHost() const
{
    return _remoteHost;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::remoteIdent() const
{
    return _remoteIdent;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::remotePort() const
{
    return _remotePort;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::remoteUser() const
{
    return _remoteUser;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::requestMethod() const
{
    return _requestMethod;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::requestUri() const
{
    return _requestUri;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::scriptFilename() const
{
    return _scriptFilename;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::scriptName() const
{
    return _scriptName;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::serverAdmin() const
{
    return _serverAdmin;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::serverName() const
{
    return _serverName;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::serverPort() const
{
    return _serverPort;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::serverProtocol() const
{
    return _serverProtocol;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::serverSoftware() const
{
    return _serverSoftware;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::httpReferer() const
{
    return _httpReferer;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::httpHost() const
{
    return _httpHost;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::httpAcceptLanguage() const
{
   return _httpAcceptLanguage;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiEnvironment::countryCode() const
{
    return _countryCode;
}
//-------------------------------------------------------------------------------------------------
CgiEnvironment::RequestType
CgiEnvironment::requestType() const
{
    return _requestType;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CgiEnvironment::dump() const
{
    std::tstring_t sRv;

    sRv = Format::str(
            xT("[CgiEnvironment dump]\n\n")
            xT("AUTH_TYPE: {}\n")
            xT("CONTENT_LENGTH: {}\n")
            xT("CONTENT_TYPE: {}\n")
            xT("DOCUMENT_ROOT: {}\n")
            xT("GATEWAY_INTERFACE: {}\n")
            xT("HTTP_ACCEPT: {}\n")
            xT("HTTP_COOKIE: {}\n")
            xT("HTTP_PRAGMA: {}\n")
            xT("HTTP_USER_AGENT: {}\n")
            xT("PATH_INFO: {}\n")
            xT("PATH_TRANSLATED: {}\n")
            xT("QUERY_STRING: {}\n")
            xT("REMOTE_ADDR: {}\n")
            xT("REMOTE_HOST: {}\n")
            xT("REMOTE_IDENT: {}\n")
            xT("REMOTE_PORT: {}\n")
            xT("REMOTE_USER: {}\n")
            xT("REQUEST_METHOD: {}\n")
            xT("REQUEST_URI: {}\n")
            xT("SCRIPT_FILENAME: {}\n"),
            authType(),
            contentLength(),
            contentType(),
            documentRoot(),
            gatewayInterface(),
            httpAccept(),
            httpCookie(),
            httpPragma(),
            httpUserAgent(),
            pathInfo(),
            pathTranslated(),
            queryString(),
            remoteAddr(),
            remoteHost(),
            remoteIdent(),
            remotePort(),
            remoteUser(),
            requestMethod(),
            requestUri(),
            scriptFilename());

    sRv += Format::str(
            xT("SCRIPT_FILENAME: {}\n")
            xT("SCRIPT_NAME: {}\n")
            xT("SERVER_ADMIN: {}\n")
            xT("SERVER_NAME: {}\n")
            xT("SERVER_PORT: {}\n")
            xT("SERVER_PROTOCOL: {}\n")
            xT("SERVER_SOFTWARE: {}\n")
            xT("HTTP_REFERER: {}\n")
            xT("HTTP_HOST: {}\n")
            xT("HTTP_ACCEPT_LANGUAGE: {}\n")
            xT("GEOIP_COUNTRY_CODE: {}\n\n"),
            scriptFilename(),
            scriptName(),
            serverAdmin(),
            serverName(),
            serverPort(),
            serverProtocol(),
            serverSoftware(),
            httpReferer(),
            httpHost(),
            httpAcceptLanguage(),
            countryCode());

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
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
        _requestType = RequestType::rtGet;
    } else if (StringCI::compare(xT("POST"), requestMethod())) {
        _requestType = RequestType::rtPost;
    }
    else {
        _requestType = RequestType::rtUknown;
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
CgiCookies::CgiCookies(
    Cgi &a_cgi
):
    _cgi(a_cgi)
{
    _construct();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
CgiCookies::~CgiCookies()
{
    xFOR_EACH(TCookies, it, items) {
        Utils::ptrDeleteT(*it);
    }
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CgiCookies::operator [] (
    std::ctstring_t &a_cookieName
)
{
    for (const auto &it : items) {
        xCHECK_DO(!StringCI::compare(a_cookieName, it->value()), continue);

        return it->value();
    }

    return std::tstring_t();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CgiCookies::dump() const
{
    std::tstring_t sRv;

    sRv.append(xT("[CgiCookies dump]\n\n"));

    for (const auto &it : items) {
        std::tstring_t itemN = Format::str(
                xT("Name: {}\n")
                xT("Value: {}\n")
                xT("Domain: {}\n")
                xT("Path: {}\n")
                xT("Expires: {}\n")
                xT("Secure: {}\n")
                xT("HttpOnly: {}\n\n"),
                it->name(),
                it->value(),
                it->domain(),
                it->path(),
                it->expires(),
                it->secure(),
                it->httpOnly());

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
void_t
CgiCookies::_construct()
{
    std::tstring_t     rawCookies = _cgi.Environment.httpCookie();
    std::vec_tstring_t vsRawCookies;
    TCookies           cookies;

    String::split(rawCookies, Const::semicolon(), &vsRawCookies);

    for (const auto &it : vsRawCookies) {
        CookiePv0 *pckItem = new(std::nothrow) CookiePv0(it);
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
CgiFormData::CgiFormData(
    Cgi          &a_cgi,
    std::csize_t &a_maxSize
) :
    _maxData(a_maxSize),
    _cgi    (a_cgi)
{
    _construct();
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
CgiFormData::rawData() const
{
    return _formData;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CgiFormData::dump() const
{
    std::tstring_t sRv;

    sRv = Format::str(
            xT("[CgiFormData dump]\n\n")
            xT("Data: {}\n\n"),
            rawData());

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
CgiFormData::_construct()
{
    auto iRv = _cgi.Environment.requestType();
    switch (iRv) {
    case CgiEnvironment::RequestType::rtGet:
        xTEST_EQ(_cgi.Environment.queryString().empty(), false);

        // TODO: [skynowa] CgiFormData::_construct() - cgl_parsecgibuf()

        _formData = _cgi.Environment.queryString();
        break;
    case CgiEnvironment::RequestType::rtPost: {
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
        std::tstring_t buff;

        File          file;
        HandleStdFile stdIn(stdin);
        file.attach(stdIn, xT(""));

        buff.resize(postSize);

        size_t uiRv = file.read(&buff.at(0), buff.size());
        xTEST_EQ(uiRv, buff.size());

        // TODO: [skynowa] CgiFormData::_construct() - cgl_parsecgibuf()

        _formData = buff;

        HandleStdFile f;
        f = file.detach();
        xTEST_EQ(f.isValid(), true);
        break;
    }
    default:
        ////xTEST_FAIL;
        break;
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, net)
