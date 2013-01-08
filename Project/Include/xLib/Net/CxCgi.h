/**
 * \file  CxCgi.h
 * \brief CGI
 */


#ifndef xLib_Net_CxCgiH
#define xLib_Net_CxCgiH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCgi;
class CxCookiePv0;
class CxCookiePv1;

xNAMESPACE_BEGIN(NxCgi)

//---------------------------------------------------------------------------
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
    virtual             ~CxCgiEnvironment   ();
        ///< destructor

    const std::tstring_t &authType          () const xWARN_UNUSED_RESULT;
        ///< get auth type
    const std::tstring_t &contentLength     () const xWARN_UNUSED_RESULT;
        ///< get content length
    const std::tstring_t &contentType       () const xWARN_UNUSED_RESULT;
        ///< get content type
    const std::tstring_t &documentRoot      () const xWARN_UNUSED_RESULT;
        ///< get document root
    const std::tstring_t &gatewayInterface  () const xWARN_UNUSED_RESULT;
        ///< get gateway interface
    const std::tstring_t &httpAccept        () const xWARN_UNUSED_RESULT;
        ///< get HTTP accept
    const std::tstring_t &httpCookie        () const xWARN_UNUSED_RESULT;
        ///< get HTTP cookie
    const std::tstring_t &httpPragma        () const xWARN_UNUSED_RESULT;
        ///< get HTTP pragma
    const std::tstring_t &httpUserAgent     () const xWARN_UNUSED_RESULT;
        ///< get HTTP user agent
    const std::tstring_t &pathInfo          () const xWARN_UNUSED_RESULT;
        ///< get path info
    const std::tstring_t &pathTranslated    () const xWARN_UNUSED_RESULT;
        ///< get path translated
    const std::tstring_t &queryString       () const xWARN_UNUSED_RESULT;
        ///< get query string
    const std::tstring_t &remoteAddr        () const xWARN_UNUSED_RESULT;
        ///< get remote address
    const std::tstring_t &remoteHost        () const xWARN_UNUSED_RESULT;
        ///< get remote host
    const std::tstring_t &remoteIdent       () const xWARN_UNUSED_RESULT;
        ///< et remote ident
    const std::tstring_t &remotePort        () const xWARN_UNUSED_RESULT;
        ///< get remote port
    const std::tstring_t &remoteUser        () const xWARN_UNUSED_RESULT;
        ///< get remote user
    const std::tstring_t &requestMethod     () const xWARN_UNUSED_RESULT;
        ///< get request method
    const std::tstring_t &requestUri        () const xWARN_UNUSED_RESULT;
        ///< get request URI
    const std::tstring_t &scriptFilename    () const xWARN_UNUSED_RESULT;
        ///< get script file name
    const std::tstring_t &scriptName        () const xWARN_UNUSED_RESULT;
        ///< get script name
    const std::tstring_t &serverAdmin       () const xWARN_UNUSED_RESULT;
        ///< get server admin
    const std::tstring_t &serverName        () const xWARN_UNUSED_RESULT;
        ///< get server name
    const std::tstring_t &serverPort        () const xWARN_UNUSED_RESULT;
        ///< get server port
    const std::tstring_t &serverProtocol    () const xWARN_UNUSED_RESULT;
        ///< get server protocol
    const std::tstring_t &serverSoftware    () const xWARN_UNUSED_RESULT;
        ///< get server software
    const std::tstring_t &httpReferer       () const xWARN_UNUSED_RESULT;
        ///< get HTTP referer
    const std::tstring_t &httpHost          () const xWARN_UNUSED_RESULT;
        ///< get HTTP host
    const std::tstring_t &httpAcceptLanguage() const xWARN_UNUSED_RESULT;
        ///< get HTTP accept language
    const std::tstring_t &countryCode       () const xWARN_UNUSED_RESULT;
        ///< get country code

    ExRequestType        requestType        () const xWARN_UNUSED_RESULT;
        ///< get request type
    std::tstring_t       dump               () const xWARN_UNUSED_RESULT;
        ///< get dump

private:
    CxCgi                &_m_ccgCgi;                ///< CxCgi object
    std::tstring_t        _m_sAuthType;             ///< auth type
    std::tstring_t        _m_sContentLength;        ///< content length
    std::tstring_t        _m_sContentType;          ///< content type
    std::tstring_t        _m_sDocumentRoot;         ///< document root
    std::tstring_t        _m_sGatewayInterface;     ///< gateway interface
    std::tstring_t        _m_sHttpAccept;           ///< HTTP accept
    std::tstring_t        _m_sHttpCookie;           ///< HTTP cookie
    std::tstring_t        _m_sHttpPragma;           ///< HTTP pragma
    std::tstring_t        _m_sHttpUserAgent;        ///< HTTP user agent
    std::tstring_t        _m_sPathInfo;             ///< path info
    std::tstring_t        _m_sPathTranslated;       ///< path translated
    std::tstring_t        _m_sQueryString;          ///< query string
    std::tstring_t        _m_sRemoteAddr;           ///< remote address
    std::tstring_t        _m_sRemoteHost;           ///< remote host
    std::tstring_t        _m_sRemoteIdent;          ///< remote ident
    std::tstring_t        _m_sRemotePort;           ///< remote port
    std::tstring_t        _m_sRemoteUser;           ///< remote user
    std::tstring_t        _m_sRequestMethod;        ///< request method
    std::tstring_t        _m_sRequestUri;           ///< request URI
    std::tstring_t        _m_sScriptFilename;       ///< script file name
    std::tstring_t        _m_sScriptName;           ///< script name
    std::tstring_t        _m_sServerAdmin;          ///< server admin
    std::tstring_t        _m_sServerName;           ///< server name
    std::tstring_t        _m_sServerPort;           ///< server port
    std::tstring_t        _m_sServerProtocol;       ///< server protocol
    std::tstring_t        _m_sServerSoftware;       ///< server software
    std::tstring_t        _m_sHttpReferer;          ///< HTTP referrer
    std::tstring_t        _m_sHttpHost;             ///< HTTP host
    std::tstring_t        _m_sHttpAcceptLanguage;   ///< HTTP accept language
    std::tstring_t        _m_sCountryCode;          ///< country code
    ExRequestType         _m_rtRequestType;         ///< request method

    bool                  _init              ();
        ///< initiate class data
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
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

    std::tstring_t  dump       () const xWARN_UNUSED_RESULT;
        ///< get dump
    std::tstring_t  operator[]  (const std::tstring_t &csCookieName) xWARN_UNUSED_RESULT;
        ///< no case searching cookie value by name from list

private:
    CxCgi          &_m_ccgCgi;    ///< CxCgi object

    void            _init      ();
        ///< initiate class data
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class CxCgiFormData :
    private CxNonCopyable
    /// CGI form data
{
public:
                          CxCgiFormData(CxCgi &ccgCgi, const size_t cuiMaxSize);
        ///< constructor
    virtual              ~CxCgiFormData();
        ///< destructor

    const std::tstring_t &rawData     () const xWARN_UNUSED_RESULT;
        ///< get raw data
    std::tstring_t        dump        () const xWARN_UNUSED_RESULT;
        ///< get dump

private:
    // consts
    const size_t          _m_cuiMaxData;    ///< maximum data size

    CxCgi                &_m_ccgCgi;        ///< CxCgi object
    std::tstring_t        _m_sFormData;     ///< form data

    void                  _init       ();
        ///< initiate class data
};
//---------------------------------------------------------------------------

xNAMESPACE_END(NxCgi)
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class CxCgi :
    private CxNonCopyable
    /// CGI
{
public:
    static const size_t     MAX_DATA_SIZE_DEFAULT = 1024 * 1024;    ///< maximum data size by default

    NxCgi::CxCgiEnvironment Environment;    ///< CxCgiEnvironment object
    NxCgi::CxCgiCookies     Cookies;        ///< CxCgiCookies object
    NxCgi::CxCgiFormData    Formdata;       ///< CxCgiFormData object

    explicit                CxCgi          (const size_t cuiMaxSize);
        ///< constructor
    virtual                ~CxCgi          ();
        ///< destructor

    std::tstring_t          dump          () const xWARN_UNUSED_RESULT;
        ///< get dump
    static void             redirect      (const std::tstring_t &csUrl);
        ///< redirect to URL
    static void             pageShow      (const std::tstring_t &csFilePath);
        ///< show page from file

    //encoding, decoding
    static void             uriEncode     (const std::tstring_t &csUri, const std::tstring_t &csReserved, std::tstring_t *psEncodedStr);
        ///< encode URI
    static void             uriDecode     (const std::tstring_t &csUri, std::tstring_t *psDecodedStr);
        ///< decode URI

private:
    //--------------------------------------------------
    //encoding, decoding
    int                     cgl_parsecgibuf(/*cgllist *cdata, */char *query) xWARN_UNUSED_RESULT;
        ///< cgl_parsecgibuf

    int                     cgl_urlencode  (char *s, FILE *fw) xWARN_UNUSED_RESULT;
        ///< cgl_urlencode
    void                    cgl_urldecode  (char *s);
        ///< cgl_urldecode

    void                    urlEscape     (char *s, FILE *fw);
        ///< URL escape
    void                    urlUnescape   (char *s);
        ///< URL unescape

    char                    cgl_hex2char   (char *what) xWARN_UNUSED_RESULT;
        ///< hex to char
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Net_CxCgiH
