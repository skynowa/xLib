/**
 * \file   CxTest_CxEnvironment.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxEnvironment.h>


//---------------------------------------------------------------------------
CxTest_CxEnvironment::CxTest_CxEnvironment() {

}
//---------------------------------------------------------------------------
CxTest_CxEnvironment::~CxTest_CxEnvironment() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxEnvironment::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    //-------------------------------------
    //bSetVar
    xTEST_CASE(cullBlockLoops)
    {
        const std::tstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            m_bRes = CxEnvironment::bSetVar(sData[i][0], sData[i][1]);
            xTEST_DIFF(false, m_bRes);
        }
    }

    //-------------------------------------
    //bIsExists
    xTEST_CASE(cullBlockLoops)
    {
    #if xOS_ENV_WIN
        const std::tstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},

            {xT("OS"),         xT("true") },
            {xT("XXXL"),       xT("false")},
            {xT("windir"),     xT("true") }
        };
    #elif xOS_ENV_UNIX
        const std::tstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            bool bStr1 = CxEnvironment::bIsExists(sData[i][0]);
            xTEST_EQ((sData[i][1] == xT("false") ? false : true), bStr1);
        }
    }

    //-------------------------------------
    //sGetVar
    xTEST_CASE(cullBlockLoops)
    {
    #if xOS_ENV_WIN
        const std::tstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")},
        };
    #elif xOS_ENV_UNIX
        const std::tstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxEnvironment::sGetVar(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //bGetValues
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = CxEnvironment::bGetValues(&m_vsRes);
        xTEST_DIFF(false, m_bRes);
        xTEST_EQ(false, m_vsRes.empty());

        ////CxString::vStdVectorPrintT(m_vsRes);
    }

    //-------------------------------------
    //sExpandStrings
    xTEST_CASE(cullBlockLoops)
    {
    #if xOS_ENV_WIN
        const std::tstring_t sData[][2] = {
            {xT(" System root: %SystemRoot%"),  xT(" System root: C:\\WINDOWS")},
            {xT("Windows Dir: %windir% "),      xT("Windows Dir: C:\\WINDOWS ")}
        };
    #elif xOS_ENV_UNIX
        const std::tstring_t sData[][2] = {
            {xT("111%ENV_TEST_1%"),    xT("111value1")},
            {xT("%ENV_TEST_2%111"),    xT("value2111")},
            {xT("ttt%ENV_TEST_3%"),    xT("tttvalue3")},
            {xT("rrr%ENV_TEST_4%rrr"), xT("rrrvalue4rrr")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxEnvironment::sExpandStrings(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //bDeleteVar
    xTEST_CASE(cullBlockLoops)
    {
        const std::tstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            bool bStr1 = CxEnvironment::bDeleteVar(sData[i][0]);
            xTEST_DIFF(false, bStr1);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
