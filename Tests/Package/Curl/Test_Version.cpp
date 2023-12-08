/**
 * \file   Test_HttpClient.cpp
 * \brief  test HttpClient
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl::package::curl;

xTEST_UNIT(Test_HttpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_HttpClient::unit()
{
	Version version;

	xTEST_CASE("version")
	{
		CURLversion cvRv = version.version();
		xTEST_GR(cvRv, 0);
	}

	xTEST_CASE("info")
	{
		m_sRv = version.info();
		xTEST(!m_sRv.empty());
	}

	xTEST_CASE("protocols")
	{
		std::vec_tstring_t protos;
		version.protocols(&protos);
		xTEST(!protos.empty())
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
