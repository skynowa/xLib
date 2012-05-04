/**
 * \file   CxTest_CxAtomicLongInt.h
 * \brief
 */


#ifndef CxTest_CxAtomicLongIntH
#define CxTest_CxAtomicLongIntH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxAtomicLongInt.h>
//---------------------------------------------------------------------------
class CxTest_CxAtomicLongInt :
    public CxTest
{
    public:
                     CxTest_CxAtomicLongInt();
        virtual     ~CxTest_CxAtomicLongInt();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAtomicLongIntH
