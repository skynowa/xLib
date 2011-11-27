/**
 * \file   CxTest_CxReport.h
 * \brief
 */


#ifndef CxTest_CxReportH
#define CxTest_CxReportH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxReport.h>
//---------------------------------------------------------------------------
class CxTest_CxReport :
    public CxTest
{
    public:
                     CxTest_CxReport();
        virtual     ~CxTest_CxReport();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxReportH
