/**
 * \file   CxTest_CxBase64.cpp
 * \brief
 */


#include <Test/Crypt/CxTest_CxBase64.h>


//---------------------------------------------------------------------------
CxTest_CxBase64::CxTest_CxBase64() {

}
//---------------------------------------------------------------------------
CxTest_CxBase64::~CxTest_CxBase64() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxBase64::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxBase64::encode sDecode", cullCaseLoops)
    {
        const std::string sTestData[][1] = {
            {"ADP GmbH\nAnalyse Design & Programmierung\nGesellschaft mit beschrankter Haftung"},
            {"TEST_STRING_2"},
            {"evrtvertre=-430956=-lmj';l'654"},
            {"ngb213,jhv560vlk254mlkvj6254klj'lcmkc34;lr,m34;'rtlm2cv456467809=-0i=-09i=-24i09v5grfmkldfgjghmjgyuiyuirvbty34v5"},
            {"On-line Testing Pages by dev.FYIcenter.com\nWelcome to dev.FYIcenter.com on-line learning and testing pages.\nClick the Start button to play regular expression, date formatting, \nURL encoding, and many more programming techniques..."},
            {"TEST_STRING_3"},
            {"On-line Testing Pages by dev.FYIcenter.comWelcome to dev.FYIcenter.com on-line learning and testing pages.Click the Start button to play regular expression, date formatting, \nURL encoding, and many more programming techniques..."},
            {"If you need a javascript for md5: http://pajhome.org.uk/crypt/md5/md5src.html"}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::string sSource = sTestData[i][0];

            std::string sEncoded = CxBase64::encode(sSource);
            std::string sDecoded = CxBase64::decode(sEncoded);
            xTEST_EQ(true, sSource == sDecoded);
        }
    }

    xTEST_CASE("CxBase64::encode sDecode", cullCaseLoops)
    {
        const std::string casData[][2] = {
            {"YOYO!", "WU9ZTyE="},
            {"111111111111111", "MTExMTExMTExMTExMTEx"},
            {"!@#$%^&*()_+", "IUAjJCVeJiooKV8r"},
            {"A", "QQ=="},
            {"AB", "QUI="},
            {"ABC", "QUJD"},
            {"This is an encoded string", "VGhpcyBpcyBhbiBlbmNvZGVkIHN0cmluZw=="}
        };

        for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
            const std::string csSource  = casData[i][0];
            const std::string csMustBe  = casData[i][1];

            const std::string csEncoded = CxBase64::encode(csSource);
            //xTRACEV("csEncoded: %s (%zu), csMustBe (%zu)", csEncoded.c_str(), csEncoded.size(), csMustBe.size());
            xTEST_EQ(true, csMustBe == csEncoded);

            const std::string csDecoded = CxBase64::decode(csEncoded);
            //xTRACEV("csEncoded: %s (%zu), csSource (%zu)", csDecoded.c_str(), csDecoded.size(), csSource.size());
            xTEST_EQ(true, csSource == csDecoded);
        }
    }

    xTEST_CASE("CxBase64::isCharValid", cullCaseLoops)
    {
        {
            const std::string csValidChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

            for (size_t i = 0; i < csValidChars.size(); ++ i) {
                m_bRv = CxBase64::isCharValid(csValidChars.at(i));
                //xTRACEV(xT("csValidChars.at(i): %c"), csValidChars.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        {
            const std::string csNonValidChars = "!@#$%^&*()_|:?";

            for (size_t i = 0; i < csNonValidChars.size(); ++ i) {
                m_bRv = CxBase64::isCharValid(csNonValidChars.at(i));
                //xTRACEV(xT("csNonValidChars.at(i): %c"), csNonValidChars.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }
}
//---------------------------------------------------------------------------
