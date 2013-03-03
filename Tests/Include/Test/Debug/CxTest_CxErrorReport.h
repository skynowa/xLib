/**
 * \file   CxTest_CxErrorReport.h
 * \brief
 */


#ifndef CxTest_CxReportH
#define CxTest_CxReportH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxErrorReport.h>
//------------------------------------------------------------------------------
class CxTest_CxErrorReport :
    public CxTest
{
public:
                 CxTest_CxErrorReport();
    virtual     ~CxTest_CxErrorReport();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxReportH
