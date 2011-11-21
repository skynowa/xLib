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
    const ulonglong_t cullBlockLoops
)
{
    const size_t cuiArraySize = 5;


    CxArray<size_t, cuiArraySize> aszArray = {{0, 1, 2, 3, 4}};

    //--------------------------------------------------
    //operator[]
    xTEST_CASE(cullBlockLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray[i]);
        }
    }

    //--------------------------------------------------
    //at
    xTEST_CASE(cullBlockLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xTEST_EQ(i, aszArray.at(i));
        }
    }

    //--------------------------------------------------
    //uiGetSize
    xTEST_CASE(cullBlockLoops)
    {
        m_stRes = aszArray.size();
        xTEST_EQ(cuiArraySize, m_stRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullBlockLoops)
    {
        /*m_bRes =*/ aszArray.clear();
        ////xTEST_DIFF(false, m_bRes);
    }

    xTEST_CASE(cullBlockLoops) {
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1") );
        NxArray::make_array<std::tstring_t>( xT("0"),  xT("1"),  xT("2") );
    }

    return true;
}
//---------------------------------------------------------------------------
