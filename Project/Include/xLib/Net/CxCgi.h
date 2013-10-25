/**
 * \file  CxCgi.h
 * \brief CGI
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCgi;
class CxCookiePv0;
class CxCookiePv1;

xNAMESPACE_BEGIN(NxCgi)

//------------------------------------------------------------------------------
class CxCgiEnvironment :
    private CxNonCopyable
    /// CGI environment
{
public:
    enum ExRequestType
        /// request type
    {
        rtUknown,
        rtGet,
        rtPost
    };

                      CxCgiEnvironment(CxCgi &cgi);
        ///< constructor
    virtual          ~CxCgiEnvironment() {}
        ///< destructor

    std::ctstring_t & authType() const xWARN_UNUSED_RV;
        ///< get auth type
    std::ctstring_t & contentLength() const xWARN_UNUSED_RV;
        ///< get content length
    std::ctstring_t & contentType() const xWARN_UNUSED_RV;
        ///< get content type
    std::ctstring_t & documentRoot() const xWARN_UNUSED_RV;
        ///< get document root
    std::ctstring_t & gatewayInterface() const xWARN_UNUSED_RV;
        ///< get gateway interface
    std::ctstring_t & httpAccept() const xWARN_UNUSED_RV;
        ///< get HTTP accept
    std::ctstring_t & httpCookie() const xWARN_UNUSED_RV;
        ///< get HTTP cookie
    std::ctstring_t & httpPragma() const xWARN_UNUSED_RV;
        ///< get HTTP pragma
    std::ctstring_t & httpUserAgent() const xWARN_UNUSED_RV;
        ///< get HTTP user agent
    std::ctstring_t & pathInfo() const xWARN_UNUSED_RV;
        ///< get path info
    std::ctstring_t & pathTranslated() const xWARN_UNUSED_RV;
        ///< get path translated
    std::ctstring_t & queryString() const xWARN_UNUSED_RV;
        ///< get query string
    std::ctstring_t & remoteAddr() const xWARN_UNUSED_RV;
        ///< get remote address
    std::ctstring_t & remoteHost() const xWARN_UNUSED_RV;
        ///< get remote host
    std::ctstring_t & remoteIdent() const xWARN_UNUSED_RV;
        ///< et remote ident
    std::ctstring_t & remotePort() const xWARN_UNUSED_RV;
        ///< get remote port
    std::ctstring_t & remoteUser() const xWARN_UNUSED_RV;
        ///< get remote user
    std::ctstring_t & requestMethod() const xWARN_UNUSED_RV;
        ///< get request method
    std::ctstring_t & requestUri() const xWARN_UNUSED_RV;
        ///< get request URI
    std::ctstring_t & scriptFilename() const xWARN_UNUSED_RV;
        ///< get script file name
    std::ctstring_t & scriptName() const xWARN_UNUSED_RV;
        ///< get script name
    std::ctstring_t & serverAdmin() const xWARN_UNUSED_RV;
        ///< get server admin
    std::ctstring_t & serverName() const xWARN_UNUSED_RV;
        ///< get server name
    std::ctstring_t & serverPort() const xWARN_UNUSED_RV;
        ///< get server port
    std::ctstring_t & serverProtocol() const xWARN_UNUSED_RV;
        ///< get server protocol
    std::ctstring_t & serverSoftware() const xWARN_UNUSED_RV;
        ///< get server software
    std::ctstring_t & httpReferer() const xWARN_UNUSED_RV;
        ///< get HTTP referer
    std::ctstring_t & httpHost() const xWARN_UNUSED_RV;
        ///< get HTTP host
    std::ctstring_t & httpAcceptLanguage() const xWARN_UNUSED_RV;
        ///< get HTTP accept language
    std::ctstring_t & countryCode() const xWARN_UNUSED_RV;
        ///< get country code

    ExRequestType     requestType() const xWARN_UNUSED_RV;
        ///< get request type
    std::tstring_t    dump() const xWARN_UNUSED_RV;
        ///< get dump

private:
    CxCgi           & _cgi;                ///< CxCgi object
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
    ExRequestType     _requestType;          ///< request method

    bool_t            _construct();
        ///< initiate class data
};
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
class CxCgiCookies :
    private CxNonCopyable
    /// CGI cookies
{
public:
    typedef std::vector<CxCookiePv0 *> TCookies;

    TCookies        items;    ///< cookie items

                    CxCgiCookies(CxCgi &cgi);
        ///< constructor
    virtual        ~CxCgiCookies();
        ///< destructor

    std::tstring_t  dump() const xWARN_UNUSED_RV;
        ///< get dump
    std::tstring_t  operator[](std::ctstring_t &cookieName) xWARN_UNUSED_RV;
        ///< no case searching cookie value by name from list

private:
    CxCgi          &_cgi;    ///< CxCgi object

    void_t          _construct();
        ///< initiate class data
};
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
class CxCgiFormData :
    private CxNonCopyable
    /// CGI form data
{
public:
                     CxCgiFormData(CxCgi &cgi, std::csize_t &maxSize);
        ///< constructor
    virtual         ~CxCgiFormData() {}
        ///< destructor

    std::ctstring_t &rawData() const xWARN_UNUSED_RV;
        ///< get raw data
    std::tstring_t   dump() const xWARN_UNUSED_RV;
        ///< get dump

private:
    // consts
    std::csize_t     _maxData;    ///< maximum data size

    CxCgi           &_cgi;        ///< CxCgi object
    std::tstring_t   _formData;     ///< form data

    void_t           _construct();
        ///< initiate class data
};
//------------------------------------------------------------------------------

xNAMESPACE_END(NxCgi)
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
class CxCgi :
    private CxNonCopyable
    /// CGI
{
public:
    static std::csize_t     MAX_DATA_SIZE_DEFAULT = 1024 * 1024;    ///< maximum data size by default

    NxCgi::CxCgiEnvironment Environment;    ///< CxCgiEnvironment object
    NxCgi::CxCgiCookies     Cookies;        ///< CxCgiCookies object
    NxCgi::CxCgiFormData    Formdata;       ///< CxCgiFormData object

    explicit                CxCgi(std::csize_t &maxSize);
        ///< constructor
    virtual                ~CxCgi() {}
        ///< destructor

    std::tstring_t          dump() const xWARN_UNUSED_RV;
        ///< get dump
    static void_t           redirect(std::ctstring_t &url);
        ///< redirect to URL
    static void_t           pageShow(std::ctstring_t &filePath);
        ///< show page from file

    //encoding, decoding
    static void_t           uriEncode(std::ctstring_t &uri, std::ctstring_t &reserved,
                                std::tstring_t *encodedStr);
        ///< encode URI
    static void_t           uriDecode(std::ctstring_t &uri, std::tstring_t *decodedStr);
        ///< decode URI

private:
    //--------------------------------------------------
    //encoding, decoding
    int_t                   cgl_parsecgibuf(/*cgllist *cdata, */char *query) xWARN_UNUSED_RV;
        ///< cgl_parsecgibuf

    int_t                   cgl_urlencode(char *s, FILE *fw) xWARN_UNUSED_RV;
        ///< cgl_urlencode
    void_t                  cgl_urldecode(char *s);
        ///< cgl_urldecode

    void_t                  urlEscape(char *s, FILE *fw);
        ///< URL escape
    void_t                  urlUnescape(char *s);
        ///< URL unescape

    char                    cgl_hex2char(char *what) xWARN_UNUSED_RV;
        ///< hex to char
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Net/CxCgi.cpp>
#endif
