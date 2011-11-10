/**
 * \file   CxTest_CxAutoMallocT.h
 * \brief
 */


#ifndef CxTest_CxAutoMallocTH
#define CxTest_CxAutoMallocTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxAutoMallocT.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoMallocT :
    public CxTest
{
    public:
                     CxTest_CxAutoMallocT();
        virtual     ~CxTest_CxAutoMallocT();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAutoMallocTH
