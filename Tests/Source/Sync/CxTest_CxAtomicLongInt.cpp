/****************************************************************************
* Class name:  CxTest_CxAtomicLongInt
* Description: test CxAtomicLongInt
* File name:   CxTest_CxAtomicLongInt.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxAtomicLongInt.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxAtomicLongInt
CxTest_CxAtomicLongInt::CxTest_CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxAtomicLongInt
CxTest_CxAtomicLongInt::~CxTest_CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxAtomicLongInt::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_WIN)
#if xTEMP_DISABLED
    LONG iRes = 0;

    CxAtomicLongInt alAL_1;
    CxAtomicLongInt alAL_2;

    alAL_1 = 1;
    alAL_2 = 2;

    alAL_1 += alAL_2;
    /*DEBUG*/xASSERT_EQ(alAL_1, 3L);

    alAL_1 -= alAL_2;
    /*DEBUG*/xASSERT_EQ(alAL_1, 1L);

    alAL_1  = alAL_2;
    /*DEBUG*/xASSERT_EQ(alAL_1, 2L);

    alAL_1 += 10;
    /*DEBUG*/xASSERT_EQ(alAL_1, 12L);

    alAL_1 -= 10;
    /*DEBUG*/xASSERT_EQ(alAL_1, 2L);

    alAL_1  = 10;
    /*DEBUG*/xASSERT_EQ(alAL_1, 10L);


    iRes = alAL_1;
#endif




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
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
