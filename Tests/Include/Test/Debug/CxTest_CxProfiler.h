/**
 * \file   CxTest_CxProfiler.h
 * \brief
 */


#ifndef CxTest_CxProfilerH
#define CxTest_CxProfilerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxProfiler.h>
//---------------------------------------------------------------------------
class CxTest_CxProfiler :
    public CxTest
{
    public:
                     CxTest_CxProfiler();
        virtual     ~CxTest_CxProfiler();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxProfilerH
