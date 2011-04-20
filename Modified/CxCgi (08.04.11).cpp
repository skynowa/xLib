/****************************************************************************
* Class name:  CxCgi
* Description: common gateway interace
* File name:   CxCgi.cpp
* Compilers:   Visual C++ 2010
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     11:01:2010 13:20:00
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Net/CxCgi.h>

#include <xLib/Filesystem/CxEnvironment.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCgi (constructor)
CxCgi::CxCgi() {

}
//---------------------------------------------------------------------------
//DONE: CxCgi (destructor)
/*virtual*/
CxCgi::~CxCgi() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*   Environ
*
****************************************************************************/


/****************************************************************************
*   Form data
*
****************************************************************************/


/****************************************************************************
*   Cookies
*
****************************************************************************/




//---------------------------------------------------------------------------
tString
CxCgi::sGetCookieValueByName(const tString &csCookieName) {
    if (csCookieName.empty() == TRUE) {
        return tString();
    }

    ////return m_msCookie[csCookieName];    //<<----- !!!! добавляется элемент если его нет

    TStringMap::iterator pIter = m_msCookie.find(csCookieName);
    if (pIter == m_msCookie.end()) {
        return tString();
    } else {
        return pIter->second;
    }
}
//---------------------------------------------------------------------------
ULONG
CxCgi::ulGetCookieCount() {
    return m_msCookie.size();
}
//---------------------------------------------------------------------------
BOOL
CxCgi::bSetCookie(const tString &csName, const tString &csValue, const tString &csExpires, const tString &csDomain, const tString &csPath, BOOL bSecure) {
    //-------------------------------------
    //CHECK
    if (csName.empty() == TRUE) {
        return FALSE;
    }
    if (csValue.empty() == TRUE) {
        return FALSE;
    }
    if (csPath.empty() == TRUE) {
        return FALSE;
    }

    /*
    print "Content-type: text/html\n";
    print "Set-Cookie: username=aaa13; expires=Friday, 31-Dec-99 23:59:59 GMT; path=/; domain=www.citforum.ru;\n\n";
    */

    //print "Content-type: text/html\n";
    //std::cout << "Set-Cookie: username=Serg; path=/;\n";
    //std::cout << "Set-Cookie: IP=127.0.0.1;  path=/;\n";
    //std::cout << "Set-Cookie: Url=localhost; path=/;\n\n";

    //date   = wdy, dd-mon-yyyy hh:mm:ss gmt,
    //domain = cit-forum.com
    //path   = /win
    //set-cookie: NAME=value; expires=date; path=path; domain=domain_name; secure

    //-------------------------------------
    //tString sUrl = "Set-Cookie: " + csName + "=" + csValue + "; path=/;\n\n";
	tString sSecure;
    if (bSecure == TRUE) {
        sSecure = "SECURE";
    } else {
        sSecure = "";
    }

    tString sUrl = "Set-Cookie: " +
                                csName    + "=" + csValue   + "; " +
                                "EXPIRES" + "=" + csExpires + "; " +
                                "DOMAIN"  + "=" + csDomain  + "; " +
                                "PATH"    + "=" + csPath    + "; " +
                                sSecure   +
                                "\n\n";
    std::cout << sUrl;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCgi::bDeleteCookie(const tString &csName) {
    //-------------------------------------
    //CHECK
    if (csName.empty() == TRUE) {
        return FALSE;
    }

    //-------------------------------------
    //
    // document.cookie = strName + "=" + "; expires = Thu, 01-Jan-70 00:00:01 GMT";
    tString sUrl = "Set-Cookie: " +
                                csName    + "=" + ""                            + "; " +
                                "EXPIRES" + "=" + "Thu, 01-Jan-70 00:00:01 GMT" + "; " +
                                "\n\n";
    std::cout << sUrl;

    return TRUE;
}
//---------------------------------------------------------------------------




/****************************************************************************
*   Query
*
*****************************************************************************/


//---------------------------------------------------------------------------
BOOL
CxCgi::bInitQuery() {
	//-------------------------------------
	//m_sQueryStr - заполняем
	m_bFillQueryStr(m_sQueryStr);	//вызыв один только раз

	//-------------------------------------
	//m_msQuery - парсим
	std::vector<tString> sVecDelim;
	////sVecDelim = svecExplode("\n", m_sQueryStr);

	for (size_t i = 4; i < sVecDelim.size(); i = i + 4) {	//i + 1
		//выюрать текст между двойными ковычками
		tString     sLine           = sVecDelim.at(i - 3);
		std::size_t uiBeginPos      = sLine.find_first_of('"') + 1;
		std::size_t uiEndPos        = sLine.find_last_of('"');
		std::size_t uiParamValueLen = uiEndPos - uiBeginPos;
		tString     sParamValue     = sLine.substr(uiBeginPos, uiParamValueLen);	//MessageBox(0, sParamValue.c_str(), "", MB_OK);

		m_msQuery[sParamValue]  = sVecDelim.at(i - 1);
	}

	//-------------------------------------
	//m_msCookie - парсим
	tString sCookie = CxEnvironment::sGetVar("HTTP_COOKIE");  //"username=Serg; IP=127.0.0.1; Url=localhost";
	if (sCookie.empty() == FALSE) {
		//-------------------------------------
		//разделить на пары (name1=value1; name2=value2; nameN=valueN")
		std::vector<tString> vecsDelim;

		CxString::bSplit(sCookie, xT(";"), &vecsDelim);

		for (size_t i = 0; i < vecsDelim.size(); i ++) {
			//разделить имя и значени (name=value)
			std::vector<tString> vecsTemp;

			CxString::bSplit(vecsDelim.at(i), xT("="), &vecsTemp);

			tString sCookieName  = CxString::sTrimSpace(vecsTemp.at(0));
			tString sCookieValue = vecsTemp.at(1);

			m_msCookie[sCookieName] = sCookieValue;
		}
	}

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCgi::m_bFillQueryStr(tString &sQueryStr) {
	//функция должна выполняться только один раз (stdin)
	char *pszQuery = NULL;

	//длина контента
	size_t uiContentLen = atoi(CxEnvironment::sGetVar("CONTENT_LENGTH").c_str());	//uiContentLength(); (in bytes)
	if (uiContentLen == 0) {
		return FALSE;
	}

	//выделяем память под контент
	pszQuery = (char *)malloc(uiContentLen + 1);
	if (pszQuery == NULL) {
		return FALSE;
	}

	//все ли байты прочитаны ?
	unsigned int uiReadBytes = fread(pszQuery, 1, uiContentLen, stdin);
	if (uiReadBytes <= 0) {
		return FALSE;
	}
	if (uiReadBytes != uiContentLen) {
		////MessageBox(0, "uiReadBytes != uiContentLen", "Error", MB_OK);
		////MsgBox(uiReadBytes);
		////MsgBox(uiContentLen);
		////return FALSE;
	}

	sQueryStr = tString(pszQuery);		//MessageBox(0, m_sQueryStr.c_str(), "m_sQueryStr - Init", MB_OK);

	free(pszQuery);	pszQuery = NULL;

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCgi::bIsPostQuery() {
	tString sRequestMethod = CxEnvironment::sGetVar("REQUEST_METHOD");
	if (sRequestMethod == "POST") {
		return TRUE;
	} else {
		return FALSE;
	}
}
//---------------------------------------------------------------------------
BOOL
CxCgi::bIsGetQuery() {
	tString sRequestMethod = CxEnvironment::sGetVar("REQUEST_METHOD");
	if (sRequestMethod == "GET") {
		return TRUE;
	} else {
		return FALSE;
	}
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
tString
CxCgi::sGetQueryParamByName(const tString &csParam) {
    //-------------------------------------
    //CHECK
    if (csParam.empty() == TRUE) {
        return tString("");
    }

    //return m_msQuery[csParam];    //<<----- !!!! добавляется элемент если его нет

    TStringMap::iterator pIter = m_msQuery.find(csParam);
    if (pIter == m_msQuery.end()) {
        return tString("");
    } else {
        return pIter->second;
    }
}
//---------------------------------------------------------------------------
ULONG
CxCgi::ulGetQueryParamCount() {
    return m_msQuery.size();
}
//---------------------------------------------------------------------------




/****************************************************************************
*	Other
*
*****************************************************************************/


//---------------------------------------------------------------------------
BOOL
CxCgi::bWorkProxy() {
	//-------------------------------------
	//CHECK
	tString sPathTranslated = CxEnvironment::sGetVar("PATH_TRANSLATED");   //DOCUMENT_ROOT
	if (sPathTranslated.empty() == TRUE) {
		////MessageBox(0, "sPathTranslated.empty() == TRUE", "", MB_OK);
	}

	tifstream in(sPathTranslated.c_str());		////MessageBox(0, getenv("PATH_TRANSLATED"), "", MB_OK);
	if (!in) {
		std::cout << "Location: /404/\n\n"; ////MessageBox(0, "if (!in)", "", MB_OK);
		return FALSE;
	}


	//-------------------------------------
	//чистим страницу
	std::cout << "Content-Type: text/html\n\n";

	char ch   = '\0';
	char prev = '\0';
	BOOL on   = FALSE;

	for (in >> ch; in; in >> ch) {
		//Здесь будет код для удаления комментариев
		if (on) std::cout << '\n';
		else on = TRUE;

		std::cout << ch;
		prev = ch;
		for (in.get(ch); in && ch != '\n' && ch != '\r'; in.get(ch)) {
			//Здесь будет код для удаления комментариев
			if (!isspace (ch) || !isspace (prev)) {
				std::cout << ch;
			}

			prev = ch;
		}
	}

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCgi::bRedirect(const tString &csUrl) {
	//-------------------------------------
	//CHECK
	if (csUrl.empty() == TRUE) {
		return FALSE;
	}

	//-------------------------------------
	//
	tString sUrl = "Location: " + csUrl + "\n\n";
	std::cout << sUrl;

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCgi::bRedirectToReferer() {
	//-------------------------------------
	//CHECK
	if (getenv("HTTP_REFERER") == NULL) {
		return FALSE;
	}

	//-------------------------------------
	//
	tString sUrl = "Location: " + tString(getenv("HTTP_REFERER")) + "\n\n";
	std::cout << sUrl;

	return TRUE;
}
//---------------------------------------------------------------------------
size_t
CxCgi::uiContentLength() {	//POST
	unsigned int uiLen = 0;
	uiLen = atoi(CxEnvironment::sGetVar("CONTENT_LENGTH").c_str());

	return uiLen;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: _bInitEnv ()
BOOL
CxCgi::_bInitEnv() {
    /*DEBUG*/



    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: _bInitCookies ()
BOOL
CxCgi::_bInitCookies() {
    /*DEBUG*/



    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: _bInitFormData ()
BOOL
CxCgi::_bInitFormData() {
    /*DEBUG*/



    return TRUE;
}
//---------------------------------------------------------------------------








































