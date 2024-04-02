/**
 * \file   Test_CmdOptions.cpp
 * \brief  test CmdOptions
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_CmdOptions)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_CmdOptions::unit()
{
    xTEST_CASE("CmdOptions::CmdOptions")
    {
        std::vector<CmdOptionsUsage> usage;
        {
            cCmdOptionsUsage cmdOption =
            {
                CmdOptionsUsage::EnableType::Yes,
                CmdOptionsUsage::MandatoryType::Yes,
                "c",
                "create",
                "",
                "--create  Tells the program to create something."
            };

            usage.push_back(cmdOption);
        }

        cint_t        argc       = 3;
        cptr_ctchar_t argv[argc] =
        {
            "-a=1",
            "-b=2",
            "-c"
        };

        CmdOptions cmdOptions;
        cmdOptions.parse(argc, argv, usage);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
