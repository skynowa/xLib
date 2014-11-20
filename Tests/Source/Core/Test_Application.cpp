/**
 * \file   Test_Application.cpp
 * \brief  test Application
 */


#include <Test/Core/Test_Application.h>


//-------------------------------------------------------------------------------------------------
xLIB_CORE_APPLICATION_STATIC_DECLARE

class SignalHandlers
{
public:
    static void_t onSignals(int_t a_signal)
    {
        Trace() << xFUNCTION;

        // psignal, strsignal
        Trace() << xTRACE_VAR(a_signal) << " - " << ::strsignal[a_signal];

        ::_exit(EXIT_FAILURE);
    }

    static void_t onExit()
    {
        // Trace() << xFUNCTION << "\nStack trace:\n" << StackTrace().toString();

        // std::abort();  // forces abnormal termination
    }

    static void_t onTerminate()
    {
        Trace() << xFUNCTION;

        // std::abort();  // forces abnormal termination
    }

    static void_t onUnexpected()
    {
        Trace() << xFUNCTION;

        // std::abort();  // forces abnormal termination
    }
};
//-------------------------------------------------------------------------------------------------
class TestFail
{
public:
    void_t fail()
    {
    #if 1
        int *p = xPTR_NULL;
        *p = 10;
    #else
        throw 0;  // unhandled exception: calls terminate handler
    #endif
    }

    void_t foo1()
    {
        fail();
    }

    void_t foo2()
    {
        foo1();
    }

    void_t foo3()
    {
        foo2();
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Application::unit(
    culonglong_t &a_caseLoops
)
{
    {
        std::vector<int_t> signalNums;
        signalNums.push_back(SIGHUP);      // Hangup (POSIX)
        signalNums.push_back(SIGINT);      // Interrupt (ANSI)
        signalNums.push_back(SIGQUIT);     // Quit (POSIX)
        signalNums.push_back(SIGILL);      // Illegal instruction (ANSI)
        signalNums.push_back(SIGTRAP);     // Trace trap (POSIX)
        signalNums.push_back(SIGABRT);     // Abort (ANSI)
        signalNums.push_back(SIGIOT);      // IOT trap (4.2 BSD)
        signalNums.push_back(SIGBUS);      // BUS error (4.2 BSD)
        signalNums.push_back(SIGFPE);      // Floating-point exception (ANSI)
        signalNums.push_back(SIGKILL);     // Kill); unblockable (POSIX)
        signalNums.push_back(SIGUSR1);     // User-defined signal 1 (POSIX)
        signalNums.push_back(SIGSEGV);     // Segmentation violation (ANSI)
        signalNums.push_back(SIGUSR2);     // User-defined signal 2 (POSIX)
        signalNums.push_back(SIGPIPE);     // Broken pipe (POSIX)
        signalNums.push_back(SIGALRM);     // Alarm clock (POSIX)
        signalNums.push_back(SIGTERM);     // Termination (ANSI)
        signalNums.push_back(SIGSTKFLT);   // Stack fault
        signalNums.push_back(SIGCLD);      // Same as SIGCHLD (System V)
        signalNums.push_back(SIGCHLD);     // Child status has changed (POSIX)
        signalNums.push_back(SIGCONT);     // Continue (POSIX)
        signalNums.push_back(SIGSTOP);     // Stop); unblockable (POSIX)
        signalNums.push_back(SIGTSTP);     // Keyboard stop (POSIX)
        signalNums.push_back(SIGTTIN);     // Background read from tty (POSIX)
        signalNums.push_back(SIGTTOU);     // Background write to tty (POSIX)
        signalNums.push_back(SIGURG);      // Urgent condition on socket (4.2 BSD)
        signalNums.push_back(SIGXCPU);     // CPU limit exceeded (4.2 BSD)
        signalNums.push_back(SIGXFSZ);     // File size limit exceeded (4.2 BSD)
        signalNums.push_back(SIGVTALRM);   // Virtual alarm clock (4.2 BSD)
        signalNums.push_back(SIGPROF);     // Profiling alarm clock (4.2 BSD)
        signalNums.push_back(SIGWINCH);    // Window size change (4.3 BSD); Sun)
        signalNums.push_back(SIGPOLL);     // Pollable event occurred (System V)
        signalNums.push_back(SIGIO);       // I/O now possible (4.2 BSD)
        signalNums.push_back(SIGPWR);      // Power failure restart (System V)
        signalNums.push_back(SIGSYS);      // Bad system call

        Application application(xT("[app_name]_guid"), xT(""));
        Application::setName(xT("[app_name]"));
        application.setName(xT("[app_name]"));
        application.setDecription(xT("[decription]"));
        application.setUsage(xT("[usage]"));
        application.setHelp(xT("[help]"));
        application.setCopyrightYears(xT("[2008-2014]"));
        application.setVersionMajor(xT("[1]"));
        application.setVersionMinor(xT("[0]"));
        application.setVersionPatch(xT("[0]"));
        application.setVersionType(xT("[alpha]"));
        application.setVersionRevision(xT("[develop/970f53b]"));
        application.setVendorName(xT("[Skynowa Studio]"));
        application.setVendorDomain(xT("[com]"));
        application.setVendorAuthor(xT("[skynowa]"));
        application.setVendorUrl(xT("[http://bitbucket.org/skynowa/xlib]"));
        application.setVendorEmail(xT("[skynowa@gmail.com]"));
        application.setVendorSkype(xT("[skynowa777]"));

    #if 0
        Trace()
            << xTRACE_VAR(application.name())            << xT("\n")
            << xTRACE_VAR(application.decription())      << xT("\n")
            << xTRACE_VAR(application.usage())           << xT("\n")
            << xTRACE_VAR(application.help())            << xT("\n")
            << xTRACE_VAR(application.copyrightYears())  << xT("\n")
            << xTRACE_VAR(application.versionMajor())    << xT("\n")
            << xTRACE_VAR(application.versionMinor())    << xT("\n")
            << xTRACE_VAR(application.versionPatch())    << xT("\n")
            << xTRACE_VAR(application.versionType())     << xT("\n")
            << xTRACE_VAR(application.versionRevision()) << xT("\n")
            << xTRACE_VAR(application.vendorName())      << xT("\n")
            << xTRACE_VAR(application.vendorDomain())    << xT("\n")
            << xTRACE_VAR(application.vendorAuthor())    << xT("\n")
            << xTRACE_VAR(application.vendorUrl())       << xT("\n")
            << xTRACE_VAR(application.vendorEmail())     << xT("\n")
            << xTRACE_VAR(application.vendorSkype());
    #endif

        application.signal().connect(signalNums, SignalHandlers::onSignals);
        application.signal().connectExit(SignalHandlers::onExit);
        application.signal().connectTerminate(SignalHandlers::onTerminate);
        application.signal().connectUnexpected(SignalHandlers::onUnexpected);

        // test error
        TestFail testFail;
        testFail.foo3();
    }

    xTEST_CASE("Application::[TEST_CASE_1]", a_caseLoops)
    {

    }
}
//-------------------------------------------------------------------------------------------------
