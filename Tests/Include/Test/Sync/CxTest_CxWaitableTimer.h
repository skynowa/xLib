/**
 * \file   CxTest_CxWaitableTimer.h
 * \brief
 */


#ifndef CxTest_CxWaitableTimerH
#define CxTest_CxWaitableTimerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxWaitableTimer.h>
//---------------------------------------------------------------------------
class CxTest_CxWaitableTimer :
    public CxTest
{
    public:
                     CxTest_CxWaitableTimer();
        virtual     ~CxTest_CxWaitableTimer();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxWaitableTimerH
