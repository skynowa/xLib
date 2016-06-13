/**
 * \file  ILog.h
 * \brief logging interface
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "ILog.h"
#endif


xNAMESPACE_BEGIN2(xlib, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
ILog::ILog() :
    _isEnable(true)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
ILog::~ILog()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
ILog::setEnabled(
    cbool_t &a_flag
)
{
    _isEnable = a_flag;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
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
xINLINE std::tstring_t
ILog::_levelString(
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
