/**
 * \file   CmdOptions.cpp
 * \brief  Command-line options parser
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "CmdOptions.h"
#endif

#include <xLib/System/ProcessInfo.h>
#include <xLib/Log/Trace.h>


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CmdOptions::CmdOptions()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE
CmdOptions::~CmdOptions()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE
void_t
CmdOptions::parse(
	cint_t                              a_argsNum,
	cptr_ctchar_t                       a_argv[],
	const std::vector<CmdOptionsUsage> &a_usage
)
{
    std::vec_tstring_t args;
    ProcessInfo::commandLine(a_argsNum, a_argv, &args);

    Trace() << xTRACE_VAR(args) << "\n";
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
