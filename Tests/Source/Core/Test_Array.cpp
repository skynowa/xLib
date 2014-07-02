/**
 * \file   Test_Array.cpp
 * \brief
 */


#include <Test/Core/Test_Array.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Array::unit(
    culonglong_t &a_caseLoops
)
{
    std::csize_t arraySize = 5;


    Array<size_t, arraySize> array = {{0, 1, 2, 3, 4}};

    xTEST_CASE("Array::operator[]", a_caseLoops)
    {
        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(i, array[i]);
        }
    }

    xTEST_CASE("Array::at", a_caseLoops)
    {
        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(i, array.at(i));
        }
    }

    xTEST_CASE("Array::size", a_caseLoops)
    {
        m_stRv = array.size();
        xTEST_EQ(arraySize, m_stRv);
    }

    xTEST_CASE("Array::clear", a_caseLoops)
    {
        array.clear();
    }

    xTEST_CASE("make_array", a_caseLoops) {
        make_array<std::tstring_t>( xT("0"),  xT("1") );
        make_array<std::tstring_t>( xT("0"),  xT("1"),  xT("2") );
    }
}
//-------------------------------------------------------------------------------------------------
