/**
 * \file   CmdOptions.h
 * \brief  Command-line options parser
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, system)

struct CmdOptionsUsage
    /// CmdOptions usage
{
	enum EnableType
	{
		Disabled = 0,
		Enabled  = 1
	};

	enum MandatoryType
	{
		Optional  = 0,
		Mandatory = 1
	};

	EnableType     enableType;
	MandatoryType  mandatoryType;
	std::tstring_t optShort;
	std::tstring_t optLong;
	std::tstring_t args;
	std::tstring_t help;
};
xTYPEDEF_CONST(CmdOptionsUsage);

class CmdOptions
    ///< Command-line options parser
{
public:
             CmdOptions();
        ///< constructor
    virtual ~CmdOptions();
        ///< destructor

    void_t   parse(cint_t argsNum, cptr_ctchar_t argv[], const std::vector<CmdOptionsUsage> &usage);

private:
    xNO_COPY_ASSIGN(CmdOptions)
};

xNAMESPACE_END2(xlib, system)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "CmdOptions.cpp"
#endif
