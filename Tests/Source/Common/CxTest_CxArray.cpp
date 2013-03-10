/**
 * \file   CxTest_CxArray.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxArray.h>


//------------------------------------------------------------------------------
CxTest_CxArray::CxTest_CxArray() {

}
//------------------------------------------------------------------------------
CxTest_CxArray::~CxTest_CxArray() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxArray::unit(
    culonglong_t &a_cullCaseLoops
)
{
    std::csize_t cuiArraySize = 5;


    CxArray<size_t, cuiArraySize> aszArray = {{0, 1, 2, 3, 4}};

    xTEST_CASE("CxArray::operator[]", a_cullCaseLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray[i]);
        }
    }

    xTEST_CASE("CxArray::at", a_cullCaseLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray.at(i));
        }
    }

    xTEST_CASE("CxArray::uiGetSize", a_cullCaseLoops)
    {
        m_stRv = aszArray.size();
        xTEST_EQ(cuiArraySize, m_stRv);
    }

    xTEST_CASE("CxArray::clear", a_cullCaseLoops)
    {
        /*m_bRv =*/ aszArray.clear();
        ////xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("NxArray::make_array", a_cullCaseLoops) {
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1") );
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1"),  xT("2") );
    }
}
//------------------------------------------------------------------------------
