/**
 * \file   Test_CmdOptions.cpp
 * \brief  test CmdOptions
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_CmdOptions)
xTEST_UNIT(Test_CmdOptions)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_CmdOptions::unit()
{
    xTEST_CASE("CmdOptions::CmdOptions")
    {
		std::vector<CmdOptionsUsage> usage;
		usage.push_back(
			{
				CmdOptionsUsage::Enabled,
				CmdOptionsUsage::Mandatory,
				"c",
				"create",
				"",
				"--create  Tells the program to create something."
			});

		cint_t        argc       = 3;
		cptr_ctchar_t argv[argc] = {"a=1 b=2 c=3"};

		CmdOptions cmdOptions;
		cmdOptions.parse(argc, argv, usage);

    }

    return true;
}
//-------------------------------------------------------------------------------------------------
