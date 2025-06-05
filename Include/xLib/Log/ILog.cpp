/**
 * \file  ILog.cpp
 * \brief logging
 */


#include "ILog.h"

#include <xLib/Core/VaList.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Debug/Debug.h>

namespace xl::log
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
ILog::~ILog()
{
}
//-------------------------------------------------------------------------------------------------
void_t
ILog::setEnabled(
    cbool_t a_flag
)
{
    _isEnable = a_flag;
}
//-------------------------------------------------------------------------------------------------
void_t
ILog::trace(
	cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	VaList args(a_format);
	std::ctstring_t msg = FormatC::strV(a_format, args.get());
#else
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);
#endif

    write(Level::Trace, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
void_t
ILog::debug(
	cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	VaList args(a_format);
	std::ctstring_t msg = FormatC::strV(a_format, args.get());
#else
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);
#endif

    write(Level::Debug, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
void_t
ILog::info(
	cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	VaList args(a_format);
	std::ctstring_t msg = FormatC::strV(a_format, args.get());
#else
    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = FormatC::strV(a_format, args);
    xVA_END(args);
#endif

    write(Level::Info, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
void_t
ILog::warning(
	cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	VaList args(a_format);
	std::ctstring_t msg = FormatC::strV(a_format, args.get());
#else
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);
#endif

    write(Level::Warning, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
void_t
ILog::error(
	cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	VaList args(a_format);
	std::ctstring_t msg = FormatC::strV(a_format, args.get());
#else
    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = FormatC::strV(a_format, args);
    xVA_END(args);
#endif

    write(Level::Error, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
void_t
ILog::critical(
	cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!_isEnable,          return);
    xCHECK_DO(a_format == nullptr, return);

#if 0
	VaList args(a_format);
	std::ctstring_t msg = FormatC::strV(a_format, args.get());
#else
	std::tstring_t msg;

	va_list args;
	xVA_START(args, a_format);
	msg = FormatC::strV(a_format, args);
	xVA_END(args);
#endif

    write(Level::Critical, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
ILog::_levelString(
    cLevel a_level
) const
{
	std::tstring_t sRv;

	switch (a_level) {
	case Level::Off:
		sRv = xT("Off");
		break;
	case Level::Trace:
		sRv = xT("Trace");
		break;
	case Level::Debug:
		sRv = xT("Debug");
		break;
	case Level::Info:
		sRv = xT("Info");
		break;
	case Level::Warning:
		sRv = xT("Warning");
		break;
	case Level::Error:
		sRv = xT("Error");
		break;
	case Level::Critical:
		sRv = xT("Critical");
		break;
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
