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

		// std::tcout << (OStream() << xTRACE_VAR(m_sRv)).str() << std::endl;
	}

	xTEST_CASE("info")
	{
		m_sRv = version.info(CURLVERSION_FOURTH);
		xTEST(!m_sRv.empty());

		// std::tcout << (OStream() << xTRACE_VAR(m_sRv)).str() << std::endl;

		for (CURLversion v = CURLVERSION_FIRST; v < CURLVERSION_LAST; ++ v) {
			m_sRv = version.info(v);
			xTEST(!m_sRv.empty());
		}
	}

	xTEST_CASE("infoCurrent")
	{
		m_sRv = version.infoCurrent();
		xTEST(!m_sRv.empty());

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
