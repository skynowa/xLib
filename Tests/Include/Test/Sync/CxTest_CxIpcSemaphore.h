/**
 * \file   CxTest_CxIpcSemaphore.h
 * \brief
 */


#ifndef CxTest_CxIpcSemaphoreH
#define CxTest_CxIpcSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxIpcSemaphore.h>
//---------------------------------------------------------------------------
class CxTest_CxIpcSemaphore :
    public CxTest
{
    public:
                     CxTest_CxIpcSemaphore();
        virtual     ~CxTest_CxIpcSemaphore();

        virtual bool bUnit             (const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxIpcSemaphoreH
