/**
 * \file   Test_HttpClient.cpp
 * \brief  test HttpClient
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;
using namespace curl;

xTEST_CLASS(Test_HttpClient)
xTEST_UNIT(Test_HttpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_HttpClient::unit()
{
	Version version;

    xTEST_CASE("Version::version")
    {
		m_sRv = version.version();
		xTEST_EQ(m_sRv.empty(), false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
