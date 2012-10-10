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

namespace NxCgi {

    //---------------------------------------------------------------------------
    class CxCgiEnvironment :
        private CxNonCopyable
        /// CGI environment
    {
        public:
            enum ExRequestMethod
                /// request method
            {
                rmUknown,
                rmGet,
                rmPost
            };

                                 CxCgiEnvironment    (CxCgi &ccgCgi);
                ///< constructor
            virtual             ~CxCgiEnvironment    ();
                ///< destructor

            const std::tstring_t &sAuthType          () const;
                ///< get auth type
            const std::tstring_t &sContentLength     () const;
                ///< get content length
            const std::tstring_t &sContentType       () const;
                ///< get content type
            const std::tstring_t &sDocumentRoot      () const;
                ///< get document roor
            const std::tstring_t &sGatewayInterface  () const;
                ///< get gateway interface
            const std::tstring_t &sHttpAccept        () const;
                ///< get HTTP accept
            const std::tstring_t &sHttpCookie        () const;
                ///< get HTTP cookie
            const std::tstring_t &sHttpPragma        () const;
                ///< get HTTP pragma
            const std::tstring_t &sHttpUserAgent     () const;
                ///< get HTTP user agent
            const std::tstring_t &sPathInfo          () const;
                ///< get path info
            const std::tstring_t &sPathTranslated    () const;
                ///< get path translated
            const std::tstring_t &sQueryString       () const;
                ///< get query string
            const std::tstring_t &sRemoteAddr        () const;
                ///< get remote address
            const std::tstring_t &sRemoteHost        () const;
                ///< get remote host
            const std::tstring_t &sRemoteIdent       () const;
                ///< et remote ident
            const std::tstring_t &sRemotePort        () const;
                ///< get remote port
            const std::tstring_t &sRemoteUser        () const;
                ///< get remote user
            const std::tstring_t &sRequestMethod     () const;
                ///< get request method
            const std::tstring_t &sRequestUri        () const;
                ///< get request URI
            const std::tstring_t &sScriptFilename    () const;
                ///< get script file name
            const std::tstring_t &sScriptName        () const;
                ///< get script name
            const std::tstring_t &sServerAdmin       () const;
                ///< get server admin
            const std::tstring_t &sServerName        () const;
                ///< get server name
            const std::tstring_t &sServerPort        () const;
                ///< get server port
            const std::tstring_t &sServerProtocol    () const;
                ///< get server protocol
            const std::tstring_t &sServerSoftware    () const;
                ///< get server software
            const std::tstring_t &sHttpReferer       () const;
                ///< get HTTP referer
            const std::tstring_t &sHttpHost          () const;
                ///< get HTTP host
            const std::tstring_t &sHttpAcceptLanguage() const;
                ///< get HTTP accept language
            const std::tstring_t &sCountryCode       () const;
                ///< get country code

            ExRequestMethod       rmRequestMethod    () const;
                ///< get request method
            std::tstring_t        sDump              () const;
                ///< get dump

        private:
            CxCgi                &_m_ccgCgi;                ///< CxCgi onject
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
            std::tstring_t        _m_sHttpReferer;          ///< HTTP referer
            std::tstring_t        _m_sHttpHost;             ///< HTTP host
            std::tstring_t        _m_sHttpAcceptLanguage;   ///< HTTP accept language
            std::tstring_t        _m_sCountryCode;          ///< country code
            ExRequestMethod       _m_rmRequestMethod;       ///< request method

            bool                  _bInit              ();
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

            TCookies        Items;    ///< cookie items

                            CxCgiCookies(CxCgi &ccgCgi);
                ///< constructor
            virtual        ~CxCgiCookies();
                ///< destructor

            std::tstring_t  sDump       () const;
                ///< get dump
            std::tstring_t  operator[]  (const std::tstring_t &csCookieName);
                ///< no case searchig cookie value by name from list

        private:
            CxCgi          &_m_ccgCgi;    ///< CxCgi object

            void            _vInit      ();
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

            const std::tstring_t &sRawData     () const;
                ///< get raw data
            std::tstring_t        sDump        () const;
                ///< get dump

        private:
            //consts
            const size_t          _m_cuiMaxData;    ///< maximum data size

            CxCgi                &_m_ccgCgi;        ///< CxCgi object
            std::tstring_t        _m_sFormData;     ///< form data

            void                  _vInit       ();
                ///< initiate class data
    };
    //---------------------------------------------------------------------------

} //namespace NCgi
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

        std::tstring_t          sDump          () const;
            ///< get dump
        static bool             bRedirect      (const std::tstring_t &csUrl);
            ///< redirect to URL
        static bool             bPageShow      (const std::tstring_t &csFilePath);
            ///< show page from file

        //encoding, decoding
        static bool             bUriEncode     (const std::tstring_t &csUri, const std::tstring_t &csReserved, std::tstring_t *psEncodedStr);
            ///< encode URI
        static bool             bUriDecode     (const std::tstring_t &csUri, std::tstring_t *psDecodedStr);
            ///< decode URI

    private:
        //--------------------------------------------------
        //encoding, decoding
        int                     cgl_parsecgibuf(/*cgllist *cdata, */char *query);
            ///< cgl_parsecgibuf

        int                     cgl_urlencode  (char *s, FILE *fw);
            ///< cgl_urlencode
        void                    cgl_urldecode  (char *s);
            ///< cgl_urldecode

        int                     bUrlEscape     (char *s, FILE *fw);
            ///< URL escape
        int                     bUrlUnescape   (char *s);
            ///< URL unescape

        char                    cgl_hex2char   (char *what);
            ///< hex to char
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCgiH


#if xTODO
    format_map(resp, req, req.env, "Environment Variables");
    format_map(resp, req, req.get, "GET Variables");
    format_map(resp, req, req.post, "POST Variables");
    format_map(resp, req, req.uploads, "File Uploads");
    format_map(resp, req, req.cookies, "Cookie Variables");
#endif

#if xTODO
    fprintf(stdout, "Location: %s\n\n", "http://www.yandex.ru/");
#endif

#if xTODO
    GET  in QUERY_STRING
    POST in std::in
#endif
