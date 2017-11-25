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
ILog::ILog() :
    _isEnable(true)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
ILog::~ILog()
{
}
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
    cLevel &a_level
) const
{
    std::tstring_t sRv;

    switch (a_level) {
    case lvEmerg:
        sRv = xT("Emerg");
        break;
    case lvAlert:
        sRv = xT("Alert");
        break;
    case lvCritical:
        sRv = xT("Critical");
    break;
    case lvError:
        sRv = xT("Error");
        break;
    case lvWarning:
        sRv = xT("Warning");
        break;
    case lvNotice:
        sRv = xT("Notice");
    break;
    case lvInfo:
        sRv = xT("Info");
        break;
    case lvDebug:
        sRv = xT("Debug");
        break;
    case lvPlain:
        sRv = xT("");
        break;
    case lvUnknown:
    default:
        sRv = xT("Unknown");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, log)
