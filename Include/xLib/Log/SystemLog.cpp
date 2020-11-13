/**
 * \file   SystemLog.inl
 * \brief  logging to system log
 */


#include "SystemLog.h"

#include <xLib/Core/FormatC.h>
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
    _construct_impl( Path( Path::exe() ).fileBaseName() );
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
    write(xT("%s"), _oss.str().c_str());

    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
SystemLog::write(
    cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),        return);
    xCHECK_DO(a_format == nullptr, return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = FormatC::strV(a_format, args);
    xVA_END(args);

    write(Level::lvPlain, xT("%s"), msg.c_str());
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

    Level level = Level::lvUnknown;
    {
        xCHECK_DO(a_level == Level::lvPlain, level = Level::lvInfo);
    }

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
