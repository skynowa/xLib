/**
 * \file   Test_ApplicationInfo.cpp
 * \brief  test ApplicationInfo
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_ApplicationInfo)
xTEST_UNIT(Test_ApplicationInfo)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_ApplicationInfo::unit()
{
    xTEST_CASE("data")
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

		ApplicationInfo applicationInfo(data);

		xTEST_EQ(applicationInfo.get().name.empty(), false);
		xTEST_EQ(applicationInfo.get().decription.empty(), false);
		xTEST_EQ(applicationInfo.get().copyrightYears.empty(), false);
		xTEST_EQ(applicationInfo.get().usage.empty(), false);
		xTEST_EQ(applicationInfo.get().help.empty(), false);
		xTEST_EQ(applicationInfo.get().versionMajor.empty(), false);
		xTEST_EQ(applicationInfo.get().versionMinor.empty(), false);
		xTEST_EQ(applicationInfo.get().versionPatch.empty(), false);
		xTEST_EQ(applicationInfo.get().versionType.empty(), false);
		xTEST_EQ(applicationInfo.get().versionRevision.empty(), false);
		xTEST_EQ(applicationInfo.get().vendorName.empty(), false);
		xTEST_EQ(applicationInfo.get().vendorDomain.empty(), false);
		xTEST_EQ(applicationInfo.get().vendorAuthor.empty(), false);
		xTEST_EQ(applicationInfo.get().vendorUrl.empty(), false);
		xTEST_EQ(applicationInfo.get().vendorEmail.empty(), false);
		xTEST_EQ(applicationInfo.get().vendorSkype.empty(), false);
		xTEST_EQ(applicationInfo.get().vendorJabber.empty(), false);
		xTEST_EQ(applicationInfo.get().vendorIcq.empty(), false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
