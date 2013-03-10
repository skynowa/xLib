/**
 * \file   CxTest_CxString.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxString.h>

#include <xLib/Crypt/CxRandom.h>


//------------------------------------------------------------------------------
CxTest_CxString::CxTest_CxString() {

}
//------------------------------------------------------------------------------
CxTest_CxString::~CxTest_CxString() {

}
//------------------------------------------------------------------------------
uchar_t
RandomNumber () {
    return (uchar_t)(rand()%100);
}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxString::unit(
    culonglong_t &a_cullCaseLoops
)
{
    /*******************************************************************************
    *    converters
    *
    *******************************************************************************/

    xTEST_CASE("CxString::operator << for std::ustring_t", a_cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            std::ustring_t usStr;

            usStr.resize( (size_t)CxRandom::liInt(1, 64) );
            std::fill_n(usStr.begin(), usStr.size(), static_cast<std::ustring_t::value_type>( CxRandom::liInt(1, 255) ));

            std::tstring_t sVal1 = std::tstring_t(usStr.begin(), usStr.end());

            std::tostringstream_t osOut;   osOut << usStr;
            std::tstring_t sVal2 = osOut.str();

            xTEST_EQ(sVal1, sVal2);
        }
    }

    xTEST_CASE("CxString::operator << for std::vector", a_cullCaseLoops)
    {
        m_vsRv.clear();

        m_vsRv.push_back(xT("Value0"));
        m_vsRv.push_back(xT("Value1"));
        m_vsRv.push_back(xT("Value2"));
        m_vsRv.push_back(xT("Value3"));
        m_vsRv.push_back(xT("Value4"));

        std::tostringstream_t osOut;   osOut << m_vsRv;
        //xTRACEV(xT("\toperator << for std::vector: %s"), osOut.str().c_str());
        xTEST_EQ(false, osOut.str().empty());

        m_vsRv.clear();
    }

    xTEST_CASE("CxString::operator << for std::map", a_cullCaseLoops)
    {
        m_msRv.clear();

        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key0"), xT("Value0")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key1"), xT("Value1")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key2"), xT("Value2")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key3"), xT("Value3")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key4"), xT("Value4")) );

        std::tostringstream_t osOut;   osOut << m_msRv;
        //xTRACEV(xT("\toperator << for std::map: %s"), osOut.str().c_str());
        xTEST_EQ(false, osOut.str().empty());

        m_msRv.clear();
    }

    xTEST_CASE("CxString::operator << for std::multimap", a_cullCaseLoops)
    {
        m_mmsRv.clear();

        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key0"), xT("Value0")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key1"), xT("Value1")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key2"), xT("Value2")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key0"), xT("Value0")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key1"), xT("Value1")) );

        std::tostringstream_t osOut;   osOut << m_mmsRv;
        //xTRACEV(xT("\toperator << for std::multimap: %s"), osOut.str().c_str());
        xTEST_EQ(false, osOut.str().empty());

        m_mmsRv.clear();
    }

    xTEST_CASE("CxString::cast (to string)", a_cullCaseLoops)
    {
        m_sRv = CxString::cast(1);
        xTEST_EQ(std::tstring_t(xT("1")), m_sRv);

        m_sRv = CxString::cast(xT('A'));
        xTEST_EQ(std::tstring_t(xT("A")), m_sRv);

        m_sRv = CxString::cast(xT("-"));
        xTEST_EQ(std::tstring_t(xT("-")), m_sRv);

        m_sRv = CxString::cast(0.0);
        xTEST_EQ(std::tstring_t(xT("0")), m_sRv);

        m_sRv = CxString::cast(- 5);
        xTEST_EQ(std::tstring_t(xT("-5")), m_sRv);

        m_sRv = CxString::cast(true);
        xTEST_EQ(std::tstring_t(xT("1")), m_sRv);

        m_sRv = CxString::cast(false);
        xTEST_EQ(std::tstring_t(xT("0")), m_sRv);
    }

    xTEST_CASE("CxString::cast (from string)", a_cullCaseLoops)
    {
        m_sRv = CxString::cast<std::tstring_t>(xT("String"));
        xTEST_EQ(std::tstring_t(xT("String")), m_sRv);

        m_iRv = CxString::cast<int_t>(xT("7"));
        xTEST_EQ(7, m_iRv);

        m_ulRv = CxString::cast<ulong_t>(xT("123"));
        xTEST_EQ(123UL, m_ulRv);

        m_ullRv = CxString::cast<ulonglong_t>(xT("123"));
        xTEST_EQ(123ULL, m_ullRv);

        m_dRv = CxString::cast<double>(xT("5.3"));
        xTEST_EQ(5.3, m_dRv);

        ////m_bRv = cast<bool_t>(xT("true"));
        ////xTEST_EQ(5.3, m_dRv);

        ////m_bRv = cast<bool_t>(xT("false"));
        ////xTEST_EQ(5.3, m_dRv);

        ////m_uiRv = CxString::cast<size_t>( std::tstring_t() );
        ////xTEST_EQ(0U, m_uiRv);
    }

    xTEST_CASE("CxString::cast (to string by base)", a_cullCaseLoops)
    {
        m_sRv = CxString::cast(1033, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::cast(1033, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::cast(1033, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("CxString::cast (to string by base)", a_cullCaseLoops)
    {
        ////m_sRv = CxString::sIntToStr(1033L, 2);
        ////xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);

        m_sRv = CxString::cast(1033L, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::cast(1033L, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::cast(1033L, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("CxString::cast (to string by base)", a_cullCaseLoops)
    {
        ////m_sRv = CxString::sIntToStr(1033UL, 2);
        ////xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);

        m_sRv = CxString::cast(1033UL, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::cast(1033UL, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::cast(1033UL, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("CxString::cast (to string by base)", a_cullCaseLoops)
    {
        ////m_sRv = CxString::sIntToStr(1033LL, 2);
        ////xTEST_EQ(xT("10000001001") == m_sRv);

        m_sRv = CxString::cast(1033LL, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::cast(1033LL, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::cast(1033LL, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("CxString::cast (to string by base)", a_cullCaseLoops)
    {
        ////m_sRv = CxString::sIntToStr(1033ULL, 2);
        ////xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);

        m_sRv = CxString::cast(1033ULL, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::cast(1033ULL, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::cast(1033ULL, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("cast (from, to string by base)", a_cullCaseLoops)
    {
        cint_t caiBases[] = {8, 10, 16};

        std::ctstring_t casData[] = {
                xT("01234567890ABC"),
                xT("01234567890"),
                xT("ABCDEF"),
                xT("ABCDEF01234567890ABC"),
                xT("01234AA567890ABC")
        };

        for (size_t b = 0; b < xARRAY_SIZE(caiBases); ++ b) {
            for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
                std::ctstring_t sRv    = casData[i];

                std::ctstring_t sHexStr = CxString::cast(sRv, caiBases[b]);
                std::ctstring_t sStdStr = CxString::cast(sHexStr, caiBases[b]);

                xTEST_EQ(sRv, sStdStr);
            }
        }
    }

    xTEST_CASE("CxString::castA, CxString::castW", a_cullCaseLoops)
    {
        // TODO: tests for CxString::castA, CxString::castW
    }

    xTEST_CASE("CxString::strToWStr, CxString::wstrToStr", a_cullCaseLoops)
    {
        std::cstring_t csAnsiStr[] = {
            "gnhjfgyhj ghj...",
            "vhgnjhghjfgh 234563476 45674_+()_ (*?)casf,fjpo,e rfWAERCWER$%^*())_+)+*()BNVNH*",
            "123 456 7890",
            "!@#$% ^&*()_+|* /{}:@' \"?><",
            // TODO: "строка",
            // TODO: "_你_我_他_",
            " ",
            ""
        };

        for (size_t i = 0; i < xARRAY_SIZE(csAnsiStr) - 1; i ++) {
            std::cstring_t csTemplate = csAnsiStr[i];

            std::wstring wsUnicode = CxString::strToWStr(csTemplate);
            std::string  asAnsi    = CxString::wstrToStr(wsUnicode);
            xTEST_EQ(true, csTemplate == asAnsi);
        }
    }

    xTEST_CASE("CxString::strToWStr", a_cullCaseLoops)
    {

    }

    xTEST_CASE("CxString::wstrToStr", a_cullCaseLoops)
    {

    }

    xTEST_CASE("CxString::convertCodePage", a_cullCaseLoops)
    {
        std::cstring_t csAnsiStr[] = {
            "gnhjfgyhj ghj...",
            "vhgnjhghjfgh 234563476 45674_+()_ (*?)casf,fjpo,e rfWAERCWER$%^*())_+)+*()BNVNH*",
            "123 456 7890",
            "!@#$% ^&*()_+|* /{}:@' \"?><",
            " ",
            ""
        };

        for (size_t i = 0; i < xARRAY_SIZE(csAnsiStr) - 1; i ++) {
            #if   xOS_ENV_WIN
                // CP_ACP(ANSI) <-> CP_UTF8(UTF-8)
                std::string sAnsi;
                std::string sUtf8;

                sUtf8 = CxString::convertCodePage(csAnsiStr[i], CP_ACP,  CP_UTF8);
                sAnsi = CxString::convertCodePage(sUtf8,        CP_UTF8, CP_ACP);
                xTEST_EQ(true, csAnsiStr[i] == sAnsi);


                //1251(WIN)  <-> 20866(KOI-8r)
                std::string sKoiStr;
                std::string sWinStr;

                sKoiStr = CxString::convertCodePage(csAnsiStr[i], 1251,  20866);
                sWinStr = CxString::convertCodePage(sKoiStr,      20866, 1251);
                xTEST_EQ(true, csAnsiStr[i] == sWinStr);
            #elif xOS_ENV_UNIX
                // TODO: convertCodePage
                // xNOT_IMPLEMENTED_RET(RET_VALUE);
            #endif
        }
    }

    xTEST_CASE("CxString::charToOemBuff", a_cullCaseLoops)
    {
        std::string sRv;

        #if   xOS_ENV_WIN
            sRv = CxString::charToOemBuff(xT("Boss, hello? "));
            xTEST_EQ(true, std::string("Boss, hello? ") == sRv);
        #elif xOS_ENV_UNIX
            // TODO: charToOemBuff
        #endif
    }

    xTEST_CASE("CxString::oemToCharBuff", a_cullCaseLoops)
    {
        std::tstring_t sRv;

        #if   xOS_ENV_WIN
            sRv = CxString::oemToCharBuff(("1111, hdbhjgjk hkl, jl.,kh."));
            xTEST_EQ(true, std::tstring_t(xT("1111, hdbhjgjk hkl, jl.,kh.")) == sRv);
        #elif xOS_ENV_UNIX
            // TODO: oemToCharBuff
        #endif
    }

    xTEST_CASE("CxString::boolToStr", a_cullCaseLoops)
    {
        m_sRv = CxString::boolToStr(true);
        xTEST_EQ(std::tstring_t(xT("true")), m_sRv);

        m_sRv = CxString::boolToStr(false);
        xTEST_EQ(std::tstring_t(xT("false")), m_sRv);
    }

    xTEST_CASE("CxString::strToBool", a_cullCaseLoops)
    {
        m_bRv = CxString::strToBool(xT("true"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::strToBool(xT("trUe"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::strToBool(xT("true"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::strToBool(xT("false"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::strToBool(xT("FAlse"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::strToBool(xT("false"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::strToBool(xT(" true "));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::strToBool(xT("qwertyuiop[]"));
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxString::toLowerCase", a_cullCaseLoops)
    {
        std::ctstring_t sTestData[][2] = {
            {xT("test_string_1"),       xT("TEST_string_1")},
            {xT("test_string_1"),       xT("TEst_stRING_1")},
            {xT("test_string_1\n"),     xT("TEST_STRing_1\n")},
            {xT("test_string_1\n\r"),   xT("TEST_STring_1\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::toLowerCase(sTestData[i][0]);
            std::tstring_t sStr2 = CxString::toLowerCase(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::toLowerCase(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxString::toUpperCase", a_cullCaseLoops)
    {
        std::ctstring_t sTestData[][2] = {
            {xT("TEST_STRING_1_A"),       xT("TEST_string_1_a")},
            {xT("TEST_STRING_1_A"),       xT("TEst_stRING_1_A")},
            {xT("TEST_STRING_1_A\n"),     xT("TEST_STRing_1_a\n")},
            {xT("TEST_STRING_1_A\n\r"),   xT("TEST_STring_1_A\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::toUpperCase(sTestData[i][0]);
            std::tstring_t sStr2 = CxString::toUpperCase(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::toUpperCase(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxString::toLowerCase", a_cullCaseLoops)
    {
        std::ctstring_t sTestData[][2] = {
            {xT("test_string_1_a"), xT("test_string_1_A")},
            {xT("test_string_1_a"), xT("Test_strINg_1_a")},
            {xT("test_string_1_a"), xT("test_STRING_1_A")},
            {xT("test_string_1_a"), xT("Test_string_1_a")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::toLowerCase(sTestData[i][0], sTestData[i][0].size());
            std::tstring_t sStr2 = CxString::toLowerCase(sTestData[i][1], sTestData[i][1].size());
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::toLowerCase(sTestData[i][1], sTestData[i][1].size() + 1000);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxString::toUpperCase", a_cullCaseLoops)
    {
        std::ctstring_t sTestData[][2] = {
            {xT("TEST_STRING_1_A"), xT("tEST_string_1_A")},
            {xT("TEST_STRING_1_A"), xT("tEst_stRING_1_a")},
            {xT("TEST_STRING_1_A"), xT("TEST_STRing_1_a")},
            {xT("TEST_STRING_1_A"), xT("tEST_STring_1_A")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::toUpperCase(sTestData[i][0], sTestData[i][0].size());
            std::tstring_t sStr2 = CxString::toUpperCase(sTestData[i][1], sTestData[i][1].size());
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::toUpperCase(sTestData[i][1], sTestData[i][1].size() - 1000);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    /*******************************************************************************
    *   actions
    *
    *******************************************************************************/

    xTEST_CASE("CxString::trimLeftChars", a_cullCaseLoops)
    {
        std::tstring_t sTestData[][2] = {
            {xT("TEST_STRIN#G_1"),       xT("TEST_STRIN#G_1")},
            {xT("TEST_STRING_2#"),       xT("TEST_STRING_2#")},
            {xT("TEST_STRING_3"),        xT("#TEST_STRING_3")},
            {xT("TEST_#STRING_4"),       xT("##TEST_#STRING_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::trimLeftChars(sTestData[i][0], xT("#"));
            std::tstring_t sStr2 = CxString::trimLeftChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = sTestData[i][0];
            std::tstring_t sStr4 = CxString::trimLeftChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxString::trimRightChars", a_cullCaseLoops)
    {
        std::tstring_t sTestData[][2] = {
            {xT("#TEST_STRING_1"),       xT("#TEST_STRING_1")},
            {xT("TE#ST_STRING_2"),       xT("TE#ST_STRING_2")},
            {xT("TEST_STRING_3"),        xT("TEST_STRING_3##")},
            {xT("TEST_STRING#_4"),       xT("TEST_STRING#_4#")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::trimRightChars(sTestData[i][0], xT("#"));
            std::tstring_t sStr2 = CxString::trimRightChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = sTestData[i][0];
            std::tstring_t sStr4 = CxString::trimRightChars(sTestData[i][1], xT("#"));

            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxString::trimChars", a_cullCaseLoops)
    {
        std::tstring_t sTestData[][2] = {
            {xT("TEST_STRING_1"),        xT("+-#####TEST_STRING_1+-")},
            {xT("TEST_STRING_2"),        xT("TEST_STRING_2#####+-+-+-")},
            {xT("TEST_STRING_3"),        xT("+-+-###TEST_STRING_3####+-+-+-")},
            {xT("TEST_#STRING_4"),       xT("#+-##+-TEST_#STRING_4#+-#+-##")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::trimChars(sTestData[i][0], xT("#+-"));
            std::tstring_t sStr2 = CxString::trimChars(sTestData[i][1], xT("#+-"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr4 = sTestData[i][0];
            std::tstring_t sStr3 = CxString::trimChars(sTestData[i][1], xT("#+-"));
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxString::trimSpace", a_cullCaseLoops)
    {
        std::tstring_t sTestData[][2] = {
            {xT("TEST_STRING_1"),  xT("           TEST_STRING_1")},
            {xT("TEST_STRING_2"),  xT("TEST_STRING_2       ")},
            {xT("TEST_STRING_3"),  xT("        TEST_STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("        TEST_ STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("     TEST_ STRING_3    ")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::trimSpace(sTestData[i][0]);
            std::tstring_t sStr2 = CxString::trimSpace(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::trimSpace(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxString::removeEol", a_cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::removeEol(sTestData[i][0]);
            std::tstring_t sStr2 = CxString::removeEol(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::removeEol(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxString::replaceAll", a_cullCaseLoops)
    {
        m_sRv = CxString::replaceAll(xT("aTaaaEaST_aSTaRINaaGaa_1a"), xT("a"), xT(""));
        xTEST_EQ(std::tstring_t(xT("TEST_STRING_1")), m_sRv);

        m_sRv = CxString::replaceAll(xT("TEST_STRING_1"), xT("T"), xT("a"));
        xTEST_EQ(std::tstring_t(xT("aESa_SaRING_1")), m_sRv);

        m_sRv = CxString::replaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("/"), xT("_"));
        xTEST_EQ(std::tstring_t(xT("D:_XVCL_Include\\XVCL_Units_Gui_vSpeedButton_LoadDrives.cpp")), m_sRv);

        m_sRv = CxString::replaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("\\"), xT("_"));
        xTEST_EQ(std::tstring_t(xT("D:/XVCL/Include_XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp")), m_sRv);

        m_sRv = CxString::replaceAll(xT("_one_two_three_"), xT("two"), xT(""));
        xTEST_EQ(std::tstring_t(xT("_one__three_")), m_sRv);

        m_sRv = CxString::replaceAll(xT("_one_two_three_"), xT("two"), xT("fife"));
        xTEST_EQ(std::tstring_t(xT("_one_fife_three_")), m_sRv);

        m_sRv = CxString::replaceAll(xT("_one_two_three_"), xT("two"), xT("^"));
        xTEST_EQ(std::tstring_t(xT("_one_^_three_")), m_sRv);

        m_sRv = CxString::replaceAll(xT("aaaaffaaaa"), xT("ff"), xT("ffff"));
        xTEST_EQ(std::tstring_t(xT("aaaaffffaaaa")), m_sRv);

        m_sRv = CxString::replaceAll(xT("aaaaffaaaa"), xT("ff"), xT("f"));
        xTEST_EQ(std::tstring_t(xT("aaaafaaaa")), m_sRv);
    }

    xTEST_CASE("CxString::replaceAll", a_cullCaseLoops)
    {
        m_sRv = CxString::replaceAll(xT(" one test string "), xT(" "), xT("_"));
        xTEST_EQ(m_sRv, std::tstring_t(xT("_one_test_string_")));

        m_sRv = CxString::replaceAll(xT(" one test string "), xT(" "), xT(""));
        xTEST_EQ(m_sRv, std::tstring_t(xT("oneteststring")));

        m_sRv = CxString::replaceAll(xT(" one test string "), xT(' '), xT('-'));
        xTEST_EQ(m_sRv, std::tstring_t(xT("-one-test-string-")));
    }

    xTEST_CASE("CxString::removeAll", a_cullCaseLoops)
    {
        m_sRv = CxString::removeAll(xT(" one test string "), xT(" "));
        xTEST_EQ(std::tstring_t(xT("oneteststring")), m_sRv);

        m_sRv = CxString::removeAll(xT(" one test string "), xT(" "));
        xTEST_EQ(std::tstring_t(xT("oneteststring")), m_sRv);

        m_sRv = CxString::removeAll(xT("one test strin g"),  xT(" "));
        xTEST_EQ(std::tstring_t(xT("oneteststring")), m_sRv);

        m_sRv = CxString::removeAll(xT(" one test string "), xT("string"));
        xTEST_EQ(std::tstring_t(xT(" one test  ")), m_sRv);

        m_sRv = CxString::removeAll(xT(" one test string "), xT("string"));
        xTEST_EQ(std::tstring_t(xT(" one test  ")), m_sRv);

        m_sRv = CxString::removeAll(xT("one test stringg"),  xT("string"));
        xTEST_EQ(std::tstring_t(xT("one test g")), m_sRv);
    }

    xTEST_CASE("CxString::split", a_cullCaseLoops)
    {
        std::vec_tstring_t vsText;

        CxString::split(xT("1+++22+++333+++4444+++55555+++666666"), xT("+"), &vsText);
        CxString::split(xT("Key+"), xT("+"), &vsText);

        vsText.clear();
        CxString::split(xT(""), xT("+"), &vsText);
    }

    xTEST_CASE("CxString::join", a_cullCaseLoops)
    {
        std::vec_tstring_t vsRes;
        vsRes.push_back(xT("111"));
        vsRes.push_back(xT(""));
        vsRes.push_back(xT("222"));
        vsRes.push_back(xT("333"));

        m_sRv = CxString::join(vsRes, xT("-"));
        xTEST_EQ(std::tstring_t(xT("111--222-333")), m_sRv);
    }

    xTEST_CASE("CxString::join", a_cullCaseLoops)
    {
        std::vec_tstring_t vsRes;
        vsRes.push_back(xT("111"));
        vsRes.push_back(xT(""));
        vsRes.push_back(xT("222"));
        vsRes.push_back(xT("333"));

        m_sRv = CxString::join(vsRes, xT('-'));
        xTEST_EQ(std::tstring_t(xT("111--222-333")), m_sRv);
    }

    xTEST_CASE("CxString::cut", a_cullCaseLoops)
    {
        std::tstring_t sForCut;

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <_Alca@meta.ua_>");
        m_sRv = CxString::cut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("<_Alca@meta.ua_>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<_Alc<a>@meta>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alc<a>@meta>.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125>_Alca@meta.ua_<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca<>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <<_Alca@meta.ua_>>");
        m_sRv = CxString::cut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("<<_Alca@meta.ua_>>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<<_Alc<<a>>@meta>>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alc<<a>>@meta")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125>>_Alca@meta.ua_<<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca<<>>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::cut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);
    }

    xTEST_CASE("CxString::cut", a_cullCaseLoops)
    {
        std::tstring_t sForCut = xT("0123456789");


        m_sRv = CxString::cut(sForCut, 0, 1);
        xTEST_EQ(std::tstring_t(xT("0")), m_sRv);

        m_sRv = CxString::cut(sForCut, 0, 9);
        xTEST_EQ(std::tstring_t(xT("012345678")), m_sRv);

        m_sRv = CxString::cut(sForCut, 4, 5);
        xTEST_EQ(std::tstring_t(xT("4")), m_sRv);

        m_sRv = CxString::cut(sForCut, 4, 6);
        xTEST_EQ(std::tstring_t(xT("45")), m_sRv);

        m_sRv = CxString::cut(sForCut, 6, 6);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::cut(sForCut, 6, 4);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::cut(xT(""), 1, 2);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::cut(sForCut, 0);
        xTEST_EQ(std::tstring_t(xT("0123456789")), m_sRv);

        m_sRv = CxString::cut(sForCut, 4);
        xTEST_EQ(std::tstring_t(xT("456789")), m_sRv);

        m_sRv = CxString::cut(sForCut, 9);
        xTEST_EQ(std::tstring_t(xT("9")), m_sRv);

        m_sRv = CxString::cut(sForCut, 10);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::cut(xT(""), 1);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::cut(sForCut);
        xTEST_EQ(std::tstring_t(xT("0123456789")), m_sRv);
    }

    xTEST_CASE("CxString::format", a_cullCaseLoops)
    {
        std::tstring_t sData;

        m_sRv = CxString::format(xT("qqqq-wwww [%i]"), 1000);
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [1000]")));

        m_sRv = CxString::format(xT("qqqq-wwww [%f]"), 1000.0);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxString::format(xT("qqqq-wwww [%s]"), xT("1000"));
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [1000]")));

        m_sRv = CxString::format(xT("qqqq-wwww [%i]"), -1000);
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [-1000]")));

        m_sRv = CxString::format(xT("Characters: %c %c"), xT('a'), 65);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Characters: a A")));

        m_sRv = CxString::format(xT("Decimals: %d %ld"), 1977, 650000L);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Decimals: 1977 650000")));

        m_sRv = CxString::format(xT("Preceding with blanks: %10d"), 1977);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Preceding with blanks:       1977")));

        m_sRv = CxString::format(xT("Preceding with zeros: %010d"), 1977);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Preceding with zeros: 0000001977")));

        m_sRv = CxString::format(xT("Some different radixes: %d %x %o %#x %#o"), 100, 100, 100, 100, 100);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Some different radixes: 100 64 144 0x64 0144")));

        m_sRv = CxString::format(xT("floats: %4.2f %+.0e %E"), 3.1416, 3.1416, 3.1416);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxString::format(xT("Width trick: %*d"), 5, 10);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Width trick:    10")));

        sData = xT("0A string2344565600");
        m_sRv = CxString::format(xT("%s"), sData.c_str());
        xTEST_EQ(m_sRv, sData);

        sData = xT("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
        m_sRv = CxString::format(xT("%s"), sData.c_str());
        xTEST_EQ(sData, m_sRv);

        //various string size
        {
            for (size_t i = 1; i < 1024 * 2; ++ i) {
                std::tstring_t _sData(i, xT('s'));

                std::tstring_t m_sRv = CxString::format(xT("%s"), _sData.c_str());
                //xSTD_COUT("_sData (" << _sData.size() << ") = " << _sData << "\nm_sRes (" << m_sRv.size() << ") = " << m_sRv);

                xTEST_EQ(m_sRv.size(), _sData.size());
                xTEST_EQ(m_sRv,        _sData);
            }
        }
    }

    xTEST_CASE("CxString::formatV", a_cullCaseLoops)
    {
        // TODO: formatV
    }

    xTEST_CASE("CxString::minimize", a_cullCaseLoops)
    {
        m_sRv = CxString::minimize(xT("55555wwwww"), 5);
        xTEST_EQ(std::tstring_t(xT("55...")), m_sRv);

        m_sRv = CxString::minimize(xT("55555wwwww00000"), 20);
        xTEST_EQ(std::tstring_t(xT("55555wwwww00000")), m_sRv);
    }

    /*******************************************************************************
    *   compare
    *
    *******************************************************************************/

    xTEST_CASE("CxString::compareNoCase", a_cullCaseLoops)
    {
        // must true
        m_bRv = CxString::compareNoCase(xT(""),     xT(""));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::compareNoCase(xT("xxx"),  xT("XXX"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::compareNoCase(xT("111"),  xT("111"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::compareNoCase(xT("eee"),  xT("EeE"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::compareNoCase(xT("WWW"),  xT("wwW"));
        xTEST_EQ(true, m_bRv);

        // must false
        m_bRv = CxString::compareNoCase(xT("ccc"),  xT("CCCz"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::compareNoCase(xT("!!!!!"),  xT("@@@@@@"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::compareNoCase(xT("$$$$$"), xT("sdfgsdg"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::compareNoCase(xT("&&&&&"),  xT("&&&&&????"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::compareNoCase(xT("_+#$^%^&*^&*("), xT("@#$%TY(J^HGYT"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::compareNoCase(xT("dddd"), xT("d"));
        xTEST_EQ(false, m_bRv);
    }


    /*******************************************************************************
    *    formating
    *
    *******************************************************************************/

    xTEST_CASE("CxString::formatBytes(ulonglong_t)", a_cullCaseLoops)
    {
        culonglong_t caullULongLong[] = {
            0ULL,
            10ULL,
            100ULL,
            1000ULL,
            10000ULL,
            100000ULL,
            1000000ULL,
            10000000ULL,
            100000000ULL,
            1000000000ULL,
            10000000000ULL,
            100000000000ULL,
            1000000000000ULL,
            10000000000000ULL,
            100000000000000ULL,
            1000000000000000ULL,
            10000000000000000ULL,
            100000000000000000ULL,
            1000000000000000000ULL,
        };

        for (size_t i = 0; i < xARRAY_SIZE(caullULongLong); ++ i) {
            m_sRv = CxString::formatBytes(caullULongLong[i]);
            //xTRACE(m_sRv);
        }
    }

    xTEST_CASE("CxString::formatPercent", a_cullCaseLoops)
    {

    }

    xTEST_CASE("CxString::translitLatToRus", a_cullCaseLoops)
    {
        // TEST: CxString::translitLatToRus

        #if xTODO
            m_sRv = CxString::translitLatToRus(xT(""));
            xTEST_EQ(std::tstring_t(), m_sRv);

            m_sRv = CxString::translitLatToRus(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll"));
            xTEST_EQ(std::tstring_t(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll")), m_sRv);
        #endif
    }

    /*******************************************************************************
    *    memory
    *
    *******************************************************************************/

    xTEST_CASE("CxString::memoryZeroSecure", a_cullCaseLoops)
    {
        //1
        {
            tchar_t aszBuff[][50] = {
                    xT("0123456789"),
                    xT("aaaaaaaaaaaaaaaaaa"),
                    xT("wo34875j0w9958u0342ku59u28934u5"),
            };

            for (size_t i = 0; i < xARRAY_SIZE(aszBuff); ++ i) {
                m_pvRv = CxString::memoryZeroSecure(aszBuff[i], sizeof(aszBuff[i]));
                xTEST_PTR(m_pvRv);

                for (size_t x = 0; x < xARRAY_SIZE(aszBuff[i]); ++ x) {
                    xTEST_EQ(true, 0 == aszBuff[i][x]);
                }
            }
        }

        //2
        {
            std::csize_t cauiSizes[] = {1, 0, 10, 100000000};

            for (size_t i = 0; i < xARRAY_SIZE(cauiSizes); ++ i) {
                m_pvRv = CxString::memoryZeroSecure(NULL, cauiSizes[i]);
                xTEST_PTR_FAIL(m_pvRv);
            }
        }

        // 3
        {
            uchar_t ucBuff[] = {
                1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15,
                20, 21, 22, 23, 24, 25, 30, 31, 32, 33, 34, 35,
                245, 246, 247, 248, 249, 250
            };

            m_pvRv = CxString::memoryZeroSecure(ucBuff, xARRAY_SIZE(ucBuff));
            xTEST_PTR(m_pvRv);

            for (size_t i = 0; i < xARRAY_SIZE(ucBuff); ++ i) {
                xTEST_EQ(true, 0 == ucBuff[i]);
            }
        }
    }


    /*******************************************************************************
    *    other
    *
    *******************************************************************************/

    xTEST_CASE("CxString::createGuid", a_cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            m_sRv = CxString::createGuid();
            xTEST_EQ(false, m_sRv.empty());
        #elif xOS_ENV_UNIX
            ////xTEST_EQ(true, m_sRv.empty());
        #endif
    }

    xTEST_CASE("CxString::isRepeated", a_cullCaseLoops)
    {
        m_bRv = CxString::isRepeated(xT("yyyyyyyyyyyy"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::isRepeated(xT("111111111111"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::isRepeated(xT("uuuuuiuuuuuuuuuuuu"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::isRepeated(xT("000000000111111111"));
        xTEST_EQ(false, m_bRv);
    }
}
//------------------------------------------------------------------------------
