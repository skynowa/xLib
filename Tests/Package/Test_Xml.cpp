/**
 * \file   Test_Xml.cpp
 * \brief  test Xml
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Xml)
xTEST_UNIT(Test_Xml)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Xml::unit()
{
    xTEST_CASE("Xml::[TEST_CASE_1]")
    {
    	std::ctstring_t filePath = "/home/skynowa/Projects/xLib/Tests/Package/Xml/1.xml";

		XmlDoc doc("UTF-8");
		m_iRv = doc.parseFile(filePath);
		xTEST_EQ(m_iRv, 0);

		std::list<XmlNode> results;
		m_iRv = doc.getContentList("/AvailabilitySearchResult/HotelAvailability/Result", results);
		xTEST_EQ(m_iRv, 0);

		Trace() << xTRACE_VAR(results.size());

		for (auto &it_result : results) {
			std::list<XmlNode> prices;
			m_iRv = it_result.getContentList("Room/Price", prices);
			xTEST_EQ(m_iRv, 0);

			Trace() << xTRACE_VAR(prices.size());

			Trace() << xTRACE_VAR(prices.begin()->getText());
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
