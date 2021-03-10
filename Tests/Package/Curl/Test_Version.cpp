/**
 * \file   Test_HttpClient.cpp
 * \brief  test HttpClient
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl::curl;

xTEST_UNIT(Test_HttpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_HttpClient::unit()
{
	Version version;

	xTEST_CASE("version")
	{
		m_sRv = version.version();
		xTEST(!m_sRv.empty());
	}

	xTEST_CASE("info")
	{
		m_sRv = version.info(CURLVERSION_FIRST);
		xTEST(!m_sRv.empty());
	}

	xTEST_CASE("infoCurrent")
	{
		m_sRv = version.infoCurrent();
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
