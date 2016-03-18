/**
 * \file   Test_Array.cpp
 * \brief
 */


#include <Test/Core/Test_Array.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Array)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Array::unit(
    culonglong_t &a_caseLoops
)
{
    std::csize_t arraySize = 5;


    Array<size_t, arraySize> array = {{0, 1, 2, 3, 4}};

    xTEST_CASE("operator[]", a_caseLoops)
    {
        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(i, array[i]);
        }
    }

    xTEST_CASE("at", a_caseLoops)
    {
        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(i, array.at(i));
        }
    }

    xTEST_CASE("size", a_caseLoops)
    {
        m_stRv = array.size();
        xTEST_EQ(m_stRv, arraySize);
    }

    xTEST_CASE("clear", a_caseLoops)
    {
        array.clear();
        xTEST_EQ(array.size(), arraySize);

        for (size_t i = 0; i < array.size(); ++ i) {
            xTEST_EQ(array[i], std::size_t(0));
        }
    }

    xTEST_CASE("make_array", a_caseLoops)
    {
        make_array<std::tstring_t>(xT("0"), xT("1"));
        make_array<std::tstring_t>(xT("0"), xT("1"), xT("2"));
    }
}
//-------------------------------------------------------------------------------------------------
