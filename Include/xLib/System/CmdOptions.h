/**
 * \file   CmdOptions.h
 * \brief  Command-line options parser
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, system)

struct CmdOptionsUsage
    /// CmdOptions usage
{
	enum class EnableType
	{
		Disabled = 0,
		Enabled  = 1
	};
	xUSING_CONST(EnableType);

	enum class MandatoryType
	{
		Optional  = 0,
		Mandatory = 1
	};
	xUSING_CONST(MandatoryType);

	EnableType     enableType;
	MandatoryType  mandatoryType;
	std::tstring_t optShort;
	std::tstring_t optLong;
	std::tstring_t args;
	std::tstring_t help;
};
xUSING_CONST(CmdOptionsUsage);

class CmdOptions
    ///< Command-line options parser
{
public:
             CmdOptions() = default;
        ///< constructor
    virtual ~CmdOptions() = default;
        ///< destructor

    void_t   parse(cint_t argsNum, cptr_ctchar_t argv[], const std::vector<CmdOptionsUsage> &usage);
        ///< parse cmd options
    void_t   parse(std::cvec_tstring_t &args, const std::vector<CmdOptionsUsage> &usage);
        ///< parse cmd options

private:
    xNO_COPY_ASSIGN(CmdOptions)
};

xNAMESPACE_END2(xl, system)
//-------------------------------------------------------------------------------------------------
/**
 * FAQ:
 * - https://github.com/CLIUtils/CLI11
 */
//-------------------------------------------------------------------------------------------------
