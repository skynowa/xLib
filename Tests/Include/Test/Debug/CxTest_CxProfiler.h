/**
 * \file   CxTest_CxProfiler.h
 * \brief
 */


#ifndef CxTest_CxProfilerH
#define CxTest_CxProfilerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxProfiler.h>
//---------------------------------------------------------------------------
class CxTest_CxProfiler :
    public CxTest
{
public:
                 CxTest_CxProfiler();
    virtual     ~CxTest_CxProfiler();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxProfilerH
