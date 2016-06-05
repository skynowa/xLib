/**
 * \file   Test_Cgi.cpp
 * \brief
 */


#include "Test_Cgi.h"

#include <xLib/IO/File.h>
#include <xLib/Net/CookiePv0.h>
#include <xLib/Net/CookiePv1.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Cgi)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Cgi::unit()
{
    xTEST_CASE("pageShow")
    {
        #if xTEST_IGNORE
            std::ctstring_t csFilePath = data.tempDirPath + Const::slash() + xT("Test.txt");

            std::ctstring_t sFileContent =
                    xT("\t<html>")
                    xT("<head></head>")
                    xT("<body>")
                    xT("<pre>")
                    xT("test HTML page")
                    xT("</pre>")
                    xT("</body>")
                    xT("</html>");

            File::textWrite(csFilePath, sFileContent);
            Cgi::pageShow(csFilePath);
        #endif
    }

    xTEST_CASE("redirect")
    {
        #if xTEMP_DISABLED
            Cgi::redirect(xT("http://yandex.ru/"));
        #endif
    }

    #if xTEMP_DISABLED
        Cgi cgCgi(Cgi::MAX_DATA_SIZE_DEFAULT);

        cgCgi.Formdata.dump();
    #endif

    xTEST_CASE("env_vars")
    {
    #if 0
        //std::tcout << xT("<pre>");

        Cgi cgCgi(1024U * 1024U /* Cgi::MAX_DATA_SIZE_DEFAULT() */);

        //--------------------------------------------------
        //Cgi::CgiEnvironment
        {
            m_sRv = cgCgi.Environment.authType();
            //xTRACEV(xT("cgCgi.Environment.sAuthType(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.contentLength();
            //xTRACEV(xT("cgCgi.Environment.sContentLength(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.contentType();
            //xTRACEV(xT("cgCgi.Environment.sContentType(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.documentRoot();
            //xTRACEV(xT("cgCgi.Environment.sDocumentRoot(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.gatewayInterface();
            //xTRACEV(xT("cgCgi.Environment.sGatewayInterface(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.httpAccept();
            //xTRACEV(xT("cgCgi.Environment.sHttpAccept(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.httpCookie();
            //xTRACEV(xT("cgCgi.Environment.sHttpCookie(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.httpPragma();
            //xTRACEV(xT("cgCgi.Environment.sHttpPragma(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.httpUserAgent();
            //xTRACEV(xT("cgCgi.Environment.sHttpUserAgent(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.pathInfo();
            //xTRACEV(xT("cgCgi.Environment.sPathInfo(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.pathTranslated();
            //xTRACEV(xT("cgCgi.Environment.sPathTranslated(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.queryString();
            //xTRACEV(xT("cgCgi.Environment.sQueryString(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.remoteAddr();
            //xTRACEV(xT("cgCgi.Environment.sRemoteAddr(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.remoteHost();
            //xTRACEV(xT("cgCgi.Environment.sRemoteHost(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.remoteIdent();
            //xTRACEV(xT("cgCgi.Environment.sRemoteIdent(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.remotePort();
            //xTRACEV(xT("cgCgi.Environment.sRemotePort(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.remoteUser();
            //xTRACEV(xT("cgCgi.Environment.sRemoteUser(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.requestMethod();
            //xTRACEV(xT("cgCgi.Environment.sRequestMethod(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.requestUri();
            //xTRACEV(xT("cgCgi.Environment.sRequestUri(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.scriptFilename();
            //xTRACEV(xT("cgCgi.Environment.sScriptFilename(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.scriptName();
            //xTRACEV(xT("cgCgi.Environment.sScriptName(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.serverAdmin();
            //xTRACEV(xT("cgCgi.Environment.sServerAdmin(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.serverName();
            //xTRACEV(xT("cgCgi.Environment.sServerName(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.serverPort();
            //xTRACEV(xT("cgCgi.Environment.sServerPort(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.serverProtocol();
            //xTRACEV(xT("cgCgi.Environment.sServerProtocol(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.serverSoftware();
            //xTRACEV(xT("cgCgi.Environment.sServerSoftware(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.httpReferer();
            //xTRACEV(xT("cgCgi.Environment.sHttpReferer(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.httpHost();
            //xTRACEV(xT("cgCgi.Environment.sHttpHost(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.httpAcceptLanguage();
            //xTRACEV(xT("cgCgi.Environment.sHttpAcceptLanguage(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Environment.countryCode();
            //xTRACEV(xT("cgCgi.Environment.sCountryCode(): %s"), m_sRv.c_str());

            m_iRv = static_cast<int_t>( cgCgi.Environment.requestType() );
            //xTRACEV(xT("cgCgi.Environment.rmRequestMethod(): %i"), m_iRv);

            m_sRv = cgCgi.Environment.dump();
            //xTRACEV(xT("cgCgi.Environment.sDump(): %s"), m_sRv.c_str());
        }

        //--------------------------------------------------
        //Cgi::CgiCookies
        {
            /////TCookies cgCgi.Cookies.Items;

            //sDump
            {
                m_sRv = cgCgi.Cookies.dump();
                //xTRACEV(xT("cgCgi.Cookies.sDump(): %s"), m_sRv.c_str());
            }

            //operator[]
            {
                m_sRv = cgCgi.Cookies[xT("ValueA")];
                //xTRACEV(xT("cgCgi.Cookies[xT(\"ValueA\")]= %s"), m_sRv.c_str());

                m_sRv = cgCgi.Cookies[xT("Valuea")];
                //xTRACEV(xT("cgCgi.Cookies[xT(\"Valuea\")]= %s"), m_sRv.c_str());

                if (!cgCgi.Cookies.items.empty()) {
                    m_sRv = cgCgi.Cookies.items.at(0)->value();
                    //xTRACEV(xT("cgCgi.Cookies.Items.at(0)->sValue() = %s"), m_sRv.c_str());
                }
            }
        }

        //--------------------------------------------------
        //Cgi::CgiFormData
        {

            m_sRv = cgCgi.Formdata.rawData();
            //xTRACEV(xT("cgCgi.Formdata.sRawData(): %s"), m_sRv.c_str());

            m_sRv = cgCgi.Formdata.dump();
            //xTRACEV(xT("cgCgi.Formdata.sDump(): %s"), m_sRv.c_str());
        }

        //--------------------------------------------------
        //sDump
        {
            m_sRv = cgCgi.dump();
            //xTRACEV(xT("cgCgi.sDump(): %s"), m_sRv.c_str());
        }

        //std::tcout << xT("</pre>");
        //std::tcout << std::endl;
    #endif
    }

    xTEST_CASE("uriEncode, decodedStr")
    {
        //1
        {
            std::ctstring_t sData[] = {
                xT("TEST_STRING_1"),
                xT("http://forum.vingrad.ru/forum/topic-327003/anchor-entry2330816/0.html"),
                xT("http://www.google.ru/search?hl=ru&source=hp&q=dddddddd&aq=f&aqi=g-s10&aql=&oq="),
                xT("http://www.w3schools.com/jsref/jsref_obj_string.asp"),
            };

            for (std::size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
                std::ctstring_t ILLEGAL_CHARS(xT("()[]/|\\',;"));


                std::tstring_t sUri        = sData[i];
                std::tstring_t sEncodedStr;

                Cgi::uriEncode(sUri, ILLEGAL_CHARS, &sEncodedStr);
                xTEST_EQ(false, sEncodedStr.empty());

                std::tstring_t sDecodedStr;

                Cgi::uriDecode(sEncodedStr, &sDecodedStr);
                xTEST_EQ(sUri, sDecodedStr);
            }
        }

        //2
        {
            std::ctstring_t sData[] = {
                xT("search?hl=ru&source=hp&q=%D1%80%D0%B5%D0%BF%D0%BE%D0%B7%D0%B8%D1%82%D0%B0%D1%80%D0%B8%D0%B9&aq=f&aqi=g-s10&aql=&oq="),
                xT("%E3%81%BB%E3%82%93%E3%81%A8%E3%81%86%E3%81%AB%E3%81%AA%E3%81%8C%E3%81%84%E3%82%8F%E3%81%91%E3%81%AE%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%A9%E3%82%81%E3%81%84%E3%82%93%E3%82%81%E3%81%84%E3%81%AE%E3%82%89%E3%81%B9%E3%82%8B%E3%81%BE%E3%81%A0%E3%81%AA%E3%81%8C%E3%81%8F%E3%81%97%E3%81%AA%E3%81%84%E3%81%A8%E3%81%9F%E3%82%8A%E3%81%AA%E3%81%84.%E3%81%BB%E3%82%93%E3%81%A8%E3%81%86%E3%81%AB%E3%81%AA%E3%81%8C%E3%81%84%E3%82%8F%E3%81%91%E3%81%AE%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%A9%E3%82%81%E3%81%84%E3%82%93%E3%82%81%E3%81%84%E3%81%AE%E3%82%89%E3%81%B9%E3%82%8B%E3%81%BE%E3%81%A0%E3%81%AA%E3%81%8C%E3%81%8F%E3%81%97%E3%81%AA%E3%81%84%E3%81%A8%E3%81%9F%E3%82%8A%E3%81%AA%E3%81%84.%E3%81%BB%E3%82%93%E3%81%A8%E3%81%86%E3%81%AB%E3%81%AA%E3%81%8C%E3%81%84%E3%82%8F%E3%81%91%E3%81%AE%E3%82%8F%E3%81%8B%E3%82%89%E3%81%AA%E3%81%84%E3%81%A9%E3%82%81%E3%81%84%E3%82%93%E3%82%81%E3%81%84%E3%81%AE%E3%82%89%E3%81%B9%E3%82%8B%E3%81%BE%E3%81%A0%E3%81%AA%E3%81%8C%E3%81%8F%E3%81%97%E3%81%AA%E3%81%84%E3%81%A8%E3%81%9F%E3%82%8A%E3%81%AA%E3%81%84.w3.mag.keio.ac.jp"),
                xT("xn--n8jaaaaai5bhf7as8fsfk3jnknefdde3fg11amb5gzdb4wi9bya3kc6lra.xn--n8jaaaaai5bhf7as8fsfk3jnknefdde3fg11amb5gzdb4wi9bya3kc6lra.xn--n8jaaaaai5bhf7as8fsfk3jnknefdde3fg11amb5gzdb4wi9bya3kc6lra.w3.mag.keio.ac.jp")
            };

            for (std::size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
                std::ctstring_t ILLEGAL_CHARS(xT("()[]/|\\',;"));


                std::tstring_t sUri        = sData[i];
                std::tstring_t sDecodedStr;

                Cgi::uriDecode(sUri, &sDecodedStr);
                xTEST_EQ(false, sDecodedStr.empty());

                std::tstring_t sEncodedStr;

                Cgi::uriEncode(sDecodedStr, ILLEGAL_CHARS, &sEncodedStr);
                xTEST_EQ(sUri,  sEncodedStr);
            }
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
