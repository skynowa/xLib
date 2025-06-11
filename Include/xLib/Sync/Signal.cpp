/**
 * \file   Signal.cpp
 * \brief  signal
 */


#include "Signal.h"

#if   xENV_WIN
	/// TODO: [Win] Signal_win - impl
    // #include "Platform/Win/Signal_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Signal_unix.inl"
#endif

#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/LogStream.h>

#if xENV_UNIX

namespace xl::sync
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::sig_atomic_t
Signal::state() const
{
    return _state;
}
//-------------------------------------------------------------------------------------------------
void_t
Signal::setState(
    const std::sig_atomic_t a_state	///<
)
{
    // ANDROID: SIG_ATOMIC_MIN, SIG_ATOMIC_MAX
#if xTODO_ANDROID
	xTEST(a_state >= SIG_ATOMIC_MIN && a_state <= SIG_ATOMIC_MAX);
#endif
    _state = a_state;
}
//-------------------------------------------------------------------------------------------------
void_t
Signal::connect(
    const std::vector<int_t> &a_signalNums,	///<
    const sighandler_t        a_onSignals	///<
) const
{
   /**
    * FAQ: set handlers
    *
    * https://gist.github.com/jvranish/4441299
    */

    int_t iRv = 0;

	struct sigaction action {};
	{
		action.sa_handler = a_onSignals;

		/// TODO: [xENV_APPLE]
	#if xENV_APPLE
		iRv = sigemptyset(&action.sa_mask);
	#else
		iRv = ::sigemptyset(&action.sa_mask);
	#endif
		xTEST_DIFF(iRv, - 1);

		action.sa_flags = SA_RESTART | SA_SIGINFO;
	}

    for (const auto &it : a_signalNums) {
        switch (it) {
        case SIGKILL:
        	LogCoutWarning() << Format::str(xT("xLib: Signal {} ({}) cannot be caught or ignored"),
							xLEX_TO_STR(SIGKILL), SIGKILL);
			continue;
		case SIGSTOP:
			LogCoutWarning() << Format::str(xT("xLib: Signal {} ({}) cannot be caught or ignored"),
							xLEX_TO_STR(SIGSTOP), SIGSTOP);
            continue;
            break;
        default:
            break;
        }

		iRv = ::sigaction(it, &action, nullptr);
		xTEST_DIFF_MSG(iRv, - 1, Format::str(xT("Signal: {}"), decription(it)));
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Signal::connectAll(
    const sighandler_t a_onSignals	///<
) const
{
    std::vector<int_t> signalNums;

    cint_t signalMin = SIGHUP;
    cint_t signalMax = SIGSYS;

	for (int_t i = signalMin; i <= signalMax; ++ i) {
		// filter signals
		{
			switch (i) {
			case SIGKILL:
			case SIGSTOP:
				// signals cannot be caught or ignored;
				continue;
				break;
			default:
				break;
			}

			// TODO: [skynowa] [ANDROID] SIGCLD
		}

		signalNums.push_back(i);
	}  // for (signalMax)

	connect(signalNums, a_onSignals);
}
//-------------------------------------------------------------------------------------------------
void_t
Signal::connectInfo(
    const std::vector<int_t> &a_signalNums,	///<
    const on_info_t           a_onInfo		///<
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
		// Block other terminal-generated signals while handler runs
		sigset_t blockMask;
		{
			/// TODO: [xENV_APPLE]
		#if xENV_APPLE
			iRv = sigemptyset(&blockMask);
		#else
			iRv = ::sigemptyset(&blockMask);
		#endif
			xTEST_DIFF(iRv, - 1);

			for (const auto &it : a_signalNums) {
				if (it == SIGKILL || it == SIGSTOP) {
					continue;
				}

				/// TODO: [xENV_APPLE]
			#if xENV_APPLE
				iRv = sigaddset(&blockMask, it);
			#else
				iRv = ::sigaddset(&blockMask, it);
			#endif
				xTEST_DIFF(iRv, - 1);
			}
		}

		action.sa_sigaction = a_onInfo;
		action.sa_mask      = blockMask;
		action.sa_flags     = SA_RESTART | SA_SIGINFO;
	}

    for (const auto &it : a_signalNums) {
        switch (it) {
        case SIGKILL:
        	LogCoutWarning() << Format::str(xT("xLib: Signal {} ({}) cannot be caught or ignored"),
							xLEX_TO_STR(SIGKILL), SIGKILL);
			continue;
		case SIGSTOP:
			LogCoutWarning() << Format::str(xT("xLib: Signal {} ({}) cannot be caught or ignored"),
							xLEX_TO_STR(SIGSTOP), SIGSTOP);
            continue;
            break;
        default:
            break;
        }

		iRv = ::sigaction(it, &action, nullptr);
		xTEST_DIFF_MSG(iRv, - 1, Format::str(xT("Signal: {}"), decription(it)));
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Signal::connectInfoAll(
    const on_info_t a_onInfo	///<
) const
{
    std::vector<int_t> signalNums;

    cint_t signalMin = SIGHUP;
    cint_t signalMax = SIGSYS;

	for (int_t i = signalMin; i <= signalMax; ++ i) {
		// filter signals
		{
			switch (i) {
			case SIGKILL:
			case SIGSTOP:
				// signals cannot be caught or ignored;
				continue;
				break;
			default:
				break;
			}

			// TODO: [skynowa] [ANDROID] SIGCLD
		}

		signalNums.push_back(i);
	}  // for (signalMax)

	connectInfo(signalNums, a_onInfo);
}
//-------------------------------------------------------------------------------------------------
void_t
Signal::connectExit(
    const on_exit_t a_onExit	///<
) const
{
    xCHECK_DO(a_onExit == nullptr, return);

    int_t iRv = std::atexit(a_onExit);
    xTEST(iRv == 0);
}
//-------------------------------------------------------------------------------------------------
void_t
Signal::connectTerminate(
    const std::terminate_handler a_onTerminate	///<
) const
{
    std::terminate_handler handler_old = std::set_terminate(a_onTerminate);
    xUNUSED(handler_old);
}
//-------------------------------------------------------------------------------------------------
void_t
Signal::connectUnexpected(
    const std::unexpected_handler a_onUnexpected	///<
) const
{
    std::unexpected_handler handler_old = std::set_unexpected(a_onUnexpected);
    xUNUSED(handler_old);
}
//-------------------------------------------------------------------------------------------------
void_t
Signal::raise(
    cint_t a_signalNum	///<
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
bool_t
Signal::isValid(
    cint_t a_signalNum ///< signal number
)
{
	return (::sigaction(a_signalNum, nullptr, nullptr) == 0);
}
//-------------------------------------------------------------------------------------------------
namespace
{

struct _SignalInfo
{
	int_t         num;			///<
	int_t         code;			///<
	cptr_ctchar_t codeStr;		///<
	cptr_ctchar_t description;	///<
};

}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Signal::infoDescription(
    const siginfo_t &a_info	///<  signal info struct
)
{
	std::tstring_t sRv;
	cint_t         _KERNEL = - 1;

	constexpr _SignalInfo signalInfos[] =
	{
		// _KERNEL
	#if !xENV_BSD && !xENV_APPLE
		{_KERNEL, SI_ASYNCNL,    xLEX_TO_STR(SI_ASYNCNL),    xT("Sent by asynch name lookup completion")},
		{_KERNEL, SI_TKILL,      xLEX_TO_STR(SI_TKILL),      xT("Sent by tkill")},
		{_KERNEL, SI_SIGIO,      xLEX_TO_STR(SI_SIGIO),      xT("Sent by queued SIGIO")},
	#endif
		{_KERNEL, SI_ASYNCIO,    xLEX_TO_STR(SI_ASYNCIO),    xT("Sent by AIO completion")},
		{_KERNEL, SI_MESGQ,      xLEX_TO_STR(SI_MESGQ),      xT("Sent by real time mesq state change")},
		{_KERNEL, SI_TIMER,      xLEX_TO_STR(SI_TIMER),      xT("Sent by timer expiration")},
		{_KERNEL, SI_QUEUE,      xLEX_TO_STR(SI_QUEUE),      xT("Sent by sigqueue")},
		{_KERNEL, SI_USER,       xLEX_TO_STR(SI_USER),       xT("Sent by kill, sigsend")},
	#if !xENV_APPLE
		{_KERNEL, SI_KERNEL,     xLEX_TO_STR(SI_KERNEL),     xT("Send by kernel")},
	#endif

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
	#if !xENV_BSD && !xENV_APPLE
		{SIGBUS,  BUS_MCEERR_AR, xLEX_TO_STR(BUS_MCEERR_AR), xT("Hardware memory error: action required")},
		{SIGBUS,  BUS_MCEERR_AO, xLEX_TO_STR(BUS_MCEERR_AO), xT("Hardware memory error: action optional")},
	#endif

		// SIGTRAP
		{SIGTRAP, TRAP_BRKPT,    xLEX_TO_STR(TRAP_BRKPT),    xT("Process breakpoint")},
		{SIGTRAP, TRAP_TRACE,    xLEX_TO_STR(TRAP_TRACE),    xT("Process trace trap")},

		// SIGCHLD
		{SIGCHLD, CLD_EXITED,    xLEX_TO_STR(CLD_EXITED),    xT("Child has exited")},
		{SIGCHLD, CLD_KILLED,    xLEX_TO_STR(CLD_KILLED),    xT("Child was killed")},
		{SIGCHLD, CLD_DUMPED,    xLEX_TO_STR(CLD_DUMPED),    xT("Child terminated abnormally")},
		{SIGCHLD, CLD_TRAPPED,   xLEX_TO_STR(CLD_TRAPPED),   xT("Traced child has trapped")},
		{SIGCHLD, CLD_STOPPED,   xLEX_TO_STR(CLD_STOPPED),   xT("Child has stopped")},
		{SIGCHLD, CLD_CONTINUED, xLEX_TO_STR(CLD_CONTINUED), xT("Stopped child has continued")}

		// SIGPOLL
	#if !xENV_BSD && !xENV_APPLE
		,
		{SIGPOLL, POLL_IN,       xLEX_TO_STR(POLL_IN),       xT("Data input available")},
		{SIGPOLL, POLL_OUT,      xLEX_TO_STR(POLL_OUT),      xT("Output buffers available")},
		{SIGPOLL, POLL_MSG,      xLEX_TO_STR(POLL_MSG),      xT("Input message available")},
		{SIGPOLL, POLL_ERR,      xLEX_TO_STR(POLL_ERR),      xT("I/O error")},
		{SIGPOLL, POLL_PRI,      xLEX_TO_STR(POLL_PRI),      xT("High priority input available")},
		{SIGPOLL, POLL_HUP,      xLEX_TO_STR(POLL_HUP),      xT("Device disconnected")}
	#endif
	};

	for (const auto &it_signalInfo : signalInfos) {
		xCHECK_DO(it_signalInfo.num  != a_info.si_signo, continue);
		xCHECK_DO(it_signalInfo.code != a_info.si_code,  continue);

		sRv = Format::str(xT("{}\n{} ({}) - {}\n{}"),
				decription(it_signalInfo.num),
				it_signalInfo.codeStr,
				it_signalInfo.code,
				it_signalInfo.description,
				NativeError::format( static_cast<ulong_t>(a_info.si_errno)) );

		break;
	}

	if ( !sRv.empty() ) {
		return sRv;
	}

	// _KERNEL
	for (const auto &it_signalInfo : signalInfos) {
		xCHECK_DO(it_signalInfo.num  != _KERNEL,        continue);
		xCHECK_DO(it_signalInfo.code != a_info.si_code, continue);

		sRv = Format::str(xT("{}\n{} ({}) - {}\n{}"),
				decription(it_signalInfo.num),
				it_signalInfo.codeStr,
				it_signalInfo.code,
				it_signalInfo.description,
				NativeError::format( static_cast<ulong_t>(a_info.si_errno)) );

		break;
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Signal::decription(
    cint_t a_signalNum ///< signal number
)
{
    return Format::str(xT("{} - {}"), a_signalNum, _decription_impl(a_signalNum));
}
//-------------------------------------------------------------------------------------------------

} // namespace

#endif
