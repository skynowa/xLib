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
            virtual           ~CxCgiEnvironment       ();

            const std::tstring &sGetAuthType          () const;
            const std::tstring &sGetContentLength     () const;
            const std::tstring &sGetContentType       () const;
            const std::tstring &sGetDocumentRoot      () const;
            const std::tstring &sGetGatewayInterface  () const;
            const std::tstring &sGetHttpAccept        () const;
            const std::tstring &sGetHttpCookie        () const;
            const std::tstring &sGetHttpPragma        () const;
            const std::tstring &sGetHttpUserAgent     () const;
            const std::tstring &sGetPathInfo          () const;
            const std::tstring &sGetPathTranslated    () const;
            const std::tstring &sGetQueryString       () const;
            const std::tstring &sGetRemoteAddr        () const;
            const std::tstring &sGetRemoteHost        () const;
            const std::tstring &sGetRemoteIdent       () const;
            const std::tstring &sGetRemotePort        () const;
            const std::tstring &sGetRemoteUser        () const;
            const std::tstring &sGetRequestMethod     () const;
            const std::tstring &sGetRequestUri        () const;
            const std::tstring &sGetScriptFilename    () const;
            const std::tstring &sGetScriptName        () const;
            const std::tstring &sGetServerAdmin       () const;
            const std::tstring &sGetServerName        () const;
            const std::tstring &sGetServerPort        () const;
            const std::tstring &sGetServerProtocol    () const;
            const std::tstring &sGetServerSoftware    () const;
            const std::tstring &sGetHttpReferer       () const;
            const std::tstring &sGetHttpHost          () const;
            const std::tstring &sGetHttpAcceptLanguage() const;
            const std::tstring &sGetCountryCode       () const;

            ERequestMethod      rmGetRequestMethod    () const;
            std::tstring        sGetDump              () const;

        private:
            CxCgi              &_m_ccgCgi;
            std::tstring        _m_sAuthType;
            std::tstring        _m_sContentLength;
            std::tstring        _m_sContentType;
            std::tstring        _m_sDocumentRoot;
            std::tstring        _m_sGatewayInterface;
            std::tstring        _m_sHttpAccept;
            std::tstring        _m_sHttpCookie;
            std::tstring        _m_sHttpPragma;
            std::tstring        _m_sHttpUserAgent;
            std::tstring        _m_sPathInfo;
            std::tstring        _m_sPathTranslated;
            std::tstring        _m_sQueryString;
            std::tstring        _m_sRemoteAddr;
            std::tstring        _m_sRemoteHost;
            std::tstring        _m_sRemoteIdent;
            std::tstring        _m_sRemotePort;
            std::tstring        _m_sRemoteUser;
            std::tstring        _m_sRequestMethod;
            std::tstring        _m_sRequestUri;
            std::tstring        _m_sScriptFilename;
            std::tstring        _m_sScriptName;
            std::tstring        _m_sServerAdmin;
            std::tstring        _m_sServerName;
            std::tstring        _m_sServerPort;
            std::tstring        _m_sServerProtocol;
            std::tstring        _m_sServerSoftware;
            std::tstring        _m_sHttpReferer;
            std::tstring        _m_sHttpHost;
            std::tstring        _m_sHttpAcceptLanguage;
            std::tstring        _m_sCountryCode;
            ERequestMethod      _m_rmRequestMethod;

            BOOL                _bInit                ();
    };
    //---------------------------------------------------------------------------


    //---------------------------------------------------------------------------
    class CxCgiCookies :
        public CxNonCopyable
        /// CGI cookies
    {
        public:
            typedef std::vector<CxCookiePv0 *> TCookies;

            TCookies      Items;
            
                          CxCgiCookies(CxCgi &ccgCgi);
            virtual      ~CxCgiCookies();
            
            std::tstring  sGetDump    () const;
            std::tstring  operator[]  (const std::tstring &csCookieName);

        private:
            CxCgi        &_m_ccgCgi;

            BOOL          _bInit      ();
    };
    //---------------------------------------------------------------------------


    //---------------------------------------------------------------------------
    class CxCgiFormData :
        public CxNonCopyable
        /// CGI form data
    {
        public:
                                CxCgiFormData(CxCgi &ccgCgi, const size_t cuiMaxSize);
            virtual            ~CxCgiFormData();

            const std::tstring &sGetRawData  () const;
            std::tstring        sGetDump     () const;

        private:
            //consts
            const size_t        _m_cuiMaxData;

            CxCgi               &_m_ccgCgi;
            std::tstring        _m_sFormData;

            BOOL                _bInit       ();
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
        static const size_t     MAX_DATA_SIZE_DEFAULT = 1024 * 1024;

        NxCgi::CxCgiEnvironment Environment;
        NxCgi::CxCgiCookies     Cookies;
        NxCgi::CxCgiFormData    Formdata;

        explicit                CxCgi          (const size_t cuiMaxSize);
        virtual                ~CxCgi          ();

        std::tstring            sGetDump       () const;

        static BOOL             bRedirect      (const std::tstring &csUrl);
        static BOOL             bPageShow      (const std::tstring &csFilePath);

        //encoding, decoding
        static BOOL             bUriEncode     (const std::tstring &csUri, const std::tstring &csReserved, std::tstring *psEncodedStr);
        static BOOL             bUriDecode     (const std::tstring &csUri, std::tstring *psDecodedStr);

    private:
        //--------------------------------------------------
        //encoding, decoding
        int                     cgl_parsecgibuf(/*cgllist *cdata, */char *query);

        int                     cgl_urlencode  (char *s, FILE *fw);
        void                    cgl_urldecode  (char *s);

        int                     bUrlEscape     (char *s, FILE *fw);
        int                     bUrlUnescape   (char *s);

        char                    cgl_hex2char   (char *what);
};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxCgiH























































/*
  format_map(resp, req, req.env, "Environment Variables");
  format_map(resp, req, req.get, "GET Variables");
  format_map(resp, req, req.post, "POST Variables");
  format_map(resp, req, req.uploads, "File Uploads");
  format_map(resp, req, req.cookies, "Cookie Variables");
*/

//    fprintf(stdout, "Location: %s\n\n", "http://www.yandex.ru/");

/*
GET  in QUERY_STRING
POST in std::in
*/

/*
Существует два способа, которыми данные из форм могут быть переданы серверу броузером:
URL-Encoded
Это наиболее используемый формат данных, передаваемых из форм. Содержимое полей формы выделяются из формы и передаются согласно спецификации HTML 1.0, а затем собираются в одну строку, где отделяются друг от друга символом амперсанда. Тип содержания сообщения устанавливается броузером в application/x-www-form-urlencoded.
Multipart Form Data
Данный формат разработан для эффективной загрузки файлов на сервер с использованием форм. Содержимое полей формы передается как многостраничное MIME сообщение. Каждое поле содержится в одной странице. Тип содержания, устанавливается броузером в multipart/form-data.
*/
