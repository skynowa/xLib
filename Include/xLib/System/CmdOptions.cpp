/**
 * \file   CmdOptions.cpp
 * \brief  Command-line options parser
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "CmdOptions.h"
#endif


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
	cint_t                              a_argc,
	cptr_ctchar_t                       a_argv[],
	const std::vector<CmdOptionsUsage> &a_usage
)
{

}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
