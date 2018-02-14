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
		xTEST_EQ(results.size(), (std::size_t)3);

		for (auto &it_result : results) {
			std::list<XmlNode> prices;
			m_iRv = it_result.getContentList("Room/Price", prices);
			xTEST_EQ(m_iRv, 0);
			xTEST_EQ(prices.size(), (std::size_t)1);

            const XmlNode &result = *prices.begin();

			Trace() << xTRACE_VAR(result.getText());

			std::map_tstring_t attrs;
			result.getAttributes(attrs);

			std::cout << xTRACE_VAR(attrs) << "\n";
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
