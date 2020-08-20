/**
 * \file  Cgi.h
 * \brief CGI
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, net)

class Cgi;
class CookiePv0;
class CookiePv1;

//-------------------------------------------------------------------------------------------------
class CgiEnvironment
    /// CGI environment
{
public:
    enum class RequestType
        /// request type
    {
        rtUknown,
        rtGet,
        rtPost
    };
    xUSING_CONST(RequestType);

    explicit          CgiEnvironment(Cgi &cgi);
    virtual          ~CgiEnvironment() = default;

    std::ctstring_t & authType() const;
        ///< get auth type
    std::ctstring_t & contentLength() const;
        ///< get content length
    std::ctstring_t & contentType() const;
        ///< get content type
    std::ctstring_t & documentRoot() const;
        ///< get document root
    std::ctstring_t & gatewayInterface() const;
        ///< get gateway interface
    std::ctstring_t & httpAccept() const;
        ///< get HTTP accept
    std::ctstring_t & httpCookie() const;
        ///< get HTTP cookie
    std::ctstring_t & httpPragma() const;
        ///< get HTTP pragma
    std::ctstring_t & httpUserAgent() const;
        ///< get HTTP user agent
    std::ctstring_t & pathInfo() const;
        ///< get path info
    std::ctstring_t & pathTranslated() const;
        ///< get path translated
    std::ctstring_t & queryString() const;
        ///< get query string
    std::ctstring_t & remoteAddr() const;
        ///< get remote address
    std::ctstring_t & remoteHost() const;
        ///< get remote host
    std::ctstring_t & remoteIdent() const;
        ///< et remote ident
    std::ctstring_t & remotePort() const;
        ///< get remote port
    std::ctstring_t & remoteUser() const;
        ///< get remote user
    std::ctstring_t & requestMethod() const;
        ///< get request method
    std::ctstring_t & requestUri() const;
        ///< get request URI
    std::ctstring_t & scriptFilename() const;
        ///< get script file name
    std::ctstring_t & scriptName() const;
        ///< get script name
    std::ctstring_t & serverAdmin() const;
        ///< get server admin
    std::ctstring_t & serverName() const;
        ///< get server name
    std::ctstring_t & serverPort() const;
        ///< get server port
    std::ctstring_t & serverProtocol() const;
        ///< get server protocol
    std::ctstring_t & serverSoftware() const;
        ///< get server software
    std::ctstring_t & httpReferer() const;
        ///< get HTTP referer
    std::ctstring_t & httpHost() const;
        ///< get HTTP host
    std::ctstring_t & httpAcceptLanguage() const;
        ///< get HTTP accept language
    std::ctstring_t & countryCode() const;
        ///< get country code

    RequestType       requestType() const;
        ///< get request type
    std::tstring_t    dump() const;
        ///< get dump

private:
    Cgi           & _cgi;                ///< Cgi object
    std::tstring_t    _authType;             ///< auth type
    std::tstring_t    _contentLength;        ///< content length
    std::tstring_t    _contentType;          ///< content type
    std::tstring_t    _documentRoot;         ///< document root
    std::tstring_t    _gatewayInterface;     ///< gateway interface
    std::tstring_t    _httpAccept;           ///< HTTP accept
    std::tstring_t    _httpCookie;           ///< HTTP cookie
    std::tstring_t    _httpPragma;           ///< HTTP pragma
    std::tstring_t    _httpUserAgent;        ///< HTTP user agent
    std::tstring_t    _pathInfo;             ///< path info
    std::tstring_t    _pathTranslated;       ///< path translated
    std::tstring_t    _queryString;          ///< query string
    std::tstring_t    _remoteAddr;           ///< remote address
    std::tstring_t    _remoteHost;           ///< remote host
    std::tstring_t    _remoteIdent;          ///< remote ident
    std::tstring_t    _remotePort;           ///< remote port
    std::tstring_t    _remoteUser;           ///< remote user
    std::tstring_t    _requestMethod;        ///< request method
    std::tstring_t    _requestUri;           ///< request URI
    std::tstring_t    _scriptFilename;       ///< script file name
    std::tstring_t    _scriptName;           ///< script name
    std::tstring_t    _serverAdmin;          ///< server admin
    std::tstring_t    _serverName;           ///< server name
    std::tstring_t    _serverPort;           ///< server port
    std::tstring_t    _serverProtocol;       ///< server protocol
    std::tstring_t    _serverSoftware;       ///< server software
    std::tstring_t    _httpReferer;          ///< HTTP referrer
    std::tstring_t    _httpHost;             ///< HTTP host
    std::tstring_t    _httpAcceptLanguage;   ///< HTTP accept language
    std::tstring_t    _countryCode;          ///< country code
    RequestType       _requestType {};       ///< request method

    bool_t            _construct();
        ///< initiate class data

    xNO_COPY_ASSIGN(CgiEnvironment)
};
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
class CgiCookies
    /// CGI cookies
{
public:
    using TCookies = std::vector<CookiePv0 *>;

    TCookies        items;    ///< cookie items

    explicit        CgiCookies(Cgi &cgi);
    virtual        ~CgiCookies();

    std::tstring_t  dump() const;
        ///< get dump
    std::tstring_t  operator[](std::ctstring_t &cookieName);
        ///< no case searching cookie value by name from list

private:
    Cgi          &_cgi;    ///< Cgi object

    void_t          _construct();
        ///< initiate class data

    xNO_COPY_ASSIGN(CgiCookies)
};
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
class CgiFormData
    /// CGI form data
{
public:
                     CgiFormData(Cgi &cgi, std::csize_t &maxSize);
    virtual         ~CgiFormData() {}

    std::ctstring_t &rawData() const;
        ///< get raw data
    std::tstring_t   dump() const;
        ///< get dump

private:
    // consts
    std::csize_t     _maxData;    ///< maximum data size

    Cgi           &_cgi;        ///< Cgi object
    std::tstring_t   _formData;     ///< form data

    void_t           _construct();
        ///< initiate class data

    xNO_COPY_ASSIGN(CgiFormData)
};
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
class Cgi
    /// CGI
{
public:
    std::csize_t & MAX_DATA_SIZE_DEFAULT()
    {
        static std::csize_t uiRv = 1024U * 1024U;

        return uiRv;
    }
         ///< maximum data size by default

    CgiEnvironment        Environment;    ///< CgiEnvironment object
    CgiCookies            Cookies;        ///< CgiCookies object
    CgiFormData           Formdata;       ///< CgiFormData object

    explicit                Cgi(std::csize_t &maxSize);
    virtual                ~Cgi() {}

    std::tstring_t          dump() const;
        ///< get dump
    static
    void_t                  redirect(std::ctstring_t &url);
        ///< redirect to URL
    static
    void_t                  pageShow(std::ctstring_t &filePath);
        ///< show page from file

private:
    xNO_COPY_ASSIGN(Cgi)
};

xNAMESPACE_END2(xl, net)
//-------------------------------------------------------------------------------------------------
