/**
 * \file   SystemLog.inl
 * \brief  logging to system log
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "SystemLog.h"
#endif

#include <xLib/Core/FormatC.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
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


xNAMESPACE_BEGIN2(xl, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
SystemLog::SystemLog()
#if xENV_WIN
    :
    _handle(xNATIVE_HANDLE_NULL)
#endif
{
    _construct_impl( Path( Path::exe() ).fileBaseName() );
}
//-------------------------------------------------------------------------------------------------
xINLINE
SystemLog::SystemLog(
    std::ctstring_t &a_logName
)
#if xENV_WIN
    :
    _handle(xNATIVE_HANDLE_NULL)
#endif
{
    _construct_impl(a_logName);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
SystemLog::~SystemLog()
{
    write(xT("%s"), _oss.str().c_str());

    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
SystemLog::write(
    cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),          return);
    xCHECK_DO(a_format == xPTR_NULL, return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = FormatC::strV(a_format, args);
    xVA_END(args);

    write(lvPlain, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
SystemLog::write(
    cLevel        &a_level,
    cptr_ctchar_t  a_format, ...
) const
{
    xCHECK_DO(!isEnabled(), return);
    xTEST_PTR(a_format);

    Level level = lvUnknown;
    {
        xCHECK_DO(a_level == lvPlain, level = lvInfo);
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

xNAMESPACE_END2(xl, log)
