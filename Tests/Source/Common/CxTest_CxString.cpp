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
//DONE: CxTest_CxString
CxTest_CxString::CxTest_CxString() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxString
CxTest_CxString::~CxTest_CxString() {

}
//---------------------------------------------------------------------------

UCHAR RandomNumber () { return (UCHAR)(rand()%100); }


//DONE: bUnit ()
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
    //operator << for uString
    xTEST_BLOCK(cullBlockLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            uString usStr;

            usStr.resize( (size_t)CxRandom::liGetInt(1, 64) );
            std::fill_n(usStr.begin(), usStr.size(), static_cast<uString::value_type>( CxRandom::liGetInt(1, 255) ));

            tString sVal1 = tString(usStr.begin(), usStr.end());

            tostringstream osOut;   osOut << usStr;
            tString sVal2 = osOut.str();

            xASSERT_EQ(sVal1, sVal2);
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

        tostringstream osOut;   osOut << m_vsRes;
        //xTRACEV(xT("\toperator << for std::vector: %s"), osOut.str().c_str());
        xASSERT_EQ(false, osOut.str().empty());

        m_vsRes.clear();
    }

    //--------------------------------------------------
    //operator << for std::map
    xTEST_BLOCK(cullBlockLoops)
    {
        m_msRes.clear();

        m_msRes.insert( std::pair<tString, tString>(xT("Key0"), xT("Value0")) );
        m_msRes.insert( std::pair<tString, tString>(xT("Key1"), xT("Value1")) );
        m_msRes.insert( std::pair<tString, tString>(xT("Key2"), xT("Value2")) );
        m_msRes.insert( std::pair<tString, tString>(xT("Key3"), xT("Value3")) );
        m_msRes.insert( std::pair<tString, tString>(xT("Key4"), xT("Value4")) );

        tostringstream osOut;   osOut << m_msRes;
        //xTRACEV(xT("\toperator << for std::map: %s"), osOut.str().c_str());
        xASSERT_EQ(false, osOut.str().empty());

        m_msRes.clear();
    }

    //--------------------------------------------------
    //operator << for std::multimap
    xTEST_BLOCK(cullBlockLoops)
    {
        m_mmsRes.clear();

        m_mmsRes.insert( std::pair<tString, tString>(xT("Key0"), xT("Value0")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key1"), xT("Value1")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key2"), xT("Value2")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key0"), xT("Value0")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key1"), xT("Value1")) );

        tostringstream osOut;   osOut << m_mmsRes;
        //xTRACEV(xT("\toperator << for std::multimap: %s"), osOut.str().c_str());
        xASSERT_EQ(false, osOut.str().empty());

        m_mmsRes.clear();
    }

    //-------------------------------------
    //lexical_cast (to string)
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::lexical_cast(1);
        xASSERT_EQ(tString(xT("1")), m_sRes);

        m_sRes = CxString::lexical_cast(xT('A'));
        xASSERT_EQ(tString(xT("A")), m_sRes);

        m_sRes = CxString::lexical_cast(xT("-"));
        xASSERT_EQ(tString(xT("-")), m_sRes);

        m_sRes = CxString::lexical_cast(0.0);
        xASSERT_EQ(tString(xT("0")), m_sRes);

        m_sRes = CxString::lexical_cast(- 5);
        xASSERT_EQ(tString(xT("-5")), m_sRes);

        m_sRes = CxString::lexical_cast(true);
        xASSERT_EQ(tString(xT("1")), m_sRes);

        m_sRes = CxString::lexical_cast(false);
        xASSERT_EQ(tString(xT("0")), m_sRes);
    }

    //-------------------------------------
    //lexical_cast (from string)
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::lexical_cast<tString>(xT("String"));
        xASSERT_EQ(tString(xT("String")), m_sRes);

        m_iRes = CxString::lexical_cast<INT>(xT("7"));
        xASSERT_EQ(7, m_iRes);

        m_ulRes = CxString::lexical_cast<ULONG>(xT("123"));
        xASSERT_EQ(123UL, m_ulRes);

        m_ullRes = CxString::lexical_cast<ULONGLONG>(xT("123"));
        xASSERT_EQ(123ULL, m_ullRes);

        m_dRes = CxString::lexical_cast<double>(xT("5.3"));
        xASSERT_EQ(5.3, m_dRes);

        ////m_bRes = lexical_cast<bool>(xT("true"));
        ////xASSERT_EQ(5.3, m_dRes);

        ////m_bRes = lexical_cast<bool>(xT("false"));
        ////xASSERT_EQ(5.3, m_dRes);

        ////m_uiRes = CxString::lexical_cast<size_t>( tString() );
        ////xASSERT_EQ(0U, m_uiRes);
    }

    //-------------------------------------
    //lexical_cast (to string by base)
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::lexical_cast(1033, 8);
        xASSERT_EQ(tString(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033, 10);
        xASSERT_EQ(tString(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033, 16);
        xASSERT_EQ(tString(xT("409")), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_sRes = CxString::sIntToStr(1033L, 2);
        ////xASSERT_EQ(tString(xT("10000001001")), m_sRes);

        m_sRes = CxString::lexical_cast(1033L, 8);
        xASSERT_EQ(tString(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033L, 10);
        xASSERT_EQ(tString(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033L, 16);
        xASSERT_EQ(tString(xT("409")), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_sRes = CxString::sIntToStr(1033UL, 2);
        ////xASSERT_EQ(tString(xT("10000001001")), m_sRes);

        m_sRes = CxString::lexical_cast(1033UL, 8);
        xASSERT_EQ(tString(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033UL, 10);
        xASSERT_EQ(tString(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033UL, 16);
        xASSERT_EQ(tString(xT("409")), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_sRes = CxString::sIntToStr(1033LL, 2);
        ////xASSERT_EQ(xT("10000001001") == m_sRes);

        m_sRes = CxString::lexical_cast(1033LL, 8);
        xASSERT_EQ(tString(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033LL, 10);
        xASSERT_EQ(tString(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033LL, 16);
        xASSERT_EQ(tString(xT("409")), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_sRes = CxString::sIntToStr(1033ULL, 2);
        ////xASSERT_EQ(tString(xT("10000001001")), m_sRes);

        m_sRes = CxString::lexical_cast(1033ULL, 8);
        xASSERT_EQ(tString(xT("2011")), m_sRes);

        m_sRes = CxString::lexical_cast(1033ULL, 10);
        xASSERT_EQ(tString(xT("1033")), m_sRes);

        m_sRes = CxString::lexical_cast(1033ULL, 16);
        xASSERT_EQ(tString(xT("409")), m_sRes);
    }

    //-------------------------------------
    //lexical_cast (from, to string by base)
    xTEST_BLOCK(cullBlockLoops)
    {
        const INT caiBases[] = {8, 10, 16};

        const tString casData[] = {
                xT("01234567890ABC"),
                xT("01234567890"),
                xT("ABCDEF"),
                xT("ABCDEF01234567890ABC"),
                xT("01234AA567890ABC")
        };

        for (size_t b = 0; b < xARRAY_SIZE(caiBases); ++ b) {
            for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
                const tString sRes    = casData[i];

                const tString sHexStr = CxString::lexical_cast(sRes, caiBases[b]);
                const tString sStdStr = CxString::lexical_cast<tString>(sHexStr, caiBases[b]);

                xASSERT_EQ(sRes, sStdStr);
            }
        }
    }

    //-------------------------------------
    //bBoolToStr
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::sBoolToStr(TRUE);
        xASSERT_EQ(tString(xT("TRUE")), m_sRes);

        m_sRes = CxString::sBoolToStr(FALSE);
        xASSERT_EQ(tString(xT("FALSE")), m_sRes);
    }

    //-------------------------------------
    //bStrToBool
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxString::bStrToBool(xT("true"));
        xASSERT_EQ(TRUE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("trUe"));
        xASSERT_EQ(TRUE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("TRUE"));
        xASSERT_EQ(TRUE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("false"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("FAlse"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("FALSE"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bStrToBool(xT(" TRUE "));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bStrToBool(xT("qwertyuiop[]"));
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //sTrimLeftChars
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sTestData[][2] = {
            {xT("TEST_STRIN#G_1"),       xT("TEST_STRIN#G_1")},
            {xT("TEST_STRING_2#"),       xT("TEST_STRING_2#")},
            {xT("TEST_STRING_3"),        xT("#TEST_STRING_3")},
            {xT("TEST_#STRING_4"),       xT("##TEST_#STRING_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sTrimLeftChars(sTestData[i][0], xT("#"));
            tString sStr2 = CxString::sTrimLeftChars(sTestData[i][1], xT("#"));
            xASSERT_EQ(sStr1, sStr2);

            tString sStr3 = sTestData[i][0];
            tString sStr4 = CxString::sTrimLeftChars(sTestData[i][1], xT("#"));
            xASSERT_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sTrimRightChars
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sTestData[][2] = {
            {xT("#TEST_STRING_1"),       xT("#TEST_STRING_1")},
            {xT("TE#ST_STRING_2"),       xT("TE#ST_STRING_2")},
            {xT("TEST_STRING_3"),        xT("TEST_STRING_3##")},
            {xT("TEST_STRING#_4"),       xT("TEST_STRING#_4#")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sTrimRightChars(sTestData[i][0], xT("#"));
            tString sStr2 = CxString::sTrimRightChars(sTestData[i][1], xT("#"));
            xASSERT_EQ(sStr1, sStr2);

            tString sStr3 = sTestData[i][0];
            tString sStr4 = CxString::sTrimRightChars(sTestData[i][1], xT("#"));

            xASSERT_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sTrimChars
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sTestData[][2] = {
            {xT("TEST_STRING_1"),        xT("+-#####TEST_STRING_1+-")},
            {xT("TEST_STRING_2"),        xT("TEST_STRING_2#####+-+-+-")},
            {xT("TEST_STRING_3"),        xT("+-+-###TEST_STRING_3####+-+-+-")},
            {xT("TEST_#STRING_4"),       xT("#+-##+-TEST_#STRING_4#+-#+-##")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sTrimChars(sTestData[i][0], xT("#+-"));
            tString sStr2 = CxString::sTrimChars(sTestData[i][1], xT("#+-"));
            xASSERT_EQ(sStr1, sStr2);

            tString sStr4 = sTestData[i][0];
            tString sStr3 = CxString::sTrimChars(sTestData[i][1], xT("#+-"));
            xASSERT_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sTrimSpace
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sTestData[][2] = {
            {xT("TEST_STRING_1"),  xT("           TEST_STRING_1")},
            {xT("TEST_STRING_2"),  xT("TEST_STRING_2       ")},
            {xT("TEST_STRING_3"),  xT("        TEST_STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("        TEST_ STRING_3    ")},
            {xT("TEST_ STRING_3"), xT("     TEST_ STRING_3    ")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sTrimSpace(sTestData[i][0]);
            tString sStr2 = CxString::sTrimSpace(sTestData[i][1]);
            xASSERT_EQ(sStr1, sStr2);

            tString sStr3 = CxString::sTrimSpace(sTestData[i][1]);
            tString sStr4 = sTestData[i][0];
            xASSERT_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sRemoveEol
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_WIN)
            const tString sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\r")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #elif defined(xOS_LINUX)
            const tString sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n\n")},
                {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sRemoveEol(sTestData[i][0]);
            tString sStr2 = CxString::sRemoveEol(sTestData[i][1]);
            xASSERT_EQ(sStr1, sStr2);

            tString sStr3 = CxString::sRemoveEol(sTestData[i][1]);
            tString sStr4 = sTestData[i][0];
            xASSERT_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sReplaceAll
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::sReplaceAll(xT("aTaaaEaST_aSTaRINaaGaa_1a"), xT("a"), xT(""));
        xASSERT_EQ(tString(xT("TEST_STRING_1")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("TEST_STRING_1"), xT("T"), xT("a"));
        xASSERT_EQ(tString(xT("aESa_SaRING_1")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("/"), xT("_"));
        xASSERT_EQ(tString(xT("D:_XVCL_Include\\XVCL_Units_Gui_vSpeedButton_LoadDrives.cpp")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("\\"), xT("_"));
        xASSERT_EQ(tString(xT("D:/XVCL/Include_XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT(""));
        xASSERT_EQ(tString(xT("_one__three_")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT("fife"));
        xASSERT_EQ(tString(xT("_one_fife_three_")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT("^"));
        xASSERT_EQ(tString(xT("_one_^_three_")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("aaaaffaaaa"), xT("ff"), xT("ffff"));
        xASSERT_EQ(tString(xT("aaaaffffaaaa")), m_sRes);

        m_sRes = CxString::sReplaceAll(xT("aaaaffaaaa"), xT("ff"), xT("f"));
        xASSERT_EQ(tString(xT("aaaafaaaa")), m_sRes);
    }

    //-------------------------------------
    //sReplaceAll
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::sReplaceAll(xT(" one test string "), xT(" "), xT("_"));
        xASSERT_EQ(m_sRes, tString(xT("_one_test_string_")));

        m_sRes = CxString::sReplaceAll(xT(" one test string "), xT(" "), xT(""));
        xASSERT_EQ(m_sRes, tString(xT("oneteststring")));

        m_sRes = CxString::sReplaceAll(xT(" one test string "), xT(' '), xT('-'));
        xASSERT_EQ(m_sRes, tString(xT("-one-test-string-")));
    }

    //-------------------------------------
    //sRemoveAll
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT(" "));
        xASSERT_EQ(tString(xT("oneteststring")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT(" "));
        xASSERT_EQ(tString(xT("oneteststring")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT("one test strin g"),  xT(" "));
        xASSERT_EQ(tString(xT("oneteststring")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT("string"));
        xASSERT_EQ(tString(xT(" one test  ")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT("string"));
        xASSERT_EQ(tString(xT(" one test  ")), m_sRes);

        m_sRes = CxString::sRemoveAll(xT("one test stringg"),  xT("string"));
        xASSERT_EQ(tString(xT("one test g")), m_sRes);
    }

    //-------------------------------------
    //bSplit
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<tString> vecsText;

        m_bRes = CxString::bSplit(xT("1+++22+++333+++4444+++55555+++666666"), xT("+"), &vecsText);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bSplit(xT("Key+"), xT("+"), &vecsText);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        vecsText.clear();
        m_bRes = CxString::bSplit(xT(""), xT("+"), &vecsText);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //sJoin
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<tString> vecsRes;
        vecsRes.push_back(xT("111"));
        vecsRes.push_back(xT(""));
        vecsRes.push_back(xT("222"));
        vecsRes.push_back(xT("333"));

        m_sRes = CxString::sJoin(vecsRes, xT("-"));
        xASSERT_EQ(tString(xT("111--222-333")), m_sRes);
    }

    //-------------------------------------
    //sJoin
    xTEST_BLOCK(cullBlockLoops)
    {
        std::vector<tString> vecsRes;
        vecsRes.push_back(xT("111"));
        vecsRes.push_back(xT(""));
        vecsRes.push_back(xT("222"));
        vecsRes.push_back(xT("333"));

        m_sRes = CxString::sJoin(vecsRes, xT('-'));
        xASSERT_EQ(tString(xT("111--222-333")), m_sRes);
    }

    //-------------------------------------
    //sCut
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sForCut;

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <_Alca@meta.ua_>");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT_EQ(tString(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("<_Alca@meta.ua_>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT_EQ(tString(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT_EQ(tString(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125<_Alc<a>@meta>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT_EQ(tString(xT("_Alc<a>@meta>.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT_EQ(tString(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT_EQ(tString(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125>_Alca@meta.ua_<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT_EQ(tString(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125_Alca<>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT_EQ(tString(xT("")), m_sRes);

        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <<_Alca@meta.ua_>>");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT_EQ(tString(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("<<_Alca@meta.ua_>>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT_EQ(tString(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT_EQ(tString(xT("_Alca@meta.ua_")), m_sRes);

        sForCut = xT("To: =?windows-125<<_Alc<<a>>@meta>>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT_EQ(tString(xT("_Alc<<a>>@meta")), m_sRes);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT_EQ(tString(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT_EQ(tString(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125>>_Alca@meta.ua_<<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT_EQ(tString(xT("")), m_sRes);

        sForCut = xT("To: =?windows-125_Alca<<>>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT_EQ(tString(xT("")), m_sRes);
    }

    //-------------------------------------
    //sCut
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sForCut = xT("0123456789");


        m_sRes = CxString::sCut(sForCut, 0, 1);
        xASSERT_EQ(tString(xT("0")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 0, 9);
        xASSERT_EQ(tString(xT("012345678")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 4, 5);
        xASSERT_EQ(tString(xT("4")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 4, 6);
        xASSERT_EQ(tString(xT("45")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 6, 6);
        xASSERT_EQ(tString(xT("")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 6, 4);
        xASSERT_EQ(tString(xT("")), m_sRes);

        m_sRes = CxString::sCut(xT(""), 1, 2);
        xASSERT_EQ(tString(xT("")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 0);
        xASSERT_EQ(tString(xT("0123456789")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 4);
        xASSERT_EQ(tString(xT("456789")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 9);
        xASSERT_EQ(tString(xT("9")), m_sRes);

        m_sRes = CxString::sCut(sForCut, 10);
        xASSERT_EQ(tString(xT("")), m_sRes);

        m_sRes = CxString::sCut(xT(""), 1);
        xASSERT_EQ(tString(xT("")), m_sRes);

        m_sRes = CxString::sCut(sForCut);
        xASSERT_EQ(tString(xT("0123456789")), m_sRes);
    }

    //-------------------------------------
    //sToLowerCase
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString sTestData[][2] = {
            {xT("test_string_1"),       xT("TEST_string_1")},
            {xT("test_string_1"),       xT("TEst_stRING_1")},
            {xT("test_string_1\n"),     xT("TEST_STRing_1\n")},
            {xT("test_string_1\n\r"),   xT("TEST_STring_1\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sToLowerCase(sTestData[i][0]);
            tString sStr2 = CxString::sToLowerCase(sTestData[i][1]);
            xASSERT_EQ(sStr1, sStr2);

            tString sStr3 = CxString::sToLowerCase(sTestData[i][1]);
            tString sStr4 = sTestData[i][0];
            xASSERT_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToUpperCase
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString sTestData[][2] = {
            {xT("TEST_STRING_1_A"),       xT("TEST_string_1_a")},
            {xT("TEST_STRING_1_A"),       xT("TEst_stRING_1_A")},
            {xT("TEST_STRING_1_A\n"),     xT("TEST_STRing_1_a\n")},
            {xT("TEST_STRING_1_A\n\r"),   xT("TEST_STring_1_A\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sToUpperCase(sTestData[i][0]);
            tString sStr2 = CxString::sToUpperCase(sTestData[i][1]);
            xASSERT_EQ(sStr1, sStr2);

            tString sStr3 = CxString::sToUpperCase(sTestData[i][1]);
            tString sStr4 = sTestData[i][0];
            xASSERT_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToLowerCase
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString sTestData[][2] = {
            {xT("test_string_1_a"), xT("test_string_1_A")},
            {xT("test_string_1_a"), xT("Test_strINg_1_a")},
            {xT("test_string_1_a"), xT("test_STRING_1_A")},
            {xT("test_string_1_a"), xT("Test_string_1_a")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sToLowerCase(sTestData[i][0], sTestData[i][0].size());
            tString sStr2 = CxString::sToLowerCase(sTestData[i][1], sTestData[i][1].size());
            xASSERT_EQ(sStr1, sStr2);

            tString sStr3 = CxString::sToLowerCase(sTestData[i][1], sTestData[i][1].size() + 1000);
            tString sStr4 = sTestData[i][0];
            xASSERT_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToUpperCase
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString sTestData[][2] = {
            {xT("TEST_STRING_1_A"), xT("tEST_string_1_A")},
            {xT("TEST_STRING_1_A"), xT("tEst_stRING_1_a")},
            {xT("TEST_STRING_1_A"), xT("TEST_STRing_1_a")},
            {xT("TEST_STRING_1_A"), xT("tEST_STring_1_A")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sToUpperCase(sTestData[i][0], sTestData[i][0].size());
            tString sStr2 = CxString::sToUpperCase(sTestData[i][1], sTestData[i][1].size());
            xASSERT_EQ(sStr1, sStr2);

            tString sStr3 = CxString::sToUpperCase(sTestData[i][1], sTestData[i][1].size() - 1000);
            tString sStr4 = sTestData[i][0];
            xASSERT_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sFormat
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sData;

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%i]"), 1000);
        xASSERT_EQ(m_sRes, tString(xT("qqqq-wwww [1000]")));

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%f]"), 1000.0);
        #if defined(xOS_WIN)
            xASSERT_EQ(m_sRes, tString(xT("qqqq-wwww [1000,000000]")));
        #elif defined(xOS_LINUX)
            xASSERT_EQ(m_sRes, tString(xT("qqqq-wwww [1000.000000]")));
        #endif

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%s]"), xT("1000"));
        xASSERT_EQ(m_sRes, tString(xT("qqqq-wwww [1000]")));

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%i]"), -1000);
        xASSERT_EQ(m_sRes, tString(xT("qqqq-wwww [-1000]")));

        m_sRes = CxString::sFormat(xT("Characters: %c %c"), xT('a'), 65);
        xASSERT_EQ(m_sRes, tString(xT("Characters: a A")));

        m_sRes = CxString::sFormat(xT("Decimals: %d %ld"), 1977, 650000L);
        xASSERT_EQ(m_sRes, tString(xT("Decimals: 1977 650000")));

        m_sRes = CxString::sFormat(xT("Preceding with blanks: %10d"), 1977);
        xASSERT_EQ(m_sRes, tString(xT("Preceding with blanks:       1977")));

        m_sRes = CxString::sFormat(xT("Preceding with zeros: %010d"), 1977);
        xASSERT_EQ(m_sRes, tString(xT("Preceding with zeros: 0000001977")));

        m_sRes = CxString::sFormat(xT("Some different radixes: %d %x %o %#x %#o"), 100, 100, 100, 100, 100);
        xASSERT_EQ(m_sRes, tString(xT("Some different radixes: 100 64 144 0x64 0144")));

        m_sRes = CxString::sFormat(xT("floats: %4.2f %+.0e %E"), 3.1416, 3.1416, 3.1416);
        xASSERT_EQ(false, m_sRes.empty());

        m_sRes = CxString::sFormat(xT("Width trick: %*d"), 5, 10);
        xASSERT_EQ(m_sRes, tString(xT("Width trick:    10")));

        sData = xT("0A string2344565600");
        m_sRes = CxString::sFormat(xT("%s"), sData.c_str());
        xASSERT_EQ(m_sRes, sData);

        sData = xT("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
        m_sRes = CxString::sFormat(xT("%s"), sData.c_str());
        xASSERT_EQ(sData, m_sRes);

        //various string size
        {
            for (size_t i = 1; i < 1024 * 2; ++ i) {
                tString sData(i, xT('s'));

                tString m_sRes = CxString::sFormat(xT("%s"), sData.c_str());
                //xSTD_COUT("sData (" << sData.size() << ") = " << sData << "\nm_sRes (" << m_sRes.size() << ") = " << m_sRes);

                xASSERT_EQ(m_sRes.size(), sData.size());
                xASSERT_EQ(m_sRes,        sData);
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
        xASSERT_EQ(tString(xT("55...")), m_sRes);

        m_sRes = CxString::sMinimize(xT("55555wwwww00000"), 20);
        xASSERT_EQ(tString(xT("55555wwwww00000")), m_sRes);
    }

    //-------------------------------------
    //bCompareNoCase
    xTEST_BLOCK(cullBlockLoops)
    {
        //must TRUE
        m_bRes = CxString::bCompareNoCase(xT(""),     xT(""));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("xxx"),  xT("XXX"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("111"),  xT("111"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("eee"),  xT("EeE"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("WWW"),  xT("wwW"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        //maust FALSE
        m_bRes = CxString::bCompareNoCase(xT("ccc"),  xT("CCCz"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("!!!!!"),  xT("@@@@@@"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("$$$$$"), xT("sdfgsdg"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("&&&&&"),  xT("&&&&&????"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("_+#$^%^&*^&*("), xT("@#$%TY(J^HGYT"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("dddd"), xT("d"));
        xASSERT_EQ(FALSE, m_bRes);
    }


    /****************************************************************************
    *   �������������
    *
    *****************************************************************************/

    //-------------------------------------
    //sDecodeWinKoi
    xTEST_BLOCK(cullBlockLoops) {
        //m_sRes = sDecodeWinKoi(INT iFrom, INT iTo, const tString &sOldStr);
    }

    //-------------------------------------
    //sTranslitLatToRus
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            m_sRes = CxString::sTranslitLatToRus(xT(""));
            xASSERT_EQ(tString(), m_sRes);

            m_sRes = CxString::sTranslitLatToRus(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll"));
            xASSERT_EQ(tString(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll")), m_sRes);
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
        //m_sRes = CxString::sStrToRtf(tString sStr);
    }

    //-------------------------------------
    //sRtfToStr
    xTEST_BLOCK(cullBlockLoops) {
        //m_sRes = CxString::sRtfToStr(tString sStr);
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
            tString sRes = sColorStr(xT("Linux Console Color"), (EForeground)i, FALSE, FALSE, bgBlack, FALSE);
            std::cout<< xT("Color: ") << i << xT(" ") << sRes << std::endl;
        }

        tString sRes = CxString::sFormatNixTerminal(xT("Linux Console Color"), CxString::fgYellow_, TRUE, FALSE, CxString::bgBlue_, FALSE);
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
            tString asBuff[] = {
                    xT("0123456789"),
                    xT("aaaaaaaaaaaaaaaaaa"),
                    xT("wo34875j0w9958u0342ku59u28934u5"),
            };

            for (size_t i = 0; i < xARRAY_SIZE(asBuff); ++ i) {
                m_pvRes = CxString::pvMemoryZeroSecure(&asBuff[i].at(0), asBuff[i].size() * sizeof(tString::value_type));
                xASSERT(NULL != m_pvRes);

                for (size_t x = 0; x < asBuff[i].size() * sizeof(tString::value_type); ++ x) {
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
        #if defined(xOS_WIN)
            m_sRes = CxString::sCreateGuid();
            xASSERT_EQ(false, m_sRes.empty());
        #elif defined(xOS_LINUX)
            ////xASSERT_EQ(true, m_sRes.empty());
        #endif
    }

    //-------------------------------------
    //bIsRepeated
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxString::bIsRepeated(xT("yyyyyyyyyyyy"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bIsRepeated(xT("111111111111"));
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bIsRepeated(xT("uuuuuiuuuuuuuuuuuu"));
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = CxString::bIsRepeated(xT("000000000111111111"));
        xASSERT_EQ(FALSE, m_bRes);
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
            #if defined(xOS_WIN)
                //CP_ACP(ANSI) <-> CP_UTF8(UTF-8)
                std::string sAnsi;
                std::string sUtf8;

                sUtf8 = CxString::sConvertCodePage(csAnsiStr[i], CP_ACP,  CP_UTF8);
                sAnsi = CxString::sConvertCodePage(sUtf8,        CP_UTF8, CP_ACP);
                xASSERT_EQ(csAnsiStr[i], sAnsi);


                //1251(WIN)  <-> 20866(KOI-8r)
                std::string sKoiStr;
                std::string sWinStr;

                sKoiStr = CxString::sConvertCodePage(csAnsiStr[i], 1251,  20866);
                sWinStr = CxString::sConvertCodePage(sKoiStr,      20866, 1251);
                xASSERT_EQ(csAnsiStr[i], sWinStr);
            #elif defined(xOS_LINUX)
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

        #if defined(xOS_WIN)
            sRes = CxString::asCharToOemBuff(xT("Boss, hello? "));
            xASSERT_EQ(std::string("Boss, hello? "), sRes);
        #elif defined(xOS_LINUX)
            //TODO: sCharToOemBuff
        #endif
    }

    //-------------------------------------
    //sOemToCharBuff
    xTEST_BLOCK(cullBlockLoops)
    {
        tString sRes;

        #if defined(xOS_WIN)
            sRes = CxString::sOemToCharBuff(("1111, hdbhjgjk hkl, jl.,kh."));
            xASSERT_EQ(tString(xT("1111, hdbhjgjk hkl, jl.,kh.")), sRes);
        #elif defined(xOS_LINUX)
            //TODO: sOemToCharBuff
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
