/**
 * \file   Test_Application.cpp
 * \brief  test Application
 */


#include "Test_Application.h"


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Application)
//-------------------------------------------------------------------------------------------------
class Failer
{
public:
    void_t main()
    {
        foo2();
    }

protected:
    void_t foo1()
    {
        bug_DevisionByZero();	// <<< set BUG here
    }

    void_t foo2()
    {
        foo1();
    }

private:
    void_t bug_Segmentationfault()
    {
        int *p = xPTR_NULL;
        *p = 10;

        Trace() << xTRACE_VAR(p);
    }

    void_t bug_UnhandledException()
    {
        std::vector<size_t> vecRv;
        vecRv.at(1);	  // unhandled exception: calls terminate handler

        Trace() << xTRACE_VAR(vecRv);
    }

    void_t bug_DevisionByZero()
    {
		double dRv = 40 / 0;

		Trace() << xTRACE_VAR(dRv);
    }
};
//-------------------------------------------------------------------------------------------------
class UserApplication :
    public Application
    /// user application
{
public:
	UserApplication(std::ctstring_t &a_appGuid, std::ctstring_t &a_locale) :
		Application(a_appGuid, a_locale)
	{
	}

    virtual int_t onRun() xOVERRIDE
    {
        std::vec_tstring_t args;
        Application::args(true, &args);
        Application::isRunnig();
        Application::dirsCreate();
        bool bRv = Application::selfCheck();

        Failer().main();
    }

    static void_t onSignals(int_t a_signal)
    {
        xTRACE_FUNC;
        Trace() << Signal::decription(a_signal);

        Application::exit(a_signal);
    }

    static void_t onExit()
    {
        xTRACE_FUNC;
    }

    static void_t onTerminate()
    {
        xTRACE_FUNC;
    }

    static void_t onUnexpected()
    {
        xTRACE_FUNC;
    }

private:
    xNO_COPY_ASSIGN(UserApplication)
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Application::unit()
{
    xTEST_CASE("Application")
    {
        UserApplication userApp(xT("[app_name]_guid"), xT(""));
	#if 1
		userApp.signal().connectAll(UserApplication::onSignals);
		userApp.signal().connectExit(UserApplication::onExit);
		userApp.signal().connectTerminate(UserApplication::onTerminate);
		userApp.signal().connectUnexpected(UserApplication::onUnexpected);
	#endif
        userApp.run();
    }

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

		Application::setInfo(applicationInfo);
		xTEST_EQ(Application::info().get().name,            data.name);
		xTEST_EQ(Application::info().get().decription,      data.decription);
		xTEST_EQ(Application::info().get().copyrightYears,  data.copyrightYears);
		xTEST_EQ(Application::info().get().usage,           data.usage);
		xTEST_EQ(Application::info().get().help,            data.help);
		xTEST_EQ(Application::info().get().versionMajor,    data.versionMajor);
		xTEST_EQ(Application::info().get().versionMinor,    data.versionMinor);
		xTEST_EQ(Application::info().get().versionPatch,    data.versionPatch);
		xTEST_EQ(Application::info().get().versionType,     data.versionType);
		xTEST_EQ(Application::info().get().versionRevision, data.versionRevision);
		xTEST_EQ(Application::info().get().vendorName,      data.vendorName);
		xTEST_EQ(Application::info().get().vendorDomain,    data.vendorDomain);
		xTEST_EQ(Application::info().get().vendorAuthor,    data.vendorAuthor);
		xTEST_EQ(Application::info().get().vendorUrl,       data.vendorUrl);
		xTEST_EQ(Application::info().get().vendorEmail,     data.vendorEmail);
		xTEST_EQ(Application::info().get().vendorSkype,     data.vendorSkype);
		xTEST_EQ(Application::info().get().vendorJabber,    data.vendorJabber);
		xTEST_EQ(Application::info().get().vendorIcq,       data.vendorIcq);
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
