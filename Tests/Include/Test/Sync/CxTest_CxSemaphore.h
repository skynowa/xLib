/**
 * \file   CxTest_CxSemaphore.h
 * \brief
 */


#ifndef CxTest_CxSemaphoreH
#define CxTest_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxSemaphore.h>
//---------------------------------------------------------------------------
class CxTest_CxSemaphore :
    public CxTest
{
    public:
                     CxTest_CxSemaphore();
        virtual     ~CxTest_CxSemaphore();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSemaphoreH
