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
/*virtual*/
bool
CxTest_CxArray::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const size_t cuiArraySize = 5;


    CxArray<size_t, cuiArraySize> aszArray = {{0, 1, 2, 3, 4}};

    //--------------------------------------------------
    //operator[]
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray[i]);
        }
    }

    //--------------------------------------------------
    //at
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray.at(i));
        }
    }

    //--------------------------------------------------
    //uiGetSize
    xTEST_CASE(cullCaseLoops)
    {
        m_stRv = aszArray.size();
        xTEST_EQ(cuiArraySize, m_stRv);
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        /*m_bRv =*/ aszArray.clear();
        ////xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE(cullCaseLoops) {
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1") );
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1"),  xT("2") );
    }

    return true;
}
//---------------------------------------------------------------------------
