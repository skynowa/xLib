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

	xTEST_CASE("version")
	{
		m_sRv = version.version();
		xTEST_EQ(m_sRv.empty(), false);

		// std::tcout << (OStream() << xTRACE_VAR(m_sRv)).str() << std::endl;
	}

	xTEST_CASE("info")
	{
		m_sRv = version.info(CURLVERSION_FOURTH);
		xTEST_EQ(m_sRv.empty(), false);

		// std::tcout << (OStream() << xTRACE_VAR(m_sRv)).str() << std::endl;
	}

	xTEST_CASE("infoCurrent")
	{
		m_sRv = version.infoCurrent();
		xTEST_EQ(m_sRv.empty(), false);

		// std::tcout << (OStream() << xTRACE_VAR(m_sRv)).str() << std::endl;
	}

	xTEST_CASE("protocols")
	{
		std::vec_tstring_t protos;
		version.protocols(&protos);
		xTEST_EQ(protos.empty(), false)

		// std::tcout << (OStream() << xTRACE_VAR(protos)).str() << std::endl;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
