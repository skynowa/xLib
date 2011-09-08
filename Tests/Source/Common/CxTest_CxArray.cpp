/****************************************************************************
* Array name:  CxTest_CxArray
* Description: test CxArray
* File name:   CxTest_CxArray.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxArray.h>


//---------------------------------------------------------------------------
CxTest_CxArray::CxTest_CxArray() {

}
//---------------------------------------------------------------------------
CxTest_CxArray::~CxTest_CxArray() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxArray::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const size_t cuiArraySize = 5;


    CxArray<size_t, cuiArraySize> aszArray = {{0, 1, 2, 3, 4}};

    //--------------------------------------------------
    //operator[]
    xTEST_BLOCK(cullBlockLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xASSERT_EQ(i, aszArray[i]);
        }
    }

    //--------------------------------------------------
    //at
    xTEST_BLOCK(cullBlockLoops)
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xASSERT_EQ(i, aszArray.at(i));
        }
    }

    //--------------------------------------------------
    //uiGetSize
    xTEST_BLOCK(cullBlockLoops)
    {
        m_stRes = aszArray.size();
        xASSERT_EQ(cuiArraySize, m_stRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        /*m_bRes =*/ aszArray.clear();
        ////xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    xTEST_BLOCK(cullBlockLoops) {
        NxArray::make_array<std::tstring>( xT("0"),  xT("1") );
        NxArray::make_array<std::tstring>( xT("0"),  xT("1"),  xT("2") );
    }

    return TRUE;
}
//---------------------------------------------------------------------------
