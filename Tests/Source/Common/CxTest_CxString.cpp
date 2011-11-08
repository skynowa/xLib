/****************************************************************************
* Class name:  CxTest_CxString
* Description: test CxString
* File name:   CxTest_CxString.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxString.h>


//---------------------------------------------------------------------------
CxTest_CxString::CxTest_CxString() {

}
//---------------------------------------------------------------------------
CxTest_CxString::~CxTest_CxString() {

}
//---------------------------------------------------------------------------
UCHAR 
RandomNumber () { 
    return (UCHAR)(rand()%100); 
}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxString::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    /****************************************************************************
    *    convertation
    *
    *****************************************************************************/

    //--------------------------------------------------
    //operator << for std::ustring
    xTEST_BLOCK(cullBlockLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            std::ustring usStr;

            usStr.resize( (size_t)CxRandom::liGetInt(1, 64) );
            std::fill_n(usStr.begin(), usStr.size(), static_cast<std::ustring::value_type>( CxRandom::liGetInt(1, 255) ));

            std::tstring sVal1 = std::tstring(usStr.begin(), usStr.end());

            std::tostringstream osOut;   osOut << usStr;
            std::tstring sVal2 = osOut.str();

            xTEST_EQ(sVal1, sVal2);
        }
    }

    //--------------------------------------------------
    //operator << for std::vector
    xTEST_BLOCK(cullBlockLoops)
    {
        m_vsRes.clear();

        m_vsRes.push_back(xT("Value0"));
        m_vsRes.push_back(xT("Value1"));
        m_vsRes.push_back(xT("Value2"));
        m_vsRes.push_back(xT("Value3"));
        m_vsRes.push_back(xT("Value4"));

        std::tostringstream osOut;   osOut << m_vsRes;
        //xTRACEV(xT("\toperator << for std::vector: %s"), osOut.str().c_str());
        xTEST_EQ(false, osOut.str().empty());

        m_vsRes.clear();
    }

    //--------------------------------------------------
    //operator << for std::map
    xTEST_BLOCK(cullBlockLoops)
    {
        m_msRes.clear();

        m_msRes.insert( std::pair<std::tstring, std::tstring>(xT("Key0"), xT("Value0")) );
        m_msRes.insert( std::pair<std::tstring, std::tstring>(xT("Key1"), xT("Value1")) );
        m_msRes.insert( std::pair<std::tstring, std::tstring>(xT("Key2"), xT("Value2")) );
        m_msRes.insert( std::pair<std::tstring, std::tstring>(xT("Key3"), xT("Value3")) );
        m_msRes.insert( std::pair<std::tstring, std::tstring>(xT("Key4"), xT("Value4")) );

        std::tostringstream osOut;   osOut << m_msRes;
        //xTRACEV(xT("\toperator << for std::map: %s"), osOut.str().c_str());
        xTEST_EQ(false, osOut.str().empty());

        m_msRes.clear();
    }

    //--------------------------------------------------
    //operator << for std::multimap
    xTEST_BLOCK(cullBlockLoops)
    {
        m_mmsRes.clear();

        m_mmsRes.insert( std::pair<std::tstring, std::tstring>(xT("Key0"), xT("Value0")) );
        m_mmsRes.insert( std::pair<std::tstring, std::tstring>(xT("Key1"), xT("Value1")) );
        m_mmsRes.insert( std::pair<std::tstring, std::tstring>(xT("Key2"), xT("Value2")) );
        m_mmsRes.insert( std::pair<std::tstring, std::tstring>(xT("Key0"), xT("Value0")) );
        m_mmsRes.insert( std::pair<std::tstring, std::tstring>(xT("Key1"), xT("Value1")) );

        std::tostringstream osOut;   osOut << m_mmsRes;
        //xTRACEV(xT("\toperator << for std::multimap: %s"), osOut.str().c_str());
        xTEST_EQ(false, osOut.str().empty());

        m_mmsRes.clear();
    }

    //-------------------------------------
    //lexical_cast (to string)
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::lexical_cast(1);
        xTEST_EQ(std::tstring(xT("1")), m_sRes);

        m_sRes = CxString::lexical_cast(xT('A'));
        xTEST_EQ(std::tstring(xT("A")), m_sRes);

        m_sRes = CxString::lexical_cast(xT("-"));
        xTEST_EQ(std::tstring(xT("-")), m_sRes);

        m_sRes = CxString::lexical_cast(0.0);
        xTEST_EQ(std::tstring(xT("0")), m_sRes);

        m_sRes = CxString::lexical_cast(- 5);
        xTEST_EQ(std::tstring(xT("-5")), m_sRes);

        m_sRes = CxString::lexical_cast(true);
        xTEST_EQ(std::tstring(xT("1")), m_sRes);

        m_sRes = CxString::lexical_cast(false);
        xTEST_EQ(std::tstring(xT("0")), m_sRes);
    }

    //-------------------------------------
    //lexical_cast (from string)
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::lexical_cast<std::tstring>(xT("String"));
        xTEST_EQ(std::tstring(xT("String")), m_sRes);

        m_iRes = CxString::lexical_cast<INT>(xT("7"));
        xTEST_EQ(7, m_iRes);

        m_ulRes = CxString::lexical_cast<ULONG>(xT("123"));
        xTEST_EQ(123UL, m_ulRes);

        m_ullRes = CxString::lexical_cast<ULONGLONG>(xT("123"));
        xTEST_EQ(123ULL, m_ullRes);

        m_dRes = CxString::lexical_cast<double>(xT("5.3"));
        xTEST_EQ(5.3, m_dRes);

        ////m_bRes = lexical_cast<bool>(xT("true"));
        ////xTEST_EQ(5.3, m_dRes);

        ////m_bRes = lexical_cast<bool>(xT("false"));
        ////xTEST_EQ(5.3, m_dRes);

        ////m_uiRes = CxString::lexical_cast<size_t>( std::tstring() );
        ////xTEST_EQ(0U, m_uiRes);
    }

    //-------------------------------------
    //lexical_cast (to string by base)
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::lexical_cast(1033, 8);
        xTEST_EQ(std::tstring(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033, 10);
        xTEST_EQ(std::tstring(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033, 16);
        xTEST_EQ(std::tstring(xT("409")), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_sRes = CxString::sIntToStr(1033L, 2);
        ////xTEST_EQ(std::tstring(xT("10000001001")), m_sRes);

        m_sRes = CxString::lexical_cast(1033L, 8);
        xTEST_EQ(std::tstring(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033L, 10);
        xTEST_EQ(std::tstring(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033L, 16);
        xTEST_EQ(std::tstring(xT("409")), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_sRes = CxString::sIntToStr(1033UL, 2);
        ////xTEST_EQ(std::tstring(xT("10000001001")), m_sRes);

        m_sRes = CxString::lexical_cast(1033UL, 8);
        xTEST_EQ(std::tstring(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033UL, 10);
        xTEST_EQ(std::tstring(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033UL, 16);
        xTEST_EQ(std::tstring(xT("409")), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_sRes = CxString::sIntToStr(1033LL, 2);
        ////xTEST_EQ(xT("10000001001") == m_sRes);

        m_sRes = CxString::lexical_cast(1033LL, 8);
        xTEST_EQ(std::tstring(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033LL, 10);
        xTEST_EQ(std::tstring(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033LL, 16);
        xTEST_EQ(std::tstring(xT("409")), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_sRes = CxString::sIntToStr(1033ULL, 2);
        ////xTEST_EQ(std::tstring(xT("10000001001")), m_sRes);

        m_sRes = CxString::lexical_cast(1033ULL, 8);
        xTEST_EQ(std::tstring(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033ULL, 10);
        xTEST_EQ(std::tstring(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033ULL, 16);
        xTEST_EQ(std::tstring(xT("409")), m_sRes);
    }

    //-------------------------------------
    //lexical_cast (from, to string by base)
    xTEST_BLOCK(cullBlockLoops)
    {
        const INT caiBases[] = {8, 10, 16};

        const std::tstring casData[] = {
                xT("01234567890ABC"),
                xT("01234567890"),
                xT("ABCDEF"),
                xT("ABCDEF01234567890ABC"),
                xT("01234AA567890ABC")
        };

        for (size_t b = 0; b < xARRAY_SIZE(caiBases); ++ b) {
            for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
                const std::tstring sRes    = casData[i];

                const std::tstring sHexStr = CxString::lexical_cast(sRes, caiBases[b]);
                const std::tstring sStdStr = CxString::lexical_cast<std::tstring>(sHexStr, caiBases[b]);

                xTEST_EQ(sRes, sStdStr);
            }
        }
    }

    //-------------------------------------
    //bBoolToStr
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::sBoolToStr(TRUE);
        xTEST_EQ(std::tstring(xT("TRUE")), m_sRes);

        m_sRes = CxString::sBoolToStr(FALSE);
        xTEST_EQ(std::tstring(xT("FALSE")), m_sRes);
    }

    //-------------------------------------
    //bStrToBool
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxString::bStrToBool(xT("true"));
        xTEST_EQ(TRUE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("trUe"));
        xTEST_EQ(TRUE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("TRUE"));
        xTEST_EQ(TRUE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("false"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("FAlse"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("FALSE"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bStrToBool(xT(" TRUE "));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("qwertyuiop[]"));
        xTEST_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //sTrimLeftChars
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sTestData[][2] = {
            {xT("TEST_STRIN#G_1"),       xT("TEST_STRIN#G_1")},
            {xT("TEST_STRING_2#"),       xT("TEST_STRING_2#")},
            {xT("TEST_STRING_3"),        xT("#TEST_STRING_3")},
            {xT("TEST_#STRING_4"),       xT("##TEST_#STRING_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring sStr1 = CxString::sTrimLeftChars(sTestData[i][0], xT("#"));
            std::tstring sStr2 = CxString::sTrimLeftChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring sStr3 = sTestData[i][0];
            std::tstring sStr4 = CxString::sTrimLeftChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sTrimRightChars
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sTestData[][2] = {
            {xT("#TEST_STRING_1"),       xT("#TEST_STRING_1")},
            {xT("TE#ST_STRING_2"),       xT("TE#ST_STRING_2")},
            {xT("TEST_STRING_3"),        xT("TEST_STRING_3##")},
            {xT("TEST_STRING#_4"),       xT("TEST_STRING#_4#")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring sStr1 = CxString::sTrimRightChars(sTestData[i][0], xT("#"));
            std::tstring sStr2 = CxString::sTrimRightChars(sTestData[i][1], xT("#"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring sStr3 = sTestData[i][0];
            std::tstring sStr4 = CxString::sTrimRightChars(sTestData[i][1], xT("#"));

            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sTrimChars
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sTestData[][2] = {
            {xT("TEST_STRING_1"),        xT("+-#####TEST_STRING_1+-")},
            {xT("TEST_STRING_2"),        xT("TEST_STRING_2#####+-+-+-")},
            {xT("TEST_STRING_3"),        xT("+-+-###TEST_STRING_3####+-+-+-")},
            {xT("TEST_#STRING_4"),       xT("#+-##+-TEST_#STRING_4#+-#+-##")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring sStr1 = CxString::sTrimChars(sTestData[i][0], xT("#+-"));
            std::tstring sStr2 = CxString::sTrimChars(sTestData[i][1], xT("#+-"));
            xTEST_EQ(sStr1, sStr2);

            std::tstring sStr4 = sTestData[i][0];
            std::tstring sStr3 = CxString::sTrimChars(sTestData[i][1], xT("#+-"));
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sTrimSpace
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sTestData[][2] = {
            {xT("TEST_STRING_1"),  xT("           TEST_STRING_1")},
            {xT("TEST_STRING_2"),  xT("TEST_STRING_2       ")},
            {xT("TEST_STRING_3"),  xT("        TEST_STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("        TEST_ STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("     TEST_ STRING_3    ")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring sStr1 = CxString::sTrimSpace(sTestData[i][0]);
            std::tstring sStr2 = CxString::sTrimSpace(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring sStr3 = CxString::sTrimSpace(sTestData[i][1]);
            std::tstring sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sRemoveEol
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const std::tstring sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #elif defined(xOS_ENV_UNIX)
            const std::tstring sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring sStr1 = CxString::sRemoveEol(sTestData[i][0]);
            std::tstring sStr2 = CxString::sRemoveEol(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring sStr3 = CxString::sRemoveEol(sTestData[i][1]);
            std::tstring sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sReplaceAll
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::sReplaceAll(xT("aTaaaEaST_aSTaRINaaGaa_1a"), xT("a"), xT(""));
        xTEST_EQ(std::tstring(xT("TEST_STRING_1")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("TEST_STRING_1"), xT("T"), xT("a"));
        xTEST_EQ(std::tstring(xT("aESa_SaRING_1")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("/"), xT("_"));
        xTEST_EQ(std::tstring(xT("D:_XVCL_Include\\XVCL_Units_Gui_vSpeedButton_LoadDrives.cpp")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("\\"), xT("_"));
        xTEST_EQ(std::tstring(xT("D:/XVCL/Include_XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT(""));
        xTEST_EQ(std::tstring(xT("_one__three_")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT("fife"));
        xTEST_EQ(std::tstring(xT("_one_fife_three_")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT("^"));
        xTEST_EQ(std::tstring(xT("_one_^_three_")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("aaaaffaaaa"), xT("ff"), xT("ffff"));
        xTEST_EQ(std::tstring(xT("aaaaffffaaaa")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("aaaaffaaaa"), xT("ff"), xT("f"));
        xTEST_EQ(std::tstring(xT("aaaafaaaa")), m_sRes);
    }

    //-------------------------------------
    //sReplaceAll
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::sReplaceAll(xT(" one test string "), xT(" "), xT("_"));
        xTEST_EQ(m_sRes, std::tstring(xT("_one_test_string_")));

        m_sRes = CxString::sReplaceAll(xT(" one test string "), xT(" "), xT(""));
        xTEST_EQ(m_sRes, std::tstring(xT("oneteststring")));

        m_sRes = CxString::sReplaceAll(xT(" one test string "), xT(' '), xT('-'));
        xTEST_EQ(m_sRes, std::tstring(xT("-one-test-string-")));
    }

    //-------------------------------------
    //sRemoveAll
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT(" "));
        xTEST_EQ(std::tstring(xT("oneteststring")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT(" "));
        xTEST_EQ(std::tstring(xT("oneteststring")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT("one test strin g"),  xT(" "));
        xTEST_EQ(std::tstring(xT("oneteststring")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT("string"));
        xTEST_EQ(std::tstring(xT(" one test  ")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT("string"));
        xTEST_EQ(std::tstring(xT(" one test  ")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT("one test stringg"),  xT("string"));
        xTEST_EQ(std::tstring(xT("one test g")), m_sRes);
    }

    //-------------------------------------
    //bSplit
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<std::tstring> vsText;

        m_bRes = CxString::bSplit(xT("1+++22+++333+++4444+++55555+++666666"), xT("+"), &vsText);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxString::bSplit(xT("Key+"), xT("+"), &vsText);
        xTEST_DIFF(FALSE, m_bRes);

        vsText.clear();
        m_bRes = CxString::bSplit(xT(""), xT("+"), &vsText);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //sJoin
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<std::tstring> vsRes;
        vsRes.push_back(xT("111"));
        vsRes.push_back(xT(""));
        vsRes.push_back(xT("222"));
        vsRes.push_back(xT("333"));

        m_sRes = CxString::sJoin(vsRes, xT("-"));
        xTEST_EQ(std::tstring(xT("111--222-333")), m_sRes);
    }

    //-------------------------------------
    //sJoin
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<std::tstring> vsRes;
        vsRes.push_back(xT("111"));
        vsRes.push_back(xT(""));
        vsRes.push_back(xT("222"));
        vsRes.push_back(xT("333"));

        m_sRes = CxString::sJoin(vsRes, xT('-'));
        xTEST_EQ(std::tstring(xT("111--222-333")), m_sRes);
    }

    //-------------------------------------
    //sCut
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sForCut;

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <_Alca@meta.ua_>");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("<_Alca@meta.ua_>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125<_Alc<a>@meta>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring(xT("_Alc<a>@meta>.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125>_Alca@meta.ua_<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125_Alca<>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <<_Alca@meta.ua_>>");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("<<_Alca@meta.ua_>>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125<<_Alc<<a>>@meta>>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring(xT("_Alc<<a>>@meta")), m_sRes);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125>>_Alca@meta.ua_<<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125_Alca<<>>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xTEST_EQ(std::tstring(xT("")), m_sRes);
    }

    //-------------------------------------
    //sCut
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sForCut = xT("0123456789");


        m_sRes = CxString::sCut(sForCut, 0, 1);
        xTEST_EQ(std::tstring(xT("0")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 0, 9);
        xTEST_EQ(std::tstring(xT("012345678")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 4, 5);
        xTEST_EQ(std::tstring(xT("4")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 4, 6);
        xTEST_EQ(std::tstring(xT("45")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 6, 6);
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 6, 4);
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        m_sRes = CxString::sCut(xT(""), 1, 2);
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 0);
        xTEST_EQ(std::tstring(xT("0123456789")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 4);
        xTEST_EQ(std::tstring(xT("456789")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 9);
        xTEST_EQ(std::tstring(xT("9")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 10);
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        m_sRes = CxString::sCut(xT(""), 1);
        xTEST_EQ(std::tstring(xT("")), m_sRes);

        m_sRes = CxString::sCut(sForCut);
        xTEST_EQ(std::tstring(xT("0123456789")), m_sRes);
    }

    //-------------------------------------
    //sToLowerCase
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring sTestData[][2] = {
            {xT("test_string_1"),       xT("TEST_string_1")},
            {xT("test_string_1"),       xT("TEst_stRING_1")},
            {xT("test_string_1\n"),     xT("TEST_STRing_1\n")},
            {xT("test_string_1\n\r"),   xT("TEST_STring_1\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring sStr1 = CxString::sToLowerCase(sTestData[i][0]);
            std::tstring sStr2 = CxString::sToLowerCase(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring sStr3 = CxString::sToLowerCase(sTestData[i][1]);
            std::tstring sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToUpperCase
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring sTestData[][2] = {
            {xT("TEST_STRING_1_A"),       xT("TEST_string_1_a")},
            {xT("TEST_STRING_1_A"),       xT("TEst_stRING_1_A")},
            {xT("TEST_STRING_1_A\n"),     xT("TEST_STRing_1_a\n")},
            {xT("TEST_STRING_1_A\n\r"),   xT("TEST_STring_1_A\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring sStr1 = CxString::sToUpperCase(sTestData[i][0]);
            std::tstring sStr2 = CxString::sToUpperCase(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring sStr3 = CxString::sToUpperCase(sTestData[i][1]);
            std::tstring sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToLowerCase
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring sTestData[][2] = {
            {xT("test_string_1_a"), xT("test_string_1_A")},
            {xT("test_string_1_a"), xT("Test_strINg_1_a")},
            {xT("test_string_1_a"), xT("test_STRING_1_A")},
            {xT("test_string_1_a"), xT("Test_string_1_a")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring sStr1 = CxString::sToLowerCase(sTestData[i][0], sTestData[i][0].size());
            std::tstring sStr2 = CxString::sToLowerCase(sTestData[i][1], sTestData[i][1].size());
            xTEST_EQ(sStr1, sStr2);

            std::tstring sStr3 = CxString::sToLowerCase(sTestData[i][1], sTestData[i][1].size() + 1000);
            std::tstring sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToUpperCase
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring sTestData[][2] = {
            {xT("TEST_STRING_1_A"), xT("tEST_string_1_A")},
            {xT("TEST_STRING_1_A"), xT("tEst_stRING_1_a")},
            {xT("TEST_STRING_1_A"), xT("TEST_STRing_1_a")},
            {xT("TEST_STRING_1_A"), xT("tEST_STring_1_A")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring sStr1 = CxString::sToUpperCase(sTestData[i][0], sTestData[i][0].size());
            std::tstring sStr2 = CxString::sToUpperCase(sTestData[i][1], sTestData[i][1].size());
            xTEST_EQ(sStr1, sStr2);

            std::tstring sStr3 = CxString::sToUpperCase(sTestData[i][1], sTestData[i][1].size() - 1000);
            std::tstring sStr4 = sTestData[i][0];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sFormat
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sData;

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%i]"), 1000);
        xTEST_EQ(m_sRes, std::tstring(xT("qqqq-wwww [1000]")));

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%f]"), 1000.0);
        #if defined(xOS_ENV_WIN)
            xTEST_EQ(m_sRes, std::tstring(xT("qqqq-wwww [1000,000000]")));
        #elif defined(xOS_ENV_UNIX)
            xTEST_EQ(m_sRes, std::tstring(xT("qqqq-wwww [1000.000000]")));
        #endif

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%s]"), xT("1000"));
        xTEST_EQ(m_sRes, std::tstring(xT("qqqq-wwww [1000]")));

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%i]"), -1000);
        xTEST_EQ(m_sRes, std::tstring(xT("qqqq-wwww [-1000]")));

        m_sRes = CxString::sFormat(xT("Characters: %c %c"), xT('a'), 65);
        xTEST_EQ(m_sRes, std::tstring(xT("Characters: a A")));

        m_sRes = CxString::sFormat(xT("Decimals: %d %ld"), 1977, 650000L);
        xTEST_EQ(m_sRes, std::tstring(xT("Decimals: 1977 650000")));

        m_sRes = CxString::sFormat(xT("Preceding with blanks: %10d"), 1977);
        xTEST_EQ(m_sRes, std::tstring(xT("Preceding with blanks:       1977")));

        m_sRes = CxString::sFormat(xT("Preceding with zeros: %010d"), 1977);
        xTEST_EQ(m_sRes, std::tstring(xT("Preceding with zeros: 0000001977")));

        m_sRes = CxString::sFormat(xT("Some different radixes: %d %x %o %#x %#o"), 100, 100, 100, 100, 100);
        xTEST_EQ(m_sRes, std::tstring(xT("Some different radixes: 100 64 144 0x64 0144")));

        m_sRes = CxString::sFormat(xT("floats: %4.2f %+.0e %E"), 3.1416, 3.1416, 3.1416);
        xTEST_EQ(false, m_sRes.empty());

        m_sRes = CxString::sFormat(xT("Width trick: %*d"), 5, 10);
        xTEST_EQ(m_sRes, std::tstring(xT("Width trick:    10")));

        sData = xT("0A string2344565600");
        m_sRes = CxString::sFormat(xT("%s"), sData.c_str());
        xTEST_EQ(m_sRes, sData);

        sData = xT("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
        m_sRes = CxString::sFormat(xT("%s"), sData.c_str());
        xTEST_EQ(sData, m_sRes);

        //various string size
        {
            for (size_t i = 1; i < 1024 * 2; ++ i) {
                std::tstring _sData(i, xT('s'));

                std::tstring m_sRes = CxString::sFormat(xT("%s"), _sData.c_str());
                //xSTD_COUT("_sData (" << _sData.size() << ") = " << _sData << "\nm_sRes (" << m_sRes.size() << ") = " << m_sRes);

                xTEST_EQ(m_sRes.size(), _sData.size());
                xTEST_EQ(m_sRes,        _sData);
            }
        }
    }

    //-------------------------------------
    //sFormatV
    xTEST_BLOCK(cullBlockLoops)
    {
        //TODO: sFormatV
    }

    //-------------------------------------
    //sMinimize
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::sMinimize(xT("55555wwwww"), 5);
        xTEST_EQ(std::tstring(xT("55...")), m_sRes);

        m_sRes = CxString::sMinimize(xT("55555wwwww00000"), 20);
        xTEST_EQ(std::tstring(xT("55555wwwww00000")), m_sRes);
    }

    //-------------------------------------
    //bCompareNoCase
    xTEST_BLOCK(cullBlockLoops)
    {
        //must TRUE
        m_bRes = CxString::bCompareNoCase(xT(""),     xT(""));
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("xxx"),  xT("XXX"));
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("111"),  xT("111"));
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("eee"),  xT("EeE"));
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("WWW"),  xT("wwW"));
        xTEST_DIFF(FALSE, m_bRes);

        //maust FALSE
        m_bRes = CxString::bCompareNoCase(xT("ccc"),  xT("CCCz"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("!!!!!"),  xT("@@@@@@"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("$$$$$"), xT("sdfgsdg"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("&&&&&"),  xT("&&&&&????"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("_+#$^%^&*^&*("), xT("@#$%TY(J^HGYT"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("dddd"), xT("d"));
        xTEST_EQ(FALSE, m_bRes);
    }


    /****************************************************************************
    *   �������������
    *
    *****************************************************************************/

    //-------------------------------------
    //sDecodeWinKoi
    xTEST_BLOCK(cullBlockLoops) {
        //m_sRes = sDecodeWinKoi(INT iFrom, INT iTo, const std::tstring &sOldStr);
    }

    //-------------------------------------
    //sTranslitLatToRus
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            m_sRes = CxString::sTranslitLatToRus(xT(""));
            xTEST_EQ(std::tstring(), m_sRes);

            m_sRes = CxString::sTranslitLatToRus(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll"));
            xTEST_EQ(std::tstring(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll")), m_sRes);
        #endif
    }

    //-------------------------------------
    //bCharToWide
    xTEST_BLOCK(cullBlockLoops) {
        //m_bRes = CxString::bCharToWide(const CHAR *pszSrc, WCHAR *pwszDest, INT iDestSize);
    }

    //-------------------------------------
    //sStrToRtf
    xTEST_BLOCK(cullBlockLoops) {
        //m_sRes = CxString::sStrToRtf(std::tstring sStr);
    }

    //-------------------------------------
    //sRtfToStr
    xTEST_BLOCK(cullBlockLoops) {
        //m_sRes = CxString::sRtfToStr(std::tstring sStr);
    }

    //-------------------------------------
    //sBytesToStr
    xTEST_BLOCK(cullBlockLoops)
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
            m_sRes = CxString::sFormatBytes(cafFloats[i]);
            //xTRACE(m_sRes);
        }
    }

    //-------------------------------------
    //sBytesToStr(ULONGLONG )
    xTEST_BLOCK(cullBlockLoops)
    {
        const ULONGLONG caullULongLong[] = {
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
            m_sRes = CxString::sFormatBytes(caullULongLong[i]);
            //xTRACE(m_sRes);
        }
    }

    //TODO: CxString::sFormatPercent(ULONGLONG ullMaxValue, ULONGLONG ullCurrValue)
    xTEST_BLOCK(cullBlockLoops)
    {

    }

    //--------------------------------------------------
    //sFormatNixTerminal
    xTEST_BLOCK(cullBlockLoops)
    {
    #if xTODO
        for (int i = 0; i <= 120; ++ i) {
            std::tstring sRes = sColorStr(xT("Linux Console Color"), (EForeground)i, FALSE, FALSE, bgBlack, FALSE);
            std::cout<< xT("Color: ") << i << xT(" ") << sRes << std::endl;
        }

        std::tstring sRes = CxString::sFormatNixTerminal(xT("Linux Console Color"), CxString::fgYellow_, TRUE, FALSE, CxString::bgBlue_, FALSE);
        std::cout << sRes << std::endl;
    #endif
    }

    /****************************************************************************
    *    memory
    *
    *****************************************************************************/

    //--------------------------------------------------
    //pvMemoryZeroSecure
    xTEST_BLOCK(cullBlockLoops)
    {
        //1
        {
            std::tstring asBuff[] = {
                    xT("0123456789"),
                    xT("aaaaaaaaaaaaaaaaaa"),
                    xT("wo34875j0w9958u0342ku59u28934u5"),
            };

            for (size_t i = 0; i < xARRAY_SIZE(asBuff); ++ i) {
                m_pvRes = CxString::pvMemoryZeroSecure(&asBuff[i].at(0), asBuff[i].size() * sizeof(std::tstring::value_type));
                xASSERT(NULL != m_pvRes);

                for (size_t x = 0; x < asBuff[i].size() * sizeof(std::tstring::value_type); ++ x) {
                    xASSERT(0 == asBuff[i].at(x));
                }
            }
        }

        //2
        {
            const size_t cauiSizes[] = {1, 0, 10, 100000000};

            for (size_t i = 0; i < xARRAY_SIZE(cauiSizes); ++ i) {
                m_pvRes = CxString::pvMemoryZeroSecure(NULL, cauiSizes[i]);
                xASSERT(NULL == m_pvRes);
            }
        }
    }


    /****************************************************************************
    *    ������
    *
    *****************************************************************************/

    //-------------------------------------
    //sCreateGuid
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            m_sRes = CxString::sCreateGuid();
            xTEST_EQ(false, m_sRes.empty());
        #elif defined(xOS_ENV_UNIX)
            ////xTEST_EQ(true, m_sRes.empty());
        #endif
    }

    //-------------------------------------
    //bIsRepeated
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxString::bIsRepeated(xT("yyyyyyyyyyyy"));
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxString::bIsRepeated(xT("111111111111"));
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxString::bIsRepeated(xT("uuuuuiuuuuuuuuuuuu"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxString::bIsRepeated(xT("000000000111111111"));
        xTEST_EQ(FALSE, m_bRes);
    }


    /****************************************************************************
    *   formating
    *
    *****************************************************************************/

    //-------------------------------------
    //sConvertCodePage
    xTEST_BLOCK(cullBlockLoops)
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
            #if defined(xOS_ENV_WIN)
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
            #elif defined(xOS_ENV_UNIX)
                //TODO: sConvertCodePage
                //xNOT_IMPLEMENTED_RET(RET_VALUE);
            #endif
        }
    }

    //-------------------------------------
    //sCharToOemBuff
    xTEST_BLOCK(cullBlockLoops)
    {
        std::string sRes;

        #if defined(xOS_ENV_WIN)
            sRes = CxString::asCharToOemBuff(xT("Boss, hello? "));
            xTEST_EQ(std::string("Boss, hello? "), sRes);
        #elif defined(xOS_ENV_UNIX)
            //TODO: sCharToOemBuff
        #endif
    }

    //-------------------------------------
    //sOemToCharBuff
    xTEST_BLOCK(cullBlockLoops)
    {
        std::tstring sRes;

        #if defined(xOS_ENV_WIN)
            sRes = CxString::sOemToCharBuff(("1111, hdbhjgjk hkl, jl.,kh."));
            xTEST_EQ(std::tstring(xT("1111, hdbhjgjk hkl, jl.,kh.")), sRes);
        #elif defined(xOS_ENV_UNIX)
            //TODO: sOemToCharBuff
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
