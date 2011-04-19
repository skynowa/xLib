/****************************************************************************
* Class name:  CxTest_CxAutoMutex
* Description: test CxAutoMutex
* File name:   CxTest_CxAutoMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxAutoMutexH
#define CxTest_CxAutoMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxAutoMutex.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoMutex : public CxTest {
	public:
		CxTest_CxAutoMutex();
	   ~CxTest_CxAutoMutex();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//TODO: + CxTest_CxAutoMutex (constructor)
CxTest_CxAutoMutex::CxTest_CxAutoMutex() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxAutoMutex (destructor)
CxTest_CxAutoMutex::~CxTest_CxAutoMutex() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxAutoMutex::bUnit() {
	//-------------------------------------
	//CxMutexScopeLock()
	{
		//CxMutexScopeLock objCxMutexScopeLock());
	}


    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxAutoMutexH
