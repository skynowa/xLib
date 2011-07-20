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
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxString::bUnit() {
    /****************************************************************************
    *    convertation
    *
    *****************************************************************************/

    //-------------------------------------
    //lexical_cast (to string)
    {
        m_sRes = CxString::lexical_cast(1);
        xASSERT(xT("1") == m_sRes);

        m_sRes = CxString::lexical_cast(xT('A'));
        xASSERT(xT("A") == m_sRes);

        m_sRes = CxString::lexical_cast(xT("-"));
        xASSERT(xT("-") == m_sRes);

        m_sRes = CxString::lexical_cast(0.0);
        xASSERT(xT("0") == m_sRes);

        m_sRes = CxString::lexical_cast(- 5);
        xASSERT(xT("-5") == m_sRes);

        m_sRes = CxString::lexical_cast(true);
        xASSERT(xT("1") == m_sRes);

        m_sRes = CxString::lexical_cast(false);
        xASSERT(xT("0") == m_sRes);
    }

    //-------------------------------------
    //lexical_cast (from string)
    {
        m_sRes = CxString::lexical_cast<tString>(xT("String"));
        xASSERT(xT("String") == m_sRes);

        m_iRes = CxString::lexical_cast<INT>(xT("7"));
        xASSERT(7 == m_iRes);

        m_ulRes = CxString::lexical_cast<ULONG>(xT("123"));
        xASSERT(123 == m_ulRes);

        m_ullRes = CxString::lexical_cast<ULONGLONG>(xT("123"));
        xASSERT(123UL == m_ullRes);

        m_dRes = CxString::lexical_cast<double>(xT("5.3"));
        xASSERT(5.3 == m_dRes);

        ////m_bRes = lexical_cast<bool>(xT("true"));
        ////xASSERT(5.3 == m_dRes);

        ////m_bRes = lexical_cast<bool>(xT("false"));
        ////xASSERT(5.3 == m_dRes);

        ////m_uiRes = CxString::lexical_cast<size_t>( tString() );
        ////xASSERT_MSG(0U == m_uiRes, CxString::lexical_cast<size_t>( m_uiRes ));
    }

    //-------------------------------------
    //lexical_cast (to string by base)
    {
        ////m_sRes = CxString::sIntToStr(1033, 2);
        ////xASSERT(xT("10000001001") == m_sRes);

        m_sRes = CxString::lexical_cast(1033, 8);
        xASSERT(xT("2011") == m_sRes);

        m_sRes = CxString::lexical_cast(1033, 10);
        xASSERT(xT("1033") == m_sRes);

        m_sRes = CxString::lexical_cast(1033, 16);
        xASSERT(xT("409") == m_sRes);
    }
    {
        ////m_sRes = CxString::sIntToStr(1033L, 2);
        ////xASSERT(xT("10000001001") == m_sRes);

        m_sRes = CxString::lexical_cast(1033L, 8);
        xASSERT(xT("2011") == m_sRes);

        m_sRes = CxString::lexical_cast(1033L, 10);
        xASSERT(xT("1033") == m_sRes);

        m_sRes = CxString::lexical_cast(1033L, 16);
        xASSERT(xT("409") == m_sRes);
    }
    {
        ////m_sRes = CxString::sIntToStr(1033UL, 2);
        ////xASSERT(xT("10000001001") == m_sRes);

        m_sRes = CxString::lexical_cast(1033UL, 8);
        xASSERT(xT("2011") == m_sRes);

        m_sRes = CxString::lexical_cast(1033UL, 10);
        xASSERT(xT("1033") == m_sRes);

        m_sRes = CxString::lexical_cast(1033UL, 16);
        xASSERT(xT("409") == m_sRes);
    }
    {
        ////m_sRes = CxString::sIntToStr(1033LL, 2);
        ////xASSERT(xT("10000001001") == m_sRes);

        m_sRes = CxString::lexical_cast(1033LL, 8);
        xASSERT(xT("2011") == m_sRes);

        m_sRes = CxString::lexical_cast(1033LL, 10);
        xASSERT(xT("1033") == m_sRes);

        m_sRes = CxString::lexical_cast(1033LL, 16);
        xASSERT(xT("409") == m_sRes);
    }
    {
        ////m_sRes = CxString::sIntToStr(1033ULL, 2);
        ////xASSERT(xT("10000001001") == m_sRes);

        m_sRes = CxString::lexical_cast(1033ULL, 8);
        xASSERT(xT("2011") == m_sRes);

        m_sRes = CxString::lexical_cast(1033ULL, 10);
        xASSERT(xT("1033") == m_sRes);

        m_sRes = CxString::lexical_cast(1033ULL, 16);
        xASSERT(xT("409") == m_sRes);
    }

    //-------------------------------------
    //lexical_cast (from, to string by base)
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

                xASSERT(sRes == sStdStr);
            }
        }
    }

    //-------------------------------------
    //bBoolToStr
    {
        m_sRes = CxString::sBoolToStr(TRUE);
        xASSERT(xT("TRUE") == m_sRes);

        m_sRes = CxString::sBoolToStr(FALSE);
        xASSERT(xT("FALSE") == m_sRes);
    }

    //-------------------------------------
    //bStrToBool
    {
        m_bRes = CxString::bStrToBool(xT("true"));
        xASSERT(TRUE  == m_bRes);

        m_bRes = CxString::bStrToBool(xT("trUe"));
        xASSERT(TRUE  == m_bRes);

        m_bRes = CxString::bStrToBool(xT("TRUE"));
        xASSERT(TRUE  == m_bRes);

        m_bRes = CxString::bStrToBool(xT("false"));
        xASSERT(FALSE  == m_bRes);

        m_bRes = CxString::bStrToBool(xT("FAlse"));
        xASSERT(FALSE  == m_bRes);

        m_bRes = CxString::bStrToBool(xT("FALSE"));
        xASSERT(FALSE  == m_bRes);

        m_bRes = CxString::bStrToBool(xT(" TRUE "));
        xASSERT(FALSE  == m_bRes);

        m_bRes = CxString::bStrToBool(xT("qwertyuiop[]"));
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //sTrimLeftChars
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
            xASSERT(sStr1 == sStr2);

            tString sStr3 = sTestData[i][0];
            tString sStr4 = CxString::sTrimLeftChars(sTestData[i][1], xT("#"));
            xASSERT(sStr3 == sStr4);
        }
    }

    //-------------------------------------
    //sTrimRightChars
    {
        tString sTestData[][2] = {
            ////{xT("#TEST_STRING_1"),       xT("#TEST_STRING_1")},
            ////{xT("TE#ST_STRING_2"),       xT("TE#ST_STRING_2")},
            {xT("TEST_STRING_3"),        xT("TEST_STRING_3##")},
            {xT("TEST_STRING#_4"),       xT("TEST_STRING#_4#")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sTrimRightChars(sTestData[i][0], xT("#"));
            tString sStr2 = CxString::sTrimRightChars(sTestData[i][1], xT("#"));
            xASSERT(sStr1 == sStr2);

            tString sStr3 = sTestData[i][0];
            tString sStr4 = CxString::sTrimRightChars(sTestData[i][1], xT("#"));

            xASSERT(sStr3 == sStr4);
        }
    }

    //-------------------------------------
    //sTrimChars
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
            xASSERT(sStr1 == sStr2);

            tString sStr4 = sTestData[i][0];
            tString sStr3 = CxString::sTrimChars(sTestData[i][1], xT("#+-"));
            xASSERT(sStr3 == sStr4);
        }
    }

    //-------------------------------------
    //sTrimSpace
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
            xASSERT(sStr1 == sStr2);

            tString sStr3 = CxString::sTrimSpace(sTestData[i][1]);
            tString sStr4 = sTestData[i][0];
            xASSERT(sStr3 == sStr4);
        }
    }

    //-------------------------------------
    //sRemoveEol
    {
        #if defined(xOS_WIN)
        const tString sTestData[][2] = {
            {xT("TEST_STRING_1"), xT("TEST_STRING_1\r\n")},
            {xT("TEST_STRING_1"), xT("TEST_STRING_1\r")},
            //{xT("TEST_STRING_1"), xT("TEST_STRING_1\n")},
            //{xT("TEST_STRING_1"), xT("TEST_STRING_1\n\r")},
        };
        #elif defined(xOS_LINUX)
        const tString sTestData[][2] = {
            {xT("TEST_STRING_1"), xT("TEST_STRING_1\n")},
            {xT("TEST_STRING_1"), xT("TEST_STRING_1\n\n")},
            //{xT("TEST_STRING_1"), xT("TEST_STRING_1\n")},
            //{xT("TEST_STRING_1"), xT("TEST_STRING_1\n\r")},
        };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sRemoveEol(sTestData[i][0]);
            tString sStr2 = CxString::sRemoveEol(sTestData[i][1]);
            xASSERT(sStr1 == sStr2);

            tString sStr3 = CxString::sRemoveEol(sTestData[i][1]);
            tString sStr4 = sTestData[i][0];
            xASSERT(sStr3 == sStr4);
        }
    }

    //-------------------------------------
    //sReplaceAll
    //m_sRes = sReplaceAll(const tString &csStr, const tString &csOldStr, const tString &csNewStr);
    {
        m_sRes = CxString::sReplaceAll(xT("aTaaaEaST_aSTaRINaaGaa_1a"), xT("a"), xT(""));
        xASSERT(xT("TEST_STRING_1") == m_sRes);

        m_sRes = CxString::sReplaceAll(xT("TEST_STRING_1"), xT("T"), xT("a"));
        xASSERT(xT("aESa_SaRING_1") == m_sRes);

        m_sRes = CxString::sReplaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("/"), xT("_"));
        xASSERT(xT("D:_XVCL_Include\\XVCL_Units_Gui_vSpeedButton_LoadDrives.cpp") == m_sRes);

        m_sRes = CxString::sReplaceAll(xT("D:/XVCL/Include\\XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp"), xT("\\"), xT("_"));
        xASSERT(xT("D:/XVCL/Include_XVCL/Units/Gui/vSpeedButton_LoadDrives.cpp") == m_sRes);


        m_sRes = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT(""));
        xASSERT(xT("_one__three_") == m_sRes);

        m_sRes = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT("fife"));
        xASSERT(xT("_one_fife_three_") == m_sRes);

        m_sRes = CxString::sReplaceAll(xT("_one_two_three_"), xT("two"), xT("^"));
        xASSERT(xT("_one_^_three_") == m_sRes);

        m_sRes = CxString::sReplaceAll(xT("aaaaffaaaa"), xT("ff"), xT("ffff"));
        xASSERT(xT("aaaaffffaaaa") == m_sRes);

        m_sRes = CxString::sReplaceAll(xT("aaaaffaaaa"), xT("ff"), xT("f"));
        xASSERT(xT("aaaafaaaa") == m_sRes);

    }

    //-------------------------------------
    //sReplaceAll
    {
        m_sRes = CxString::sReplaceAll(xT(" one test string "), xT(" "), xT("_"));
        xASSERT(m_sRes == xT("_one_test_string_"));

        m_sRes = CxString::sReplaceAll(xT(" one test string "), xT(" "), xT(""));
        xASSERT(m_sRes == xT("oneteststring"));

        m_sRes = CxString::sReplaceAll(xT(" one test string "), xT(' '), xT('-'));
        xASSERT(m_sRes == xT("-one-test-string-"));
    }

    //-------------------------------------
    //sRemoveAll
    {
        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT(" "));
        xASSERT(xT("oneteststring") == m_sRes);

        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT(" "));
        xASSERT(xT("oneteststring") == m_sRes);

        m_sRes = CxString::sRemoveAll(xT("one test strin g"),  xT(" "));
        xASSERT(xT("oneteststring") == m_sRes);

        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT("string"));
        xASSERT(xT(" one test  ") == m_sRes);

        m_sRes = CxString::sRemoveAll(xT(" one test string "), xT("string"));
        xASSERT(xT(" one test  ") == m_sRes);

        m_sRes = CxString::sRemoveAll(xT("one test stringg"),  xT("string"));
        xASSERT(xT("one test g") == m_sRes);
    }

    //-------------------------------------
    //bSplit
    {
        std::vector<tString> vecsText;

        m_bRes = CxString::bSplit(xT("1+++22+++333+++4444+++55555+++666666"), xT("+"), &vecsText);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxString::bSplit(xT("Key+"), xT("+"), &vecsText);
        xASSERT(FALSE != m_bRes);

        vecsText.clear();
        m_bRes = CxString::bSplit(xT(""), xT("+"), &vecsText);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //sJoin
    {
        std::vector<tString> vecsRes;
        vecsRes.push_back(xT("111"));
        vecsRes.push_back(xT(""));
        vecsRes.push_back(xT("222"));
        vecsRes.push_back(xT("333"));

        m_sRes = CxString::sJoin(vecsRes, xT("-"));
        xASSERT(xT("111--222-333") == m_sRes);
    }

    //-------------------------------------
    //sCut
    {
        tString sForCut;

        //���� ������
        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <_Alca@meta.ua_>");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT(xT("_Alca@meta.ua_") == m_sRes);

        sForCut = xT("<_Alca@meta.ua_>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT(xT("_Alca@meta.ua_") == m_sRes);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT(xT("_Alca@meta.ua_") == m_sRes);

        sForCut = xT("To: =?windows-125<_Alc<a>@meta>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT(xT("_Alc<a>@meta>.ua_") == m_sRes);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT(xT("") == m_sRes);

        sForCut = xT("To: =?windows-125<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT(xT("") == m_sRes);

        sForCut = xT("To: =?windows-125>_Alca@meta.ua_<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT(xT("") == m_sRes);

        sForCut = xT("To: =?windows-125_Alca<>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<"), xT(">"));
        xASSERT(xT("") == m_sRes);


        //������
        sForCut = xT("To: =?windows-1251?B?x+Di4+7w7uTt//8=?= <<_Alca@meta.ua_>>");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT(xT("_Alca@meta.ua_") == m_sRes);

        sForCut = xT("<<_Alca@meta.ua_>>To: =?windows-1251?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT(xT("_Alca@meta.ua_") == m_sRes);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT(xT("_Alca@meta.ua_") == m_sRes);

        sForCut = xT("To: =?windows-125<<_Alc<<a>>@meta>>.ua_>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT(xT("_Alc<<a>>@meta") == m_sRes);

        sForCut = xT("To: =?windows-125_Alca@meta.ua_>>1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT(xT("") == m_sRes);

        sForCut = xT("To: =?windows-125<<_Alca@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT(xT("") == m_sRes);

        sForCut = xT("To: =?windows-125>>_Alca@meta.ua_<<1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT(xT("") == m_sRes);

        sForCut = xT("To: =?windows-125_Alca<<>>@meta.ua_1?B?x+Di4+7w7uTt//8=?= ");
        m_sRes = CxString::sCut(sForCut, xT("<<"), xT(">>"));
        xASSERT(xT("") == m_sRes);
    }

    //-------------------------------------
    //sCut
    {
        tString sForCut = xT("0123456789");


        //��� ���������
        m_sRes = CxString::sCut(sForCut, 0, 1);
        xASSERT(xT("0") == m_sRes);

        m_sRes = CxString::sCut(sForCut, 0, 9);
        xASSERT(xT("012345678") == m_sRes);

        m_sRes = CxString::sCut(sForCut, 4, 5);
        xASSERT(xT("4") == m_sRes);

        m_sRes = CxString::sCut(sForCut, 4, 6);
        xASSERT(xT("45") == m_sRes);

        m_sRes = CxString::sCut(sForCut, 6, 6);
        xASSERT(xT("") == m_sRes);

        m_sRes = CxString::sCut(sForCut, 6, 4); //error
        xASSERT(xT("") == m_sRes);

        m_sRes = CxString::sCut(xT(""), 1, 2);  //error
        xASSERT(xT("") == m_sRes);


        //���� ��������
        m_sRes = CxString::sCut(sForCut, 0);
        xASSERT(xT("0123456789") == m_sRes);

        m_sRes = CxString::sCut(sForCut, 4);
        xASSERT(xT("456789") == m_sRes);

        m_sRes = CxString::sCut(sForCut, 9);
        xASSERT(xT("9") == m_sRes);

        m_sRes = CxString::sCut(sForCut, 10);       //error
        xASSERT(xT("") == m_sRes);

        //m_sRes = CxString::sCut(sForCut, - 1);    //error
        //xASSERT(xT("") == m_sRes);

        m_sRes = CxString::sCut(xT(""), 1);     //error
        xASSERT(xT("") == m_sRes);


        //��� ����������
        m_sRes = CxString::sCut(sForCut);
        xASSERT(xT("0123456789") == m_sRes);
    }

    //-------------------------------------
    //sToLowerCase
    {
        const tString sTestData[][2] = {
            {xT("test_string_1"),       xT("TEST_string_1")},
            {xT("test_string_1"),       xT("TEst_stRING_1")},
            {xT("test_string_1\n"),     xT("TEST_STRing_1\n")},
            {xT("test_string_1\n\r"),   xT("TEST_STring_1\n\r")},
           //// {xT("фффффффффффф\n\r"),    xT("ФФФФфффффффф\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sToLowerCase(sTestData[i][0]);
            tString sStr2 = CxString::sToLowerCase(sTestData[i][1]);
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());

            tString sStr3 = CxString::sToLowerCase(sTestData[i][1]);
            tString sStr4 = sTestData[i][0];
            xASSERT_MSG(sStr3 == sStr4, (sStr3 + xT(" == ") + sStr4).c_str());
        }
    }

    //-------------------------------------
    //sToUpperCase
    {
        const tString sTestData[][2] = {
            {xT("TEST_STRING_1_A"),       xT("TEST_string_1_a")},
            {xT("TEST_STRING_1_A"),       xT("TEst_stRING_1_A")},
            {xT("TEST_STRING_1_A\n"),     xT("TEST_STRing_1_a\n")},
            {xT("TEST_STRING_1_A\n\r"),   xT("TEST_STring_1_A\n\r")},
            ////{xT("ААААААААААААА\n\r"),   xT("АААААААААаааа\n\r")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sToUpperCase(sTestData[i][0]);
            tString sStr2 = CxString::sToUpperCase(sTestData[i][1]);
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());

            tString sStr3 = CxString::sToUpperCase(sTestData[i][1]);
            tString sStr4 = sTestData[i][0];
            xASSERT_MSG(sStr3 == sStr4, (sStr3 + xT(" == ") + sStr4).c_str());
        }
    }

    //-------------------------------------
    //sToLowerCase
    {
        const tString sTestData[][2] = {
            ////{xT("тест_строка1"),  xT("тест_СТРОКА1")},
            {xT("test_string_1_a"), xT("test_string_1_A")},
            {xT("test_string_1_a"), xT("Test_strINg_1_a")},
            {xT("test_string_1_a"), xT("test_STRING_1_A")},
            {xT("test_string_1_a"), xT("Test_string_1_a")},
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sToLowerCase(sTestData[i][0], sTestData[i][0].size());
            tString sStr2 = CxString::sToLowerCase(sTestData[i][1], sTestData[i][1].size());
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());

            tString sStr3 = CxString::sToLowerCase(sTestData[i][1], sTestData[i][1].size() + 1000);
            tString sStr4 = sTestData[i][0];
            xASSERT_MSG(sStr3 == sStr4, (sStr3 + xT(" == ") + sStr4).c_str());
        }
    }

    //-------------------------------------
    //sToUpperCase
    {
        const tString sTestData[][2] = {
            {xT("TEST_STRING_1_A"), xT("tEST_string_1_A")},
            {xT("TEST_STRING_1_A"), xT("tEst_stRING_1_a")},
            {xT("TEST_STRING_1_A"), xT("TEST_STRing_1_a")},
            {xT("TEST_STRING_1_A"), xT("tEST_STring_1_A")},
            ////{xT("ТЕСТ_СТРОКА_1"), xT("ТеСт_сТРока1")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxString::sToUpperCase(sTestData[i][0], sTestData[i][0].size());
            tString sStr2 = CxString::sToUpperCase(sTestData[i][1], sTestData[i][1].size());
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());

            tString sStr3 = CxString::sToUpperCase(sTestData[i][1], sTestData[i][1].size() - 1000);
            tString sStr4 = sTestData[i][0];
            xASSERT_MSG(sStr3 == sStr4, (sStr3 + xT(" == ") + sStr4).c_str());
        }
    }

    //-------------------------------------
    //sFormat
    {
        m_sRes = CxString::sFormat(xT("qqqq-wwww [%i]"), 1000);
        xASSERT(m_sRes == xT("qqqq-wwww [1000]"));

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%f]"), 1000.0);
        #if defined(xOS_WIN)
        xASSERT(m_sRes == xT("qqqq-wwww [1000,000000]"));
        #elif defined(xOS_LINUX)
        xASSERT(m_sRes == xT("qqqq-wwww [1000.000000]"));
        #endif

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%s]"), xT("1000"));
        xASSERT(m_sRes == xT("qqqq-wwww [1000]"));

        m_sRes = CxString::sFormat(xT("qqqq-wwww [%i]"), -1000);
        xASSERT(m_sRes == xT("qqqq-wwww [-1000]"));



        m_sRes = CxString::sFormat(xT("Characters: %c %c"), xT('a'), 65);
        xASSERT(m_sRes == xT("Characters: a A"));

        m_sRes = CxString::sFormat(xT("Decimals: %d %ld"), 1977, 650000L);
        xASSERT(m_sRes == xT("Decimals: 1977 650000"));

        m_sRes = CxString::sFormat(xT("Preceding with blanks: %10d"), 1977);
        xASSERT(m_sRes == xT("Preceding with blanks:       1977"));

        m_sRes = CxString::sFormat(xT("Preceding with zeros: %010d"), 1977);
        xASSERT(m_sRes == xT("Preceding with zeros: 0000001977"));

        m_sRes = CxString::sFormat(xT("Some different radixes: %d %x %o %#x %#o"), 100, 100, 100, 100, 100);
        xASSERT(m_sRes == xT("Some different radixes: 100 64 144 0x64 0144"));


        #if defined(xOS_WIN)
        m_sRes = CxString::sFormat(xT("floats: %4.2f %+.0e %E"), 3.1416, 3.1416, 3.1416);
        xASSERT(m_sRes == xT("floats: 3,14 +3e+000 3,141600E+000"));
        #elif defined(xOS_LINUX)
        m_sRes = CxString::sFormat(xT("floats: %4.2f %+.0e %E"), 3.1416, 3.1416, 3.1416);
        ////xASSERT(m_sRes == xT("floats: 3,14 +3e+000 3,141600E+000"));
        #endif

        m_sRes = CxString::sFormat(xT("Width trick: %*d"), 5, 10);
        xASSERT(m_sRes == xT("Width trick:    10"));

        m_sRes = CxString::sFormat(xT("%s"), xT("A string"));
        xASSERT(m_sRes == xT("A string"));
    }

    //-------------------------------------
    //sFormatV
    {
        ////m_sRes = sFormatV(LPCSTR pcszFormat, va_list palArgs);
    }

    //-------------------------------------
    //sMinimize
    {
        m_sRes = CxString::sMinimize(xT("55555wwwww"), 5);
        xASSERT(xT("55...") == m_sRes);

        m_sRes = CxString::sMinimize(xT("55555wwwww00000"), 20);
        xASSERT(xT("55555wwwww00000") == m_sRes);
    }

    //-------------------------------------
    //bCompareNoCase
    {
        m_bRes = CxString::bCompareNoCase(xT(""),     xT(""));
        xASSERT(FALSE != m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("xxx"),  xT("XXX"));
        xASSERT(FALSE != m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("111"),  xT("111"));
        xASSERT(FALSE != m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("eee"),  xT("EeE"));
        xASSERT(FALSE != m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("WWW"),  xT("wwW"));
        xASSERT(FALSE != m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("ccc"),  xT("���"));
        xASSERT(FALSE == m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("���"),  xT("����"));
        xASSERT(FALSE == m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("����"), xT("���"));
        xASSERT(FALSE == m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("���"),  xT("����"));
        xASSERT(FALSE == m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("����"), xT("���"));
        xASSERT(FALSE == m_bRes);

        m_bRes = CxString::bCompareNoCase(xT("dddd"), xT("d"));
        xASSERT(FALSE == m_bRes);
    }


    /****************************************************************************
    *   �������������
    *
    *****************************************************************************/

    //-------------------------------------
    //sDecodeWinKoi
    //m_sRes = sDecodeWinKoi(INT iFrom, INT iTo, const tString &sOldStr);

    //-------------------------------------
    //sTranslitLatToRus
    {
        #if xTODO
        m_sRes = CxString::sTranslitLatToRus(xT("Привет! Как дела чувак? Чего делаешь?"));
        xASSERT(xT("Privet! Kak dela 4uvak? 4ego delaesh'?") == m_sRes);

        m_sRes = CxString::sTranslitLatToRus(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll"));
        xASSERT(xT("ConsoleTest.exe': Loaded 'C:\\Program Files\\Kaspersky Lab\\Kaspersky Internet Security 2009\\adialhk.dll") == m_sRes);
        #endif
    }

    //-------------------------------------
    //bCharToWide
    //m_bRes = CxString::bCharToWide(const CHAR *pszSrc, WCHAR *pwszDest, INT iDestSize);

    //-------------------------------------
    //sStrToRtf
    //m_sRes = CxString::sStrToRtf(tString sStr);

    //-------------------------------------
    //sRtfToStr
    //m_sRes = CxString::sRtfToStr(tString sStr);

    //-------------------------------------
    //sBytesToStr
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

    //TODO: CxString::sFormatPercent(ULONGLONG ullMaxValue, ULONGLONG ullCurrValue) {
    {

    }

    //--------------------------------------------------
    //sFormatNixTerminal
    {
////        for (int i = 0; i <= 120; ++ i) {
//            tString sRes = sColorStr(xT("Linux Console Color"), (EForeground)i, FALSE, FALSE, bgBlack, FALSE);
//
//            std::cout<< xT("Color: ") << i << xT(" ") << sRes << std::endl;
//        }
//
//        tString sRes = CxString::sFormatNixTerminal(xT("Linux Console Color"), CxString::fgYellow_, TRUE, FALSE, CxString::bgBlue_, FALSE);
//
////        std::cout << sRes << std::endl;
    }

    /****************************************************************************
    *    memory
    *
    *****************************************************************************/

    //--------------------------------------------------
    //pvMemoryZeroSecure
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
    {
        #if defined(xOS_WIN)
        m_sRes = CxString::sCreateGuid();
        xASSERT(false == m_sRes.empty());
        #elif defined(xOS_LINUX)
        ////xASSERT(true == m_sRes.empty());
        #endif
    }

    //-------------------------------------
    //bIsRepeated
    {
        m_bRes = CxString::bIsRepeated(xT("yyyyyyyyyyyy"));
        xASSERT(FALSE != m_bRes);

        m_bRes = CxString::bIsRepeated(xT("111111111111"));
        xASSERT(FALSE != m_bRes);

        m_bRes = CxString::bIsRepeated(xT("uuuuuiuuuuuuuuuuuu"));
        xASSERT(FALSE == m_bRes);

        m_bRes = CxString::bIsRepeated(xT("000000000111111111"));
        xASSERT(FALSE == m_bRes);
    }

    //-------------------------------------
    //vStdVectorPrintT
    {
        m_vecsRes.push_back(xT("qqqq"));
        m_vecsRes.push_back(xT("wwww"));
        m_vecsRes.push_back(xT("eeee"));
        m_vecsRes.push_back(xT("rrrr"));
        m_vecsRes.push_back(xT("tttt"));

        ////CxString::vStdVectorPrintT(m_vecsRes);
    }

    //-------------------------------------
    //vStdMultiMapPrintT
    {
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key0"), xT("Value0")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key1"), xT("Value1")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key2"), xT("Value2")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key3"), xT("Value3")) );
        m_mmsRes.insert( std::pair<tString, tString>(xT("Key4"), xT("Value4")) );

        ////CxString::vStdMultiMapPrintT(m_mmsRes);
    }


    /****************************************************************************
    *   �������������
    *
    *****************************************************************************/

    //-------------------------------------
    //sConvertCodePage
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
                xASSERT(csAnsiStr[i] == sAnsi);


                //1251(WIN)  <-> 20866(KOI-8r)
                std::string sKoiStr;
                std::string sWinStr;

                sKoiStr = CxString::sConvertCodePage(csAnsiStr[i], 1251,  20866);
                sWinStr = CxString::sConvertCodePage(sKoiStr,      20866, 1251);
                xASSERT(csAnsiStr[i] == sWinStr);
            #elif defined(xOS_LINUX)
                //TODO: sConvertCodePage
                //xNOT_IMPLEMENTED_RET(RET_VALUE);
            #endif
        }
    }

    //-------------------------------------
    //sCharToOemBuff
    {
        std::string sRes;

        #if defined(xOS_WIN)
        sRes = CxString::asCharToOemBuff(xT("Boss, hello? "));
        xASSERT("Boss, hello? " == sRes);
        #elif defined(xOS_LINUX)
        //TODO: sCharToOemBuff
        #endif
    }

    //-------------------------------------
    //sOemToCharBuff
    {
        tString sRes;

        #if defined(xOS_WIN)
        sRes = CxString::sOemToCharBuff(("1111, hdbhjgjk hkl, jl.,kh."));
        xASSERT(xT("1111, hdbhjgjk hkl, jl.,kh.") == sRes);
        #elif defined(xOS_LINUX)
        //TODO: sOemToCharBuff
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
