/**
 * \file  CxCgi.h
 * \brief CGI
 */


#ifndef xLib_Net_CxCgiH
#define xLib_Net_CxCgiH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
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

                      CxCgiEnvironment   (CxCgi &ccgCgi);
        ///< constructor
    virtual          ~CxCgiEnvironment   ();
        ///< destructor

    std::ctstring_t & authType          () const xWARN_UNUSED_RV;
        ///< get auth type
    std::ctstring_t & contentLength     () const xWARN_UNUSED_RV;
        ///< get content length
    std::ctstring_t & contentType       () const xWARN_UNUSED_RV;
        ///< get content type
    std::ctstring_t & documentRoot      () const xWARN_UNUSED_RV;
        ///< get document root
    std::ctstring_t & gatewayInterface  () const xWARN_UNUSED_RV;
        ///< get gateway interface
    std::ctstring_t & httpAccept        () const xWARN_UNUSED_RV;
        ///< get HTTP accept
    std::ctstring_t & httpCookie        () const xWARN_UNUSED_RV;
        ///< get HTTP cookie
    std::ctstring_t & httpPragma        () const xWARN_UNUSED_RV;
        ///< get HTTP pragma
    std::ctstring_t & httpUserAgent     () const xWARN_UNUSED_RV;
        ///< get HTTP user agent
    std::ctstring_t & pathInfo          () const xWARN_UNUSED_RV;
        ///< get path info
    std::ctstring_t & pathTranslated    () const xWARN_UNUSED_RV;
        ///< get path translated
    std::ctstring_t & queryString       () const xWARN_UNUSED_RV;
        ///< get query string
    std::ctstring_t & remoteAddr        () const xWARN_UNUSED_RV;
        ///< get remote address
    std::ctstring_t & remoteHost        () const xWARN_UNUSED_RV;
        ///< get remote host
    std::ctstring_t & remoteIdent       () const xWARN_UNUSED_RV;
        ///< et remote ident
    std::ctstring_t & remotePort        () const xWARN_UNUSED_RV;
        ///< get remote port
    std::ctstring_t & remoteUser        () const xWARN_UNUSED_RV;
        ///< get remote user
    std::ctstring_t & requestMethod     () const xWARN_UNUSED_RV;
        ///< get request method
    std::ctstring_t & requestUri        () const xWARN_UNUSED_RV;
        ///< get request URI
    std::ctstring_t & scriptFilename    () const xWARN_UNUSED_RV;
        ///< get script file name
    std::ctstring_t & scriptName        () const xWARN_UNUSED_RV;
        ///< get script name
    std::ctstring_t & serverAdmin       () const xWARN_UNUSED_RV;
        ///< get server admin
    std::ctstring_t & serverName        () const xWARN_UNUSED_RV;
        ///< get server name
    std::ctstring_t & serverPort        () const xWARN_UNUSED_RV;
        ///< get server port
    std::ctstring_t & serverProtocol    () const xWARN_UNUSED_RV;
        ///< get server protocol
    std::ctstring_t & serverSoftware    () const xWARN_UNUSED_RV;
        ///< get server software
    std::ctstring_t & httpReferer       () const xWARN_UNUSED_RV;
        ///< get HTTP referer
    std::ctstring_t & httpHost          () const xWARN_UNUSED_RV;
        ///< get HTTP host
    std::ctstring_t & httpAcceptLanguage() const xWARN_UNUSED_RV;
        ///< get HTTP accept language
    std::ctstring_t & countryCode       () const xWARN_UNUSED_RV;
        ///< get country code

    ExRequestType     requestType        () const xWARN_UNUSED_RV;
        ///< get request type
    std::tstring_t    dump               () const xWARN_UNUSED_RV;
        ///< get dump

private:
    CxCgi           & _m_ccgCgi;                ///< CxCgi object
    std::tstring_t    _m_sAuthType;             ///< auth type
    std::tstring_t    _m_sContentLength;        ///< content length
    std::tstring_t    _m_sContentType;          ///< content type
    std::tstring_t    _m_sDocumentRoot;         ///< document root
    std::tstring_t    _m_sGatewayInterface;     ///< gateway interface
    std::tstring_t    _m_sHttpAccept;           ///< HTTP accept
    std::tstring_t    _m_sHttpCookie;           ///< HTTP cookie
    std::tstring_t    _m_sHttpPragma;           ///< HTTP pragma
    std::tstring_t    _m_sHttpUserAgent;        ///< HTTP user agent
    std::tstring_t    _m_sPathInfo;             ///< path info
    std::tstring_t    _m_sPathTranslated;       ///< path translated
    std::tstring_t    _m_sQueryString;          ///< query string
    std::tstring_t    _m_sRemoteAddr;           ///< remote address
    std::tstring_t    _m_sRemoteHost;           ///< remote host
    std::tstring_t    _m_sRemoteIdent;          ///< remote ident
    std::tstring_t    _m_sRemotePort;           ///< remote port
    std::tstring_t    _m_sRemoteUser;           ///< remote user
    std::tstring_t    _m_sRequestMethod;        ///< request method
    std::tstring_t    _m_sRequestUri;           ///< request URI
    std::tstring_t    _m_sScriptFilename;       ///< script file name
    std::tstring_t    _m_sScriptName;           ///< script name
    std::tstring_t    _m_sServerAdmin;          ///< server admin
    std::tstring_t    _m_sServerName;           ///< server name
    std::tstring_t    _m_sServerPort;           ///< server port
    std::tstring_t    _m_sServerProtocol;       ///< server protocol
    std::tstring_t    _m_sServerSoftware;       ///< server software
    std::tstring_t    _m_sHttpReferer;          ///< HTTP referrer
    std::tstring_t    _m_sHttpHost;             ///< HTTP host
    std::tstring_t    _m_sHttpAcceptLanguage;   ///< HTTP accept language
    std::tstring_t    _m_sCountryCode;          ///< country code
    ExRequestType     _m_rtRequestType;         ///< request method

    bool_t            _construct         ();
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

                    CxCgiCookies(CxCgi &ccgCgi);
        ///< constructor
    virtual        ~CxCgiCookies();
        ///< destructor

    std::tstring_t  dump        () const xWARN_UNUSED_RV;
        ///< get dump
    std::tstring_t  operator[]  (std::ctstring_t &csCookieName) xWARN_UNUSED_RV;
        ///< no case searching cookie value by name from list

private:
    CxCgi          &_m_ccgCgi;    ///< CxCgi object

    void_t          _construct  ();
        ///< initiate class data
};
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
class CxCgiFormData :
    private CxNonCopyable
    /// CGI form data
{
public:
                     CxCgiFormData(CxCgi &ccgCgi, std::csize_t &cuiMaxSize);
        ///< constructor
    virtual         ~CxCgiFormData();
        ///< destructor

    std::ctstring_t &rawData      () const xWARN_UNUSED_RV;
        ///< get raw data
    std::tstring_t   dump         () const xWARN_UNUSED_RV;
        ///< get dump

private:
    // consts
    std::csize_t     _m_cuiMaxData;    ///< maximum data size

    CxCgi           &_m_ccgCgi;        ///< CxCgi object
    std::tstring_t   _m_sFormData;     ///< form data

    void_t           _construct   ();
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
    static std::csize_t     MAX_DATA_SIZE_DEFAULT;    ///< maximum data size by default

    NxCgi::CxCgiEnvironment Environment;    ///< CxCgiEnvironment object
    NxCgi::CxCgiCookies     Cookies;        ///< CxCgiCookies object
    NxCgi::CxCgiFormData    Formdata;       ///< CxCgiFormData object

    explicit                CxCgi         (std::csize_t &cuiMaxSize);
        ///< constructor
    virtual                ~CxCgi         ();
        ///< destructor

    std::tstring_t          dump          () const xWARN_UNUSED_RV;
        ///< get dump
    static void_t           redirect      (std::ctstring_t &csUrl);
        ///< redirect to URL
    static void_t           pageShow      (std::ctstring_t &csFilePath);
        ///< show page from file

    //encoding, decoding
    static void_t           uriEncode     (std::ctstring_t &csUri, std::ctstring_t &csReserved, std::tstring_t *psEncodedStr);
        ///< encode URI
    static void_t           uriDecode     (std::ctstring_t &csUri, std::tstring_t *psDecodedStr);
        ///< decode URI

private:
    //--------------------------------------------------
    //encoding, decoding
    int_t                   cgl_parsecgibuf(/*cgllist *cdata, */char *query) xWARN_UNUSED_RV;
        ///< cgl_parsecgibuf

    int_t                   cgl_urlencode  (char *s, FILE *fw) xWARN_UNUSED_RV;
        ///< cgl_urlencode
    void_t                  cgl_urldecode  (char *s);
        ///< cgl_urldecode

    void_t                  urlEscape      (char *s, FILE *fw);
        ///< URL escape
    void_t                  urlUnescape    (char *s);
        ///< URL unescape

    char                    cgl_hex2char   (char *what) xWARN_UNUSED_RV;
        ///< hex to char
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Net_CxCgiH
