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
    void_t foo();

protected:
    void_t foo1();
    void_t foo2();

private:
    void_t bug_Segmentationfault();
        ///< segmentation fault
    void_t bug_UnhandledException();
        ///< unhandled exception: calls terminate handler
    void_t bug_DevisionByZero();
        ///< devision by zero
};

xNO_INLINE void_t
Failer::foo()
{
	foo2();
}
xNO_INLINE void_t
Failer::foo1()
{
	bug_DevisionByZero();	// <<< set BUG here
}
xNO_INLINE void_t
Failer::foo2()
{
	foo1();
}
xNO_INLINE void_t
Failer::bug_Segmentationfault()
{
	int *p = xPTR_NULL;
	*p = 10;

	Trace() << xTRACE_VAR(p);
}
xNO_INLINE void_t
Failer::bug_UnhandledException()
{
	std::vector<std::size_t> vecRv;
	vecRv.at(10);

	Trace() << xTRACE_VAR(vecRv);
}
xNO_INLINE void_t
Failer::bug_DevisionByZero()
{
	double dRv = 40 / 0;

	Trace() << xTRACE_VAR(dRv);
}
//-------------------------------------------------------------------------------------------------
class UserApplication :
    public Application
    /// user application
{
public:
	xNO_INLINE
	UserApplication(std::ctstring_t &a_appGuid, std::ctstring_t &a_locale) :
		Application(a_appGuid, a_locale)
	{
	}

    xNO_INLINE virtual int_t
    onRun() xOVERRIDE
    {
        Failer().foo();
    }

    xNO_INLINE static void_t
    onSignals(int_t a_signal)
    {
        xTRACE_FUNC;

        Trace() << Signal::decription(a_signal) << "\n";
        Trace() << StackTrace().toString()      << "\n";

        exit(a_signal);
    }

    xNO_INLINE static void_t
    onExit()
    {
        xTRACE_FUNC;
    }

    xNO_INLINE static void_t
    onTerminate()
    {
        xTRACE_FUNC;
    }

    xNO_INLINE static void_t
    onUnexpected()
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
    xTEST_CASE("args")
    {
        UserApplication application(xT("[app_name]_guid"), xT(""));

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
        UserApplication application(xT("[app_name]_guid"), xT(""));
        application.dirsCreate();
    }

    xTEST_CASE("selfCheck")
    {
        UserApplication application(xT("[app_name]_guid"), xT(""));
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

		UserApplication::setInfo(applicationInfo);
		xTEST_EQ(UserApplication::info().get().name,            data.name);
		xTEST_EQ(UserApplication::info().get().decription,      data.decription);
		xTEST_EQ(UserApplication::info().get().copyrightYears,  data.copyrightYears);
		xTEST_EQ(UserApplication::info().get().usage,           data.usage);
		xTEST_EQ(UserApplication::info().get().help,            data.help);
		xTEST_EQ(UserApplication::info().get().versionMajor,    data.versionMajor);
		xTEST_EQ(UserApplication::info().get().versionMinor,    data.versionMinor);
		xTEST_EQ(UserApplication::info().get().versionPatch,    data.versionPatch);
		xTEST_EQ(UserApplication::info().get().versionType,     data.versionType);
		xTEST_EQ(UserApplication::info().get().versionRevision, data.versionRevision);
		xTEST_EQ(UserApplication::info().get().vendorName,      data.vendorName);
		xTEST_EQ(UserApplication::info().get().vendorDomain,    data.vendorDomain);
		xTEST_EQ(UserApplication::info().get().vendorAuthor,    data.vendorAuthor);
		xTEST_EQ(UserApplication::info().get().vendorUrl,       data.vendorUrl);
		xTEST_EQ(UserApplication::info().get().vendorEmail,     data.vendorEmail);
		xTEST_EQ(UserApplication::info().get().vendorSkype,     data.vendorSkype);
		xTEST_EQ(UserApplication::info().get().vendorJabber,    data.vendorJabber);
		xTEST_EQ(UserApplication::info().get().vendorIcq,       data.vendorIcq);
    }

    xTEST_CASE("files")
    {

    }

    xTEST_CASE("directories")
    {

    }

    xTEST_CASE("connect")
    {
        UserApplication userApp(xT("[app_name]_guid"), xT(""));
	#if 0
		userApp.signal().connectAll(UserApplication::onSignals);
		userApp.signal().connectExit(UserApplication::onExit);
		userApp.signal().connectTerminate(UserApplication::onTerminate);
		userApp.signal().connectUnexpected(UserApplication::onUnexpected);
	#endif
        userApp.run();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
