/**
 * \file  ILog.cpp
 * \brief logging
 */


#include "ILog.h"


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
	switch (a_level) {
	case Level::Trace:    return xT("TRACE   ");
	case Level::Debug:    return xT("DEBUG   ");
	case Level::Info:     return xT("INFO    ");
	case Level::Warning:  return xT("WARNING ");
	case Level::Error:    return xT("ERROR   ");
	case Level::Critical: return xT("CRITICAL");
	}

	return {};
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
ILog::_levelIcon(
	cLevel a_level
) const
{
	switch (a_level) {
	case Level::Trace:    return xT("🔍 ");
	case Level::Debug:    return xT("🛠️ ");
	case Level::Info:     return xT("ℹ️ ");
	case Level::Warning:  return xT("⚠️ ");
	case Level::Error:    return xT("❌");
	case Level::Critical: return xT("❗");
	}

	return {};
}
//-------------------------------------------------------------------------------------------------

} // namespace
