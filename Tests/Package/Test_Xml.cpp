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
        doc.parseFile(filePath);

        // getRootNode
        XmlNode root;
        doc.getRootNode(root);

        // getContents
        std::list<XmlNode> results;
        root.getContents("/AvailabilitySearchResult/HotelAvailability/Result", results);
        xTEST_EQ(results.size(), (std::size_t)3);

        // findContents
        {
            std::clist_tstring_t xpaths
            {
                "/AvailabilitySearchResult/HotelAvailability/Result",
                "/AvailabilitySearchResult/HotelAvailability/Result/Room"
            };

            std::list<XmlNode> finds;
            root.findContents(xpaths, finds);
            xTEST_EQ(finds.size(), (std::size_t)6);
        }

        for (size_t i = 0; i < results.size(); ++ i) {
            XmlNode &it_result = *std::next(results.begin(), i);

            XmlNode price;
            it_result.getContent("Room/Price", price);

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

            // getAttribute, getAttributes
            {
                std::map_tstring_t priceAttrs;
                price.getAttributes(priceAttrs);

                switch (i) {
                case 0:
                    {
                        std::map_tstring_t expected {{"amt1", "211.40"}, {"amt2", "211.50"}};
                        xTEST_EQ(priceAttrs, expected);
                        xTEST_EQ(price.getAttribute("amt1"), std::tstring_t("211.40"));
                    }
                    break;
                case 1:
                    {
                        std::map_tstring_t expected {{"amt1", "161.20"}, {"amt2", "211.50"}, {"amt3", "211.60"}};
                        xTEST_EQ(priceAttrs, expected);
                        xTEST_EQ(price.getAttribute("amt2"), std::tstring_t("211.50"));
                    }
                    break;
                case 2:
                    {
                        std::map_tstring_t expected {{"amt1", "172.00"}, {"amt2", "211.50"}, {"amt3", "211.60"}, {"amt4", "211.70"}};
                        xTEST_EQ(priceAttrs, expected);
                        xTEST_EQ(price.getAttribute("amt3"), std::tstring_t("211.60"));
                    }
                    break;
                default:
                    xTEST_FAIL;
                    break;
                }
            }

            // dump
			if (i == 0) {
				std::ctstring_t expected = xT("<Result id=\"13030163-2\">\n"
					"            <Room>\n"
					"                <RoomType code=\"1004527\" text=\"Double Or Twin Deluxe\"/>\n"
					"                <MealType code=\"1000018\" text=\"Bed and breakfast\"/>\n"
					"                <Price amt1=\"211.40\" amt2=\"211.50\">111</Price>\n"
					"            </Room>\n"
					"        </Result>");

				m_sRv = it_result.dump(true);
				xTEST_EQ(m_sRv, expected);
			}
        } // for (results)
    }

    xTEST_CASE("lastError, lastErrorStr")
    {
        std::ctstring_t filePath = "/home/skynowa/Projects/xLib/Tests/Package/Xml/bad.xml";

        XmlDoc doc("UTF-8");
        doc.parseFile(filePath);
    }

    xTEST_CASE("isValidLight")
    {
        const data2_bool_t data[]
        {
            {"<?xml version=\"1.0\"?>", true},
            {"<?xml version=\"1.0\" encoding=\"UTF-8\"?>", true},
            {"<?xml version=\"1.0\" standalone=\"yes\"?>", true},
            {"<?xml version=\"1.0\" encoding=\"UTF-16\" standalone=\"yes\"?>", true},
            {"", false},
            {"abcdef123456789", false},
            {"<?xml", false},
            {"<", false}
        };

        for (size_t i = 0; i < Utils::arraySizeT(data); ++ i) {
            m_bRv = XmlDoc::isValidLight(data[i].test);
            xTEST_EQ(m_bRv, data[i].expect);
        }
    }

    xTEST_CASE("XmlNode::getChildrenContents")
    {
        std::ctstring_t filePath = "/home/skynowa/Projects/xLib/Tests/Package/Xml/2.xml";

        std::cmap_tstring_t expect
        {
            {xT("Currency"),  xT("EUR")},
            {xT("TestMode"),  xT("true")},
            {xT("HotelID"),   xT("12345")},
            {xT("HotelName"), xT("XXXXX")},
            {xT("RoomType"),  xT("Double Or Twin Deluxe")},
            {xT("MealType"),  xT("Bed and breakfast")},
            {xT("BedsID"),    xT("")},
            {xT("Price"),     xT("211.50")}
        };

        XmlDoc doc("UTF-8");
        doc.parseFile(filePath);

        XmlNode root;
        doc.getRootNode(root);

        std::map_tstring_t results;
        root.getChildrenContents("/AvailabilitySearchResult", results);
        xTEST_EQ(results.size(), expect.size());
        xTEST_EQ(results, expect);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
