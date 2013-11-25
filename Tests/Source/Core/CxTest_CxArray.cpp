/**
 * \file   CxTest_CxArray.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxArray.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxArray::unit(
    culonglong_t &a_caseLoops
)
{
    std::csize_t cuiArraySize = 5;


    CxArray<size_t, cuiArraySize> aszArray = {{0, 1, 2, 3, 4}};

    xTEST_CASE("CxArray::operator[]", a_caseLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray[i]);
        }
    }

    xTEST_CASE("CxArray::at", a_caseLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray.at(i));
        }
    }

    xTEST_CASE("CxArray::uiGetSize", a_caseLoops)
    {
        m_stRv = aszArray.size();
        xTEST_EQ(cuiArraySize, m_stRv);
    }

    xTEST_CASE("CxArray::clear", a_caseLoops)
    {
        /*m_bRv =*/ aszArray.clear();
        ////xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("NxArray::make_array", a_caseLoops) {
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1") );
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1"),  xT("2") );
    }
}
//------------------------------------------------------------------------------
