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
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
