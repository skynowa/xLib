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
		ApplicationInfo applicationInfo;
		applicationInfo.name            = xT("[name]");
		applicationInfo.decription      = xT("[decription]");
		applicationInfo.copyrightYears  = xT("[copyrightYears]");
		applicationInfo.usage           = xT("[usage]");
		applicationInfo.help            = xT("[help]");
		applicationInfo.versionMajor    = xT("[versionMajor]");
		applicationInfo.versionMinor    = xT("[versionMinor]");
		applicationInfo.versionPatch    = xT("[versionPatch]");
		applicationInfo.versionType     = xT("[versionType]");
		applicationInfo.versionRevision = xT("[versionRevision]");
		applicationInfo.vendorName      = xT("[vendorName]");
		applicationInfo.vendorDomain    = xT("[vendorDomain]");
		applicationInfo.vendorAuthor    = xT("[vendorAuthor]");
		applicationInfo.vendorUrl       = xT("[vendorUrl]");
		applicationInfo.vendorEmail     = xT("[vendorEmail]");
		applicationInfo.vendorSkype     = xT("[vendorSkype]");
		applicationInfo.vendorJabber    = xT("[vendorJabber]");
		applicationInfo.vendorIcq       = xT("[vendorIcq]");

		xTEST_EQ(applicationInfo.name.empty(), false);
		xTEST_EQ(applicationInfo.decription.empty(), false);
		xTEST_EQ(applicationInfo.copyrightYears.empty(), false);
		xTEST_EQ(applicationInfo.usage.empty(), false);
		xTEST_EQ(applicationInfo.help.empty(), false);
		xTEST_EQ(applicationInfo.versionMajor.empty(), false);
		xTEST_EQ(applicationInfo.versionMinor.empty(), false);
		xTEST_EQ(applicationInfo.versionPatch.empty(), false);
		xTEST_EQ(applicationInfo.versionType.empty(), false);
		xTEST_EQ(applicationInfo.versionRevision.empty(), false);
		xTEST_EQ(applicationInfo.vendorName.empty(), false);
		xTEST_EQ(applicationInfo.vendorDomain.empty(), false);
		xTEST_EQ(applicationInfo.vendorAuthor.empty(), false);
		xTEST_EQ(applicationInfo.vendorUrl.empty(), false);
		xTEST_EQ(applicationInfo.vendorEmail.empty(), false);
		xTEST_EQ(applicationInfo.vendorSkype.empty(), false);
		xTEST_EQ(applicationInfo.vendorJabber.empty(), false);
		xTEST_EQ(applicationInfo.vendorIcq.empty(), false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
