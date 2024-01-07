/**
 * \file   Test_Environment.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Environment)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Environment::unit()
{
    xTEST_CASE("str")
    {
        const std::set<std::pair_tstring_t> vars
        {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (const auto &[it_var, it_value] : vars) {
            Environment env(it_var);
            env.setValue(it_value);

            const auto &test     = env.str();
            const auto &expected = it_var + Const::equal() + it_value;
            xTEST_EQ(test, expected);
        }
    }

    xTEST_CASE("setValue")
    {
        std::ctstring_t data[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            Environment env(data[i][0]);
            env.setValue(data[i][1]);
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
        std::ctstring_t data[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},

            {xT("OS"),         xT("true") },
            {xT("XXXL"),       xT("false")},
            {xT("windir"),     xT("true") }
        };
    #elif xENV_UNIX
        std::ctstring_t data[][2] = {
            {xT("ENV_TEST_1"), xT("true")},
            {xT("ENV_TEST_2"), xT("true")},
            {xT("ENV_TEST_3"), xT("true")},
            {xT("ENV_TEST_4"), xT("true")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
        	Environment env(data[i][0]);

            bool_t bStr1 = env.isExists();
            xTEST_EQ(String::castBool(data[i][1]), bStr1);
        }
    }

    xTEST_CASE("value")
    {
    #if   xENV_WIN
        std::ctstring_t data[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")},
        };
    #elif xENV_UNIX
        std::ctstring_t data[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            Environment env(data[i][0]);

            std::tstring_t str1 = env.value();
            std::tstring_t str2 = data[i][1];
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("vars")
    {
        Environment::vars(&m_vsRv);
        xTEST(!m_vsRv.empty());
    }

    xTEST_CASE("expandVars")
    {
    #if   xENV_WIN
        std::ctstring_t data[][2] = {
            {xT(" System root: %SystemRoot%"),  xT(" System root: C:\\Windows")},
            {xT("Windows Dir: %windir% "),      xT("Windows Dir: C:\\Windows ")}
        };
    #elif xENV_UNIX
        std::ctstring_t data[][2] = {
            {xT("111%ENV_TEST_1%"),    xT("111value1")},
            {xT("%ENV_TEST_2%111"),    xT("value2111")},
            {xT("ttt%ENV_TEST_3%"),    xT("tttvalue3")},
            {xT("rrr%ENV_TEST_4%rrr"), xT("rrrvalue4rrr")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Environment::expandVars(data[i][0]);
            std::tstring_t str2 = data[i][1];
            xTEST(StringCI::compare(str1, str2));
        }
    }

    xTEST_CASE("remove")
    {
        std::ctstring_t data[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},
            {xT("ENV_TEST_2"), xT("value2")},
            {xT("ENV_TEST_3"), xT("value3")},
            {xT("ENV_TEST_4"), xT("value4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            Environment env(data[i][0]);
            env.remove();
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
