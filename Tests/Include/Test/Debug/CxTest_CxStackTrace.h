/**
 * \file   CxTest_CxStackTrace.h
 * \brief  test CxStackTrace
 */


#ifndef CxTest_CxStackTraceH
#define CxTest_CxStackTraceH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxStackTrace.h>
//---------------------------------------------------------------------------
class CxTest_CxStackTrace :
    public CxTest
{
    public:
                      CxTest_CxStackTrace();
            ///< constructor
        virtual      ~CxTest_CxStackTrace();
            ///< destructor

        virtual bool  bUnit(const ulonglong_t cullCaseLoops);
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxStackTraceH
