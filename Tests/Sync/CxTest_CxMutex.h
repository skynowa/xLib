/****************************************************************************
* Class name:  CxTest_CxMutex
* Description: test CxMutex
* File name:   CxTest_CxMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxMutexH
#define CxTest_CxMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxMutex.h>
//---------------------------------------------------------------------------
class CxTest_CxMutex : public CxTest {
	public:
		CxTest_CxMutex();
	   ~CxTest_CxMutex();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxMutex (constructor)
CxTest_CxMutex::CxTest_CxMutex() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxMutex (destructor)
CxTest_CxMutex::~CxTest_CxMutex() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxMutex::bUnit() {
	CxMutex MyMutex;

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxMutexH

