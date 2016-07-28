/**
 * \file   Test_Application.cpp
 * \brief  test Application
 */


#include "Test_Application.h"


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Application)
//-------------------------------------------------------------------------------------------------
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
bool_t
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
		ApplicationInfoData data;
		data.name            = xT("[name]");
		data.decription      = xT("[decription]");
		data.copyrightYears  = xT("[copyrightYears]");
		data.usage           = xT("[usage]");
		data.help            = xT("[help]");
		data.versionMajor    = xT("[versionMajor]");
		data.versionMinor    = xT("[versionMinor]");
		data.versionPatch    = xT("[versionPatch]");
		data.versionType     = xT("[versionType]");
		data.versionRevision = xT("[versionRevision]");
		data.vendorName      = xT("[vendorName]");
		data.vendorDomain    = xT("[vendorDomain]");
		data.vendorAuthor    = xT("[vendorAuthor]");
		data.vendorUrl       = xT("[vendorUrl]");
		data.vendorEmail     = xT("[vendorEmail]");
		data.vendorSkype     = xT("[vendorSkype]");
		data.vendorJabber    = xT("[vendorJabber]");
		data.vendorIcq       = xT("[vendorIcq]");

		ApplicationInfo applicationInfo;
		applicationInfo.set(data);

		Application::set(applicationInfo);
		xTEST_EQ(applicationInfo.get().name,            data.name);
		xTEST_EQ(applicationInfo.get().decription,      data.decription);
		xTEST_EQ(applicationInfo.get().copyrightYears,  data.copyrightYears);
		xTEST_EQ(applicationInfo.get().usage,           data.usage);
		xTEST_EQ(applicationInfo.get().help,            data.help);
		xTEST_EQ(applicationInfo.get().versionMajor,    data.versionMajor);
		xTEST_EQ(applicationInfo.get().versionMinor,    data.versionMinor);
		xTEST_EQ(applicationInfo.get().versionPatch,    data.versionPatch);
		xTEST_EQ(applicationInfo.get().versionType,     data.versionType);
		xTEST_EQ(applicationInfo.get().versionRevision, data.versionRevision);
		xTEST_EQ(applicationInfo.get().vendorName,      data.vendorName);
		xTEST_EQ(applicationInfo.get().vendorDomain,    data.vendorDomain);
		xTEST_EQ(applicationInfo.get().vendorAuthor,    data.vendorAuthor);
		xTEST_EQ(applicationInfo.get().vendorUrl,       data.vendorUrl);
		xTEST_EQ(applicationInfo.get().vendorEmail,     data.vendorEmail);
		xTEST_EQ(applicationInfo.get().vendorSkype,     data.vendorSkype);
		xTEST_EQ(applicationInfo.get().vendorJabber,    data.vendorJabber);
		xTEST_EQ(applicationInfo.get().vendorIcq,       data.vendorIcq);
    }

    xTEST_CASE("files")
    {

    }

    xTEST_CASE("directories")
    {

    }

    return true;
}
//-------------------------------------------------------------------------------------------------
