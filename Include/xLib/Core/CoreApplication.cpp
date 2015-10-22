/**
 * \file   CoreApplication.inl
 * \brief
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "CoreApplication.h"
#endif

#include <xLib/Debug/Exception.h>
#include <xLib/Log/Trace.h>


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CoreApplication::CoreApplication(
    std::ctstring_t &a_appGuid, ///< application GUID
    std::ctstring_t &a_locale   ///< locale, empty value for current locale
) :
    Application(a_appGuid, a_locale)
{
    Trace() << xFUNCTION;

#if 0
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
    signalNums.push_back(SIGKILL);
    signalNums.push_back(SIGUSR1);
    signalNums.push_back(SIGSEGV);
    signalNums.push_back(SIGUSR2);
    signalNums.push_back(SIGPIPE);
    signalNums.push_back(SIGALRM);
    signalNums.push_back(SIGTERM);
    signalNums.push_back(SIGSTKFLT);
    // TODO: [Android] SIGCLD
#if xTODO_ANDROID
    signalNums.push_back(SIGCLD);
#endif
    signalNums.push_back(SIGCHLD);
    signalNums.push_back(SIGCONT);
    signalNums.push_back(SIGSTOP);
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

    signal().connect(signalNums, onSignals);
    signal().connectExit(onExit);
    signal().connectTerminate(onTerminate);
    signal().connectUnexpected(onUnexpected);
#endif
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
CoreApplication::~CoreApplication()
{
    Trace() << xFUNCTION;

    Trace() << StackTrace().toString();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE int_t
CoreApplication::run()
{
    Trace() << xFUNCTION;

    int_t iRv = EXIT_FAILURE;

    const bool_t isUseException = false;
    if (isUseException) {
        try {
            iRv = onRun();
        }
        catch (const xlib::Exception &a_ex) {
            xTEST_FAIL_MSG(a_ex.what());
        }
        catch (const std::exception &a_ex) {
            std::string msg = a_ex.what();
            xTEST_FAIL_MSG(xS2TS(msg));
        }
        catch (...) {
            xTEST_FAIL_MSG(xT("unknown error"));
        }
    } else {
        iRv = onRun();
    }

    return iRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
CoreApplication::onSignals(
    int_t a_signal
)
{
    Trace() << xFUNCTION;

    Trace() << StackTrace().toString();
    Trace() << xTRACE_VAR(a_signal) << " - " << Signal::decription(a_signal);

    Application::exit(a_signal);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
CoreApplication::onExit()
{
    Trace() << xFUNCTION;

    xTEST(false);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
CoreApplication::onTerminate()
{
    Trace() << xFUNCTION;

    xTEST(false);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
CoreApplication::onUnexpected()
{
    Trace() << xFUNCTION;

    xTEST(false);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
