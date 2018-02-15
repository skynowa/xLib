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
	LIBXML_TEST_VERSION

    xTEST_CASE("1.xml")
    {
    	std::ctstring_t filePath = "/home/skynowa/Projects/xLib/Tests/Package/Xml/1.xml";

		XmlDoc doc("UTF-8");
		m_iRv = doc.parseFile(filePath);
		xTEST_EQ(m_iRv, 0);

		// getRootNode
		{
			XmlNode root;
			m_iRv = doc.getRootNode(root);
			xTEST_EQ(m_iRv, 0);

			std::list<XmlNode> results;
			m_iRv = root.getContents("/AvailabilitySearchResult/HotelAvailability/Result", results);
			xTEST_EQ(m_iRv, 0);
			xTEST_EQ(results.size(), (std::size_t)3);
		}

		std::list<XmlNode> results;
		m_iRv = doc.getContents("/AvailabilitySearchResult/HotelAvailability/Result", results);
		xTEST_EQ(m_iRv, 0);
		xTEST_EQ(results.size(), (std::size_t)3);

		for (size_t i = 0; i < results.size(); ++ i) {
			XmlNode &it_result = *std::next(results.begin(), i);

			XmlNode price;
			m_iRv = it_result.getContent("Room/Price", price);
			xTEST_EQ(m_iRv, 0);

			// getText
			{
				switch (i) {
				case 0:
					xTEST_EQ(price.getText(), std::tstring_t("111"));
					break;
				case 1:
					xTEST_EQ(price.getText(), std::tstring_t("222"));
					break;
				case 2:
					xTEST_EQ(price.getText(), std::tstring_t("333"));
					break;
				default:
					xTEST_FAIL;
					break;
				}
			}

			// getAttributes
			{
				std::map_tstring_t priceAttrs;
				price.getAttributes(priceAttrs);

				switch (i) {
				case 0:
					{
						std::map_tstring_t expected {{"amt1", "211.40"}, {"amt2", "211.50"}};
						xTEST_EQ(priceAttrs, expected);
					}
					break;
				case 1:
					{
						std::map_tstring_t expected {{"amt1", "161.20"}, {"amt2", "211.50"}, {"amt3", "211.60"}};
						xTEST_EQ(priceAttrs, expected);
					}
					break;
				case 2:
					{
						std::map_tstring_t expected {{"amt1", "172.00"}, {"amt2", "211.50"}, {"amt3", "211.60"}, {"amt4", "211.70"}};
						xTEST_EQ(priceAttrs, expected);
					}
					break;
				default:
					xTEST_FAIL;
					break;
				}
			}

			//
			{
			}
		} // for (results)
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
