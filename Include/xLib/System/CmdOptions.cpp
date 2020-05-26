/**
 * \file   CmdOptions.cpp
 * \brief  Command-line options parser
 */


#include "CmdOptions.h"

#include <xLib/Core/String.h>
#include <xLib/System/ProcessInfo.h>

xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

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
	// a_args: {host-name=0, date=0, time=1}

	for (auto &it_arg : a_args) {
		std::vec_tstring_t items;
		String::split(it_arg, xT("="), &items);

		Cout() << xTRACE_VAR(items);
	} // for (a_args)
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
