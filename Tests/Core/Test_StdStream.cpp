/**
 * \file   Test_StdStream.cpp
 * \brief  test StdStream
 */


#include "Test_StdStream.h"

#include <xLib/Crypt/Random.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_StdStream)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_StdStream::unit()
{
    xTEST_CASE("operator << for std::ustring_t")
    {
        for (size_t i = 0; i < 10; ++ i) {
            std::ustring_t str;
            StdRandom      random;

            str.resize( random.nextInt(size_t(1), size_t(64)) );
            std::fill_n(str.begin(), str.size(), static_cast<std::ustring_t::value_type>( random.nextInt(1, 255) ));

            std::tstring_t val1 = std::tstring_t(str.begin(), str.end());

            std::tostringstream_t oss;
            oss << str;
            std::tstring_t val2 = oss.str();
            xTEST_EQ(val1, val2);
        }
    }

    xTEST_CASE("operator << for std::pair")
    {
        std::pair<std::tstring_t, std::tstring_t> data(xT("aaa"), xT("bbb"));

        std::tostringstream_t oss;
        oss << data;
        xTEST_EQ(oss.str().empty(), false);
    }

    xTEST_CASE("operator << for std::vector")
    {
        m_vsRv.clear();

        m_vsRv.push_back(xT("Value0"));
        m_vsRv.push_back(xT("Value1"));
        m_vsRv.push_back(xT("Value2"));
        m_vsRv.push_back(xT("Value3"));
        m_vsRv.push_back(xT("Value4"));

        std::tostringstream_t oss;
        oss << m_vsRv;
        xTEST_EQ(oss.str().empty(), false);

        m_vsRv.clear();
    }

    xTEST_CASE("operator << for std::map")
    {
        m_msRv.clear();

        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key0"), xT("Value0")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key1"), xT("Value1")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key2"), xT("Value2")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key3"), xT("Value3")) );
        m_msRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key4"), xT("Value4")) );

        std::tostringstream_t oss;
        oss << m_msRv;
        xTEST_EQ(oss.str().empty(), false);

        m_msRv.clear();
    }

    xTEST_CASE("operator << for std::multimap")
    {
        m_mmsRv.clear();

        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key0"), xT("Value0")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key1"), xT("Value1")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key2"), xT("Value2")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key0"), xT("Value0")) );
        m_mmsRv.insert( std::pair<std::tstring_t, std::tstring_t>(xT("Key1"), xT("Value1")) );

        std::tostringstream_t oss;
        oss << m_mmsRv;
        xTEST_EQ(oss.str().empty(), false);

        m_mmsRv.clear();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
