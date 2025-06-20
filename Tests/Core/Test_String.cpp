/**
 * \file   Test_String.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_String)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_String::unit()
{
    /*******************************************************************************
    *    converters
    *
    *******************************************************************************/

    xTEST_CASE("castTo")
    {
        // bool_t
        m_bRv = String::castTo<bool_t>("0");
        xTEST(!m_bRv);

        // tchar_t
        m_chRv = String::castTo<tchar_t>("d");
        xTEST_EQ(m_chRv, xT('d'));
        m_ucRv = String::castTo<uchar_t>("c");
        xTEST_EQ(m_ucRv, (uchar_t)'c');

        // short_t
        m_siRv = String::castTo<short_t>("-5");
        xTEST_EQ(m_siRv, (short_t)-5);
        m_usiRv = String::castTo<ushort_t>("6");
        xTEST_EQ(m_usiRv, (ushort_t)6);

        // int_t
        m_iRv = String::castTo<int_t>("1");
        xTEST_EQ(m_iRv, 1);
        m_uiRv = String::castTo<uint_t>("8");
        xTEST_EQ(m_uiRv, 8U);

        // long_t
        m_liRv = String::castTo<long_t>("-345");
        xTEST_EQ(m_liRv, -345L);
        m_ulRv = String::castTo<ulong_t>("234");
        xTEST_EQ(m_ulRv, 234UL);

        // longlong_t
        m_llRv = String::castTo<longlong_t>("-789");
        xTEST_EQ(m_llRv, -789LL);
        m_ullRv = String::castTo<ulonglong_t>("145");
        xTEST_EQ(m_ullRv, 145ULL);

        // float_t
        m_fRv = String::castTo<float_t>("-0.7");
        xTEST_EQ(m_fRv, -0.7f);
        m_dRv = String::castTo<double_t>("15.87");
        xTEST_EQ(m_dRv, 15.87);
        m_ldRv = String::castTo<longdouble_t>("178.89");
        xTEST_EQ(m_ldRv, 178.89L);
    }

    xTEST_CASE("cast (to string)")
    {
        m_sRv = String::cast(1);
        xTEST_EQ(std::tstring_t(xT("1")), m_sRv);

        m_sRv = String::cast(xT('A'));
        xTEST_EQ(std::tstring_t(xT("A")), m_sRv);

        m_sRv = String::cast(xT("-"));
        xTEST_EQ(std::tstring_t(xT("-")), m_sRv);

        m_sRv = String::cast(0.0);
        xTEST_EQ(std::tstring_t(xT("0")), m_sRv);

        m_sRv = String::cast(- 5);
        xTEST_EQ(std::tstring_t(xT("-5")), m_sRv);

        m_sRv = String::cast(true);
        xTEST_EQ(std::tstring_t(xT("1")), m_sRv);

        m_sRv = String::cast(false);
        xTEST_EQ(std::tstring_t(xT("0")), m_sRv);
    }

    xTEST_CASE("cast (from string)")
    {
        m_sRv = String::cast<std::tstring_t>(xT("String"));
        xTEST_EQ(std::tstring_t(xT("String")), m_sRv);

        m_iRv = String::cast<int_t>(xT("7"));
        xTEST_EQ(7, m_iRv);

        m_ulRv = String::cast<ulong_t>(xT("123"));
        xTEST_EQ(123UL, m_ulRv);

        m_ullRv = String::cast<ulonglong_t>(xT("123"));
        xTEST_EQ(123ULL, m_ullRv);

        m_dRv = String::cast<double>(xT("5.3"));
        xTEST_EQ(5.3, m_dRv);
    }

    xTEST_CASE("cast (to string by base)")
    {
        m_sRv = String::cast(1033, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = String::cast(1033, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = String::cast(1033, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("cast (to string by base)")
    {
        #if xTODO
            m_sRv = String::cast(1033L, 2);
            xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);
        #endif

        m_sRv = String::cast(1033L, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = String::cast(1033L, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = String::cast(1033L, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("cast (to string by base)")
    {
        #if xTODO
            m_sRv = String::cast(1033UL, 2);
            xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);
        #endif

        m_sRv = String::cast(1033UL, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = String::cast(1033UL, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = String::cast(1033UL, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("cast (to string by base)")
    {
        #if xTODO
            m_sRv = String::cast(1033LL, 2);
            xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);
        #endif

        m_sRv = String::cast(1033LL, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = String::cast(1033LL, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = String::cast(1033LL, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("cast (to string by base)")
    {
        #if xTODO
            m_sRv = String::cast(1033ULL, 2);
            xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);
        #endif

        m_sRv = String::cast(1033ULL, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = String::cast(1033ULL, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = String::cast(1033ULL, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE("cast (from, to string by base)")
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

                std::ctstring_t sHexStr = String::cast(sRv, caiBases[b]);
                std::ctstring_t sStdStr = String::cast(sHexStr, caiBases[b]);

                xTEST_EQ(sRv, sStdStr);
            }
        }
    }

    xTEST_CASE("castA castW")
    {
        // TODO: [skynowa] tests for String::castA, String::castW
    }

    xTEST_CASE("castA, castW")
    {
        std::cstring_t csAnsiStr[] = {
            "gnhjfgyhj ghj...",
            "vhgnjhghjfgh 234563476 45674_+()_ (*?)casf,fjpo,e rfWAERCWER$%^*())_+)+*()BNVNH*",
            "123 456 7890",
            "!@#$% ^&*()_+|* /{}:@' \"?><",
            "0123456789",
            "0123456789",
            // TEST: String::castW() - "строка",
            // TEST: String::castW() - "_你_我_他_",
            "z",
            " ",
            ""
        };

        for (size_t i = 0; i < xARRAY_SIZE(csAnsiStr) - 1; i ++) {
            std::cstring_t asTemplate = csAnsiStr[i];

            std::cwstring_t wsUnicode = String::castW(asTemplate);
            std::cstring_t  asAnsi    = String::castA(wsUnicode);
            xTEST_EQ(asTemplate, asAnsi);
        }
    }

    xTEST_CASE("castW")
    {

    }

    xTEST_CASE("castA")
    {

    }

    xTEST_CASE("castCodePage")
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
            #if   xENV_WIN
                // CP_ACP(ANSI) <-> CP_UTF8(UTF-8)
                std::string sAnsi;
                std::string sUtf8;

                sUtf8 = String::castCodePage(csAnsiStr[i], CP_ACP,  CP_UTF8);
                sAnsi = String::castCodePage(sUtf8,        CP_UTF8, CP_ACP);
                xTEST(csAnsiStr[i] == sAnsi);


                //1251(WIN)  <-> 20866(KOI-8r)
                std::string sKoiStr;
                std::string sWinStr;

                sKoiStr = String::castCodePage(csAnsiStr[i], 1251,  20866);
                sWinStr = String::castCodePage(sKoiStr,      20866, 1251);
                xTEST(csAnsiStr[i] == sWinStr);
            #elif xENV_UNIX
                // TODO: [skynowa] TETST - String::castCodePage()
                // xNOT_IMPLEMENTED_RET(RET_VALUE);
            #endif
        }
    }

    xTEST_CASE("castToOem")
    {
        std::string sRv;

        #if   xENV_WIN
            sRv = String::castToOem(xT("Boss, hello? "));
            xTEST(std::string("Boss, hello? ") == sRv);
        #elif xENV_UNIX
            // TEST: String::castToOem()
        #endif
    }

    xTEST_CASE("castFromOem")
    {
        std::tstring_t sRv;

        #if   xENV_WIN
            sRv = String::castFromOem(("1111, hdbhjgjk hkl, jl.,kh."));
            xTEST(std::tstring_t(xT("1111, hdbhjgjk hkl, jl.,kh.")) == sRv);
        #elif xENV_UNIX
            // TODO: [skynowa] String::castFromOem()
        #endif
    }

    xTEST_CASE("castBool")
    {
        m_sRv = String::castBool(true);
        xTEST_EQ(std::tstring_t(xT("true")), m_sRv);

        m_sRv = String::castBool(false);
        xTEST_EQ(std::tstring_t(xT("false")), m_sRv);
    }

    xTEST_CASE("castBool")
    {
        m_bRv = String::castBool( std::tstring_t(xT("true")) );
        xTEST(m_bRv);

        m_bRv = String::castBool( std::tstring_t(xT("trUe")) );
        xTEST(m_bRv);

        m_bRv = String::castBool( std::tstring_t(xT("true")) );
        xTEST(m_bRv);

        m_bRv = String::castBool( std::tstring_t(xT("false")) );
        xTEST(!m_bRv);

        m_bRv = String::castBool( std::tstring_t(xT("FAlse")) );
        xTEST(!m_bRv);

        m_bRv = String::castBool( std::tstring_t(xT("false")) );
        xTEST(!m_bRv);

        m_bRv = String::castBool( std::tstring_t(xT(" true ")) );
        xTEST(!m_bRv);

        m_bRv = String::castBool( std::tstring_t(xT("qwertyuiop[]")) );
        xTEST(!m_bRv);
    }

    xTEST_CASE("toLowerCase")
    {
        std::ctstring_t sTestData[][2] = {
            {xT("test_string_1"),       xT("TEST_string_1")},
            {xT("test_string_1"),       xT("TEst_stRING_1")},
            {xT("test_string_1\n"),     xT("TEST_STRing_1\n")},
            {xT("test_string_1\n\r"),   xT("TEST_STring_1\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = String::toLowerCase(sTestData[i][0]);
            std::tstring_t sStr2 = String::toLowerCase(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = String::toLowerCase(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("toUpperCase")
    {
        std::ctstring_t sTestData[][2] = {
            {xT("TEST_STRING_1_A"),       xT("TEST_string_1_a")},
            {xT("TEST_STRING_1_A"),       xT("TEst_stRING_1_A")},
            {xT("TEST_STRING_1_A\n"),     xT("TEST_STRing_1_a\n")},
            {xT("TEST_STRING_1_A\n\r"),   xT("TEST_STring_1_A\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = String::toUpperCase(sTestData[i][0]);
            std::tstring_t sStr2 = String::toUpperCase(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = String::toUpperCase(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("toLowerCase")
    {
        std::ctstring_t sTestData[][2] = {
            {xT("test_string_1_a"), xT("test_string_1_A")},
            {xT("test_string_1_a"), xT("Test_strINg_1_a")},
            {xT("test_string_1_a"), xT("test_STRING_1_A")},
            {xT("test_string_1_a"), xT("Test_string_1_a")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = String::toLowerCase(sTestData[i][0], sTestData[i][0].size());
            std::tstring_t sStr2 = String::toLowerCase(sTestData[i][1], sTestData[i][1].size());
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = String::toLowerCase(sTestData[i][1], sTestData[i][1].size() + 1000);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("toUpperCase")
    {
        std::ctstring_t sTestData[][2] = {
            {xT("TEST_STRING_1_A"), xT("tEST_string_1_A")},
            {xT("TEST_STRING_1_A"), xT("tEst_stRING_1_a")},
            {xT("TEST_STRING_1_A"), xT("TEST_STRing_1_a")},
            {xT("TEST_STRING_1_A"), xT("tEST_STring_1_A")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = String::toUpperCase(sTestData[i][0], sTestData[i][0].size());
            std::tstring_t sStr2 = String::toUpperCase(sTestData[i][1], sTestData[i][1].size());
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = String::toUpperCase(sTestData[i][1], sTestData[i][1].size() - 1000);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    /*******************************************************************************
    *   actions
    *
    *******************************************************************************/

    xTEST_CASE("trimLeftChars")
    {
        std::tstring_t sTestData[][2] = {
            {xT("TEST_STRIN#G_1"),       xT("TEST_STRIN#G_1")},
            {xT("TEST_STRING_2#"),       xT("TEST_STRING_2#")},
            {xT("TEST_STRING_3"),        xT("#TEST_STRING_3")},
            {xT("TEST_#STRING_4"),       xT("##TEST_#STRING_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = String::trimLeftChars(sTestData[i][0], xT("#"));
            std::tstring_t sStr2 = String::trimLeftChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = sTestData[i][0];
            std::tstring_t sStr4 = String::trimLeftChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("trimRightChars")
    {
        std::tstring_t sTestData[][2] = {
            {xT("#TEST_STRING_1"),       xT("#TEST_STRING_1")},
            {xT("TE#ST_STRING_2"),       xT("TE#ST_STRING_2")},
            {xT("TEST_STRING_3"),        xT("TEST_STRING_3##")},
            {xT("TEST_STRING#_4"),       xT("TEST_STRING#_4#")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = String::trimRightChars(sTestData[i][0], xT("#"));
            std::tstring_t sStr2 = String::trimRightChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = sTestData[i][0];
            std::tstring_t sStr4 = String::trimRightChars(sTestData[i][1], xT("#"));

            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("trimChars")
    {
        std::tstring_t sTestData[][2] = {
            {xT("TEST_STRING_1"),        xT("+-#####TEST_STRING_1+-")},
            {xT("TEST_STRING_2"),        xT("TEST_STRING_2#####+-+-+-")},
            {xT("TEST_STRING_3"),        xT("+-+-###TEST_STRING_3####+-+-+-")},
            {xT("TEST_#STRING_4"),       xT("#+-##+-TEST_#STRING_4#+-#+-##")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = String::trimChars(sTestData[i][0], xT("#+-"));
            std::tstring_t sStr2 = String::trimChars(sTestData[i][1], xT("#+-"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr4 = sTestData[i][0];
            std::tstring_t sStr3 = String::trimChars(sTestData[i][1], xT("#+-"));
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("trimSpace")
    {
        std::tstring_t sTestData[][2] = {
            {xT("TEST_STRING_1"),  xT("           TEST_STRING_1")},
            {xT("TEST_STRING_2"),  xT("TEST_STRING_2       ")},
            {xT("TEST_STRING_3"),  xT("        TEST_STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("        TEST_ STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("     TEST_ STRING_3    ")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = String::trimSpace(sTestData[i][0]);
            std::tstring_t sStr2 = String::trimSpace(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = String::trimSpace(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("removeEol")
    {
        #if   xENV_WIN
            std::ctstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #elif xENV_UNIX
            std::ctstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = String::removeEol(sTestData[i][0]);
            std::tstring_t sStr2 = String::removeEol(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = String::removeEol(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("quoted")
    {
        std::ctstring_t data[][2] =
        {
            {xT("TEST_STRING_1"),  xT("\"TEST_STRING_1\"")},
            {xT("TEST_\"STRING\"_1"), xT("\"TEST_\\\"STRING\\\"_1\"")}
        };

        for (const auto &it_data : data) {
            std::tstring_t str1 = String::quoted(it_data[0], xT('\"'), xT('\\'));
            std::tstring_t str2 = it_data[1];
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("replaceAll")
    {
        m_sRv = String::replaceAll(xT("aTaaaEaST_aSTaRINaaGaa_1a"), xT("a"), xT(""));
        xTEST_EQ(std::tstring_t(xT("TEST_STRING_1")), m_sRv);

        m_sRv = String::replaceAll(xT("TEST_STRING_1"), xT("T"), xT("a"));
        xTEST_EQ(std::tstring_t(xT("aESa_SaRING_1")), m_sRv);

        m_sRv = String::replaceAll(xT("D:/XVCL/Include\\XVCL/Units/Ui/vSpeedButton_LoadDrives.cpp"), xT("/"), xT("_"));
        xTEST_EQ(std::tstring_t(xT("D:_XVCL_Include\\XVCL_Units_Ui_vSpeedButton_LoadDrives.cpp")), m_sRv);

        m_sRv = String::replaceAll(xT("D:/XVCL/Include\\XVCL/Units/Ui/vSpeedButton_LoadDrives.cpp"), xT("\\"), xT("_"));
        xTEST_EQ(std::tstring_t(xT("D:/XVCL/Include_XVCL/Units/Ui/vSpeedButton_LoadDrives.cpp")), m_sRv);

        m_sRv = String::replaceAll(xT("_one_two_three_"), xT("two"), xT(""));
        xTEST_EQ(std::tstring_t(xT("_one__three_")), m_sRv);

        m_sRv = String::replaceAll(xT("_one_two_three_"), xT("two"), xT("fife"));
        xTEST_EQ(std::tstring_t(xT("_one_fife_three_")), m_sRv);

        m_sRv = String::replaceAll(xT("_one_two_three_"), xT("two"), xT("^"));
        xTEST_EQ(std::tstring_t(xT("_one_^_three_")), m_sRv);

        m_sRv = String::replaceAll(xT("aaaaffaaaa"), xT("ff"), xT("ffff"));
        xTEST_EQ(std::tstring_t(xT("aaaaffffaaaa")), m_sRv);

        m_sRv = String::replaceAll(xT("aaaaffaaaa"), xT("ff"), xT("f"));
        xTEST_EQ(std::tstring_t(xT("aaaafaaaa")), m_sRv);
    }

    xTEST_CASE("replaceAll")
    {
        m_sRv = String::replaceAll(xT(" one test string "), xT(" "), xT("_"));
        xTEST_EQ(m_sRv, std::tstring_t(xT("_one_test_string_")));

        m_sRv = String::replaceAll(xT(" one test string "), xT(" "), xT(""));
        xTEST_EQ(m_sRv, std::tstring_t(xT("oneteststring")));

        m_sRv = String::replaceAll(xT(" one test string "), xT(' '), xT('-'));
        xTEST_EQ(m_sRv, std::tstring_t(xT("-one-test-string-")));
    }

    xTEST_CASE("removeAll")
    {
        m_sRv = String::removeAll(xT(" one test string "), xT(" "));
        xTEST_EQ(std::tstring_t(xT("oneteststring")), m_sRv);

        m_sRv = String::removeAll(xT(" one test string "), xT(" "));
        xTEST_EQ(std::tstring_t(xT("oneteststring")), m_sRv);

        m_sRv = String::removeAll(xT("one test strin g"),  xT(" "));
        xTEST_EQ(std::tstring_t(xT("oneteststring")), m_sRv);

        m_sRv = String::removeAll(xT(" one test string "), xT("string"));
        xTEST_EQ(std::tstring_t(xT(" one test  ")), m_sRv);

        m_sRv = String::removeAll(xT(" one test string "), xT("string"));
        xTEST_EQ(std::tstring_t(xT(" one test  ")), m_sRv);

        m_sRv = String::removeAll(xT("one test stringg"),  xT("string"));
        xTEST_EQ(std::tstring_t(xT("one test g")), m_sRv);
    }

    xTEST_CASE("split")
    {
        String::split(xT("aaa|bbb|"), xT("|"), &m_vsRv);
        xTEST_EQ(m_vsRv.size(), std::size_t(3));
        xTEST_EQ(m_vsRv.at(0),  std::tstring_t(xT("aaa")));
        xTEST_EQ(m_vsRv.at(1),  std::tstring_t(xT("bbb")));
        xTEST_EQ(m_vsRv.at(2),  std::tstring_t());

        String::split(xT("1+++22+++333+++4444+++55555+++666666"), xT("+"), &m_vsRv);
        xTEST_EQ(m_vsRv.size(), std::size_t(16));
        xTEST_EQ(m_vsRv.at(0),  std::tstring_t(xT("1")));
        xTEST_EQ(m_vsRv.at(1),  std::tstring_t());
        xTEST_EQ(m_vsRv.at(2),  std::tstring_t());
        xTEST_EQ(m_vsRv.at(3),  std::tstring_t(xT("22")));
        xTEST_EQ(m_vsRv.at(4),  std::tstring_t());
        xTEST_EQ(m_vsRv.at(5),  std::tstring_t());
        xTEST_EQ(m_vsRv.at(6),  std::tstring_t(xT("333")));
        xTEST_EQ(m_vsRv.at(7),  std::tstring_t());
        xTEST_EQ(m_vsRv.at(8),  std::tstring_t());
        xTEST_EQ(m_vsRv.at(9),  std::tstring_t(xT("4444")));
        xTEST_EQ(m_vsRv.at(10), std::tstring_t());
        xTEST_EQ(m_vsRv.at(11), std::tstring_t());
        xTEST_EQ(m_vsRv.at(12), std::tstring_t(xT("55555")));
        xTEST_EQ(m_vsRv.at(13), std::tstring_t());
        xTEST_EQ(m_vsRv.at(14), std::tstring_t());
        xTEST_EQ(m_vsRv.at(15), std::tstring_t(xT("666666")));

        String::split(xT("1+22+333+4444+55555+666666"), xT("+"), &m_vsRv);
        xTEST_EQ(m_vsRv.size(), std::size_t(6));
        xTEST_EQ(m_vsRv.at(0),  std::tstring_t(xT("1")));
        xTEST_EQ(m_vsRv.at(1),  std::tstring_t(xT("22")));
        xTEST_EQ(m_vsRv.at(2),  std::tstring_t(xT("333")));
        xTEST_EQ(m_vsRv.at(3),  std::tstring_t(xT("4444")));
        xTEST_EQ(m_vsRv.at(4),  std::tstring_t(xT("55555")));
        xTEST_EQ(m_vsRv.at(5),  std::tstring_t(xT("666666")));

        String::split(xT("Key+"), xT("+"), &m_vsRv);
        xTEST_EQ(m_vsRv.size(), std::size_t(2));
        xTEST_EQ(m_vsRv.at(0),  std::tstring_t(xT("Key")));
        xTEST_EQ(m_vsRv.at(1),  std::tstring_t());

        String::split(xT(""), xT("+"), &m_vsRv);
        xTEST(m_vsRv.empty());
    }

	xTEST_CASE("split (maps)")
    {
		{
			std::cmap_tstring_t m
			{
				{"aaa", "111"},
				{"bbb", "222"},
				{"ccc", "333"}
			};

			String::split(xT("aaa:111\r\nbbb:222\r\nccc:333"), xT("\r\n"), xT(":"), &m_msRv);
			xTEST_EQ(m_msRv, m);
		}

		{
			std::cmmap_tstring_t m
			{
				{"aaa", "111"},
				{"bbb", "222"},
				{"ccc", "333"},
				{"ccc", "333"}
			};

			String::split(xT("aaa:111\r\nbbb:222\r\nccc:333\r\nccc:333"), xT("\r\n"), xT(":"), &m_mmsRv);
			xTEST_EQ(m_mmsRv, m);
		}

		{
			std::ctstring_t sRv =
				"HTTP/1.1 200 OK\r\n"
				"Cache-Control: max-age=604800\r\n"
				"Content-Type: text/html; charset=UTF-8\r\n"
				"Date: Thu, 20 Sep 2018 06:50:29 GMT\r\n"
				"Etag: \"1541025663+ident\"\r\n"
				"Expires: Thu, 27 Sep 2018 06:50:29 GMT\r\n"
				"Last-Modified: Fri, 09 Aug 2013 23:54:35 GMT\r\n"
				"Server: ECS (dca/24E0)\r\n"
				"Vary: Accept-Encoding\r\n"
				"X-Cache: HIT\r\n"
				"Content-Length: 1270\r\n"
				"\r\n"
				"\r\n";

			std::cmmap_tstring_t m
			{
				{"Cache-Control",  "max-age=604800"},
				{"Content-Length", "1270"},
				{"Content-Type",   "text/html; charset=UTF-8"},
				{"Date",           "Thu, 20 Sep 2018 06:50:29 GMT"},
				{"Etag",           "\"1541025663+ident\""},
				{"Expires",        "Thu, 27 Sep 2018 06:50:29 GMT"},
				{"Last-Modified",  "Fri, 09 Aug 2013 23:54:35 GMT"},
				{"Server",         "ECS (dca/24E0)"},
				{"Vary",           "Accept-Encoding"},
				{"X-Cache",        "HIT"}
			};

			String::split(sRv, xT("\r\n"), xT(": "), &m_mmsRv);
			xTEST_EQ(m_mmsRv, m);
		}
	}

    xTEST_CASE("join")
    {
        std::vec_tstring_t vsRes;
        vsRes.push_back(xT("111"));
        vsRes.push_back(xT(""));
        vsRes.push_back(xT("222"));
        vsRes.push_back(xT("333"));

        m_sRv = String::join(vsRes, xT("-"));
        xTEST_EQ(std::tstring_t(xT("111--222-333")), m_sRv);
    }

    xTEST_CASE("join")
    {
        std::vec_tstring_t vsRes;
        vsRes.push_back(xT("111"));
        vsRes.push_back(xT(""));
        vsRes.push_back(xT("222"));
        vsRes.push_back(xT("333"));

        m_sRv = String::join(vsRes, xT('-'));
        xTEST_EQ(std::tstring_t(xT("111--222-333")), m_sRv);
    }

	xTEST_CASE("join (maps)")
    {
		{
			std::cmap_tstring_t m
			{
				{"aaa", "111"},
				{"bbb", "222"},
				{"ccc", "333"}
			};

			m_sRv = String::join(m, xT("\r\n"), xT(":"));
			xTEST_EQ(m_sRv, std::tstring_t(xT("aaa:111\r\nbbb:222\r\nccc:333\r\n")));
		}

		{
			std::cmmap_tstring_t m
			{
				{"aaa", "111"},
				{"bbb", "222"},
				{"ccc", "333"},
				{"ccc", "333"}
			};

			m_sRv = String::join(m, xT("\r\n"), xT(":"));
			xTEST_EQ(m_sRv, std::tstring_t(xT("aaa:111\r\nbbb:222\r\nccc:333\r\nccc:333\r\n")));
		}
	}

    xTEST_CASE("cut")
    {
        {
            std::tstring_t data = xT("111<<<aaa>>>222>>>");

            m_sRv = String::cut(data, xT("<<<"), (">>>"));
            xTEST_EQ(m_sRv, std::tstring_t(xT("aaa")));
        }

        {
            std::tstring_t data = xT("111<<<>>>222>>>");

            m_sRv = String::cut(data, xT("<<<"), xT(">>>"));
            xTEST_EQ(m_sRv, std::tstring_t(xT("")));
        }

        {
            std::tstring_t data = xT("<<<a>>>>>>");

            m_sRv = String::cut(data, xT("<<<"), xT(">>>"));
            xTEST_EQ(m_sRv, std::tstring_t(xT("a")));
        }
    }

    xTEST_CASE("rcut")
    {
        std::tstring_t sForCut;

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <_Alca@meta.ua_>");
        m_sRv = String::rcut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("<_Alca@meta.ua_>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<_Alc<a>@meta>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alc<a>@meta>.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125>_Alca@meta.ua_<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca<>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <<_Alca@meta.ua_>>");
        m_sRv = String::rcut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("<<_Alca@meta.ua_>>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<<_Alc<<a>>@meta>>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alc<<a>>@meta")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125>>_Alca@meta.ua_<<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca<<>>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = String::rcut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);
    }

    xTEST_CASE("cut")
    {
        std::ctstring_t sForCut = xT("0123456789");

        m_sRv = String::cut(sForCut, 0, 1);
        xTEST_EQ(std::tstring_t(xT("0")), m_sRv);

        m_sRv = String::cut(sForCut, 0, 9);
        xTEST_EQ(std::tstring_t(xT("012345678")), m_sRv);

        m_sRv = String::cut(sForCut, 4, 5);
        xTEST_EQ(std::tstring_t(xT("4")), m_sRv);

        m_sRv = String::cut(sForCut, 4, 6);
        xTEST_EQ(std::tstring_t(xT("45")), m_sRv);

        m_sRv = String::cut(sForCut, 6, 6);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = String::cut(sForCut, 6, 4);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = String::cut(xT(""), 1, 2);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = String::cut(sForCut, 0);
        xTEST_EQ(std::tstring_t(xT("0123456789")), m_sRv);

        m_sRv = String::cut(sForCut, 4);
        xTEST_EQ(std::tstring_t(xT("456789")), m_sRv);

        m_sRv = String::cut(sForCut, 9);
        xTEST_EQ(std::tstring_t(xT("9")), m_sRv);

        m_sRv = String::cut(sForCut, 10);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = String::cut(xT(""), 1);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = String::cut(sForCut, 0, std::tstring_t::npos);
        xTEST_EQ(m_sRv, sForCut);
    }

    xTEST_CASE("minimize")
    {
        m_sRv = String::minimize(xT("55555wwwww"), 5);
        xTEST_EQ(std::tstring_t(xT("55...")), m_sRv);

        m_sRv = String::minimize(xT("55555wwwww00000"), 20);
        xTEST_EQ(std::tstring_t(xT("55555wwwww00000")), m_sRv);
    }


    /*******************************************************************************
    *    formating
    *
    *******************************************************************************/

    xTEST_CASE("formatBytes")
    {
        const Data2<ulonglong_t, std::tstring_t> data[] = {
            {0ULL, xT("0.00 Bit(s)")},
            {10ULL, xT("10.00 Byte(s)")},
            {100ULL, xT("100.00 Byte(s)")},
            {1000ULL, xT("1000.00 Byte(s)")},
            {10000ULL, xT("9.77 KB")},
            {100000ULL, xT("97.66 KB")},
            {1000000ULL, xT("976.56 KB")},
            {10000000ULL, xT("9.54 MB")},
            {100000000ULL, xT("95.37 MB")},
            {1000000000ULL, xT("953.67 MB")},
            {10000000000ULL, xT("9.31 GB")},
            {100000000000ULL, xT("93.13 GB")},
            {1000000000000ULL, xT("931.32 GB")},
            {10000000000000ULL, xT("9.09 TB")},
            {100000000000000ULL, xT("90.95 TB")},
            {1000000000000000ULL, xT("909.49 TB")},
            {10000000000000000ULL, xT("8.88 PB")},
            {100000000000000000ULL, xT("88.82 PB")},
            {1000000000000000000ULL, xT("888.18 PB")},
            {10000000000000000000ULL, xT("8.67 EB")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            m_sRv = String::formatBytes(data[i].test);
            // LogCout() << xTRACE_VAR(m_sRv);
        }
    }

    xTEST_CASE("formatPercent")
    {
        // TEST: String::formatPercent
    }

    /*******************************************************************************
    *    memory
    *
    *******************************************************************************/

    xTEST_CASE("memoryZeroSecure")
    {
        //1
        {
            tchar_t aszBuff[][50] = {
                    xT("0123456789"),
                    xT("aaaaaaaaaaaaaaaaaa"),
                    xT("wo34875j0w9958u0342ku59u28934u5"),
            };

            for (size_t i = 0; i < xARRAY_SIZE(aszBuff); ++ i) {
                m_pvRv = String::memoryZeroSecure(aszBuff[i], sizeof(aszBuff[i]));
                xTEST_PTR(m_pvRv);

                for (size_t x = 0; x < xARRAY_SIZE(aszBuff[i]); ++ x) {
                    xTEST(0 == aszBuff[i][x]);
                }
            }
        }

        //2
        {
            std::csize_t cauiSizes[] = {1, 0, 10, 100000000};

            for (size_t i = 0; i < xARRAY_SIZE(cauiSizes); ++ i) {
                m_pvRv = String::memoryZeroSecure(nullptr, cauiSizes[i]);
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

            m_pvRv = String::memoryZeroSecure(ucBuff, xARRAY_SIZE(ucBuff));
            xTEST_PTR(m_pvRv);

            for (size_t i = 0; i < xARRAY_SIZE(ucBuff); ++ i) {
                xTEST(0 == ucBuff[i]);
            }
        }
    }


    /*******************************************************************************
    *    other
    *
    *******************************************************************************/

    xTEST_CASE("isRepeated")
    {
        m_bRv = String::isRepeated(xT("yyyyyyyyyyyy"));
        xTEST(m_bRv);

        m_bRv = String::isRepeated(xT("111111111111"));
        xTEST(m_bRv);

        m_bRv = String::isRepeated(xT("uuuuuiuuuuuuuuuuuu"));
        xTEST(!m_bRv);

        m_bRv = String::isRepeated(xT("000000000111111111"));
        xTEST(!m_bRv);
    }


    /*******************************************************************************
    *   search, compare
    *
    *******************************************************************************/

    xTEST_CASE("find")
    {
        const data3_size_t data[] = {
            // not using position
            { xT(""), xT(""), 0 },
            { xT("xxx"), xT("XXX"), 0 },
            { xT("111"), xT("111"), 0 },
            { xT("eee"), xT("EeE"), 0 },
            { xT("WWW"), xT("wwW"), 0 },
            { xT("ccc"), xT("CCCz"), std::tstring_t::npos },
            { xT(""), xT("222"), std::tstring_t::npos },
            { xT("111"), xT(""), 0 },
            { xT(""), xT("2"), std::tstring_t::npos },
            { xT("1"), xT(""), 0 },
            { xT("!!!!!"), xT("@@@@@@"), std::tstring_t::npos },
            { xT("$$$$$"), xT("sdfgsdg"), std::tstring_t::npos },
            { xT("&&&&&"), xT("&&&&&????"), std::tstring_t::npos },
            { xT("_+#$^%^&*^&*("), xT("@#$%TY(J^HGYT"), std::tstring_t::npos },
            { xT("dddd"), xT("d"), 0 },

            // using position
            { xT("111Dddd3333"), xT("dD"), 3 },
            { xT("111Dddd3333"), xT("dDddddd"), std::tstring_t::npos }
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            m_stRv = StringCI::find(data[i].test1, data[i].test2);
            xTEST_EQ(m_stRv, data[i].expect);
        }
    }

    xTEST_CASE("compare")
    {
        const data3_bool_t data[] = {
            { xT(""), xT(""), true },
            { xT("xxx"), xT("XXX"), true },
            { xT("111"), xT("111"), true },
            { xT("eee"), xT("EeE"), true },
            { xT("WWW"), xT("wwW"), true },
            { xT("ccc"), xT("CCCz"), false },
            { xT(""), xT("222"), false },
            { xT("111"), xT(""), false },
            { xT(""), xT("2"), false },
            { xT("1"), xT(""), false },
            { xT("!!!!!"), xT("@@@@@@"), false },
            { xT("$$$$$"), xT("sdfgsdg"), false },
            { xT("&&&&&"), xT("&&&&&????"), false },
            { xT("_+#$^%^&*^&*("), xT("@#$%TY(J^HGYT"), false },
            { xT("dddd"), xT("d"), false },
            { xT("111Dddd3333"), xT("dD"), false },
            { xT("111Dddd3333"), xT("dDddddd"), false }
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            m_bRv = StringCI::compare(data[i].test1, data[i].test2);
            xTEST_EQ(m_bRv, data[i].expect);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
