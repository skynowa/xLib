/**
 * \file  ILog.h
 * \brief logging interface
 */


#include "ILog.h"


xNAMESPACE_BEGIN2(xl, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
ILog::setEnabled(
    cbool_t &a_flag
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
    case Level::lvEmerg:
        sRv = xT("Emerg");
        break;
    case Level::lvAlert:
        sRv = xT("Alert");
        break;
    case Level::lvCritical:
        sRv = xT("Critical");
    break;
    case Level::lvError:
        sRv = xT("Error");
        break;
    case Level::lvWarning:
        sRv = xT("Warning");
        break;
    case Level::lvNotice:
        sRv = xT("Notice");
    break;
    case Level::lvInfo:
        sRv = xT("Info");
        break;
    case Level::lvDebug:
        sRv = xT("Debug");
        break;
    case Level::lvPlain:
        sRv = xT("");
        break;
    case Level::lvUnknown:
    default:
        sRv = xT("Unknown");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, log)
