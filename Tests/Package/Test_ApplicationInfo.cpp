/**
 * \file   Test_ApplicationInfo.cpp
 * \brief  test ApplicationInfo
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
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

		xTEST(!applicationInfo.name.empty());
		xTEST(!applicationInfo.decription.empty());
		xTEST(!applicationInfo.copyrightYears.empty());
		xTEST(!applicationInfo.usage.empty());
		xTEST(!applicationInfo.help.empty());
		xTEST(!applicationInfo.versionMajor.empty());
		xTEST(!applicationInfo.versionMinor.empty());
		xTEST(!applicationInfo.versionPatch.empty());
		xTEST(!applicationInfo.versionType.empty());
		xTEST(!applicationInfo.versionRevision.empty());
		xTEST(!applicationInfo.vendorName.empty());
		xTEST(!applicationInfo.vendorDomain.empty());
		xTEST(!applicationInfo.vendorAuthor.empty());
		xTEST(!applicationInfo.vendorUrl.empty());
		xTEST(!applicationInfo.vendorEmail.empty());
		xTEST(!applicationInfo.vendorSkype.empty());
		xTEST(!applicationInfo.vendorJabber.empty());
		xTEST(!applicationInfo.vendorIcq.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
