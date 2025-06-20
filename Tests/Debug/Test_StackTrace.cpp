/**
 * \file  Test_StackTrace.cpp
 * \brief test StackTrace
 */


#include <xLib/xLib.h>

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
		cStackTraceOption option
		{
			.skipFramesNum     {2},
			.isReverse         {false},
			.isWrapFilePaths   {false},
			.isFuncArgsDisable {true}
		};

		StackTrace stack(option);
		const auto &sRv = stack.str();
		xCHECK_RET(sRv.empty(), false);

		LogCout() << "\n:::::::::: StackTrace ::::::::::\n";
		LogCout() << sRv << "\n";
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
