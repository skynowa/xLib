/**
 * \file  Test_StackTrace.cpp
 * \brief test StackTrace
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_StackTrace)
//-------------------------------------------------------------------------------------------------
std::tstring_t
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

	StackTraceData data
	{
		.skipFramesNum       {0},
		.isWrapFilePaths     {false},
		.isFuncParamsDisable {true}
	};

    StackTrace stack(data);

    std::tstring_t sRv = stack.str();
    Cout() << "\n" << sRv << "\n";

	return sRv;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_StackTrace::unit()
{
    xTEST_CASE("str")
    {
        m_sRv = ::foo();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
