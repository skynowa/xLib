/**
 * \file   Test_Env.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Env)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Env::unit()
{
	std::ctstring_t prefixes[]
	{
		Path::exe().fileBaseName() + "_",
		"XLIB_",
		"1_",
		"_",
		""
	};

	/**************************************************
	* Env
	*
	**************************************************/

	xTEST_CASE("str")
	{
		for (const auto &it_prefix : prefixes) {
			const std::set<std::pair_tstring_t> vars
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")}
			};

			for (const auto &[it_var, it_value] : vars) {
				Env env(it_prefix, it_var);
				env.setValue(it_value);

				const auto &test     = env.str();
				const auto &expected = it_prefix + it_var + Const::equal() + it_value;
				xTEST_EQ(test, expected);
			}
		}
	}

	xTEST_CASE("setValue")
	{
		for (const auto &it_prefix : prefixes) {
			std::ctstring_t data[][2]
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")}
			};

			for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
				Env env(it_prefix, data[i][0]);
				env.setValue(data[i][1]);

				xTEST(env.isExists());
			}
		}
	}

	xTEST_CASE("isExists")
	{
		for (const auto &it_prefix : prefixes) {
		#if   xENV_WIN
			std::ctstring_t data[][2]
			{
				{xT("ENV_TEST_1"), xT("true")},
				{xT("ENV_TEST_2"), xT("true")},
				{xT("ENV_TEST_3"), xT("true")},
				{xT("ENV_TEST_4"), xT("true")},

				{xT("OS"),         xT("true") },
				{xT("XXXL"),       xT("false")},
				{xT("windir"),     xT("true") }
			};
		#elif xENV_UNIX
			std::ctstring_t data[][2]
			{
				{xT("ENV_TEST_1"), xT("true")},
				{xT("ENV_TEST_2"), xT("true")},
				{xT("ENV_TEST_3"), xT("true")},
				{xT("ENV_TEST_4"), xT("true")},
			};
		#endif

			for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
				Env env(it_prefix, data[i][0]);

				bool_t bStr1 = env.isExists();
				xTEST_EQ(String::castBool(data[i][1]), bStr1);
			}
		}
	}

	xTEST_CASE("value")
	{
		for (const auto &it_prefix : prefixes) {
		#if   xENV_WIN
			std::ctstring_t data[][2]
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")},
			};
		#elif xENV_UNIX
			std::ctstring_t data[][2]
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")}
			};
		#endif

			for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
				Env env(it_prefix, data[i][0]);

				std::tstring_t str1 = env.value();
				std::tstring_t str2 = data[i][1];
				xTEST_EQ(str1, str2);
			}
		}
	}

	xTEST_CASE("remove")
	{
		for (const auto &it_prefix : prefixes) {
			std::ctstring_t data[][2]
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")}
			};

			for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
				Env env(it_prefix, data[i][0]);
				env.remove();

				xTEST(!env.isExists());
			}
		}
	}

	/**************************************************
	* Envs
	*
	**************************************************/

	xTEST_CASE("Envs::setVars")
	{
		for (const auto &it_prefix : prefixes) {
			const std::set<std::pair_tstring_t> vars
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")}
			};

			Envs envs(it_prefix);
			envs.setVars(vars);
		}
	}

	xTEST_CASE("Envs::vars")
	{
		for (const auto &it_prefix : prefixes) {
			Envs envs(it_prefix);
			m_vsRv = envs.vars();
			xTEST(!m_vsRv.empty());
		}
	}

	xTEST_CASE("Envs::findFirstOf")
	{
		for (const auto &it_prefix : prefixes) {
			std::ctstring_t envName = xT("XLIB_ENV_2");

			Env env(it_prefix, envName);
			env.setValue("2");

			const data2_tstring_t datas[]
			{
				{xT("__XLIB_ENV_1"), {}},
				{ envName,           xT("2")},
				{xT("__XLIB_ENV_3"), {}}
			};

			for (const auto &[it_test, it_expect] : datas) {
				std::cvec_tstring_t findEnvs = {xT("XLIB_ENV_1"), it_test, xT("XLIB_ENV_3")};

				Envs envs(it_prefix);
				m_sRv = envs.findFirstOf(findEnvs);
				xTEST_EQ(m_sRv, it_expect);
			}
		}
	}


	xTEST_CASE("Envs::expandVars")
	{
	#if   xENV_WIN
		std::ctstring_t data[][2]
		{
			{xT(" System root: %SystemRoot%"),  xT(" System root: C:\\Windows")},
			{xT("Windows Dir: %windir% "),      xT("Windows Dir: C:\\Windows ")}
		};
	#elif xENV_UNIX
		std::ctstring_t data[][2]
		{
			{xT("111%ENV_TEST_1%"),    xT("111value1")},
			{xT("%ENV_TEST_2%111"),    xT("value2111")},
			{xT("ttt%ENV_TEST_3%"),    xT("tttvalue3")},
			{xT("rrr%ENV_TEST_4%rrr"), xT("rrrvalue4rrr")}
		};
	#endif

		for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
			std::tstring_t str1 = Envs::expandVars(data[i][0]);
			std::tstring_t str2 = data[i][1];
			xTEST(StringCI::compare(str1, str2));
		}
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
