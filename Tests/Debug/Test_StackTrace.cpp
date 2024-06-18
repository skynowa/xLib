/**
 * \file  Test_StackTrace.cpp
 * \brief test StackTrace
 */


#include <xLib/xLib.h>

#if __has_include(<boost/version.hpp>)
	#include <boost/version.hpp>
#endif

#if defined(BOOST_VERSION)
	#define BOOST_STACKTRACE_USE_ADDR2LINE 1
	#include <boost/stacktrace.hpp>
#endif
//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_StackTrace)
//-------------------------------------------------------------------------------------------------
bool_t
foo(
	const bool                        a_bool = false,
	const std::size_t                 a_int = 10U,
	const double                      a_float = 300.0,
	const std::string                &a_string = "str",
	const std::map<int, std::string> &a_map = {}
)
{
	xUNUSED(a_bool);
	xUNUSED(a_int);
	xUNUSED(a_float);
	xUNUSED(a_string);
	xUNUSED(a_map);

	// StackTrace
	{
		cStackTraceData data
		{
			.skipFramesNum     {0},
			.isWrapFilePaths   {false},
			.isFuncArgsDisable {true}
		};

		StackTrace stack(data);
		const auto &sRv = stack.str();
		xCHECK_RET(sRv.empty(), false);

		Cout() << "\n:::::::::: StackTrace ::::::::::\n";
		Cout() << sRv << "\n";
	}

	// boost::stacktrace::stacktrace()
	{
	#if defined(BOOST_VERSION)
		const auto &aRv = boost::stacktrace::stacktrace();
		xCHECK_RET(aRv.as_vector().empty(), false);

		std::tcout << "\n:::::::::: boost::stacktrace ::::::::::\n\n";
		std::tcout << aRv << "\n\n";
	#endif
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_StackTrace::unit()
{
    xTEST_CASE("str")
    {
        m_bRv = ::foo();
        xTEST(m_bRv);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
