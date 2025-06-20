/**
 * \file  SystemLog.cpp
 * \brief logging to system log
 */


#include "SystemLog.h"

#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Fs/Path.h>
#include "Platform/SystemLog_internal.inl"

#if   xENV_WIN
    #include "Platform/Win/SystemLog_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/SystemLog_unix.inl"

    #if   xENV_LINUX
        #if   xOS_LINUX

        #elif xOS_ANDROID
            #include "Platform/Linux/SystemLog_android.inl"
        #endif
    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


namespace xl::log
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
SystemLog::SystemLog()
{
    _ctor_impl( Path::exe().fileBaseName() );
}
//-------------------------------------------------------------------------------------------------
SystemLog::SystemLog(
    std::ctstring_t &a_logName
)
{
    _ctor_impl(a_logName);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
SystemLog::~SystemLog()
{
    _dtor_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
SystemLog::write(
    cLevel           a_level,
    std::ctstring_t &a_msg
) const /* final */
{
    xCHECK_DO(!_isEnable, return);

    _write_impl(a_level, a_msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace
