/**
 * \file   SystemLog.inl
 * \brief  logging to system log
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "SystemLog.h"
#endif

#include <xLib/Core/String.h>
#include <xLib/IO/Path.h>
#include "Platform/SystemLog_internal.inl"

#if   xENV_WIN
    #include "Platform/Win/SystemLog_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #if   xOS_LINUX
            #include "Platform/Unix/SystemLog_unix.inl"
        #elif xOS_ANDROID
            #include "Platform/Linux/SystemLog_android.inl"
        #endif
    #elif xENV_BSD
        #include "Platform/Unix/SystemLog_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/SystemLog_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, log)

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
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),          return);
    xCHECK_DO(a_format == xPTR_NULL, return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = String::formatV(a_format, args);
    xVA_END(args);

    write(lvPlain, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
SystemLog::write(
    cExLevel &a_level,
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(), return);
    xTEST_PTR(a_format);

    ExLevel level = lvUnknown;
    {
        xCHECK_DO(a_level == lvPlain, level = lvInfo);
    }

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = String::formatV(a_format, args);
        xVA_END(args);
    }

    _write_impl(level, msg);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, log)
