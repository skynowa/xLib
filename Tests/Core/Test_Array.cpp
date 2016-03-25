/**
 * \file   Test_Array.cpp
 * \brief
 */


#include "Test_Array.h"


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Array)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Array::unit()
{
    std::csize_t arraySize = 5;

    Array<size_t, arraySize> array = {{0, 1, 2, 3, 4}};

    xTEST_CASE("operator[]")
    {
        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(i, array[i]);
        }
    }

    xTEST_CASE("at")
    {
        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(i, array.at(i));
        }
    }

    xTEST_CASE("size")
    {
        m_stRv = array.size();
        xTEST_EQ(m_stRv, arraySize);
    }

    xTEST_CASE("clear")
    {
        array.clear();
        xTEST_EQ(array.size(), arraySize);

        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(array[i], std::size_t(0));
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
