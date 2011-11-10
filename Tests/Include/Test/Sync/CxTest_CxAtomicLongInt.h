/**
 * \file   CxTest_CxAtomicLongInt.h
 * \brief
 */


#ifndef CxTest_CxAtomicLongIntH
#define CxTest_CxAtomicLongIntH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxAtomicLongInt.h>
//---------------------------------------------------------------------------
class CxTest_CxAtomicLongInt :
    public CxTest
{
    public:
                     CxTest_CxAtomicLongInt();
        virtual     ~CxTest_CxAtomicLongInt();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAtomicLongIntH
