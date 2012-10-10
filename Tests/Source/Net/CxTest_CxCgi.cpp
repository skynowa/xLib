/**
 * \file   CxTest_CxCgi.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxCgi.h>

#include <xLib/Net/CxCookiePv0.h>
#include <xLib/Net/CxCookiePv1.h>


//---------------------------------------------------------------------------
CxTest_CxCgi::CxTest_CxCgi() {

}
//---------------------------------------------------------------------------
CxTest_CxCgi::~CxTest_CxCgi() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxCgi::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxCgi::vPageShow, cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("Test.txt");

            const std::tstring_t sFileContent =
                    xT("\t<html>")
                    xT("<head></head>")
                    xT("<body>")
                    xT("<pre>")
                    xT("test HTML page")
                    xT("</pre>")
                    xT("</body>")
                    xT("</html>");

            CxFile::vTextWrite(csFilePath, sFileContent);
            CxCgi::vPageShow(csFilePath);
        #endif
    }

    xTEST_CASE(CxCgi::vRedirect, cullCaseLoops)
    {
        #if xTEMP_DISABLED
            CxCgi::vRedirect(xT("http://yandex.ru/"));
        #endif
    }

    #if xTEMP_DISABLED
        CxCgi cgCgi(CxCgi::MAX_DATA_SIZE_DEFAULT);

        cgCgi.Formdata.sDump();
    #endif

    xTEST_CASE(CxCgi::env_vars, cullCaseLoops)
    {
        //std::tcout << xT("<pre>");

        CxCgi cgCgi(CxCgi::MAX_DATA_SIZE_DEFAULT);

        //--------------------------------------------------
        //CxCgi::CxCgiEnvironment
        {
            m_sRv = cgCgi.Environment.sAuthType();
            //xTRACEV(xT("cgCgi.Environment.sAuthType(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sContentLength();
            //xTRACEV(xT("cgCgi.Environment.sContentLength(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sContentType();
            //xTRACEV(xT("cgCgi.Environment.sContentType(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sDocumentRoot();
            //xTRACEV(xT("cgCgi.Environment.sDocumentRoot(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sGatewayInterface();
            //xTRACEV(xT("cgCgi.Environment.sGatewayInterface(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sHttpAccept();
            //xTRACEV(xT("cgCgi.Environment.sHttpAccept(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sHttpCookie();
            //xTRACEV(xT("cgCgi.Environment.sHttpCookie(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sHttpPragma();
            //xTRACEV(xT("cgCgi.Environment.sHttpPragma(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sHttpUserAgent();
            //xTRACEV(xT("cgCgi.Environment.sHttpUserAgent(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sPathInfo();
            //xTRACEV(xT("cgCgi.Environment.sPathInfo(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sPathTranslated();
            //xTRACEV(xT("cgCgi.Environment.sPathTranslated(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sQueryString();
            //xTRACEV(xT("cgCgi.Environment.sQueryString(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sRemoteAddr();
            //xTRACEV(xT("cgCgi.Environment.sRemoteAddr(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sRemoteHost();
            //xTRACEV(xT("cgCgi.Environment.sRemoteHost(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sRemoteIdent();
            //xTRACEV(xT("cgCgi.Environment.sRemoteIdent(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sRemotePort();
            //xTRACEV(xT("cgCgi.Environment.sRemotePort(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sRemoteUser();
            //xTRACEV(xT("cgCgi.Environment.sRemoteUser(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sRequestMethod();
            //xTRACEV(xT("cgCgi.Environment.sRequestMethod(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sRequestUri();
            //xTRACEV(xT("cgCgi.Environment.sRequestUri(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sScriptFilename();
            //xTRACEV(xT("cgCgi.Environment.sScriptFilename(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sScriptName();
            //xTRACEV(xT("cgCgi.Environment.sScriptName(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sServerAdmin();
            //xTRACEV(xT("cgCgi.Environment.sServerAdmin(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sServerName();
            //xTRACEV(xT("cgCgi.Environment.sServerName(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sServerPort();
            //xTRACEV(xT("cgCgi.Environment.sServerPort(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sServerProtocol();
            //xTRACEV(xT("cgCgi.Environment.sServerProtocol(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sServerSoftware();
            //xTRACEV(xT("cgCgi.Environment.sServerSoftware(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sHttpReferer();
            //xTRACEV(xT("cgCgi.Environment.sHttpReferer(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sHttpHost();
            //xTRACEV(xT("cgCgi.Environment.sHttpHost(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sHttpAcceptLanguage();
            //xTRACEV(xT("cgCgi.Environment.sHttpAcceptLanguage(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.sCountryCode();
            //xTRACEV(xT("cgCgi.Environment.sCountryCode(): %s"), m_sRv.c_str());

            m_iRv = static_cast<int>( cgCgi.Environment.rmRequestMethod() );
            //xTRACEV(xT("cgCgi.Environment.rmRequestMethod(): %i"), m_iRv);

            m_sRv = cgCgi.Environment.sDump();
            //xTRACEV(xT("cgCgi.Environment.sDump(): %s"), m_sRv.c_str());
        }

        //--------------------------------------------------
        //CxCgi::CxCgiCookies
        {
            /////TCookies cgCgi.Cookies.Items;

            //sDump
            {
                m_sRv = cgCgi.Cookies.sDump();
                //xTRACEV(xT("cgCgi.Cookies.sDump(): %s"), m_sRv.c_str());
            }

            //operator[]
            {
                m_sRv = cgCgi.Cookies[xT("ValueA")];
                //xTRACEV(xT("cgCgi.Cookies[xT(\"ValueA\")]= %s"), m_sRv.c_str());

                m_sRv = cgCgi.Cookies[xT("Valuea")];
                //xTRACEV(xT("cgCgi.Cookies[xT(\"Valuea\")]= %s"), m_sRv.c_str());

                if (false == cgCgi.Cookies.Items.empty()) {
                    m_sRv = cgCgi.Cookies.Items.at(0)->sValue();
                    //xTRACEV(xT("cgCgi.Cookies.Items.at(0)->sValue() = %s"), m_sRv.c_str());
                }
            }
        }

        //--------------------------------------------------
        //CxCgi::CxCgiFormData
        {

            m_sRv = cgCgi.Formdata.sRawData();
            //xTRACEV(xT("cgCgi.Formdata.sRawData(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Formdata.sDump();
            //xTRACEV(xT("cgCgi.Formdata.sDump(): %s"), m_sRv.c_str());
        }

        //--------------------------------------------------
        //sDump
        {
            m_sRv = cgCgi.sDump();
            //xTRACEV(xT("cgCgi.sDump(): %s"), m_sRv.c_str());
        }

        //std::tcout << xT("</pre>");
        //std::tcout << std::endl;
    }

    xTEST_CASE(CxCgi::bUriEncode CxCgi::sDecodedStr, cullCaseLoops)
    {
        //1
        {
            const std::tstring_t sData[] = {
                xT("TEST_STRING_1"),
                xT("http://forum.vingrad.ru/forum/topic-327003/anchor-entry2330816/0.html"),
                xT("http://www.google.ru/search?hl=ru&source=hp&q=репозитарий&aq=f&aqi=g-s10&aql=&oq="),
                xT("http://www.w3schools.com/jsref/jsref_obj_string.asp"),
            };

            for (std::size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
                const std::string ILLEGAL_CHARS("()[]/|\\',;");


                std::tstring_t sUri        = sData[i];
                std::tstring_t sEncodedStr;

                m_bRv = CxCgi::bUriEncode(sUri, ILLEGAL_CHARS, &sEncodedStr);
                xTEST_EQ(true,  m_bRv);
                xTEST_EQ(false, sEncodedStr.empty());

                std::tstring_t sDecodedStr;

                m_bRv = CxCgi::bUriDecode(sEncodedStr, &sDecodedStr);
                xTEST_EQ(true, m_bRv)
                xTEST_EQ(sUri, sDecodedStr);
            }
        }

        //2
        {
            const std::tstring_t sData[] = {
                xT("search?hl=ru&source=hp&q=%D1%80%D0%B5%D0%BF%D0%BE%D0%B7%D0%B8%D1%82%D0%B0%D1%80%D0%B8%D0%B9&aq=f&aqi=g-s10&aql=&oq="),
                xT("%E3%81%BB%E3%82%93%E3%81%A8%E3%81%86%E3%81%AB%E3%81%AA%E3%81%8C%E3%81%84%E3%82%8F%E3%81%91%E3%81%AE%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%A9%E3%82%81%E3%81%84%E3%82%93%E3%82%81%E3%81%84%E3%81%AE%E3%82%89%E3%81%B9%E3%82%8B%E3%81%BE%E3%81%A0%E3%81%AA%E3%81%8C%E3%81%8F%E3%81%97%E3%81%AA%E3%81%84%E3%81%A8%E3%81%9F%E3%82%8A%E3%81%AA%E3%81%84.%E3%81%BB%E3%82%93%E3%81%A8%E3%81%86%E3%81%AB%E3%81%AA%E3%81%8C%E3%81%84%E3%82%8F%E3%81%91%E3%81%AE%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%A9%E3%82%81%E3%81%84%E3%82%93%E3%82%81%E3%81%84%E3%81%AE%E3%82%89%E3%81%B9%E3%82%8B%E3%81%BE%E3%81%A0%E3%81%AA%E3%81%8C%E3%81%8F%E3%81%97%E3%81%AA%E3%81%84%E3%81%A8%E3%81%9F%E3%82%8A%E3%81%AA%E3%81%84.%E3%81%BB%E3%82%93%E3%81%A8%E3%81%86%E3%81%AB%E3%81%AA%E3%81%8C%E3%81%84%E3%82%8F%E3%81%91%E3%81%AE%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%A9%E3%82%81%E3%81%84%E3%82%93%E3%82%81%E3%81%84%E3%81%AE%E3%82%89%E3%81%B9%E3%82%8B%E3%81%BE%E3%81%A0%E3%81%AA%E3%81%8C%E3%81%8F%E3%81%97%E3%81%AA%E3%81%84%E3%81%A8%E3%81%9F%E3%82%8A%E3%81%AA%E3%81%84.w3.mag.keio.ac.jp"),
                xT("xn--n8jaaaaai5bhf7as8fsfk3jnknefdde3fg11amb5gzdb4wi9bya3kc6lra.xn--n8jaaaaai5bhf7as8fsfk3jnknefdde3fg11amb5gzdb4wi9bya3kc6lra.xn--n8jaaaaai5bhf7as8fsfk3jnknefdde3fg11amb5gzdb4wi9bya3kc6lra.w3.mag.keio.ac.jp")
            };

            for (std::size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
                const std::string ILLEGAL_CHARS("()[]/|\\',;");


                std::tstring_t sUri        = sData[i];
                std::tstring_t sDecodedStr;

                m_bRv = CxCgi::bUriDecode(sUri, &sDecodedStr);
                xTEST_EQ(true,  m_bRv)
                xTEST_EQ(false, sDecodedStr.empty());

                std::tstring_t sEncodedStr;

                m_bRv = CxCgi::bUriEncode(sDecodedStr, ILLEGAL_CHARS, &sEncodedStr);
                xTEST_EQ(true,  m_bRv);
                xTEST_EQ(sUri,  sEncodedStr);
            }
        }
    }
}
//---------------------------------------------------------------------------
