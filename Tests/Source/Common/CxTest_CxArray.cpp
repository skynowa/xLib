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
//DONE: CxTest_CxArray
CxTest_CxArray::CxTest_CxArray() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxArray
CxTest_CxArray::~CxTest_CxArray() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxArray::bUnit() {
    const size_t cuiArraySize = 5;


    CxArray<size_t, cuiArraySize> aszArray = {{0, 1, 2, 3, 4}};

    //--------------------------------------------------
    //operator[]
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xASSERT(i == aszArray[i]);
        }
    }

    //--------------------------------------------------
    //at
    {
        for (size_t i = 0; i < aszArray.size(); ++ i) {
            xASSERT(i == aszArray.at(i) );
        }
    }

    //--------------------------------------------------
    //uiGetSize
    {
        m_uiRes = aszArray.size();
        xASSERT(cuiArraySize == m_uiRes);
    }

    //--------------------------------------------------
    //bClear
    {
        /*m_bRes =*/ aszArray.clear();
        ////xASSERT(FALSE != m_bRes);
    }


    NxArray::make_array<tString>( xT("0"),  xT("1") );
    NxArray::make_array<tString>( xT("0"),  xT("1"),  xT("2") );


    return TRUE;
}
//---------------------------------------------------------------------------
