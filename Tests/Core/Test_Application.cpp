/**
 * \file   Test_Application.cpp
 * \brief  test Application
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_Application)
xTEST_UNIT(Test_Application)
//-------------------------------------------------------------------------------------------------
class Failer
{
public:
    void_t bug();

private:
	int_t  bug_DivideByZero();
	int_t  bug_CauseSegfault();
	bool_t bug_StackOverflow();
	int_t  bug_InfiniteLoop();
		///< break out with CTRL+C to test SIGINT handling
	bool_t bug_IllegalInstruction();
	bool_t bug_CauseCalamity();
	bool_t bug_UnhandledException();
        ///< unhandled exception: calls terminate handler
};
//-------------------------------------------------------------------------------------------------
xNO_INLINE int_t
Failer::bug_DivideByZero()
{
	int a = 1;
	int b = 0;

	return a / b;
}
//-------------------------------------------------------------------------------------------------
xNO_INLINE int_t
Failer::bug_CauseSegfault()
{
	int * p = (int*)0x12345678;
	*p = 0;

	return *p;
}
//-------------------------------------------------------------------------------------------------
xNO_INLINE bool_t
bug_StackOverflow();

xNO_INLINE bool_t
Failer::bug_StackOverflow()
{
	int foo[1000000];

#if xTEMP_DISABLED
    (void)foo;
    bug_StackOverflow();
#endif

	return true;
}
//-------------------------------------------------------------------------------------------------
xNO_INLINE int_t
Failer::bug_InfiniteLoop()
{
	int_t i = 0;

	while (true) {
		++ i;
	}

	return i;
}
//-------------------------------------------------------------------------------------------------
xNO_INLINE bool_t
Failer::bug_IllegalInstruction()
{
	// I couldn't find an easy way to cause this one, so I'm cheating
	return raise(SIGILL);
}
//-------------------------------------------------------------------------------------------------
xNO_INLINE bool_t
Failer::bug_UnhandledException()
{
	std::vector<std::size_t> vecRv;
	vecRv.at(10);

	return !vecRv.empty();
}
//-------------------------------------------------------------------------------------------------
xNO_INLINE void_t
Failer::bug()
{
	//// ::: set BUG here :::

	std::tcout << bug_DivideByZero()       << std::endl;
//	std::tcout << bug_CauseSegfault()      << std::endl;
//	std::tcout << bug_StackOverflow()      << std::endl;
//	std::tcout << bug_InfiniteLoop()       << std::endl;
//	std::tcout << bug_IllegalInstruction() << std::endl;
//	std::tcout << bug_StackOverflow()      << std::endl;
//	std::tcout << bug_UnhandledException() << std::endl;
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
        Failer().bug();

        return 0;
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
        userApp.run();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
