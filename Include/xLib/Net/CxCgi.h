/****************************************************************************
* Class name:  CxCgi
* Description: common gateway interace
* File name:   CxCgi.h
* Compilers:   Visual C++ 2010
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     11:01:2010 13:20:00
* Version:     1.0.0.0 Debug
*
*****************************************************************************/

#ifndef xLib_Net_CxCgiH
#define xLib_Net_CxCgiH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#include <xLib/Net/CxCookiePv0.h>
#include <xLib/Net/CxCookiePv1.h>
//---------------------------------------------------------------------------
class CxCgi;
//---------------------------------------------------------------------------
class CxCgiEnvironment : public CxNonCopyable  {
    public:
        enum ERequestMethod {
            rmUknown,
            rmGet,
            rmPost
        };

                       CxCgiEnvironment      (CxCgi &ccgCgi);
        virtual       ~CxCgiEnvironment      ();

        const tString &sGetAuthType          () const;
        const tString &sGetContentLength     () const;
        const tString &sGetContentType       () const;
        const tString &sGetDocumentRoot      () const;
        const tString &sGetGatewayInterface  () const;
        const tString &sGetHttpAccept        () const;
        const tString &sGetHttpCookie        () const;
        const tString &sGetHttpPragma        () const;
        const tString &sGetHttpUserAgent     () const;
        const tString &sGetPathInfo          () const;
        const tString &sGetPathTranslated    () const;
        const tString &sGetQueryString       () const;
        const tString &sGetRemoteAddr        () const;
        const tString &sGetRemoteHost        () const;
        const tString &sGetRemoteIdent       () const;
        const tString &sGetRemotePort        () const;
        const tString &sGetRemoteUser        () const;
        const tString &sGetRequestMethod     () const;
        const tString &sGetRequestUri        () const;
        const tString &sGetScriptFilename    () const;
        const tString &sGetScriptName        () const;
        const tString &sGetServerAdmin       () const;
        const tString &sGetServerName        () const;
        const tString &sGetServerPort        () const;
        const tString &sGetServerProtocol    () const;
        const tString &sGetServerSoftware    () const;
        const tString &sGetHttpReferer       () const;
        const tString &sGetHttpHost          () const;
        const tString &sGetHttpAcceptLanguage() const;
        const tString &sGetCountryCode       () const;

        ERequestMethod rmGetRequestMethod    () const;
        tString        sGetDump              () const;

    private:
        BOOL           _m_bRes;
        CxCgi         &_m_ccgCgi;
        tString        _m_sAuthType;
        tString        _m_sContentLength;
        tString        _m_sContentType;
        tString        _m_sDocumentRoot;
        tString        _m_sGatewayInterface;
        tString        _m_sHttpAccept;
        tString        _m_sHttpCookie;
        tString        _m_sHttpPragma;
        tString        _m_sHttpUserAgent;
        tString        _m_sPathInfo;
        tString        _m_sPathTranslated;
        tString        _m_sQueryString;
        tString        _m_sRemoteAddr;
        tString        _m_sRemoteHost;
        tString        _m_sRemoteIdent;
        tString        _m_sRemotePort;
        tString        _m_sRemoteUser;
        tString        _m_sRequestMethod;
        tString        _m_sRequestUri;
        tString        _m_sScriptFilename;
        tString        _m_sScriptName;
        tString        _m_sServerAdmin;
        tString        _m_sServerName;
        tString        _m_sServerPort;
        tString        _m_sServerProtocol;
        tString        _m_sServerSoftware;
        tString        _m_sHttpReferer;
        tString        _m_sHttpHost;
        tString        _m_sHttpAcceptLanguage;
        tString        _m_sCountryCode;
        ERequestMethod _m_rmRequestMethod;

        BOOL           _bInit                ();
};
//---------------------------------------------------------------------------
class CxCgiCookies : public CxNonCopyable  {
    public:
        typedef std::vector<CxCookiePv0 *> TCookies;

                 CxCgiCookies(CxCgi &ccgCgi);
        virtual ~CxCgiCookies();

        TCookies Items;
        tString  sGetDump    () const;

        tString  operator[]  (const tString &csCookieName);

    private:
        BOOL     _m_bRes;
        CxCgi   &_m_ccgCgi;

        BOOL     _bInit      ();
};
//---------------------------------------------------------------------------
class CxCgiFormData : public CxNonCopyable  {
    public:
                       CxCgiFormData(CxCgi &ccgCgi);
        virtual       ~CxCgiFormData();

        const tString &sGetRawData  () const;
        tString        sGetDump     () const;

    private:
        //consts
        static const size_t _m_cuiMaxData = 1024 * 1024;

        BOOL           _m_bRes;
        CxCgi         &_m_ccgCgi;
        tString        _m_sFormData;

        BOOL           _bInit       ();
};
//---------------------------------------------------------------------------
class CxCgi : public CxNonCopyable {
	public:
        CxCgiEnvironment Environment;
        CxCgiCookies     Cookies;
        CxCgiFormData    Formdata;

        		         CxCgi          ();
		virtual         ~CxCgi          ();

        tString          sGetDump       () const;

        static BOOL      bRedirect      (const tString &csUrl);

        //encoding, decoding
        static BOOL      bUriEncode(const tString &csUri, const tString &csReserved, tString *psEncodedStr);
        static BOOL      bUriDecode(const tString &csUri, tString *psDecodedStr);

	private:
		BOOL             _m_bRes;

        //--------------------------------------------------
        //encoding, decoding
        int              cgl_parsecgibuf(/*cgllist *cdata, */char *query);

        int              cgl_urlencode  (char *s, FILE *fw);
        void             cgl_urldecode  (char *s);

        int              bUrlEscape     (char *s, FILE *fw);
        int              bUrlUnescape   (char *s);

        char             cgl_hex2char   (char *what);
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
