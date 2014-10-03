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


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

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
        sighandler_t shRv = std::signal(*it, a_callback);
        xTEST(shRv != SIG_ERR);
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
