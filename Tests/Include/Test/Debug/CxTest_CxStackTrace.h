/**
 * \file   CxTest_CxStackTrace.h
 * \brief  test CxStackTrace
 */


#ifndef CxTest_CxStackTraceH
#define CxTest_CxStackTraceH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
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

        virtual BOOL  bUnit(const ULONGLONG cullBlockLoops);
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxStackTraceH
