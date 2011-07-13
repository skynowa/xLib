/****************************************************************************
* Class name:  CxTest_CxCgi
* Description: test CxCgi
* File name:   CxTest_CxCgi.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Net/CxTest_CxCgi.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxCgi (constructor)
CxTest_CxCgi::CxTest_CxCgi() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxCgi (destructor)
CxTest_CxCgi::~CxTest_CxCgi() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxCgi::bUnit() {
    //--------------------------------------------------
    //bPageShow
    {
        const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");

        tString sFileContent =
                xT("<html>")
                xT("<head></head>")
                xT("<body>")
                xT("<pre>")
                xT("test HTML page")
                xT("</pre>")
                xT("</body>")
                xT("</html>");

        m_bRes = CxStdioFile::bTextWrite(csFilePath, sFileContent);
        /*DEBUG*/xASSERT_RET(FALSE != m_bRes, FALSE);

        m_bRes = CxCgi::bPageShow(csFilePath);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bRedirect
    {
        #if xTEMP_DISABLED
            CxCgi::bRedirect(xT("http://yandex.ru/"));
            xASSERT(FALSE != m_bRes);
        #endif
    }

    #if xTEMP_DISABLED
        CxCgi cgCgi(CxCgi::MAX_DATA_SIZE_DEFAULT);

        cgCgi.Formdata.sGetDump();
    #endif


    #if xTEMP_ENABLED
    {
        tcout << xT("<pre>");

        CxCgi cgCgi(CxCgi::MAX_DATA_SIZE_DEFAULT);

        //--------------------------------------------------
        //CxCgi::CxCgiEnvironment
        {
            m_sRes = cgCgi.Environment.sGetAuthType();
            xTRACEV(xT("cgCgi.Environment.sGetAuthType(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetContentLength();
            xTRACEV(xT("cgCgi.Environment.sGetContentLength(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetContentType();
            xTRACEV(xT("cgCgi.Environment.sGetContentType(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetDocumentRoot();
            xTRACEV(xT("cgCgi.Environment.sGetDocumentRoot(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetGatewayInterface();
            xTRACEV(xT("cgCgi.Environment.sGetGatewayInterface(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetHttpAccept();
            xTRACEV(xT("cgCgi.Environment.sGetHttpAccept(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetHttpCookie();
            xTRACEV(xT("cgCgi.Environment.sGetHttpCookie(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetHttpPragma();
            xTRACEV(xT("cgCgi.Environment.sGetHttpPragma(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetHttpUserAgent();
            xTRACEV(xT("cgCgi.Environment.sGetHttpUserAgent(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetPathInfo();
            xTRACEV(xT("cgCgi.Environment.sGetPathInfo(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetPathTranslated();
            xTRACEV(xT("cgCgi.Environment.sGetPathTranslated(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetQueryString();
            xTRACEV(xT("cgCgi.Environment.sGetQueryString(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetRemoteAddr();
            xTRACEV(xT("cgCgi.Environment.sGetRemoteAddr(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetRemoteHost();
            xTRACEV(xT("cgCgi.Environment.sGetRemoteHost(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetRemoteIdent();
            xTRACEV(xT("cgCgi.Environment.sGetRemoteIdent(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetRemotePort();
            xTRACEV(xT("cgCgi.Environment.sGetRemotePort(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetRemoteUser();
            xTRACEV(xT("cgCgi.Environment.sGetRemoteUser(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetRequestMethod();
            xTRACEV(xT("cgCgi.Environment.sGetRequestMethod(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetRequestUri();
            xTRACEV(xT("cgCgi.Environment.sGetRequestUri(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetScriptFilename();
            xTRACEV(xT("cgCgi.Environment.sGetScriptFilename(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetScriptName();
            xTRACEV(xT("cgCgi.Environment.sGetScriptName(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetServerAdmin();
            xTRACEV(xT("cgCgi.Environment.sGetServerAdmin(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetServerName();
            xTRACEV(xT("cgCgi.Environment.sGetServerName(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetServerPort();
            xTRACEV(xT("cgCgi.Environment.sGetServerPort(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetServerProtocol();
            xTRACEV(xT("cgCgi.Environment.sGetServerProtocol(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetServerSoftware();
            xTRACEV(xT("cgCgi.Environment.sGetServerSoftware(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetHttpReferer();
            xTRACEV(xT("cgCgi.Environment.sGetHttpReferer(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetHttpHost();
            xTRACEV(xT("cgCgi.Environment.sGetHttpHost(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetHttpAcceptLanguage();
            xTRACEV(xT("cgCgi.Environment.sGetHttpAcceptLanguage(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Environment.sGetCountryCode();
            xTRACEV(xT("cgCgi.Environment.sGetCountryCode(): %s"), m_sRes.c_str());

            m_iRes = static_cast<INT>( cgCgi.Environment.rmGetRequestMethod() );
            xTRACEV(xT("cgCgi.Environment.rmGetRequestMethod(): %i"), m_iRes);

            m_sRes = cgCgi.Environment.sGetDump();
            xTRACEV(xT("cgCgi.Environment.sGetDump(): %s"), m_sRes.c_str());
        }

        //--------------------------------------------------
        //CxCgi::CxCgiCookies
        {
            /////TCookies cgCgi.Cookies.Items;

            //sGetDump
            {
                m_sRes = cgCgi.Cookies.sGetDump();
                xTRACEV(xT("cgCgi.Cookies.sGetDump(): %s"), m_sRes.c_str());
            }

            //operator[]
            {
                m_sRes = cgCgi.Cookies[xT("ValueA")];
                xTRACEV(xT("cgCgi.Cookies[xT(\"ValueA\")]= %s"), m_sRes.c_str());

                m_sRes = cgCgi.Cookies[xT("Valuea")];
                xTRACEV(xT("cgCgi.Cookies[xT(\"Valuea\")]= %s"), m_sRes.c_str());

                if (false == cgCgi.Cookies.Items.empty()) {
                    m_sRes = cgCgi.Cookies.Items.at(0)->sGetValue();
                    xTRACEV(xT("cgCgi.Cookies.Items.at(0)->sGetValue() = %s"), m_sRes.c_str());
                }
            }
        }

        //--------------------------------------------------
        //CxCgi::CxCgiFormData
        {

            m_sRes = cgCgi.Formdata.sGetRawData();
            xTRACEV(xT("cgCgi.Formdata.sGetRawData(): %s"), m_sRes.c_str());

            m_sRes = cgCgi.Formdata.sGetDump();
            xTRACEV(xT("cgCgi.Formdata.sGetDump(): %s"), m_sRes.c_str());
        }

        //--------------------------------------------------
        //sGetDump
        {
            m_sRes = cgCgi.sGetDump();
            xTRACEV(xT("cgCgi.sGetDump(): %s"), m_sRes.c_str());
        }

        tcout << xT("</pre>");
        tcout << tendl;
    }
    #endif

    //-------------------------------------
    //bUriEncode, bUriDecode
    {
        //1
        {
            const tString sData[] = {
                xT("TEST_STRING_1"),
                xT("http://forum.vingrad.ru/forum/topic-327003/anchor-entry2330816/0.html"),
                xT("http://www.google.ru/search?hl=ru&source=hp&q=репозитарий&aq=f&aqi=g-s10&aql=&oq="),
                xT("http://www.w3schools.com/jsref/jsref_obj_string.asp"),
            };

            for (std::size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
                const std::string ILLEGAL_CHARS("()[]/|\\',;");


                tString sUri        = sData[i];
                tString sEncodedStr;

                m_bRes = CxCgi::bUriEncode(sUri, ILLEGAL_CHARS, &sEncodedStr);
                xASSERT_EQUAL(TRUE,  m_bRes);
                xASSERT_EQUAL(false, sEncodedStr.empty());

                tString sDecodedStr;

                m_bRes = CxCgi::bUriDecode(sEncodedStr, &sDecodedStr);
                xASSERT_EQUAL(TRUE, m_bRes)
                xASSERT_EQUAL(sUri, sDecodedStr);
            }
        }

        //2
        {
            const tString sData[] = {
                xT("search?hl=ru&source=hp&q=%D1%80%D0%B5%D0%BF%D0%BE%D0%B7%D0%B8%D1%82%D0%B0%D1%80%D0%B8%D0%B9&aq=f&aqi=g-s10&aql=&oq="),
                xT("%E3%81%BB%E3%82%93%E3%81%A8%E3%81%86%E3%81%AB%E3%81%AA%E3%81%8C%E3%81%84%E3%82%8F%E3%81%91%E3%81%AE%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%A9%E3%82%81%E3%81%84%E3%82%93%E3%82%81%E3%81%84%E3%81%AE%E3%82%89%E3%81%B9%E3%82%8B%E3%81%BE%E3%81%A0%E3%81%AA%E3%81%8C%E3%81%8F%E3%81%97%E3%81%AA%E3%81%84%E3%81%A8%E3%81%9F%E3%82%8A%E3%81%AA%E3%81%84.%E3%81%BB%E3%82%93%E3%81%A8%E3%81%86%E3%81%AB%E3%81%AA%E3%81%8C%E3%81%84%E3%82%8F%E3%81%91%E3%81%AE%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%A9%E3%82%81%E3%81%84%E3%82%93%E3%82%81%E3%81%84%E3%81%AE%E3%82%89%E3%81%B9%E3%82%8B%E3%81%BE%E3%81%A0%E3%81%AA%E3%81%8C%E3%81%8F%E3%81%97%E3%81%AA%E3%81%84%E3%81%A8%E3%81%9F%E3%82%8A%E3%81%AA%E3%81%84.%E3%81%BB%E3%82%93%E3%81%A8%E3%81%86%E3%81%AB%E3%81%AA%E3%81%8C%E3%81%84%E3%82%8F%E3%81%91%E3%81%AE%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%A9%E3%82%81%E3%81%84%E3%82%93%E3%82%81%E3%81%84%E3%81%AE%E3%82%89%E3%81%B9%E3%82%8B%E3%81%BE%E3%81%A0%E3%81%AA%E3%81%8C%E3%81%8F%E3%81%97%E3%81%AA%E3%81%84%E3%81%A8%E3%81%9F%E3%82%8A%E3%81%AA%E3%81%84.w3.mag.keio.ac.jp"),
                xT("xn--n8jaaaaai5bhf7as8fsfk3jnknefdde3fg11amb5gzdb4wi9bya3kc6lra.xn--n8jaaaaai5bhf7as8fsfk3jnknefdde3fg11amb5gzdb4wi9bya3kc6lra.xn--n8jaaaaai5bhf7as8fsfk3jnknefdde3fg11amb5gzdb4wi9bya3kc6lra.w3.mag.keio.ac.jp")
            };

            for (std::size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
                const std::string ILLEGAL_CHARS("()[]/|\\',;");


                tString sUri        = sData[i];
                tString sDecodedStr;

                m_bRes = CxCgi::bUriDecode(sUri, &sDecodedStr);
                xASSERT_EQUAL(TRUE,  m_bRes)
                xASSERT_EQUAL(false, sDecodedStr.empty());

                tString sEncodedStr;

                m_bRes = CxCgi::bUriEncode(sDecodedStr, ILLEGAL_CHARS, &sEncodedStr);
                xASSERT_EQUAL(TRUE,  m_bRes);
                xASSERT_EQUAL(sUri,  sEncodedStr);
            }
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------



//  tString sQueryStr =
//          xT("");
//
//  CxCgi cgCgi;
//
//  cgCgi.bInitQuery(sQueryStr);
//
//
//
//  /****************************************************************************
//  *   Query
//  *
//  *****************************************************************************/
//
//  //MessageBox(0, objCgi.sGetQueryParamByName("inpLogin").c_str(),  "sGetQueryParamByName()", MB_OK);
//  //MessageBox(0, objCgi.sGetQueryParamByName("inpPin").c_str(),    "sGetQueryParamByName()", MB_OK);
//  //MessageBox(0, objCgi.sGetQueryParamByName("inpId").c_str(),     "sGetQueryParamByName()", MB_OK);
//  //MessageBox(0, objCgi.sGetQueryParamByName("inpServId").c_str(), "sGetQueryParamByName()", MB_OK);
//  //MessageBox(0, objCgi.sGetQueryParamByName("btnSubmit").c_str(), "sGetQueryParamByName()", MB_OK);
//  //unsigned long int ulQueryCount = objCgi.ulGetQueryParamCount();
//  bool bRes1 = objCgi.bIsPostQuery();
//  bool bRes2 = objCgi.bIsGetQuery();
//
//
//  /****************************************************************************
//  *   Environ
//  *
//  *****************************************************************************/
//
//  ////MessageBox(0, objCgi.sGetEnvironStringByName("OS").c_str(), "sGetEnvironItemByName()", MB_OK);
//  ////unsigned long int ulEnvironCount = objCgi.ulGetEnvironStringCount();
//  ////MessageBox(0, objCgi.sGetEnvironStrings().c_str(), "sGetEnvironStrings()", MB_OK);
//
//
//  /****************************************************************************
//  *   Coockie
//  *
//  *****************************************************************************/
//
//  //std::string sCoockie = "username=Serg; IP=127.0.0.1; Url=localhost";
//  ////std::string sCoockie = "username=Serg";
//  ////MessageBox(0, objCgi.sGetCookieValueByName("username").c_str(), "sGetCookieValueByName", MB_OK);
//  ////unsigned long int ulCookieCount = objCgi.ulGetCookieCount();
//  ////objCgi.bSetCookie("Pass", "1111", "Thu, 01-Jan-70 00:00:01 GMT", "\\", "Serg", true);
//  ////objCgi.bDeleteCookie("Pass");
//
//
//  /****************************************************************************
//  *   Log
//  *
//  *****************************************************************************/
//
//  //objCgi.vLog("xxxxxxx");
//
//
//  /****************************************************************************
//  *   Other
//  *
//  *****************************************************************************/
//
//  ////objCgi.bRedirect("http://127.0.0.1");
//  ////objCgi.bRedirectToReferer();

