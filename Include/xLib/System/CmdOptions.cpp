/**
 * \file   CmdOptions.cpp
 * \brief  Command-line options parser
 */


#include "CmdOptions.h"

#include <xLib/Core/String.h>
#include <xLib/System/ProcessInfo.h>

namespace xl::system
{

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
	xCHECK_DO(a_args.empty(), return);

	// TODO: a_usage - impl
	xUNUSED(a_usage);

	// a_args: {host-name=0, date=0, time=1, test, =}
	// LogCout() << xTRACE_VAR(a_args);

	std::cstring_t delimiter = xT("=");

	for (const auto &it_arg : a_args) {
		std::vec_tstring_t items;
		String::split(it_arg, delimiter, &items);

		switch ( items.size() ) {
		case 0:
			continue;
			break;
		case 1:
			{
				auto &key = items[0];
				xCHECK_DO(key.empty(), continue);

				_params.insert( {key, {}} );
			}
			break;
		case 2:
		default:
			{
				auto &key = items[0];
				xCHECK_DO(key.empty(), continue);

				_params.insert( {key, items[1]} );
			}
			break;
		}
	} // for (a_args)

	// LogCout() << xTRACE_VAR(_params);
}
//-------------------------------------------------------------------------------------------------

} // namespace
