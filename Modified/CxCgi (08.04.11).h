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


//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxCgi : public CxNonCopyable {
	public:
        typedef std::map<tString, tString>                     TStringMap;

        		   CxCgi                  ();
		virtual   ~CxCgi                  ();

        //Environ

        //Cookie (http://tools.ietf.org/html/rfc2965)
        tString    sGetCookieValueByName  (const tString &csCookieName);
        ULONG      ulGetCookieCount       ();
        BOOL       bSetCookie             (const tString &csName, const tString &csValue, const tString &csExpires, const tString &csDomain, const tString &csPath, BOOL bSecure);
        BOOL       bDeleteCookie          (const tString &csName/*, const tString &csPath, const tString &csDomain*/);
        //SetCookieForNSeconds(*name, *value, atoi(*seconds), "/docs/web", 0, 0);

		//Query
		BOOL       bInitQuery             ();
		BOOL       bIsPostQuery			  ();
		BOOL       bIsGetQuery            ();
		//request_method
		tString    sGetQueryParamByName   (const tString &csParam);
		ULONG      ulGetQueryParamCount   ();



		//GetCookieValueByIndex(i, value); // получаем значение параметра по его индексу
		//GetCookieNameByIndex(i, name);   // получаем имя параметра

		//-------------------------Other----------------------------------------------------
		//Escape
		//Unescape

		BOOL       bWorkProxy             ();
		BOOL	   bRedirect			  (const tString &csUrl);
		BOOL	   bRedirectToReferer	  ();

		//md5
		size_t     uiContentLength        ();	//не использ.

	private:
		TStringMap m_msQuery;
		tString    m_sQueryStr;
		TStringMap m_msCookie;

		BOOL       m_bFillQueryStr        (tString &sQueryStr);


		BOOL       _bInitEnv              ();
		BOOL       _bInitCookies          ();
		BOOL       _bInitFormData         ();

};
//---------------------------------------------------------------------------


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
