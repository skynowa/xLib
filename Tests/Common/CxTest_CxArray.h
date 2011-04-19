/****************************************************************************
* Array name:  CxTest_CxArray
* Description: test CxArray
* File name:   CxTest_CxArray.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxArrayH
#define CxTest_CxArrayH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxArray.h>
//---------------------------------------------------------------------------
class CxTest_CxArray : public CxTest {
	public:
		CxTest_CxArray();
	   ~CxTest_CxArray();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxArray (constructor)
CxTest_CxArray::CxTest_CxArray() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxArray (destructor)
CxTest_CxArray::~CxTest_CxArray() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
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
#endif //CxTest_CxArrayH
