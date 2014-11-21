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

        // psignal, strsignal, sys_siglist
        Trace() << xTRACE_VAR(a_signal) << " - " << ::strsignal(a_signal);

        Application::exit(EXIT_FAILURE);
    }

    static void_t onExit()
    {
        // Trace() << xFUNCTION << "\nStack trace:\n" << StackTrace().toString();

        // Application::abort();  // forces abnormal termination
    }

    static void_t onTerminate()
    {
        Trace() << xFUNCTION;

        // Application::abort();  // forces abnormal termination
    }

    static void_t onUnexpected()
    {
        Trace() << xFUNCTION;

        // Application::abort();  // forces abnormal termination
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
    xTEST_CASE("all", a_caseLoops)
    {
        Application::setName(xT("[app_name]"));
        Application::setDecription(xT("[decription]"));
        Application::setUsage(xT("[usage]"));
        Application::setHelp(xT("[help]"));
        Application::setCopyrightYears(xT("[2008-2014]"));
        Application::setVersionMajor(xT("[1]"));
        Application::setVersionMinor(xT("[0]"));
        Application::setVersionPatch(xT("[0]"));
        Application::setVersionType(xT("[alpha]"));
        Application::setVersionRevision(xT("[develop/970f53b]"));
        Application::setVendorName(xT("[Skynowa Studio]"));
        Application::setVendorDomain(xT("[com]"));
        Application::setVendorAuthor(xT("[skynowa]"));
        Application::setVendorUrl(xT("[http://bitbucket.org/skynowa/xlib]"));
        Application::setVendorEmail(xT("[skynowa@gmail.com]"));
        Application::setVendorSkype(xT("[skynowa777]"));

    #if 1
        Trace()
            << xTRACE_VAR(Application::name())            << xT("\n")
            << xTRACE_VAR(Application::decription())      << xT("\n")
            << xTRACE_VAR(Application::usage())           << xT("\n")
            << xTRACE_VAR(Application::help())            << xT("\n")
            << xTRACE_VAR(Application::copyrightYears())  << xT("\n")
            << xTRACE_VAR(Application::versionMajor())    << xT("\n")
            << xTRACE_VAR(Application::versionMinor())    << xT("\n")
            << xTRACE_VAR(Application::versionPatch())    << xT("\n")
            << xTRACE_VAR(Application::versionType())     << xT("\n")
            << xTRACE_VAR(Application::versionRevision()) << xT("\n")
            << xTRACE_VAR(Application::vendorName())      << xT("\n")
            << xTRACE_VAR(Application::vendorDomain())    << xT("\n")
            << xTRACE_VAR(Application::vendorAuthor())    << xT("\n")
            << xTRACE_VAR(Application::vendorUrl())       << xT("\n")
            << xTRACE_VAR(Application::vendorEmail())     << xT("\n")
            << xTRACE_VAR(Application::vendorSkype());
    #endif

        Application application(xT("[app_name]_guid"), xT(""));

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
        signalNums.push_back(SIGCLD);
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

        application.signal().connect(signalNums, SignalHandlers::onSignals);
        application.signal().connectExit(SignalHandlers::onExit);
        application.signal().connectTerminate(SignalHandlers::onTerminate);
        application.signal().connectUnexpected(SignalHandlers::onUnexpected);

        // test error
        TestFail testFail;
        testFail.foo3();
    }
}
//-------------------------------------------------------------------------------------------------
