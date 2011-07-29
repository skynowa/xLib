/****************************************************************************
* Class name:  CxTest_CxEnvironment
* Description: test CxEnvironment
* File name:   CxTest_CxEnvironment.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Filesystem/CxTest_CxEnvironment.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxEnvironment
CxTest_CxEnvironment::CxTest_CxEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxEnvironment
CxTest_CxEnvironment::~CxTest_CxEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxEnvironment::bUnit() {
    //-------------------------------------
    //bSetVar
    {
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            m_bRes = CxEnvironment::bSetVar(sData[i][0], sData[i][1]);
            xASSERT_EQUAL(TRUE, m_bRes);
        }
    }

    //-------------------------------------
    //bIsExists
    {
    #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("TRUE")},
            {xT("ENV_TEST_2"), xT("TRUE")},
            {xT("ENV_TEST_3"), xT("TRUE")},
            {xT("ENV_TEST_4"), xT("TRUE")},

            {xT("OS"),         xT("TRUE") },
            {xT("XXXL"),       xT("FALSE")},
            {xT("windir"),     xT("TRUE") }
        };
    #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("TRUE")},
            {xT("ENV_TEST_2"), xT("TRUE")},
            {xT("ENV_TEST_3"), xT("TRUE")},
            {xT("ENV_TEST_4"), xT("TRUE")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            BOOL bStr1 = CxEnvironment::bIsExists(sData[i][0]);
            xASSERT_EQUAL((sData[i][1] == xT("FALSE") ? FALSE : TRUE), bStr1);
        }
    }

    //-------------------------------------
    //sGetVar
    {
    #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")},
        };
    #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")},

            {xT("TERM"),  xT("xterm")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxEnvironment::sGetVar(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT_EQUAL(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //bGetValues
    {
        m_bRes = CxEnvironment::bGetValues(&m_vecsRes);
        xASSERT_EQUAL(TRUE, m_bRes);
        xASSERT_EQUAL(false, m_vecsRes.empty());

        ////CxString::vStdVectorPrintT(m_vecsRes);
    }

	//-------------------------------------
	//sExpandStrings
    {
    #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT(" System root: %SystemRoot%"),  xT(" System root: C:\\WINDOWS")},
            {xT("Windows Dir: %windir% "),      xT("Windows Dir: C:\\WINDOWS ")}
        };
    #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("111%ENV_TEST_1%"),    xT("111value1")},
            {xT("%ENV_TEST_2%111"),    xT("value2111")},
            {xT("ttt%ENV_TEST_3%"),    xT("tttvalue3")},
            {xT("rrr%ENV_TEST_4%rrr"), xT("rrrvalue4rrr")},
            {xT("TERM =   %TERM%  "),  xT("TERM =   xterm  ")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxEnvironment::sExpandStrings(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT_EQUAL(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //bDeleteVar
    {
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            BOOL bStr1 = CxEnvironment::bDeleteVar(sData[i][0]);
            xASSERT_EQUAL(TRUE, bStr1);
        }
    }

    //-------------------------------------
    //sGetCommandLine
    {
        m_sRes = CxEnvironment::sGetCommandLine();
        xTRACEV(xT("\tCxEnvironment::sGetCommandLine(): %s"), m_sRes.c_str());
        xASSERT_EQUAL(false, m_sRes.empty());
    }

    //-------------------------------------
    //bGetCommandLineArgs
    {
        m_bRes = CxEnvironment::bGetCommandLineArgs(&m_vecsRes);
        xASSERT_EQUAL(TRUE,  m_bRes);
        xASSERT_EQUAL(false, m_vecsRes.empty());
    }

    return TRUE;
}
//---------------------------------------------------------------------------
