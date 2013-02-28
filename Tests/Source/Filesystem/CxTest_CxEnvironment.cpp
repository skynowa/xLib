/**
 * \file   CxTest_CxEnvironment.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxEnvironment.h>

#include <xLib/Common/CxString.h>


//------------------------------------------------------------------------------
CxTest_CxEnvironment::CxTest_CxEnvironment() {

}
//------------------------------------------------------------------------------
CxTest_CxEnvironment::~CxTest_CxEnvironment() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxEnvironment::unit(
    culonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxEnvironment::setVar", cullCaseLoops)
    {
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            CxEnvironment::setVar(sData[i][0], sData[i][1]);
        }
    }

    xTEST_CASE("CxEnvironment::isExists", cullCaseLoops)
    {
    #if   xOS_ENV_WIN
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},

            {xT("OS"),         xT("true") },
            {xT("XXXL"),       xT("false")},
            {xT("windir"),     xT("true") }
        };
    #elif xOS_ENV_UNIX
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            bool_t bStr1 = CxEnvironment::isExists(sData[i][0]);
            xTEST_EQ(CxString::strToBool(sData[i][1]), bStr1);
        }
    }

    xTEST_CASE("CxEnvironment::isVarValid", cullCaseLoops)
    {
    #if   xOS_ENV_WIN
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},
            {xT("OS="),        xT("false")},
            {xT("XX=XL"),      xT("false")},
            {xT("=windir"),    xT("false")},
            {xT(""),           xT("false")}
        };
    #elif xOS_ENV_UNIX
        std::ctstring_t sData[][2] = {
            {xT("OS="),        xT("false")},
            {xT("XX=XL"),      xT("false")},
            {xT("=windir"),    xT("false")},
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            bool_t bStr1 = CxEnvironment::isVarValid(sData[i][0]);
            xTEST_EQ(CxString::strToBool(sData[i][1]), bStr1);
        }
    }

    xTEST_CASE("CxEnvironment::isValueValid", cullCaseLoops)
    {
    #if   xOS_ENV_WIN
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},
            {xT("OS"),         xT("true")},
            {xT("XXXL"),       xT("true")},
            {xT("windir"),     xT("true")},
            {xT(""),           xT("true")}
        };
    #elif xOS_ENV_UNIX
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},
            {xT(""),           xT("true")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            bool_t bStr1 = CxEnvironment::isValueValid(sData[i][0]);
            xTEST_EQ(CxString::strToBool(sData[i][1]), bStr1);
        }
    }

    xTEST_CASE("CxEnvironment::var", cullCaseLoops)
    {
    #if   xOS_ENV_WIN
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")},
        };
    #elif xOS_ENV_UNIX
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxEnvironment::var(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("CxEnvironment::values", cullCaseLoops)
    {
        CxEnvironment::values(&m_vsRv);
        xTEST_EQ(false, m_vsRv.empty());

        ////CxString::vStdVectorPrintT(m_vsRv);
    }

    xTEST_CASE("CxEnvironment::expandStrings", cullCaseLoops)
    {
    #if   xOS_ENV_WIN
        std::ctstring_t sData[][2] = {
            {xT(" System root: %SystemRoot%"),  xT(" System root: C:\\Windows")},
            {xT("Windows Dir: %windir% "),      xT("Windows Dir: C:\\Windows ")}
        };
    #elif xOS_ENV_UNIX
        std::ctstring_t sData[][2] = {
            {xT("111%ENV_TEST_1%"),    xT("111value1")},
            {xT("%ENV_TEST_2%111"),    xT("value2111")},
            {xT("ttt%ENV_TEST_3%"),    xT("tttvalue3")},
            {xT("rrr%ENV_TEST_4%rrr"), xT("rrrvalue4rrr")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxEnvironment::expandStrings(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(true, CxString::compareNoCase(sStr1, sStr2));
        }
    }

    xTEST_CASE("CxEnvironment::deleteVar", cullCaseLoops)
    {
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            CxEnvironment::deleteVar(sData[i][0]);
        }
    }
}
//------------------------------------------------------------------------------
