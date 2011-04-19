/****************************************************************************
* Class name:  CxTest_CxAtomicLongInt
* Description: test CxAtomicLongInt
* File name:   CxTest_CxAtomicLongInt.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxAtomicLongIntH
#define CxTest_CxAtomicLongIntH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxAtomicLongInt.h>
//---------------------------------------------------------------------------
class CxTest_CxAtomicLongInt : public CxTest {
	public:
		CxTest_CxAtomicLongInt();
		virtual     ~CxTest_CxAtomicLongInt();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxAtomicLongInt (constructor)
CxTest_CxAtomicLongInt::CxTest_CxAtomicLongInt() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxAtomicLongInt (destructor)
CxTest_CxAtomicLongInt::~CxTest_CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxAtomicLongInt::bUnit() {
	LONG iRes = 0;

	CxAtomicLongInt alAL_1;
	CxAtomicLongInt alAL_2;

	alAL_1 = 1;
	alAL_2 = 2;

	alAL_1 += alAL_2;
	/*DEBUG*/xASSERT(alAL_1 == 3L);

	alAL_1 -= alAL_2;
	/*DEBUG*/xASSERT(alAL_1 == 1L);

	alAL_1  = alAL_2;
	/*DEBUG*/xASSERT(alAL_1 == 2L);

	alAL_1 += 10;
	/*DEBUG*/xASSERT(alAL_1 == 12L);

	alAL_1 -= 10;
	/*DEBUG*/xASSERT(alAL_1 == 2L);

	alAL_1  = 10;
	/*DEBUG*/xASSERT(alAL_1 == 10L);


	iRes = alAL_1;




	//CxAtomicLongInt& operator +=   (const CxAtomicLongInt &cRight);
	//CxAtomicLongInt& operator -=   (const CxAtomicLongInt &cRight);
	//CxAtomicLongInt& operator =    (const CxAtomicLongInt &cRight);
	//CxAtomicLongInt& operator +=   (const LONG cliRight);
	//CxAtomicLongInt& operator -=   (const LONG cliRight);
	//CxAtomicLongInt& operator =    (const LONG cliRight);
	//BOOL             operator ==   (const CxAtomicLongInt &cRight);
	//BOOL             operator !=   (const CxAtomicLongInt &cRight);
	//BOOL             operator ==   (const LONG cliRight);
	//BOOL             operator !=   (const LONG cliRight);
	//operator LONG ();
	//operator BOOL ();
	//CxAtomicLongInt& operator ++   (INT iPos);
	//CxAtomicLongInt& operator --   (INT iPos);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxAtomicLongIntH

