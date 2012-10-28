/**
 * \file   CxTest_CxCondition.h
 * \brief  test CxCondition
 */


#ifndef CxTest_CxConditionH
#define CxTest_CxConditionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/Unix/CxCondition.h>
//---------------------------------------------------------------------------
#if xOS_ENV_UNIX

class CxTest_CxCondition :
    public CxTest
{
    public:
                      CxTest_CxCondition();
            ///< constructor
        virtual      ~CxTest_CxCondition();
            ///< destructor

        virtual void  vUnit(const ulonglong_t &cullCaseLoops) xOVERRIDE;
            ///< unit test

    private:
};

#endif
//---------------------------------------------------------------------------
#endif // CxTest_CxConditionH
