/**
 * \file   CxTest_CxFlags.h
 * \brief  test CxFlags
 */


#ifndef CxTest_CxFlagsH
#define CxTest_CxFlagsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxFlags.h>
//---------------------------------------------------------------------------
class CxTest_CxFlags :
    public CxTest
    ///< tests for CxFlags
{
    public:
                      CxTest_CxFlags();
            ///< constructor
        virtual      ~CxTest_CxFlags();
            ///< destructor

        virtual void  vUnit(const ulonglong_t &cullCaseLoops) xOVERRIDE;
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif // CxTest_CxFlagsH
