/**
 * \file  CxCgi.h
 * \brief CGI
 */


#ifndef xLib_Net_CxCgiH
#define xLib_Net_CxCgiH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#include <xLib/Net/CxCookiePv0.h>
#include <xLib/Net/CxCookiePv1.h>
//---------------------------------------------------------------------------
class CxCgi;

namespace NxCgi {

    //---------------------------------------------------------------------------
    class CxCgiEnvironment :
        public CxNonCopyable
        /// CGI environment
    {
        public:
            enum ERequestMethod
                /// request method
            {
                rmUknown,
                rmGet,
                rmPost
            };

                               CxCgiEnvironment       (CxCgi &ccgCgi);
                ///< constructor
            virtual           ~CxCgiEnvironment       ();
            	///< destructor

            const std::string_t &sGetAuthType          () const;
            	///< get auth type
            const std::string_t &sGetContentLength     () const;
            	///< get content length
            const std::string_t &sGetContentType       () const;
            	///< get content type
            const std::string_t &sGetDocumentRoot      () const;
            	///< get document roor
            const std::string_t &sGetGatewayInterface  () const;
            	///< get gateway interface
            const std::string_t &sGetHttpAccept        () const;
            	///< get HTTP accept
            const std::string_t &sGetHttpCookie        () const;
            	///< get HTTP cookie
            const std::string_t &sGetHttpPragma        () const;
            	///< get HTTP pragma
            const std::string_t &sGetHttpUserAgent     () const;
            	///< get HTTP user agent
            const std::string_t &sGetPathInfo          () const;
            	///< get path info
            const std::string_t &sGetPathTranslated    () const;
            	///< get path translated
            const std::string_t &sGetQueryString       () const;
            	///< get query string
            const std::string_t &sGetRemoteAddr        () const;
            	///< get remote address
            const std::string_t &sGetRemoteHost        () const;
            	///< get remote host
            const std::string_t &sGetRemoteIdent       () const;
            	///< et remote ident
            const std::string_t &sGetRemotePort        () const;
            	///< get remote port
            const std::string_t &sGetRemoteUser        () const;
            	///< get remote user
            const std::string_t &sGetRequestMethod     () const;
            	///< get request method
            const std::string_t &sGetRequestUri        () const;
            	///< get request URI
            const std::string_t &sGetScriptFilename    () const;
            	///< get script file name
            const std::string_t &sGetScriptName        () const;
            	///< get script name
            const std::string_t &sGetServerAdmin       () const;
            	///< get server admin
            const std::string_t &sGetServerName        () const;
            	///< get server name
            const std::string_t &sGetServerPort        () const;
            	///< get server port
            const std::string_t &sGetServerProtocol    () const;
            	///< get server protocol
            const std::string_t &sGetServerSoftware    () const;
            	///< get server software
            const std::string_t &sGetHttpReferer       () const;
            	///< get HTTP referer
            const std::string_t &sGetHttpHost          () const;
            	///< get HTTP host
            const std::string_t &sGetHttpAcceptLanguage() const;
            	///< get HTTP accept language
            const std::string_t &sGetCountryCode       () const;
            	///< get country code

            ERequestMethod      rmGetRequestMethod    () const;
            	///< get request method
            std::string_t        sGetDump              () const;
            	///< get dump

        private:
            CxCgi              &_m_ccgCgi;				///< CxCgi onject
            std::string_t        _m_sAuthType;			///< auth type
            std::string_t        _m_sContentLength;		///< content length
            std::string_t        _m_sContentType;		///< content type
            std::string_t        _m_sDocumentRoot;		///< document root
            std::string_t        _m_sGatewayInterface;	///< gateway interface
            std::string_t        _m_sHttpAccept;			///< HTTP accept
            std::string_t        _m_sHttpCookie;			///< HTTP cookie
            std::string_t        _m_sHttpPragma;			///< HTTP pragma
            std::string_t        _m_sHttpUserAgent;		///< HTTP user agent
            std::string_t        _m_sPathInfo;			///< path info
            std::string_t        _m_sPathTranslated;		///< path translated
            std::string_t        _m_sQueryString;		///< query string
            std::string_t        _m_sRemoteAddr;			///< remote address
            std::string_t        _m_sRemoteHost;			///< remote host
            std::string_t        _m_sRemoteIdent;		///< remote ident
            std::string_t        _m_sRemotePort;			///< remote port
            std::string_t        _m_sRemoteUser;			///< remote user
            std::string_t        _m_sRequestMethod;		///< request method
            std::string_t        _m_sRequestUri;			///< request URI
            std::string_t        _m_sScriptFilename;		///< script file name
            std::string_t        _m_sScriptName;			///< script name
            std::string_t        _m_sServerAdmin;		///< server admin
            std::string_t        _m_sServerName;			///< server name
            std::string_t        _m_sServerPort;			///< server port
            std::string_t        _m_sServerProtocol;		///< server protocol
            std::string_t        _m_sServerSoftware;		///< server software
            std::string_t        _m_sHttpReferer;		///< HTTP referer
            std::string_t        _m_sHttpHost;			///< HTTP host
            std::string_t        _m_sHttpAcceptLanguage;	///< HTTP accept language
            std::string_t        _m_sCountryCode;		///< country code
            ERequestMethod      _m_rmRequestMethod;		///< request method

            BOOL                _bInit                ();
            	///< initiate class data
    };
    //---------------------------------------------------------------------------


    //---------------------------------------------------------------------------
    class CxCgiCookies :
        public CxNonCopyable
        /// CGI cookies
    {
        public:
            typedef std::vector<CxCookiePv0 *> TCookies;

            TCookies      Items;	///< cookie items

                          CxCgiCookies(CxCgi &ccgCgi);
                ///< constructor
            virtual      ~CxCgiCookies();
            	///< destructor

            std::string_t  sGetDump    () const;
            	///< get dump
            std::string_t  operator[]  (const std::string_t &csCookieName);
            	///< no case searchig cookie value by name from list

        private:
            CxCgi        &_m_ccgCgi;	///< CxCgi object

            BOOL          _bInit      ();
            	///< initiate class data
    };
    //---------------------------------------------------------------------------


    //---------------------------------------------------------------------------
    class CxCgiFormData :
        public CxNonCopyable
        /// CGI form data
    {
        public:
                                CxCgiFormData(CxCgi &ccgCgi, const size_t cuiMaxSize);
                ///< constructor
            virtual            ~CxCgiFormData();
            	///< destructor

            const std::string_t &sGetRawData  () const;
            	///< get raw data
            std::string_t        sGetDump     () const;
            	///< get dump

        private:
            //consts
            const size_t        _m_cuiMaxData;	///< maximum data size

            CxCgi               &_m_ccgCgi;		///< CxCgi object
            std::string_t        _m_sFormData;	///< form data

            BOOL                _bInit       ();
            	///< initiate class data
    };
    //---------------------------------------------------------------------------

} //namespace NCgi
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class CxCgi :
    public CxNonCopyable
    /// CGI
{
    public:
        static const size_t     MAX_DATA_SIZE_DEFAULT = 1024 * 1024;	///< maximum data size by default

        NxCgi::CxCgiEnvironment Environment;	///< CxCgiEnvironment object
        NxCgi::CxCgiCookies     Cookies;	    ///< CxCgiCookies object
        NxCgi::CxCgiFormData    Formdata;	    ///< CxCgiFormData object

        explicit                CxCgi          (const size_t cuiMaxSize);
        	///< constructor
        virtual                ~CxCgi          ();
        	///< destructor

        std::string_t            sGetDump       () const;
        	///< get dump
        static BOOL             bRedirect      (const std::string_t &csUrl);
        	///< redirect to URL
        static BOOL             bPageShow      (const std::string_t &csFilePath);
        	///< show page from file

        //encoding, decoding
        static BOOL             bUriEncode     (const std::string_t &csUri, const std::string_t &csReserved, std::string_t *psEncodedStr);
        	///< encode URI
        static BOOL             bUriDecode     (const std::string_t &csUri, std::string_t *psDecodedStr);
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
