/**
 * \file   Test_Xml.cpp
 * \brief  test Xml
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl::package::xml;

xTEST_UNIT(Test_Xml)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Xml::unit()
{
    LIBXML_TEST_VERSION

    xTEST_CASE("1.xml")
    {
        std::ctstring_t filePath = option().testDirPath + "/Package/Xml/1.xml";
        xTEST(FileInfo(filePath).isExists());

        Doc doc("UTF-8");

        Node root;
        doc.parseFile(filePath, root);

        // nodes
        std::vector<Node> results;
        root.nodes("/AvailabilitySearchResult/HotelAvailability/Result", results);
        xTEST_EQ(results.size(), 3);

        // findNodes
        {
            std::cvec_tstring_t xpaths
            {
                "/AvailabilitySearchResult/HotelAvailability/Result",
                "/AvailabilitySearchResult/HotelAvailability/Result/Room"
            };

            std::vector<Node> finds;
            root.findNodes(xpaths, finds);
            xTEST_EQ(finds.size(), 6);
        }

        for (size_t i = 0; i < results.size(); ++ i) {
            Node &it_result = results[i];

            Node price;
            it_result.node("Room/Price", price);

            // text
            {
                switch (i) {
                case 0:
                    xTEST_EQ(price.text(), std::tstring_t("111"));
                    break;
                case 1:
                    xTEST_EQ(price.text(), std::tstring_t("222"));
                    break;
                case 2:
                    xTEST_EQ(price.text(), std::tstring_t("333"));
                    break;
                default:
                    xTEST_FAIL;
                    break;
                }
            }

            // attribute, attributes
            {
                std::map_tstring_t priceAttrs;
                price.attributes(priceAttrs);

                switch (i) {
                case 0:
                    {
                        std::map_tstring_t expected {{"amt1", "211.40"}, {"amt2", "211.50"}};
                        xTEST_EQ(priceAttrs, expected);
                        xTEST_EQ(price.attribute("amt1"), std::tstring_t("211.40"));
                    }
                    break;
                case 1:
                    {
                        std::map_tstring_t expected {{"amt1", "161.20"}, {"amt2", "211.50"}, {"amt3", "211.60"}};
                        xTEST_EQ(priceAttrs, expected);
                        xTEST_EQ(price.attribute("amt2"), std::tstring_t("211.50"));
                    }
                    break;
                case 2:
                    {
                        std::map_tstring_t expected {{"amt1", "172.00"}, {"amt2", "211.50"}, {"amt3", "211.60"}, {"amt4", "211.70"}};
                        xTEST_EQ(priceAttrs, expected);
                        xTEST_EQ(price.attribute("amt3"), std::tstring_t("211.60"));
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

    xTEST_CASE("code, str")
    {
	#if xTEST_IGNORE
		std::ctstring_t filePath = option().testDirPath + "/Package/Xml/bad.xml";

		Doc doc("UTF-8");
		doc.parseFile(filePath);
	#endif
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
            m_bRv = Doc::isValidLight(data[i].test);
            xTEST_EQ(m_bRv, data[i].expect);
        }
    }

    xTEST_CASE("Node::childSize")
    {
        std::ctstring_t filePath = option().testDirPath + "/Package/Xml/2.xml";

        std::map<std::tstring_t, std::size_t> data
        {
            {xT("Items"),  3},
            {xT("BedsID"), 0},
            {xT("Price"),  0}
        };

        Doc doc("UTF-8");

        Node root;
        doc.parseFile(filePath, root);

        Node avail;
        root.node("/AvailabilitySearchResult", avail);
        xTEST_EQ(avail.childSize(), 9);

		for (const auto &[it_tag, it_size] : data) {
			Node item;
			root.node("/AvailabilitySearchResult/" + it_tag, item);
			xTEST_EQ(item.childSize(), it_size);
		}
    }

    xTEST_CASE("Node::childMap")
    {
        std::ctstring_t filePath = option().testDirPath + "/Package/Xml/2.xml";

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

        Doc doc("UTF-8");

        Node root;
        doc.parseFile(filePath, root);

        std::map_tstring_t results;
        root.childMap("/AvailabilitySearchResult", results);
        xTEST_EQ(results.size(), expect.size());
        xTEST_EQ(results, expect);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
