/**
 * \file   CxTest_CxString.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxString.h>

#include <xLib/Crypt/CxRandom.h>


//---------------------------------------------------------------------------
CxTest_CxString::CxTest_CxString() {

}
//---------------------------------------------------------------------------
CxTest_CxString::~CxTest_CxString() {

}
//---------------------------------------------------------------------------
uchar_t
RandomNumber () {
    return (uchar_t)(rand()%100);
}
//---------------------------------------------------------------------------
/*virtual*/
bool 
CxTest_CxString::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    /****************************************************************************
    *    convertation
    *
    *****************************************************************************/

    //--------------------------------------------------
    //operator << for std::ustring_t
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            std::ustring_t usStr;

            usStr.resize( (size_t)CxRandom::liGetInt(1, 64) );
            std::fill_n(usStr.begin(), usStr.size(), static_cast<std::ustring_t::value_type>( CxRandom::liGetInt(1, 255) ));

            std::tstring_t sVal1 = std::tstring_t(usStr.begin(), usStr.end());

            std::tostringstream_t osOut;   osOut << usStr;
            std::tstring_t sVal2 = osOut.str();

            xTEST_EQ(sVal1, sVal2);
        }
    }

    //--------------------------------------------------
    //operator << for std::vector
    xTEST_CASE(cullCaseLoops)
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

    //--------------------------------------------------
    //operator << for std::map
    xTEST_CASE(cullCaseLoops)
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

    //--------------------------------------------------
    //operator << for std::multimap
    xTEST_CASE(cullCaseLoops)
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

    //-------------------------------------
    //lexical_cast (to string)
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxString::lexical_cast(1);
        xTEST_EQ(std::tstring_t(xT("1")), m_sRv);

        m_sRv = CxString::lexical_cast(xT('A'));
        xTEST_EQ(std::tstring_t(xT("A")), m_sRv);

        m_sRv = CxString::lexical_cast(xT("-"));
        xTEST_EQ(std::tstring_t(xT("-")), m_sRv);

        m_sRv = CxString::lexical_cast(0.0);
        xTEST_EQ(std::tstring_t(xT("0")), m_sRv);

        m_sRv = CxString::lexical_cast(- 5);
        xTEST_EQ(std::tstring_t(xT("-5")), m_sRv);

        m_sRv = CxString::lexical_cast(true);
        xTEST_EQ(std::tstring_t(xT("1")), m_sRv);

        m_sRv = CxString::lexical_cast(false);
        xTEST_EQ(std::tstring_t(xT("0")), m_sRv);
    }

    //-------------------------------------
    //lexical_cast (from string)
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxString::lexical_cast<std::tstring_t>(xT("String"));
        xTEST_EQ(std::tstring_t(xT("String")), m_sRv);

        m_iRv = CxString::lexical_cast<int>(xT("7"));
        xTEST_EQ(7, m_iRv);

        m_ulRv = CxString::lexical_cast<ulong_t>(xT("123"));
        xTEST_EQ(123UL, m_ulRv);

        m_ullRv = CxString::lexical_cast<ulonglong_t>(xT("123"));
        xTEST_EQ(123ULL, m_ullRv);

        m_dRv = CxString::lexical_cast<double>(xT("5.3"));
        xTEST_EQ(5.3, m_dRv);

        ////m_bRv = lexical_cast<bool>(xT("true"));
        ////xTEST_EQ(5.3, m_dRv);

        ////m_bRv = lexical_cast<bool>(xT("false"));
        ////xTEST_EQ(5.3, m_dRv);

        ////m_uiRv = CxString::lexical_cast<size_t>( std::tstring_t() );
        ////xTEST_EQ(0U, m_uiRv);
    }

    //-------------------------------------
    //lexical_cast (to string by base)
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxString::lexical_cast(1033, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::lexical_cast(1033, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::lexical_cast(1033, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE(cullCaseLoops)
    {
        ////m_sRv = CxString::sIntToStr(1033L, 2);
        ////xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);

        m_sRv = CxString::lexical_cast(1033L, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::lexical_cast(1033L, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::lexical_cast(1033L, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE(cullCaseLoops)
    {
        ////m_sRv = CxString::sIntToStr(1033UL, 2);
        ////xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);

        m_sRv = CxString::lexical_cast(1033UL, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::lexical_cast(1033UL, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::lexical_cast(1033UL, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE(cullCaseLoops)
    {
        ////m_sRv = CxString::sIntToStr(1033LL, 2);
        ////xTEST_EQ(xT("10000001001") == m_sRv);

        m_sRv = CxString::lexical_cast(1033LL, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::lexical_cast(1033LL, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::lexical_cast(1033LL, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    xTEST_CASE(cullCaseLoops)
    {
        ////m_sRv = CxString::sIntToStr(1033ULL, 2);
        ////xTEST_EQ(std::tstring_t(xT("10000001001")), m_sRv);

        m_sRv = CxString::lexical_cast(1033ULL, 8);
        xTEST_EQ(std::tstring_t(xT("2011")), m_sRv);

        m_sRv = CxString::lexical_cast(1033ULL, 10);
        xTEST_EQ(std::tstring_t(xT("1033")), m_sRv);

        m_sRv = CxString::lexical_cast(1033ULL, 16);
        xTEST_EQ(std::tstring_t(xT("409")), m_sRv);
    }

    //-------------------------------------
    //lexical_cast (from, to string by base)
    xTEST_CASE(cullCaseLoops)
    {
        const int caiBases[] = {8, 10, 16};

        const std::tstring_t casData[] = {
                xT("01234567890ABC"),
                xT("01234567890"),
                xT("ABCDEF"),
                xT("ABCDEF01234567890ABC"),
                xT("01234AA567890ABC")
        };

        for (size_t b = 0; b < xARRAY_SIZE(caiBases); ++ b) {
            for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
                const std::tstring_t sRv    = casData[i];

                const std::tstring_t sHexStr = CxString::lexical_cast(sRv, caiBases[b]);
                const std::tstring_t sStdStr = CxString::lexical_cast(sHexStr, caiBases[b]);

                xTEST_EQ(sRv, sStdStr);
            }
        }
    }

    //-------------------------------------
    //bBoolToStr
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxString::sBoolToStr(true);
        xTEST_EQ(std::tstring_t(xT("true")), m_sRv);

        m_sRv = CxString::sBoolToStr(false);
        xTEST_EQ(std::tstring_t(xT("false")), m_sRv);
    } 

    //-------------------------------------
    //bStrToBool
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxString::bStrToBool(xT("true"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bStrToBool(xT("trUe"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bStrToBool(xT("true"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bStrToBool(xT("false"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bStrToBool(xT("FAlse"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bStrToBool(xT("false"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bStrToBool(xT(" true "));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bStrToBool(xT("qwertyuiop[]"));
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    //sTrimLeftChars
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sTestData[][2] = {
            {xT("TEST_STRIN#G_1"),       xT("TEST_STRIN#G_1")},
            {xT("TEST_STRING_2#"),       xT("TEST_STRING_2#")},
            {xT("TEST_STRING_3"),        xT("#TEST_STRING_3")},
            {xT("TEST_#STRING_4"),       xT("##TEST_#STRING_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::sTrimLeftChars(sTestData[i][0], xT("#"));
            std::tstring_t sStr2 = CxString::sTrimLeftChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = sTestData[i][0];
            std::tstring_t sStr4 = CxString::sTrimLeftChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sTrimRightChars
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sTestData[][2] = {
            {xT("#TEST_STRING_1"),       xT("#TEST_STRING_1")},
            {xT("TE#ST_STRING_2"),       xT("TE#ST_STRING_2")},
            {xT("TEST_STRING_3"),        xT("TEST_STRING_3##")},
            {xT("TEST_STRING#_4"),       xT("TEST_STRING#_4#")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::sTrimRightChars(sTestData[i][0], xT("#"));
            std::tstring_t sStr2 = CxString::sTrimRightChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = sTestData[i][0];
            std::tstring_t sStr4 = CxString::sTrimRightChars(sTestData[i][1], xT("#"));

            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sTrimChars
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sTestData[][2] = {
            {xT("TEST_STRING_1"),        xT("+-#####TEST_STRING_1+-")},
            {xT("TEST_STRING_2"),        xT("TEST_STRING_2#####+-+-+-")},
            {xT("TEST_STRING_3"),        xT("+-+-###TEST_STRING_3####+-+-+-")},
            {xT("TEST_#STRING_4"),       xT("#+-##+-TEST_#STRING_4#+-#+-##")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::sTrimChars(sTestData[i][0], xT("#+-"));
            std::tstring_t sStr2 = CxString::sTrimChars(sTestData[i][1], xT("#+-"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr4 = sTestData[i][0];
            std::tstring_t sStr3 = CxString::sTrimChars(sTestData[i][1], xT("#+-"));
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sTrimSpace
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sTestData[][2] = {
            {xT("TEST_STRING_1"),  xT("           TEST_STRING_1")},
            {xT("TEST_STRING_2"),  xT("TEST_STRING_2       ")},
            {xT("TEST_STRING_3"),  xT("        TEST_STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("        TEST_ STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("     TEST_ STRING_3    ")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::sTrimSpace(sTestData[i][0]);
            std::tstring_t sStr2 = CxString::sTrimSpace(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::sTrimSpace(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sRemoveEol
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::sRemoveEol(sTestData[i][0]);
            std::tstring_t sStr2 = CxString::sRemoveEol(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::sRemoveEol(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sReplaceAll
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxString::sReplaceAll(xT("aTaaaEaST_aSTaRINaaGaa_1a"), xT("a"), xT(""));
        xTEST_EQ(std::tstring_t(xT("TEST_STRING_1")), m_sRv);

        m_sRv = CxString::sReplaceAll(xT("TEST_STRING_1"), xT("T"), xT("a"));
        xTEST_EQ(std::tstring_t(xT("aESa_SaRING_1")), m_sRv);

        m_sRv = CxString::sReplaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("/"), xT("_"));
        xTEST_EQ(std::tstring_t(xT("D:_XVCL_Include\\XVCL_Units_Gui_vSpeedButton_LoadDrives.cpp")), m_sRv);

        m_sRv = CxString::sReplaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("\\"), xT("_"));
        xTEST_EQ(std::tstring_t(xT("D:/XVCL/Include_XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp")), m_sRv);

        m_sRv = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT(""));
        xTEST_EQ(std::tstring_t(xT("_one__three_")), m_sRv);

        m_sRv = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT("fife"));
        xTEST_EQ(std::tstring_t(xT("_one_fife_three_")), m_sRv);

        m_sRv = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT("^"));
        xTEST_EQ(std::tstring_t(xT("_one_^_three_")), m_sRv);

        m_sRv = CxString::sReplaceAll(xT("aaaaffaaaa"), xT("ff"), xT("ffff"));
        xTEST_EQ(std::tstring_t(xT("aaaaffffaaaa")), m_sRv);

        m_sRv = CxString::sReplaceAll(xT("aaaaffaaaa"), xT("ff"), xT("f"));
        xTEST_EQ(std::tstring_t(xT("aaaafaaaa")), m_sRv);
    }

    //-------------------------------------
    //sReplaceAll
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxString::sReplaceAll(xT(" one test string "), xT(" "), xT("_"));
        xTEST_EQ(m_sRv, std::tstring_t(xT("_one_test_string_")));

        m_sRv = CxString::sReplaceAll(xT(" one test string "), xT(" "), xT(""));
        xTEST_EQ(m_sRv, std::tstring_t(xT("oneteststring")));

        m_sRv = CxString::sReplaceAll(xT(" one test string "), xT(' '), xT('-'));
        xTEST_EQ(m_sRv, std::tstring_t(xT("-one-test-string-")));
    }

    //-------------------------------------
    //sRemoveAll
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxString::sRemoveAll(xT(" one test string "), xT(" "));
        xTEST_EQ(std::tstring_t(xT("oneteststring")), m_sRv);

        m_sRv = CxString::sRemoveAll(xT(" one test string "), xT(" "));
        xTEST_EQ(std::tstring_t(xT("oneteststring")), m_sRv);

        m_sRv = CxString::sRemoveAll(xT("one test strin g"),  xT(" "));
        xTEST_EQ(std::tstring_t(xT("oneteststring")), m_sRv);

        m_sRv = CxString::sRemoveAll(xT(" one test string "), xT("string"));
        xTEST_EQ(std::tstring_t(xT(" one test  ")), m_sRv);

        m_sRv = CxString::sRemoveAll(xT(" one test string "), xT("string"));
        xTEST_EQ(std::tstring_t(xT(" one test  ")), m_sRv);

        m_sRv = CxString::sRemoveAll(xT("one test stringg"),  xT("string"));
        xTEST_EQ(std::tstring_t(xT("one test g")), m_sRv);
    }

    //-------------------------------------
    //bSplit
    xTEST_CASE(cullCaseLoops)
    {
        std::vec_tstring_t vsText;

        m_bRv = CxString::bSplit(xT("1+++22+++333+++4444+++55555+++666666"), xT("+"), &vsText);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bSplit(xT("Key+"), xT("+"), &vsText);
        xTEST_EQ(true, m_bRv);

        vsText.clear();
        m_bRv = CxString::bSplit(xT(""), xT("+"), &vsText);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //sJoin
    xTEST_CASE(cullCaseLoops)
    {
        std::vec_tstring_t vsRes;
        vsRes.push_back(xT("111"));
        vsRes.push_back(xT(""));
        vsRes.push_back(xT("222"));
        vsRes.push_back(xT("333"));

        m_sRv = CxString::sJoin(vsRes, xT("-"));
        xTEST_EQ(std::tstring_t(xT("111--222-333")), m_sRv);
    }

    //-------------------------------------
    //sJoin
    xTEST_CASE(cullCaseLoops)
    {
        std::vec_tstring_t vsRes;
        vsRes.push_back(xT("111"));
        vsRes.push_back(xT(""));
        vsRes.push_back(xT("222"));
        vsRes.push_back(xT("333"));

        m_sRv = CxString::sJoin(vsRes, xT('-'));
        xTEST_EQ(std::tstring_t(xT("111--222-333")), m_sRv);
    }

    //-------------------------------------
    //sCut
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sForCut;

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <_Alca@meta.ua_>");
        m_sRv = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("<_Alca@meta.ua_>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<_Alc<a>@meta>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("_Alc<a>@meta>.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125>_Alca@meta.ua_<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca<>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <<_Alca@meta.ua_>>");
        m_sRv = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("<<_Alca@meta.ua_>>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alca@meta.ua_")), m_sRv);

        sForCut = xT("To: =?windows-125<<_Alc<<a>>@meta>>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("_Alc<<a>>@meta")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125>>_Alca@meta.ua_<<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        sForCut = xT("To: =?windows-125_Alca<<>>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRv = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);
    }

    //-------------------------------------
    //sCut
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sForCut = xT("0123456789");


        m_sRv = CxString::sCut(sForCut, 0, 1);
        xTEST_EQ(std::tstring_t(xT("0")), m_sRv);

        m_sRv = CxString::sCut(sForCut, 0, 9);
        xTEST_EQ(std::tstring_t(xT("012345678")), m_sRv);

        m_sRv = CxString::sCut(sForCut, 4, 5);
        xTEST_EQ(std::tstring_t(xT("4")), m_sRv);

        m_sRv = CxString::sCut(sForCut, 4, 6);
        xTEST_EQ(std::tstring_t(xT("45")), m_sRv);

        m_sRv = CxString::sCut(sForCut, 6, 6);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::sCut(sForCut, 6, 4);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::sCut(xT(""), 1, 2);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::sCut(sForCut, 0);
        xTEST_EQ(std::tstring_t(xT("0123456789")), m_sRv);

        m_sRv = CxString::sCut(sForCut, 4);
        xTEST_EQ(std::tstring_t(xT("456789")), m_sRv);

        m_sRv = CxString::sCut(sForCut, 9);
        xTEST_EQ(std::tstring_t(xT("9")), m_sRv);

        m_sRv = CxString::sCut(sForCut, 10);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::sCut(xT(""), 1);
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv = CxString::sCut(sForCut);
        xTEST_EQ(std::tstring_t(xT("0123456789")), m_sRv);
    }

    //-------------------------------------
    //sToLowerCase
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sTestData[][2] = {
            {xT("test_string_1"),       xT("TEST_string_1")},
            {xT("test_string_1"),       xT("TEst_stRING_1")},
            {xT("test_string_1\n"),     xT("TEST_STRing_1\n")},
            {xT("test_string_1\n\r"),   xT("TEST_STring_1\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::sToLowerCase(sTestData[i][0]);
            std::tstring_t sStr2 = CxString::sToLowerCase(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::sToLowerCase(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToUpperCase
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sTestData[][2] = {
            {xT("TEST_STRING_1_A"),       xT("TEST_string_1_a")},
            {xT("TEST_STRING_1_A"),       xT("TEst_stRING_1_A")},
            {xT("TEST_STRING_1_A\n"),     xT("TEST_STRing_1_a\n")},
            {xT("TEST_STRING_1_A\n\r"),   xT("TEST_STring_1_A\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::sToUpperCase(sTestData[i][0]);
            std::tstring_t sStr2 = CxString::sToUpperCase(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::sToUpperCase(sTestData[i][1]);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToLowerCase
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sTestData[][2] = {
            {xT("test_string_1_a"), xT("test_string_1_A")},
            {xT("test_string_1_a"), xT("Test_strINg_1_a")},
            {xT("test_string_1_a"), xT("test_STRING_1_A")},
            {xT("test_string_1_a"), xT("Test_string_1_a")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::sToLowerCase(sTestData[i][0], sTestData[i][0].size());
            std::tstring_t sStr2 = CxString::sToLowerCase(sTestData[i][1], sTestData[i][1].size());
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::sToLowerCase(sTestData[i][1], sTestData[i][1].size() + 1000);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToUpperCase
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sTestData[][2] = {
            {xT("TEST_STRING_1_A"), xT("tEST_string_1_A")},
            {xT("TEST_STRING_1_A"), xT("tEst_stRING_1_a")},
            {xT("TEST_STRING_1_A"), xT("TEST_STRing_1_a")},
            {xT("TEST_STRING_1_A"), xT("tEST_STring_1_A")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxString::sToUpperCase(sTestData[i][0], sTestData[i][0].size());
            std::tstring_t sStr2 = CxString::sToUpperCase(sTestData[i][1], sTestData[i][1].size());
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxString::sToUpperCase(sTestData[i][1], sTestData[i][1].size() - 1000);
            std::tstring_t sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sFormat
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sData;

        m_sRv = CxString::sFormat(xT("qqqq-wwww [%i]"), 1000);
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [1000]")));

        m_sRv = CxString::sFormat(xT("qqqq-wwww [%f]"), 1000.0);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxString::sFormat(xT("qqqq-wwww [%s]"), xT("1000"));
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [1000]")));

        m_sRv = CxString::sFormat(xT("qqqq-wwww [%i]"), -1000);
        xTEST_EQ(m_sRv, std::tstring_t(xT("qqqq-wwww [-1000]")));

        m_sRv = CxString::sFormat(xT("Characters: %c %c"), xT('a'), 65);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Characters: a A")));

        m_sRv = CxString::sFormat(xT("Decimals: %d %ld"), 1977, 650000L);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Decimals: 1977 650000")));

        m_sRv = CxString::sFormat(xT("Preceding with blanks: %10d"), 1977);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Preceding with blanks:       1977")));

        m_sRv = CxString::sFormat(xT("Preceding with zeros: %010d"), 1977);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Preceding with zeros: 0000001977")));

        m_sRv = CxString::sFormat(xT("Some different radixes: %d %x %o %#x %#o"), 100, 100, 100, 100, 100);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Some different radixes: 100 64 144 0x64 0144")));

        m_sRv = CxString::sFormat(xT("floats: %4.2f %+.0e %E"), 3.1416, 3.1416, 3.1416);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxString::sFormat(xT("Width trick: %*d"), 5, 10);
        xTEST_EQ(m_sRv, std::tstring_t(xT("Width trick:    10")));

        sData = xT("0A string2344565600");
        m_sRv = CxString::sFormat(xT("%s"), sData.c_str());
        xTEST_EQ(m_sRv, sData);

        sData = xT("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
        m_sRv = CxString::sFormat(xT("%s"), sData.c_str());
        xTEST_EQ(sData, m_sRv);

        //various string size
        {
            for (size_t i = 1; i < 1024 * 2; ++ i) {
                std::tstring_t _sData(i, xT('s'));

                std::tstring_t m_sRv = CxString::sFormat(xT("%s"), _sData.c_str());
                //xSTD_COUT("_sData (" << _sData.size() << ") = " << _sData << "\nm_sRes (" << m_sRv.size() << ") = " << m_sRv);

                xTEST_EQ(m_sRv.size(), _sData.size());
                xTEST_EQ(m_sRv,        _sData);
            }
        }
    }

    //-------------------------------------
    //sFormatV
    xTEST_CASE(cullCaseLoops)
    {
        //TODO: sFormatV
    }

    //-------------------------------------
    //sMinimize
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxString::sMinimize(xT("55555wwwww"), 5);
        xTEST_EQ(std::tstring_t(xT("55...")), m_sRv);

        m_sRv = CxString::sMinimize(xT("55555wwwww00000"), 20);
        xTEST_EQ(std::tstring_t(xT("55555wwwww00000")), m_sRv);
    }

    //-------------------------------------
    //bCompareNoCase
    xTEST_CASE(cullCaseLoops)
    {
        //must true
        m_bRv = CxString::bCompareNoCase(xT(""),     xT(""));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bCompareNoCase(xT("xxx"),  xT("XXX"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bCompareNoCase(xT("111"),  xT("111"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bCompareNoCase(xT("eee"),  xT("EeE"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bCompareNoCase(xT("WWW"),  xT("wwW"));
        xTEST_EQ(true, m_bRv);

        //maust false
        m_bRv = CxString::bCompareNoCase(xT("ccc"),  xT("CCCz"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bCompareNoCase(xT("!!!!!"),  xT("@@@@@@"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bCompareNoCase(xT("$$$$$"), xT("sdfgsdg"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bCompareNoCase(xT("&&&&&"),  xT("&&&&&????"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bCompareNoCase(xT("_+#$^%^&*^&*("), xT("@#$%TY(J^HGYT"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bCompareNoCase(xT("dddd"), xT("d"));
        xTEST_EQ(false, m_bRv);
    }


    /****************************************************************************
    *   �������������
    *
    *****************************************************************************/

    //-------------------------------------
    //sDecodeWinKoi
    xTEST_CASE(cullCaseLoops) {
        //m_sRv = sDecodeWinKoi(int iFrom, int iTo, const std::tstring_t &sOldStr);
    }

    //-------------------------------------
    //sTranslitLatToRus
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_sRv = CxString::sTranslitLatToRus(xT(""));
            xTEST_EQ(std::tstring_t(), m_sRv);

            m_sRv = CxString::sTranslitLatToRus(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll"));
            xTEST_EQ(std::tstring_t(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll")), m_sRv);
        #endif
    }

    //-------------------------------------
    //bCharToWide
    xTEST_CASE(cullCaseLoops) {
        //m_bRv = CxString::bCharToWide(const char *pszSrc, WCHAR *pwszDest, int iDestSize);
    }

    //-------------------------------------
    //sStrToRtf
    xTEST_CASE(cullCaseLoops) {
        //m_sRv = CxString::sStrToRtf(std::tstring_t sStr);
    }

    //-------------------------------------
    //sRtfToStr
    xTEST_CASE(cullCaseLoops) {
        //m_sRv = CxString::sRtfToStr(std::tstring_t sStr);
    }

    //-------------------------------------
    //sBytesToStr
    xTEST_CASE(cullCaseLoops)
    {
        const float cafFloats[] = {
            0.00001f,
            0.0001f,
            0.001f,
            0.01f,
            0.1f,
            0.0f,
            10.0f,
            100.0f,
            1000.0f,
            10000.0f,
            100000.0f,
            1000000.0f,
            10000000.0f,
            100000000.0f,
            1000000000.0f,
            10000000000.0f,
            100000000000.0f,
            1000000000000.0f,
            10000000000000.0f,
            100000000000000.0f,
            1000000000000000.0f,
            10000000000000000.0f,
            100000000000000000.0f,
            1000000000000000000.0f
        };

        for (size_t i = 0; i < xARRAY_SIZE(cafFloats); ++ i) {
            m_sRv = CxString::sFormatBytes(cafFloats[i]);
            //xTRACE(m_sRv);
        }
    }

    //-------------------------------------
    //sBytesToStr(ulonglong_t )
    xTEST_CASE(cullCaseLoops)
    {
        const ulonglong_t caullULongLong[] = {
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
            m_sRv = CxString::sFormatBytes(caullULongLong[i]);
            //xTRACE(m_sRv);
        }
    }

    //TODO: CxString::sFormatPercent(ulonglong_t ullMaxValue, ulonglong_t ullCurrValue)
    xTEST_CASE(cullCaseLoops)
    {

    }

    //--------------------------------------------------
    //sFormatNixTerminal
    xTEST_CASE(cullCaseLoops)
    {
    #if xTODO
        for (int i = 0; i <= 120; ++ i) {
            std::tstring_t sRv = sColorStr(xT("Linux Console Color"), (EForeground)i, false, false, bgBlack, false);
            std::cout<< xT("Color: ") << i << xT(" ") << sRv << std::endl;
        }

        std::tstring_t sRv = CxString::sFormatNixTerminal(xT("Linux Console Color"), CxString::fgYellow_, true, false, CxString::bgBlue_, false);
        std::cout << sRv << std::endl;
    #endif
    }

    /****************************************************************************
    *    memory
    *
    *****************************************************************************/

    //--------------------------------------------------
    //pvMemoryZeroSecure
    xTEST_CASE(cullCaseLoops)
    {
        //1
        {
            std::tstring_t asBuff[] = {
                    xT("0123456789"),
                    xT("aaaaaaaaaaaaaaaaaa"),
                    xT("wo34875j0w9958u0342ku59u28934u5"),
            };

            for (size_t i = 0; i < xARRAY_SIZE(asBuff); ++ i) {
                m_pvRv = CxString::pvMemoryZeroSecure(&asBuff[i].at(0), asBuff[i].size() * sizeof(std::tstring_t::value_type));
                xTEST_PTR(m_pvRv);

                for (size_t x = 0; x < asBuff[i].size() * sizeof(std::tstring_t::value_type); ++ x) {
                    xASSERT(0 == asBuff[i].at(x));
                }
            }
        }

        //2
        {
            const size_t cauiSizes[] = {1, 0, 10, 100000000};

            for (size_t i = 0; i < xARRAY_SIZE(cauiSizes); ++ i) {
                m_pvRv = CxString::pvMemoryZeroSecure(NULL, cauiSizes[i]);
                xASSERT(NULL == m_pvRv);
            }
        }
    }


    /****************************************************************************
    *    ������
    *
    *****************************************************************************/

    //-------------------------------------
    //sCreateGuid
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            m_sRv = CxString::sCreateGuid();
            xTEST_EQ(false, m_sRv.empty());
        #elif xOS_ENV_UNIX
            ////xTEST_EQ(true, m_sRv.empty());
        #endif
    }

    //-------------------------------------
    //bIsRepeated
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxString::bIsRepeated(xT("yyyyyyyyyyyy"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bIsRepeated(xT("111111111111"));
        xTEST_EQ(true, m_bRv);

        m_bRv = CxString::bIsRepeated(xT("uuuuuiuuuuuuuuuuuu"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxString::bIsRepeated(xT("000000000111111111"));
        xTEST_EQ(false, m_bRv);
    }


    /****************************************************************************
    *   formating
    *
    *****************************************************************************/

    //-------------------------------------
    //sConvertCodePage
    xTEST_CASE(cullCaseLoops)
    {
        const std::string csAnsiStr[] = {
            "gnhjfgyhj ghj...",
            "vhgnjhghjfgh 234563476 45674_+()_ (*?)casf,fjpo,e rfWAERCWER$%^*())_+)+*()BNVNH*",
            "123 456 7890",
            "!@#$% ^&*()_+|* /{}:@' \"?><",
            " ",
            ""
        };

        for (size_t i = 0; i < xARRAY_SIZE(csAnsiStr) - 1; i ++) {
            #if xOS_ENV_WIN
                //CP_ACP(ANSI) <-> CP_UTF8(UTF-8)
                std::string sAnsi;
                std::string sUtf8;

                sUtf8 = CxString::sConvertCodePage(csAnsiStr[i], CP_ACP,  CP_UTF8);
                sAnsi = CxString::sConvertCodePage(sUtf8,        CP_UTF8, CP_ACP);
                xTEST_EQ(csAnsiStr[i], sAnsi);


                //1251(WIN)  <-> 20866(KOI-8r)
                std::string sKoiStr;
                std::string sWinStr;

                sKoiStr = CxString::sConvertCodePage(csAnsiStr[i], 1251,  20866);
                sWinStr = CxString::sConvertCodePage(sKoiStr,      20866, 1251);
                xTEST_EQ(csAnsiStr[i], sWinStr);
            #elif xOS_ENV_UNIX
                //TODO: sConvertCodePage
                //xNOT_IMPLEMENTED_RET(RET_VALUE);
            #endif
        }
    }

    //-------------------------------------
    //sCharToOemBuff
    xTEST_CASE(cullCaseLoops)
    {
        std::string sRv;

        #if xOS_ENV_WIN
            sRv = CxString::asCharToOemBuff(xT("Boss, hello? "));
            xTEST_EQ(std::string("Boss, hello? "), sRv);
        #elif xOS_ENV_UNIX
            //TODO: sCharToOemBuff
        #endif
    }

    //-------------------------------------
    //sOemToCharBuff
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sRv;

        #if xOS_ENV_WIN
            sRv = CxString::sOemToCharBuff(("1111, hdbhjgjk hkl, jl.,kh."));
            xTEST_EQ(std::tstring_t(xT("1111, hdbhjgjk hkl, jl.,kh.")), sRv);
        #elif xOS_ENV_UNIX
            //TODO: sOemToCharBuff
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
