/**
 * \file   Signal.cpp
 * \brief
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

volatile std::sig_atomic_t signal_flag = 0;
    ///< Integral type of an object that can be accessed as an atomic entity, even in the presence
    ///< of asynchronous signals.

//-------------------------------------------------------------------------------------------------
inline void_t
Signal::connect(
    const std::vector<int_t> &a_signalNums,
    sighandler_t              a_callback
) const
{
   /**
    * FAQ: set handlers
    *
    * https://gist.github.com/jvranish/4441299
    */

    xFOREACH_CONST(std::vector<int_t>, it, a_signalNums) {
    #if USE_SIMPLE_SIGNAL
        sighandler_t shRv = std::signal(*it, a_callback);
        xTEST(shRv != SIG_ERR);
    #else
        int_t iRv = 0;

        struct sigaction action; xSTRUCT_ZERO(action);
        action.sa_handler  = a_callback;

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
    void_t (*a_callback)()
) const
{
    xCHECK_DO(a_callback == xPTR_NULL, return);

    int_t iRv = std::atexit(a_callback);
    xTEST(iRv == 0);
}
//-------------------------------------------------------------------------------------------------
inline void_t
Signal::connectTerminate(
    void_t (*a_callback)()
) const
{
    xTEST_PTR(a_callback);

    void_t (*callback_old)() = xPTR_NULL;

    callback_old = std::set_terminate(a_callback);
    xUNUSED(callback_old);
}
//-------------------------------------------------------------------------------------------------
inline int_t
Signal::emit(cint_t &a_signalNum) const
{
    int iRv = std::raise(a_signalNum);
    xTEST(iRv == 0);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
