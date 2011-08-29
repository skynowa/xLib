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

            const std::tstring &sGetAuthType          () const;
            	///< get auth type
            const std::tstring &sGetContentLength     () const;
            	///< get content length
            const std::tstring &sGetContentType       () const;
            	///< get content type
            const std::tstring &sGetDocumentRoot      () const;
            	///< get document roor
            const std::tstring &sGetGatewayInterface  () const;
            	///< get gateway interface
            const std::tstring &sGetHttpAccept        () const;
            	///< get HTTP accept
            const std::tstring &sGetHttpCookie        () const;
            	///< get HTTP cookie
            const std::tstring &sGetHttpPragma        () const;
            	///< get HTTP pragma
            const std::tstring &sGetHttpUserAgent     () const;
            	///< get HTTP user agent
            const std::tstring &sGetPathInfo          () const;
            	///< get path info
            const std::tstring &sGetPathTranslated    () const;
            	///< get path translated
            const std::tstring &sGetQueryString       () const;
            	///< get query string
            const std::tstring &sGetRemoteAddr        () const;
            	///< get remote address
            const std::tstring &sGetRemoteHost        () const;
            	///< get remote host
            const std::tstring &sGetRemoteIdent       () const;
            	///< et remote ident
            const std::tstring &sGetRemotePort        () const;
            	///< get remote port
            const std::tstring &sGetRemoteUser        () const;
            	///< get remote user
            const std::tstring &sGetRequestMethod     () const;
            	///< get request method
            const std::tstring &sGetRequestUri        () const;
            	///< get request URI
            const std::tstring &sGetScriptFilename    () const;
            	///< get script file name
            const std::tstring &sGetScriptName        () const;
            	///< get script name
            const std::tstring &sGetServerAdmin       () const;
            	///< get server admin
            const std::tstring &sGetServerName        () const;
            	///< get server name
            const std::tstring &sGetServerPort        () const;
            	///< get server port
            const std::tstring &sGetServerProtocol    () const;
            	///< get server protocol
            const std::tstring &sGetServerSoftware    () const;
            	///< get server software
            const std::tstring &sGetHttpReferer       () const;
            	///< get HTTP referer
            const std::tstring &sGetHttpHost          () const;
            	///< get HTTP host
            const std::tstring &sGetHttpAcceptLanguage() const;
            	///< get HTTP accept language
            const std::tstring &sGetCountryCode       () const;
            	///< get country code

            ERequestMethod      rmGetRequestMethod    () const;
            	///< get request method
            std::tstring        sGetDump              () const;
            	///< get dump

        private:
            CxCgi              &_m_ccgCgi;				///< CxCgi onject
            std::tstring        _m_sAuthType;			///< auth type
            std::tstring        _m_sContentLength;		///< content length
            std::tstring        _m_sContentType;		///< content type
            std::tstring        _m_sDocumentRoot;		///< document root
            std::tstring        _m_sGatewayInterface;	///< gateway interface
            std::tstring        _m_sHttpAccept;			///< HTTP accept
            std::tstring        _m_sHttpCookie;			///< HTTP cookie
            std::tstring        _m_sHttpPragma;			///< HTTP pragma
            std::tstring        _m_sHttpUserAgent;		///< HTTP user agent
            std::tstring        _m_sPathInfo;			///< path info
            std::tstring        _m_sPathTranslated;		///< path translated
            std::tstring        _m_sQueryString;		///< query string
            std::tstring        _m_sRemoteAddr;			///< remote address
            std::tstring        _m_sRemoteHost;			///< remote host
            std::tstring        _m_sRemoteIdent;		///< remote ident
            std::tstring        _m_sRemotePort;			///< remote port
            std::tstring        _m_sRemoteUser;			///< remote user
            std::tstring        _m_sRequestMethod;		///< request method
            std::tstring        _m_sRequestUri;			///< request URI
            std::tstring        _m_sScriptFilename;		///< script file name
            std::tstring        _m_sScriptName;			///< script name
            std::tstring        _m_sServerAdmin;		///< server admin
            std::tstring        _m_sServerName;			///< server name
            std::tstring        _m_sServerPort;			///< server port
            std::tstring        _m_sServerProtocol;		///< server protocol
            std::tstring        _m_sServerSoftware;		///< server software
            std::tstring        _m_sHttpReferer;		///< HTTP referer
            std::tstring        _m_sHttpHost;			///< HTTP host
            std::tstring        _m_sHttpAcceptLanguage;	///< HTTP accept language
            std::tstring        _m_sCountryCode;		///< country code
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

            std::tstring  sGetDump    () const;
            	///< get dump
            std::tstring  operator[]  (const std::tstring &csCookieName);
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

            const std::tstring &sGetRawData  () const;
            	///< get raw data
            std::tstring        sGetDump     () const;
            	///< get dump

        private:
            //consts
            const size_t        _m_cuiMaxData;	///< maximum data size

            CxCgi               &_m_ccgCgi;		///< CxCgi object
            std::tstring        _m_sFormData;	///< form data

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

        std::tstring            sGetDump       () const;
        	///< get dump
        static BOOL             bRedirect      (const std::tstring &csUrl);
        	///< redirect to URL
        static BOOL             bPageShow      (const std::tstring &csFilePath);
        	///< show page from file

        //encoding, decoding
        static BOOL             bUriEncode     (const std::tstring &csUri, const std::tstring &csReserved, std::tstring *psEncodedStr);
        	///< encode URI
        static BOOL             bUriDecode     (const std::tstring &csUri, std::tstring *psDecodedStr);
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
