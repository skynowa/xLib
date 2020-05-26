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

    xNO_COPY_ASSIGN(CmdOptions)

    void_t   parse(cint_t argsNum, cptr_ctchar_t argv[], const std::vector<CmdOptionsUsage> &usage);
        ///< parse cmd options (to std::map)
    void_t   parse(std::cvec_tstring_t &args, const std::vector<CmdOptionsUsage> &usage);
        ///< parse cmd options (to std::map)

private:
    std::map_tstring_t _params;
};

xNAMESPACE_END2(xl, system)
//-------------------------------------------------------------------------------------------------
/**
 * FEATURES:
 * -
 *
 * FAQ:
 * - https://github.com/CppMicroServices/CppMicroServices/blob/development/third_party/optionparser.h
 * - https://github.com/CLIUtils/CLI11
 * - https://github.com/docopt
 * - https://github.com/jarro2783/cxxopts
 *
 * TODO:
 * -
 */
//-------------------------------------------------------------------------------------------------
