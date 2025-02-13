/**
 * \file   Test_Base64.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Base64)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Base64::unit()
{
    xTEST_CASE("encode, decode")
    {
        std::string data[][1] = {
            {"ADP GmbH\nAnalyse Design & Programmierung\nGesellschaft mit beschrankter Haftung"},
            {"TEST_STRING_2"},
            {"evrtvertre=-430956=-lmj';l'654"},
            {"ngb213,jhv560vlk254mlkvj6254klj'lcmkc34;lr,m34;'rtlm2cv456467809=-0i=-09i=-24i09v5"
             "grfmkldfgjghmjgyuiyuirvbty34v5"},
            {"On-line Testing Pages by dev.FYIcenter.com\nWelcome to dev.FYIcenter.com on-line "
             "learning and testing pages.\nClick the Start button to play regular expression, "
             "date formatting, \nURL encoding, and many more programming techniques..."},
            {"TEST_STRING_3"},
            {"On-line Testing Pages by dev.FYIcenter.comWelcome to dev.FYIcenter.com on-line "
             "learning and testing pages.Click the Start button to play regular expression, date "
             "formatting, \nURL encoding, and many more programming techniques..."},
            {"If you need a javascript for md5: http://pajhome.org.uk/crypt/md5/md5src.html"}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::string source = data[i][0];

            Base64 base64;

            std::string encoded = base64.encode(source);
            std::string decoded = base64.decode(encoded);
            xTEST(source == decoded);
        }
    }

    xTEST_CASE("encode, decode")
    {
        const Data2<std::string, std::string> data[] = {
            {"YOYO!", "WU9ZTyE="},
            {"111111111111111", "MTExMTExMTExMTExMTEx"},
            {"!@#$%^&*()_+", "IUAjJCVeJiooKV8r"},
            {"A", "QQ=="},
            {"AB", "QUI="},
            {"ABC", "QUJD"},
            {"This is an encoded string", "VGhpcyBpcyBhbiBlbmNvZGVkIHN0cmluZw=="}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            Base64 base64;

            std::string encoded = base64.encode(data[i].test);
            xTEST(data[i].expect == encoded);

            std::string decoded = base64.decode(encoded);
            xTEST(data[i].test == decoded);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
