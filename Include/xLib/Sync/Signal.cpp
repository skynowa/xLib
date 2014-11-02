/**
 * \file   Signal.cpp
 * \brief  signal
 */


#if !xOPTION_HEADER_ONLY
    #include "Signal.h"
#endif

#if   xENV_WIN
    #include "Platform/Win/Signal_win.inl"
#elif xENV_UNIX
    // #include "Platform/Unix/Signal_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Unix/Signal_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Unix/Signal_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Signal_apple.inl"
    #endif
#endif

#include <xLib/Core/Utils.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::sig_atomic_t
Signal::state() const
{
    return _signal_state;
}
//-------------------------------------------------------------------------------------------------
inline void_t
Signal::setState(
    const std::sig_atomic_t &a_state
)
{
    xTEST_EQ(a_state >= SIG_ATOMIC_MIN && a_state <= SIG_ATOMIC_MAX, true);

    _signal_state = a_state;
}
//-------------------------------------------------------------------------------------------------
inline void_t
Signal::connect(
    const std::vector<int_t> &a_signalNums,
    sighandler_t              a_handler
) const
{
   /**
    * FAQ: set handlers
    *
    * https://gist.github.com/jvranish/4441299
    */

    xFOREACH_CONST(std::vector<int_t>, it, a_signalNums) {
    #if USE_SIMPLE_SIGNAL
        sighandler_t shRv = std::signal(*it, a_handler);
        xTEST(shRv != SIG_ERR);
    #else
        int_t iRv = 0;

        struct sigaction action; xSTRUCT_ZERO(action);
        action.sa_handler  = a_handler;

        iRv = ::sigemptyset(&action.sa_mask);
        xTEST_DIFF(iRv, - 1);

        action.sa_flags    = SA_SIGINFO;
        action.sa_restorer = xPTR_NULL;

        iRv = ::sigaction(*it, &action, xPTR_NULL);
        xTEST_DIFF(iRv, - 1);
    #endif
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
Signal::connectExit(
    const exit_handler_t &a_handler
) const
{
    xCHECK_DO(a_handler == xPTR_NULL, return);

    int_t iRv = std::atexit(a_handler);
    xTEST(iRv == 0);
}
//-------------------------------------------------------------------------------------------------
inline void_t
Signal::connectTerminate(
    const std::terminate_handler &a_handler
) const
{
    xTEST_PTR(a_handler);

    std::terminate_handler handler_old = std::set_terminate(a_handler);
    xUNUSED(handler_old);
}
//-------------------------------------------------------------------------------------------------
inline void_t
Signal::connectUnexpected(
    const std::unexpected_handler &a_handler
) const
{
    xTEST_PTR(a_handler);

    std::unexpected_handler handler_old = std::unexpected_handler(a_handler);
    xUNUSED(handler_old);
}
//-------------------------------------------------------------------------------------------------
inline int_t
Signal::emit(
    cint_t &a_signalNum
) const
{
    int iRv = std::raise(a_signalNum);
    xTEST(iRv == 0);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
