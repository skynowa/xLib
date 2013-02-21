/**
 * \file   CxTest_CxAutoProfiler.h
 * \brief
 */


#ifndef CxTest_CxAutoProfilerH
#define CxTest_CxAutoProfilerH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxAutoProfiler.h>
//------------------------------------------------------------------------------
class CxTest_CxAutoProfiler :
    public CxTest
{
public:
                 CxTest_CxAutoProfiler();
    virtual     ~CxTest_CxAutoProfiler();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxAutoProfilerH
