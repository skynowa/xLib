/**
 * \file   CxTest_CxArray.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxArray.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxArray::unit(
    culonglong_t &a_caseLoops
)
{
    std::csize_t arraySize = 5;


    CxArray<size_t, arraySize> array = {{0, 1, 2, 3, 4}};

    xTEST_CASE("CxArray::operator[]", a_caseLoops)
    {
        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(i, array[i]);
        }
    }

    xTEST_CASE("CxArray::at", a_caseLoops)
    {
        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(i, array.at(i));
        }
    }

    xTEST_CASE("CxArray::size", a_caseLoops)
    {
        m_stRv = array.size();
        xTEST_EQ(arraySize, m_stRv);
    }

    xTEST_CASE("CxArray::clear", a_caseLoops)
    {
        array.clear();
    }

    xTEST_CASE("make_array", a_caseLoops) {
        make_array<std::tstring_t>( xT("0"),  xT("1") );
        make_array<std::tstring_t>( xT("0"),  xT("1"),  xT("2") );
    }
}
//-------------------------------------------------------------------------------------------------
