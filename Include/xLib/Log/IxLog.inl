/**
 * \file  IxLog.h
 * \brief logging interface
 */


xNAMESPACE_BEGIN2(xlib, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
IxLog::IxLog() :
    _isEnable(true)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
IxLog::~IxLog()
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
IxLog::setEnabled(
    cbool_t &a_flag
)
{
    _isEnable = a_flag;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
IxLog::isEnabled() const
{
    return _isEnable;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
IxLog::_levelString(
    cExLevel &a_level
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

xNAMESPACE_END2(xlib, log)
