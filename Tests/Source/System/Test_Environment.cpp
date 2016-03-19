/**
 * \file   Test_Environment.cpp
 * \brief
 */


#include <Test/System/Test_Environment.h>

#include <xLib/Core/String.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Environment)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Environment::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("setVar", a_caseLoops)
    {
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            Environment::setVar(sData[i][0], sData[i][1]);
        }
    }

    xTEST_CASE("isExists", a_caseLoops)
    {
    #if   xENV_WIN
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},

            {xT("OS"),         xT("true") },
            {xT("XXXL"),       xT("false")},
            {xT("windir"),     xT("true") }
        };
    #elif xENV_UNIX
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            bool_t bStr1 = Environment::isExists(sData[i][0]);
            xTEST_EQ(String::castBool(sData[i][1]), bStr1);
        }
    }

    xTEST_CASE("isVarValid", a_caseLoops)
    {
    #if   xENV_WIN
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
    #elif xENV_UNIX
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
            bool_t bStr1 = Environment::isVarValid(sData[i][0]);
            xTEST_EQ(String::castBool(sData[i][1]), bStr1);
        }
    }

    xTEST_CASE("isValueValid", a_caseLoops)
    {
    #if   xENV_WIN
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
    #elif xENV_UNIX
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},
            {xT(""),           xT("true")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            bool_t bStr1 = Environment::isValueValid(sData[i][0]);
            xTEST_EQ(String::castBool(sData[i][1]), bStr1);
        }
    }

    xTEST_CASE("var", a_caseLoops)
    {
    #if   xENV_WIN
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")},
        };
    #elif xENV_UNIX
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = Environment::var(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("values", a_caseLoops)
    {
        Environment::values(&m_vsRv);
        xTEST_EQ(false, m_vsRv.empty());
    }

    xTEST_CASE("expandStrings", a_caseLoops)
    {
    #if   xENV_WIN
        std::ctstring_t sData[][2] = {
            {xT(" System root: %SystemRoot%"),  xT(" System root: C:\\Windows")},
            {xT("Windows Dir: %windir% "),      xT("Windows Dir: C:\\Windows ")}
        };
    #elif xENV_UNIX
        std::ctstring_t sData[][2] = {
            {xT("111%ENV_TEST_1%"),    xT("111value1")},
            {xT("%ENV_TEST_2%111"),    xT("value2111")},
            {xT("ttt%ENV_TEST_3%"),    xT("tttvalue3")},
            {xT("rrr%ENV_TEST_4%rrr"), xT("rrrvalue4rrr")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = Environment::expandStrings(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(true, StringCI::compare(sStr1, sStr2));
        }
    }

    xTEST_CASE("deleteVar", a_caseLoops)
    {
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            Environment::deleteVar(sData[i][0]);
        }
    }
}
//-------------------------------------------------------------------------------------------------
