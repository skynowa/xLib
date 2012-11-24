/**
 * \file   CxTest_CxArray.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxArray.h>


//---------------------------------------------------------------------------
CxTest_CxArray::CxTest_CxArray() {

}
//---------------------------------------------------------------------------
CxTest_CxArray::~CxTest_CxArray() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxArray::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const size_t cuiArraySize = 5;


    CxArray<size_t, cuiArraySize> aszArray = {{0, 1, 2, 3, 4}};

    xTEST_CASE("CxArray::operator[]", cullCaseLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray[i]);
        }
    }

    xTEST_CASE("CxArray::at", cullCaseLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray.at(i));
        }
    }

    xTEST_CASE("CxArray::uiGetSize", cullCaseLoops)
    {
        m_stRv = aszArray.size();
        xTEST_EQ(cuiArraySize, m_stRv);
    }

    xTEST_CASE("CxArray::clear", cullCaseLoops)
    {
        /*m_bRv =*/ aszArray.clear();
        ////xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("NxArray::make_array", cullCaseLoops) {
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1") );
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1"),  xT("2") );
    }
}
//---------------------------------------------------------------------------
