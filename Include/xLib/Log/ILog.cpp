/**
 * \file  ILog.h
 * \brief logging interface
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
    std::tstring_t sRv;

    switch (a_level) {
    case Level::Emerg:
        sRv = xT("Emerg");
        break;
    case Level::Alert:
        sRv = xT("Alert");
        break;
    case Level::Critical:
        sRv = xT("Critical");
    break;
    case Level::Error:
        sRv = xT("Error");
        break;
    case Level::Warning:
        sRv = xT("Warning");
        break;
    case Level::Notice:
        sRv = xT("Notice");
    break;
    case Level::Info:
        sRv = xT("Info");
        break;
    case Level::Debug:
        sRv = xT("Debug");
        break;
    case Level::Plain:
        sRv = xT("");
        break;
    case Level::Unknown:
        sRv = xT("Unknown");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
