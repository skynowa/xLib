/**
 * \file   Signal.cpp
 * \brief  signal
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Signal.h"
#endif

#if   xENV_WIN
    #include "Platform/Win/Signal_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Signal_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Unix/Signal_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Unix/Signal_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Signal_apple.inl"
    #endif
#endif

#include <xLib/Core/String.h>
#include <xLib/Core/Utils.h>
#include <xLib/Log/Trace.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::sig_atomic_t
Signal::state() const
{
    return _state;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::setState(
    const std::sig_atomic_t &a_state
)
{
    // TODO: [Android] SIG_ATOMIC_MIN, SIG_ATOMIC_MAX
#if xTODO_ANDROID
    xTEST_EQ(a_state >= SIG_ATOMIC_MIN && a_state <= SIG_ATOMIC_MAX, true);
#endif
    _state = a_state;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connect(
    const std::vector<int_t> &a_signalNums,
    const sighandler_t       &a_onSignals
) const
{
   /**
    * FAQ: set handlers
    *
    * https://gist.github.com/jvranish/4441299
    */

    xFOR_EACH_CONST(std::vector<int_t>, it, a_signalNums) {
        switch (*it) {
        case SIGKILL:
            Trace() << xT("xLib: ") << xTRACE_VAR(SIGKILL) << xT(" cannot be caught or ignored");
            continue;
            break;
        case SIGSTOP:
            Trace() << xT("xLib: ") << xTRACE_VAR(SIGSTOP) << xT(" cannot be caught or ignored");
            continue;
            break;
        default:
            break;
        }

    #if USE_SIMPLE_SIGNAL
        sighandler_t shRv = std::signal(*it, a_onSignals);
        xTEST_MSG(shRv != SIG_ERR, xT("Signal: ") + String::cast(*it));
    #else
        int_t iRv = 0;

        struct sigaction action; xSTRUCT_ZERO(action);
        action.sa_handler  = a_onSignals;

        iRv = ::sigemptyset(&action.sa_mask);
        xTEST_DIFF(iRv, - 1);

        action.sa_flags    = SA_SIGINFO;
        action.sa_restorer = xPTR_NULL;

        iRv = ::sigaction(*it, &action, xPTR_NULL);
        xTEST_DIFF_MSG(iRv, - 1, xT("Signal: ") + String::cast(*it));
    #endif
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connectExit(
    const exit_handler_t &a_onExit
) const
{
    xCHECK_DO(a_onExit == xPTR_NULL, return);

    int_t iRv = std::atexit(a_onExit);
    xTEST(iRv == 0);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connectTerminate(
    const std::terminate_handler &a_onTerminate
) const
{
    xTEST_PTR(a_onTerminate);

    std::terminate_handler handler_old = std::set_terminate(a_onTerminate);
    xUNUSED(handler_old);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connectUnexpected(
    const std::unexpected_handler &a_onUnexpected
) const
{
    xTEST_PTR(a_onUnexpected);

    std::unexpected_handler handler_old = std::set_unexpected(a_onUnexpected);
    xUNUSED(handler_old);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::raise(
    cint_t &a_signalNum
) const
{
    int_t iRv = std::raise(a_signalNum);
    xTEST(iRv == 0);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Signal::decription(
    cint_t &a_signalNum ///< signal number
)
{
    return String::format(xT("%d - %s"), a_signalNum, _decription_impl(a_signalNum).c_str());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
