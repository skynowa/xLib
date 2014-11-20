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
