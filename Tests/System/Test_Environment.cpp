/**
 * \file   Test_Environment.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Environment)
xTEST_UNIT(Test_Environment)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Environment::unit()
{
    xTEST_CASE("setVar")
    {
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            Environment env(sData[i][0]);
            env.setVar(sData[i][1]);
        }
    }

    xTEST_CASE("setVars")
    {
        const std::set<std::pair_tstring_t> vars
        {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        Environment::setVars(vars);
    }

    xTEST_CASE("isExists")
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
        	Environment env(sData[i][0]);

            bool_t bStr1 = env.isExists();
            xTEST_EQ(String::castBool(sData[i][1]), bStr1);
        }
    }

    xTEST_CASE("var")
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
            Environment env(sData[i][0]);

            std::tstring_t sStr1 = env.var();
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("values")
    {
        Environment::values(&m_vsRv);
        xTEST_EQ(false, m_vsRv.empty());
    }

    xTEST_CASE("expandStrings")
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

    xTEST_CASE("removeVar")
    {
        std::ctstring_t sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            Environment env(sData[i][0]);
            env.removeVar();
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
