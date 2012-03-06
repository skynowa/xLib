/**
 * \file   CxTest_CxAtomicLongInt.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAtomicLongInt.h>


//---------------------------------------------------------------------------
CxTest_CxAtomicLongInt::CxTest_CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
CxTest_CxAtomicLongInt::~CxTest_CxAtomicLongInt() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxAtomicLongInt::bUnit(
    const ulonglong_t cullCaseLoops
)
{
#if xTEMP_DISABLED
    long_t iRes = 0;

    CxAtomicLongInt alAL_1;
    CxAtomicLongInt alAL_2;

    alAL_1 = 1;
    alAL_2 = 2;

    alAL_1 += alAL_2;
    /*DEBUG*/xTEST_EQ(alAL_1, 3L);

    alAL_1 -= alAL_2;
    /*DEBUG*/xTEST_EQ(alAL_1, 1L);

    alAL_1  = alAL_2;
    /*DEBUG*/xTEST_EQ(alAL_1, 2L);

    alAL_1 += 10;
    /*DEBUG*/xTEST_EQ(alAL_1, 12L);

    alAL_1 -= 10;
    /*DEBUG*/xTEST_EQ(alAL_1, 2L);

    alAL_1  = 10;
    /*DEBUG*/xTEST_EQ(alAL_1, 10L);


    iRes = alAL_1;
#endif

    return true;
}
//---------------------------------------------------------------------------
