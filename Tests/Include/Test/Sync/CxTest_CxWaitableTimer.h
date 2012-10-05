/**
 * \file   CxTest_CxWaitableTimer.h
 * \brief
 */


#ifndef CxTest_CxWaitableTimerH
#define CxTest_CxWaitableTimerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxWaitableTimer.h>
//---------------------------------------------------------------------------
class CxTest_CxWaitableTimer :
    public CxTest
{
    public:
                     CxTest_CxWaitableTimer();
        virtual     ~CxTest_CxWaitableTimer();

        virtual void vUnit(const ulonglong_t &cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxWaitableTimerH
