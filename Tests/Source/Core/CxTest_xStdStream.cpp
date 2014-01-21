/**
 * \file   CxTest_xStdStream.cpp
 * \brief  test xStdStream
 */


#include <Test/Core/CxTest_xStdStream.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_xStdStream::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxString::operator << for std::ustring_t", a_caseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            std::ustring_t usStr;
            CxStdRandom    random;

            usStr.resize( random.nextInt(size_t(1), size_t(64)) );
            std::fill_n(usStr.begin(), usStr.size(), static_cast<std::ustring_t::value_type>( random.nextInt(1, 255) ));

            std::tstring_t sVal1 = std::tstring_t(usStr.begin(), usStr.end());

            std::tostringstream_t osOut;   osOut << usStr;
            std::tstring_t sVal2 = osOut.str();

            xTEST_EQ(sVal1, sVal2);
        }
    }

    xTEST_CASE("CxString::operator << for std::vector", a_caseLoops)
    {
        m_vsRv.clear();

        m_vsRv.push_back(xT("Value0"));
        m_vsRv.push_back(xT("Value1"));
        m_vsRv.push_back(xT("Value2"));
        m_vsRv.push_back(xT("Value3"));
        m_vsRv.push_back(xT("Value4"));

        std::tostringstream_t osOut;   osOut << m_vsRv;
        xTEST_EQ(false, osOut.str().empty());

        m_vsRv.clear();
    }

    xTEST_CASE("CxString::operator << for std::map", a_caseLoops)
    {
        m_msRv.clear();

        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key0"), xT("Value0")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key1"), xT("Value1")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key2"), xT("Value2")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key3"), xT("Value3")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key4"), xT("Value4")) );

        std::tostringstream_t osOut;   osOut << m_msRv;
        xTEST_EQ(false, osOut.str().empty());

        m_msRv.clear();
    }

    xTEST_CASE("CxString::operator << for std::multimap", a_caseLoops)
    {
        m_mmsRv.clear();

        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key0"), xT("Value0")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key1"), xT("Value1")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key2"), xT("Value2")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key0"), xT("Value0")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key1"), xT("Value1")) );

        std::tostringstream_t osOut;   osOut << m_mmsRv;
        xTEST_EQ(false, osOut.str().empty());

        m_mmsRv.clear();
    }
}
//-------------------------------------------------------------------------------------------------
