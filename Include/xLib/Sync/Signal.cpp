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

    int_t iRv = 0;

	struct sigaction action;
	{
		// setup alternate stack
		{
			stack_t stack;	xSTRUCT_ZERO(stack);
			stack.ss_sp    = malloc(SIGSTKSZ);
			stack.ss_size  = SIGSTKSZ;
			stack.ss_flags = 0;

			iRv = ::sigaltstack(&stack, xPTR_NULL);
			xTEST_DIFF(iRv, - 1);
		}

		xSTRUCT_ZERO(action);
		action.sa_handler = a_onSignals;

		iRv = ::sigemptyset(&action.sa_mask);
		xTEST_DIFF(iRv, - 1);

		action.sa_flags = SA_RESTART | SA_SIGINFO | SA_ONSTACK;
	}

    xFOR_EACH_CONST(std::vector<int_t>, it, a_signalNums) {
        switch (*it) {
        case SIGKILL:
			Trace() << Format::str(xT("xLib: Signal {} ({}) cannot be caught or ignored"),
							xLEX_TO_STR(SIGKILL), SIGKILL);
			continue;
		case SIGSTOP:
			Trace() << Format::str(xT("xLib: Signal {} ({}) cannot be caught or ignored"),
							xLEX_TO_STR(SIGSTOP), SIGSTOP);
            continue;
            break;
        default:
            break;
        }

		int_t iRv = ::sigaction(*it, &action, xPTR_NULL);
		xTEST_DIFF_MSG(iRv, - 1, Format::str(xT("Signal: {}"), decription(*it)));
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
Signal::connectInfo(
    const std::vector<int_t> &a_signalNums,
    const on_info_t           a_onSignals
) const
{
   /**
    * FAQ: set handlers
    *
    * https://gist.github.com/jvranish/4441299
    */

    int_t iRv = 0;

	struct sigaction action;
	{
		// setup alternate stack
		{
			stack_t stack;	xSTRUCT_ZERO(stack);
			stack.ss_sp    = malloc(SIGSTKSZ);
			stack.ss_size  = SIGSTKSZ;
			stack.ss_flags = 0;

			iRv = ::sigaltstack(&stack, xPTR_NULL);
			xTEST_DIFF(iRv, - 1);
		}

		xSTRUCT_ZERO(action);
		action.sa_sigaction = a_onSignals;

		iRv = ::sigemptyset(&action.sa_mask);
		xTEST_DIFF(iRv, - 1);

		action.sa_flags = SA_RESTART | SA_SIGINFO | SA_ONSTACK;
	}

    xFOR_EACH_CONST(std::vector<int_t>, it, a_signalNums) {
        switch (*it) {
        case SIGKILL:
			Trace() << Format::str(xT("xLib: Signal {} ({}) cannot be caught or ignored"),
							xLEX_TO_STR(SIGKILL), SIGKILL);
			continue;
		case SIGSTOP:
			Trace() << Format::str(xT("xLib: Signal {} ({}) cannot be caught or ignored"),
							xLEX_TO_STR(SIGSTOP), SIGSTOP);
            continue;
            break;
        default:
            break;
        }

		int_t iRv = ::sigaction(*it, &action, xPTR_NULL);
		xTEST_DIFF_MSG(iRv, - 1, Format::str(xT("Signal: {}"), decription(*it)));
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connectInfoAll(
    const on_info_t a_onSignals
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

	connectInfo(signalNums, a_onSignals);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Signal::connectExit(
    const on_exit_t a_onExit
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
xINLINE bool_t
Signal::isValid(
    cint_t &a_signalNum ///< signal number
)
{
	return (::sigaction(a_signalNum, xPTR_NULL, xPTR_NULL) == 0);
}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

struct _Signal
{
	int_t          num;
	int_t          code;
	std::tstring_t codeStr;
	std::tstring_t description;
};

xNAMESPACE_ANONYM_END

/* static */
xINLINE std::tstring_t
Signal::infoDescription(
    const siginfo_t &a_info	///<  signal info struct
)
{
	std::tstring_t sRv;
	cint_t         _KERNEL = - 1;

	const _Signal signals[] =
	{
		// _KERNEL
		{_KERNEL, SI_ASYNCNL,    xLEX_TO_STR(SI_ASYNCNL),    xT("Sent by asynch name lookup completion")},
		{_KERNEL, SI_TKILL,      xLEX_TO_STR(SI_TKILL),      xT("Sent by tkill")},
		{_KERNEL, SI_SIGIO,      xLEX_TO_STR(SI_SIGIO),      xT("Sent by queued SIGIO")},
		{_KERNEL, SI_ASYNCIO,    xLEX_TO_STR(SI_ASYNCIO),    xT("Sent by AIO completion")},
		{_KERNEL, SI_MESGQ,      xLEX_TO_STR(SI_MESGQ),      xT("Sent by real time mesq state change")},
		{_KERNEL, SI_TIMER,      xLEX_TO_STR(SI_TIMER),      xT("Sent by timer expiration")},
		{_KERNEL, SI_QUEUE,      xLEX_TO_STR(SI_QUEUE),      xT("Sent by sigqueue")},
		{_KERNEL, SI_USER,       xLEX_TO_STR(SI_USER),       xT("Sent by kill, sigsend")},
		{_KERNEL, SI_KERNEL,     xLEX_TO_STR(SI_KERNEL),     xT("Send by kernel")},

		// SIGILL
		{SIGILL,  ILL_ILLOPC,    xLEX_TO_STR(ILL_ILLOPC),    xT("Illegal opcode")},
		{SIGILL,  ILL_ILLOPN,    xLEX_TO_STR(ILL_ILLOPN),    xT("Illegal operand")},
		{SIGILL,  ILL_ILLADR,    xLEX_TO_STR(ILL_ILLADR),    xT("Illegal addressing mode")},
		{SIGILL,  ILL_ILLTRP,    xLEX_TO_STR(ILL_ILLTRP),    xT("Illegal trap")},
		{SIGILL,  ILL_PRVOPC,    xLEX_TO_STR(ILL_PRVOPC),    xT("Privileged opcode")},
		{SIGILL,  ILL_PRVREG,    xLEX_TO_STR(ILL_PRVREG),    xT("Privileged register")},
		{SIGILL,  ILL_COPROC,    xLEX_TO_STR(ILL_COPROC),    xT("Coprocessor error")},
		{SIGILL,  ILL_BADSTK,    xLEX_TO_STR(ILL_BADSTK),    xT("Internal stack error")},

		// SIGFPE
		{SIGFPE,  FPE_INTDIV,    xLEX_TO_STR(FPE_INTDIV),    xT("Integer divide by zero")},
		{SIGFPE,  FPE_INTOVF,    xLEX_TO_STR(FPE_INTOVF),    xT("Integer overflow")},
		{SIGFPE,  FPE_FLTDIV,    xLEX_TO_STR(FPE_FLTDIV),    xT("Floating point divide by zero")},
		{SIGFPE,  FPE_FLTOVF,    xLEX_TO_STR(FPE_FLTOVF),    xT("Floating point overflow")},
		{SIGFPE,  FPE_FLTUND,    xLEX_TO_STR(FPE_FLTUND),    xT("Floating point underflow")},
		{SIGFPE,  FPE_FLTRES,    xLEX_TO_STR(FPE_FLTRES),    xT("Floating point inexact result")},
		{SIGFPE,  FPE_FLTINV,    xLEX_TO_STR(FPE_FLTINV),    xT("Floating point invalid operation")},
		{SIGFPE,  FPE_FLTSUB,    xLEX_TO_STR(FPE_FLTSUB),    xT("Subscript out of range")},

		// SIGSEGV
		{SIGSEGV, SEGV_MAPERR,   xLEX_TO_STR(SEGV_MAPERR),   xT("Address not mapped to object")},
		{SIGSEGV, SEGV_ACCERR,   xLEX_TO_STR(SEGV_ACCERR),   xT("Invalid permissions for mapped object")},

		// SIGBUS
		{SIGBUS,  BUS_ADRALN,    xLEX_TO_STR(BUS_ADRALN),    xT("Invalid address alignment")},
		{SIGBUS,  BUS_ADRERR,    xLEX_TO_STR(BUS_ADRERR),    xT("Non-existant physical address")},
		{SIGBUS,  BUS_OBJERR,    xLEX_TO_STR(BUS_OBJERR),    xT("Object specific hardware error")},
		{SIGBUS,  BUS_MCEERR_AR, xLEX_TO_STR(BUS_MCEERR_AR), xT("Hardware memory error: action required")},
		{SIGBUS,  BUS_MCEERR_AO, xLEX_TO_STR(BUS_MCEERR_AO), xT("Hardware memory error: action optional")},

		// SIGTRAP
		{SIGTRAP, TRAP_BRKPT,    xLEX_TO_STR(TRAP_BRKPT),    xT("Process breakpoint")},
		{SIGTRAP, TRAP_TRACE,    xLEX_TO_STR(TRAP_TRACE),    xT("Process trace trap")},

		// SIGCHLD
		{SIGCHLD, CLD_EXITED,    xLEX_TO_STR(CLD_EXITED),    xT("Child has exited")},
		{SIGCHLD, CLD_KILLED,    xLEX_TO_STR(CLD_KILLED),    xT("Child was killed")},
		{SIGCHLD, CLD_DUMPED,    xLEX_TO_STR(CLD_DUMPED),    xT("Child terminated abnormally")},
		{SIGCHLD, CLD_TRAPPED,   xLEX_TO_STR(CLD_TRAPPED),   xT("Traced child has trapped")},
		{SIGCHLD, CLD_STOPPED,   xLEX_TO_STR(CLD_STOPPED),   xT("Child has stopped")},
		{SIGCHLD, CLD_CONTINUED, xLEX_TO_STR(CLD_CONTINUED), xT("Stopped child has continued")},

		// SIGPOLL
		{SIGPOLL, POLL_IN,       xLEX_TO_STR(POLL_IN),       xT("Data input available")},
		{SIGPOLL, POLL_OUT,      xLEX_TO_STR(POLL_OUT),      xT("Output buffers available")},
		{SIGPOLL, POLL_MSG,      xLEX_TO_STR(POLL_MSG),      xT("Input message available")},
		{SIGPOLL, POLL_ERR,      xLEX_TO_STR(POLL_ERR),      xT("I/O error")},
		{SIGPOLL, POLL_PRI,      xLEX_TO_STR(POLL_PRI),      xT("High priority input available")},
		{SIGPOLL, POLL_HUP,      xLEX_TO_STR(POLL_HUP),      xT("Device disconnected")}
	};

	xFOR_ARRAY(i, signals) {
		const _Signal &signal = signals[i];

		xCHECK_DO(signal.num != a_info.si_signo, continue);
		xCHECK_DO(signal.code != a_info.si_code, continue);

		sRv = Format::str(xT("{}: {} ({}) - {}, {}"),
				decription(signal.num),
				signal.codeStr,
				signal.code,
				signal.description,
				NativeError::format(a_info.si_errno));

		break;
	}

	if ( !sRv.empty() ) {
		return sRv;
	}

	// _KERNEL
	xFOR_ARRAY(i, signals) {
		const _Signal &signal = signals[i];

		xCHECK_DO(signal.num != _KERNEL,         continue);
		xCHECK_DO(signal.code != a_info.si_code, continue);

		sRv = Format::str(xT("{}: {} ({}) - {} {}"),
				decription(signal.num),
				signal.codeStr,
				signal.code,
				signal.description,
				NativeError::format(a_info.si_errno));

		break;
	}

	return sRv;
}
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
