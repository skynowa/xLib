/**
 * \file  SystemLog.cpp
 * \brief logging to system log
 */


#include "SystemLog.h"

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
#if 0
	write(ILog::Level::Trace, xT("%s"), _oss.str().c_str()); /// TODO: fix
#else
	_write_impl(ILog::Level::Trace, xT(""));
#endif

    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
SystemLog::write(
    cLevel        a_level,
    cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!isEnabled(), return);
    xTEST_PTR(a_format);

    const auto level = (a_level == Level::Trace) ? Level::Info : Level::Off;

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = FormatC::strV(a_format, args);
        xVA_END(args);
    }

    _write_impl(level, msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace
