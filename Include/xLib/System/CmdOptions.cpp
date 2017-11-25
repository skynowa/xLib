/**
 * \file   CmdOptions.cpp
 * \brief  Command-line options parser
 */


#include "CmdOptions.h"

#include <xLib/System/ProcessInfo.h>

#if 1
    #include <xLib/Core/Format.h>
    #include <xLib/Log/Trace.h>
#endif


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
CmdOptions::CmdOptions()
{
}
//-------------------------------------------------------------------------------------------------
CmdOptions::~CmdOptions()
{
}
//-------------------------------------------------------------------------------------------------
void_t
CmdOptions::parse(
	cint_t                              a_argsNum,
	cptr_ctchar_t                       a_argv[],
	const std::vector<CmdOptionsUsage> &a_usage
)
{
    std::vec_tstring_t args;
    ProcessInfo::commandLine(a_argsNum, a_argv, &args);

    parse(args, a_usage);
}
//-------------------------------------------------------------------------------------------------
void_t
CmdOptions::parse(
	std::cvec_tstring_t                &a_args,
	const std::vector<CmdOptionsUsage> &a_usage
)
{
    // Trace() << xTRACE_VAR(a_args) << "\n";
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
