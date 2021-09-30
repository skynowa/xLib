/**
 * \file  ILog.h
 * \brief logging interface_
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
bool_t
ILog::isEnabled() const
{
    return _isEnable;
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
#if 1
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
	case Level::Fatal:
		sRv = xT("Fatal");
		break;
	}

	return sRv;
#else
	static const std::map<Level, std::tstring_t> levels
	{
		{Level::Off,     xT("Off")},
		{Level::Trace,   xT("Trace")},
		{Level::Debug,   xT("Debug")},
		{Level::Info,    xT("Info")},
		{Level::Warning, xT("Warning")},
		{Level::Error,   xT("Error")},
		{Level::Fatal,   xT("Fatal")}
	};

	const auto &it = levels.find(a_level);
	if (it == levels.cend()) {
		return {};
	}

    return it->second;
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace
