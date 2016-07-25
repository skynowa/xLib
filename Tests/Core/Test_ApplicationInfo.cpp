/**
 * \file   Test_ApplicationInfo.cpp
 * \brief  test ApplicationInfo
 */


#include "Test_ApplicationInfo.h"


//-------------------------------------------------------------------------------------------------
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

		xTEST_EQ(applicationInfo.data().name.empty(), false);
		xTEST_EQ(applicationInfo.data().decription.empty(), false);
		xTEST_EQ(applicationInfo.data().copyrightYears.empty(), false);
		xTEST_EQ(applicationInfo.data().usage.empty(), false);
		xTEST_EQ(applicationInfo.data().help.empty(), false);
		xTEST_EQ(applicationInfo.data().versionMajor.empty(), false);
		xTEST_EQ(applicationInfo.data().versionMinor.empty(), false);
		xTEST_EQ(applicationInfo.data().versionPatch.empty(), false);
		xTEST_EQ(applicationInfo.data().versionType.empty(), false);
		xTEST_EQ(applicationInfo.data().versionRevision.empty(), false);
		xTEST_EQ(applicationInfo.data().vendorName.empty(), false);
		xTEST_EQ(applicationInfo.data().vendorDomain.empty(), false);
		xTEST_EQ(applicationInfo.data().vendorAuthor.empty(), false);
		xTEST_EQ(applicationInfo.data().vendorUrl.empty(), false);
		xTEST_EQ(applicationInfo.data().vendorEmail.empty(), false);
		xTEST_EQ(applicationInfo.data().vendorSkype.empty(), false);
		xTEST_EQ(applicationInfo.data().vendorJabber.empty(), false);
		xTEST_EQ(applicationInfo.data().vendorIcq.empty(), false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
