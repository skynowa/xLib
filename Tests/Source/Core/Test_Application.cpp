/**
 * \file   Test_Application.cpp
 * \brief  test Application
 */


#include <Test/Core/Test_Application.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Application)
//-------------------------------------------------------------------------------------------------
//-- xLIB_CORE_APPLICATION_STATIC_DECLARE

class SignalHandlers
{
public:
    static void_t onSignals(int_t a_signal)
    {
    #if xTEST_IGNORE
        Trace() << xFUNCTION;
        Trace() << xTRACE_VAR(a_signal) << " - " << Signal::decription(a_signal);
    #endif
    }

    static void_t onExit()
    {
    #if xTEST_IGNORE
        Trace() << xFUNCTION;
    #endif
    }

    static void_t onTerminate()
    {
    #if xTEST_IGNORE
        Trace() << xFUNCTION;
    #endif
    }

    static void_t onUnexpected()
    {
    #if xTEST_IGNORE
        Trace() << xFUNCTION;
    #endif
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
Test_Application::unit()
{
    xTEST_CASE("args")
    {
        Application application(xT("[app_name]_guid"), xT(""));

        std::vec_tstring_t args1;
        application.args(false, &args1);
        xTEST_EQ(args1.empty(), false);

        std::vec_tstring_t args2;
        application.args(true, &args2);
        xTEST_EQ(args1.size() - 1, args2.size());
    }

    xTEST_CASE("isRunnig")
    {
        // TEST: Application::isRunnig()
    }

    xTEST_CASE("dirsCreate")
    {
        Application application(xT("[app_name]_guid"), xT(""));
        application.dirsCreate();
    }

    xTEST_CASE("selfCheck")
    {
        Application application(xT("[app_name]_guid"), xT(""));
        m_bRv = application.selfCheck();
        xTEST(m_bRv);
    }

    xTEST_CASE("handles")
    {
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
    #if xTEMP_DISABLED
        TestFail testFail;
        testFail.foo3();
    #endif
    }

    xTEST_CASE("info")
    {
        std::ctstring_t name            = xT("[app_name]");
        std::ctstring_t decription      = xT("[decription]");
        std::ctstring_t usage           = xT("[usage]");
        std::ctstring_t help            = xT("[help]");
        std::ctstring_t copyrightYears  = xT("[2008-2014]");
        std::ctstring_t versionMajor    = xT("[1]");
        std::ctstring_t versionMinor    = xT("[0]");
        std::ctstring_t versionPatch    = xT("[3]");
        std::ctstring_t versionType     = xT("[alpha]");
        std::ctstring_t versionRevision = xT("[develop/970f53b]");
        std::ctstring_t vendorName      = xT("[Skynowa Studio]");
        std::ctstring_t vendorDomain    = xT("[com]");
        std::ctstring_t vendorAuthor    = xT("[skynowa]");
        std::ctstring_t vendorUrl       = xT("[http://bitbucket.org/skynowa/xlib]");
        std::ctstring_t vendorEmail     = xT("[skynowa@gmail.com]");
        std::ctstring_t vendorSkype     = xT("[skynowa777]");

        Application::setName(name);
        xTEST_EQ(Application::name(), name);

        Application::setDecription(decription);
        xTEST_EQ(Application::decription(), decription);

        Application::setUsage(usage);
        xTEST_EQ(Application::usage(), usage);

        Application::setHelp(help);
        xTEST_EQ(Application::help(), help);

        Application::setCopyrightYears(copyrightYears);
        xTEST_EQ(Application::copyrightYears(), copyrightYears);

        Application::setVersionMajor(versionMajor);
        xTEST_EQ(Application::versionMajor(), versionMajor);

        Application::setVersionMinor(versionMinor);
        xTEST_EQ(Application::versionMinor(), versionMinor);

        Application::setVersionPatch(versionPatch);
        xTEST_EQ(Application::versionPatch(), versionPatch);

        Application::setVersionType(versionType);
        xTEST_EQ(Application::versionType(), versionType);

        Application::setVersionRevision(versionRevision);
        xTEST_EQ(Application::versionRevision(), versionRevision);

        Application::setVendorName(vendorName);
        xTEST_EQ(Application::vendorName(), vendorName);

        Application::setVendorDomain(vendorDomain);
        xTEST_EQ(Application::vendorDomain(), vendorDomain);

        Application::setVendorAuthor(vendorAuthor);
        xTEST_EQ(Application::vendorAuthor(), vendorAuthor);

        Application::setVendorUrl(vendorUrl);
        xTEST_EQ(Application::vendorUrl(), vendorUrl);

        Application::setVendorEmail(vendorEmail);
        xTEST_EQ(Application::vendorEmail(), vendorEmail);

        Application::setVendorSkype(vendorSkype);
        xTEST_EQ(Application::vendorSkype(), vendorSkype);
    }

    xTEST_CASE("files")
    {

    }

    xTEST_CASE("directories")
    {

    }
}
//-------------------------------------------------------------------------------------------------
