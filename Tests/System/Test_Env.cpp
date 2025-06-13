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
	std::ctstring_t nss[]
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

	xTEST_CASE("ctor - path")
	{
		auto env = Env::path();
		xTEST(!env.value().empty());
	}

	xTEST_CASE("str")
	{
		for (const auto &it_ns : nss) {
			const std::map_tstring_t vars
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")}
			};

			for (const auto &[it_var, it_value] : vars) {
				Env env(it_ns, it_var);
				env.setValue(it_value);

				const auto &test     = env.str();
				const auto &expected = it_ns + it_var + Const::equal() + it_value;
				xTEST_EQ(test, expected);
			}
		}
	}

	xTEST_CASE("setValue")
	{
		for (const auto &it_ns : nss) {
			std::ctstring_t data[][2]
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")}
			};

			for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
				Env env(it_ns, data[i][0]);
				env.setValue(data[i][1]);

				xTEST(env.isExists());
			}
		}
	}

	xTEST_CASE("isExists")
	{
		for (const auto &it_ns : nss) {
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
				Env env(it_ns, data[i][0]);

				bool_t bStr1 = env.isExists();
				xTEST_EQ(String::castBool(data[i][1]), bStr1);
			}
		}
	}

	xTEST_CASE("value")
	{
		for (const auto &it_ns : nss) {
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
				Env env(it_ns, data[i][0]);

				std::tstring_t str1 = env.value();
				std::tstring_t str2 = data[i][1];
				xTEST_EQ(str1, str2);
			}
		}
	}

	xTEST_CASE("remove")
	{
		for (const auto &it_ns : nss) {
			std::ctstring_t data[][2]
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")}
			};

			for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
				Env env(it_ns, data[i][0]);
				env.remove();

				xTEST(!env.isExists());
			}
		}
	}

	/**************************************************
	* Envs
	*
	**************************************************/

	xTEST_CASE("Envs::setVars(envFilePath)")
	{
		std::ctstring_t ns          = xT("SKYNOWA_");
		std::ctstring_t envFilePath = option().testDirPath + xT("/System/env_1.txt");
		// TODO: env_2.txt
		// std::ctstring_t envFilePath = option().testDirPath + xT("/System/env_2.txt");

		const std::map_tstring_t vars
		{
			{xT("DB_HOST"),     xT("127.0.0.1")},
			{xT("DB_PASSWORD"), xT("secret")},
			{xT("DB_USER"),     xT("admin")},
			{xT("X_APIKEY"),    xT("xyz")},
			{xT("Y_APIKEY"),    xT("abc")}
		};

		Envs envs(ns);
		envs.setVars(envFilePath);
		// LogCout() << xTRACE_VAR(envs.vars());

		for (const auto &[it_name, it_value] : vars) {
			xTEST_EQ(envs[it_name], it_value);
		}
	}

	xTEST_CASE("Envs::setVars(vars)")
	{
		for (const auto &it_ns : nss) {
			const std::map_tstring_t vars
			{
				{xT("ENV_TEST_1"), xT("value1")},
				{xT("ENV_TEST_2"), xT("value2")},
				{xT("ENV_TEST_3"), xT("value3")},
				{xT("ENV_TEST_4"), xT("value4")}
			};

			Envs envs(it_ns);
			envs.setVars(vars);
		}
	}

	xTEST_CASE("Envs::vars")
	{
		for (const auto &it_ns : nss) {
			Envs envs(it_ns);
			const auto spRv = envs.vars();
			xTEST(!spRv.empty());
		}
	}

	xTEST_CASE("Envs::findFirstOf")
	{
		for (const auto &it_ns : nss) {
			std::ctstring_t envName = xT("XLIB_ENV_2");

			Env env(it_ns, envName);
			env.setValue("2");

			const data2_tstring_t datas[]
			{
				{xT("__XLIB_ENV_1"), {}},
				{ envName,           xT("2")},
				{xT("__XLIB_ENV_3"), {}}
			};

			for (const auto &[it_test, it_expect] : datas) {
				std::cvec_tstring_t findEnvs = {xT("XLIB_ENV_1"), it_test, xT("XLIB_ENV_3")};

				Envs envs(it_ns);
				m_sRv = envs.findFirstOf(findEnvs);
				xTEST_EQ(m_sRv, it_expect);
			}
		}
	}

	xTEST_CASE("Envs::operator []")
	{
		for (const auto &it_ns : nss) {
			std::ctstring_t envName = xT("XLIB_ENV_2");

			Env env(it_ns, envName);
			env.setValue("2");

			const data2_tstring_t datas[]
			{
				{xT("__XLIB_ENV_1"), {}},
				{ envName,           xT("2")},
				{xT("__XLIB_ENV_3"), {}}
			};

			for (const auto &[it_test, it_expect] : datas) {
				Envs envs(it_ns);
				m_sRv = envs[it_test];
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
