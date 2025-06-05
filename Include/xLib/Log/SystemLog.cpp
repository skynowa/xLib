/**
 * \file  SystemLog.cpp
 * \brief logging to system log
 */


#include "SystemLog.h"

#include <xLib/Core/VaList.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
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
    _construct_impl( Path::exe().fileBaseName() );
}
//-------------------------------------------------------------------------------------------------
SystemLog::SystemLog(
    std::ctstring_t &a_logName
)
{
    _construct_impl(a_logName);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
SystemLog::~SystemLog()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
SystemLog::write(
    cLevel        a_level,
    cptr_ctchar_t a_format, ...
) const /* final */
{
    xCHECK_DO(!_isEnable, return);
    xTEST_PTR(a_format);

    const auto level = (a_level == ILog::Level::Trace) ? ILog::Level::Info : ILog::Level::Off;

    std::tstring_t msg;
    {
		VaList args(a_format);
		msg = FormatC::strV(a_format, args.get());
    }

    _write_impl(level, msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace
