/**
 * \file   CxSystemLog.inl
 * \brief  logging to system log
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include "Platform/CxSystemLog_internal.inl"

#if   xENV_WIN
    #include "Platform/Win/CxSystemLog_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxSystemLog_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxSystemLog_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxSystemLog_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxSystemLog::CxSystemLog()
#if xENV_WIN
    :
    _handle(xPTR_NULL)
#endif
{
    _construct_impl( CxPath( CxPath::exe() ).fileBaseName() );
}
//-------------------------------------------------------------------------------------------------
inline
CxSystemLog::CxSystemLog(
    std::ctstring_t &a_logName
)
#if xENV_WIN
    :
    _handle   (xPTR_NULL)
#endif
{
    _construct_impl(a_logName);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxSystemLog::~CxSystemLog()
{
    write(xT("%s"), _oss.str().c_str());

    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
template<class T>
inline CxSystemLog &
CxSystemLog::operator << (const T &valueT)
{
    _oss << valueT;
    return *this;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxSystemLog::write(
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),          return);
    xCHECK_DO(a_format == xPTR_NULL, return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = CxString::formatV(a_format, args);
    xVA_END(args);

    write(lvPlain, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxSystemLog::write(
    cExLevel &a_level,
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(), return);
    xTEST_PTR(a_format);
#if xENV_WIN
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);
#endif

    ExLevel level = lvUnknown;
    {
        xCHECK_DO(a_level == lvPlain, level = lvInfo);
    }

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = CxString::formatV(a_format, args);
        xVA_END(args);
    }

    _write_impl(level, msg);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, log)
