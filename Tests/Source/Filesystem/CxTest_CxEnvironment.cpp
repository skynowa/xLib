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
CxTest_CxEnvironment::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //bSetVar
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            m_bRes = CxEnvironment::bSetVar(sData[i][0], sData[i][1]);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bIsExists
    xTEST_BLOCK(cullBlockLoops)
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
            xASSERT_EQ((sData[i][1] == xT("FALSE") ? FALSE : TRUE), bStr1);
        }
    }

    //-------------------------------------
    //sGetVar
    xTEST_BLOCK(cullBlockLoops)
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
            {xT("ENV_TEST_4"), xT("value4")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxEnvironment::sGetVar(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //bGetValues
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxEnvironment::bGetValues(&m_vsRes);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        xASSERT_EQ(false, m_vsRes.empty());

        ////CxString::vStdVectorPrintT(m_vsRes);
    }

	//-------------------------------------
	//sExpandStrings
    xTEST_BLOCK(cullBlockLoops)
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
            {xT("rrr%ENV_TEST_4%rrr"), xT("rrrvalue4rrr")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxEnvironment::sExpandStrings(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //bDeleteVar
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            BOOL bStr1 = CxEnvironment::bDeleteVar(sData[i][0]);
            xASSERT_NOT_EQ(FALSE, bStr1);
        }
    }

    //-------------------------------------
    //sGetCommandLine
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxEnvironment::sGetCommandLine();
        xTRACEV(xT("\tCxEnvironment::sGetCommandLine(): %s"), m_sRes.c_str());
        xASSERT_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //bGetCommandLineArgs
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxEnvironment::bGetCommandLineArgs(&m_vsRes);
        xASSERT_NOT_EQ(FALSE,  m_bRes);
        xASSERT_EQ(false, m_vsRes.empty());
    }

    return TRUE;
}
//---------------------------------------------------------------------------
