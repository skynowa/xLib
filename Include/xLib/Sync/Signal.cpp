/**
 * \file   Signal.cpp
 * \brief  signal
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
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
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Log/Trace.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Signal::Signal() :
	_state(0)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE /* virtual */
Signal::~Signal()
{
}
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
    // ANDROID: SIG_ATOMIC_MIN, SIG_ATOMIC_MAX
#if xTODO_ANDROID
    xTEST_EQ(a_state >= SIG_ATOMIC_MIN && a_state <= SIG_ATOMIC_MAX, true);
#endif
    _state = a_state;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connect(
    const std::vector<int_t> &a_signalNums,
    const sighandler_t        a_onSignals
) const
{
   /**
    * FAQ: set handlers
    *
    * https://gist.github.com/jvranish/4441299
    */

	cbool_t opt_simpleSignal     = false;
	cbool_t opt_sigActionRestart = true;

	struct sigaction action;
	{
		if (opt_simpleSignal) {
			xUNUSED(action);
		} else {
			xSTRUCT_ZERO(action);
			action.sa_handler = a_onSignals;

			int_t iRv = ::sigemptyset(&action.sa_mask);
			xTEST_DIFF(iRv, - 1);

			action.sa_flags |= opt_sigActionRestart ? SA_RESTART : SA_SIGINFO;
		}
	}

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

		if (opt_simpleSignal) {
			sighandler_t shRv = std::signal(*it, a_onSignals);
			xTEST_MSG(shRv != SIG_ERR, xT("Signal: ") + String::cast(*it));
		} else {
			int_t iRv = ::sigaction(*it, &action, xPTR_NULL);
			xTEST_DIFF_MSG(iRv, - 1, xT("Signal: ") + String::cast(*it));
		}
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connectAll(
    const sighandler_t a_onSignals
) const
{
    std::vector<int_t> signalNums;
    signalNums.push_back(SIGHUP);
    signalNums.push_back(SIGINT);
    signalNums.push_back(SIGQUIT);
    signalNums.push_back(SIGILL);
    signalNums.push_back(SIGTRAP);
    signalNums.push_back(SIGABRT);
    signalNums.push_back(SIGIOT);
    signalNums.push_back(SIGBUS);
    signalNums.push_back(SIGFPE);
    // signalNums.push_back(SIGKILL);  // SIGKILL: 9 cannot be caught or ignored
    signalNums.push_back(SIGUSR1);
    signalNums.push_back(SIGSEGV);
    signalNums.push_back(SIGUSR2);
    signalNums.push_back(SIGPIPE);
    signalNums.push_back(SIGALRM);
    signalNums.push_back(SIGTERM);
    signalNums.push_back(SIGSTKFLT);
    // ANDROID: SIGCLD
#if xTODO_ANDROID
    signalNums.push_back(SIGCLD);
#endif
    signalNums.push_back(SIGCHLD);
    signalNums.push_back(SIGCONT);
    // signalNums.push_back(SIGSTOP);  // SIGSTOP: 19 cannot be caught or ignored
    signalNums.push_back(SIGTSTP);
    signalNums.push_back(SIGTTIN);
    signalNums.push_back(SIGTTOU);
    signalNums.push_back(SIGURG);
    signalNums.push_back(SIGXCPU);
    signalNums.push_back(SIGXFSZ);
    signalNums.push_back(SIGVTALRM);
    signalNums.push_back(SIGPROF);
    signalNums.push_back(SIGWINCH);
    signalNums.push_back(SIGPOLL);
    signalNums.push_back(SIGIO);
    signalNums.push_back(SIGPWR);
    signalNums.push_back(SIGSYS);

	connect(signalNums, a_onSignals);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connectExit(
    const exit_handler_t a_onExit
) const
{
    xCHECK_DO(a_onExit == xPTR_NULL, return);

    int_t iRv = std::atexit(a_onExit);
    xTEST(iRv == 0);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connectTerminate(
    const std::terminate_handler a_onTerminate
) const
{
    xTEST_PTR(a_onTerminate);

    std::terminate_handler handler_old = std::set_terminate(a_onTerminate);
    xUNUSED(handler_old);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connectUnexpected(
    const std::unexpected_handler a_onUnexpected
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
    return Format::str(xT("{} - {}"), a_signalNum, _decription_impl(a_signalNum));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
