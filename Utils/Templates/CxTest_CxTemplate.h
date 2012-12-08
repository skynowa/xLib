/**
 * \file   CxTest_[CxTemplate].h
 * \brief  test [CxTemplate]
 */


#ifndef CxTest_[CxTemplate]H
#define CxTest_[CxTemplate]H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/xxxxxxxxx/[CxTemplate].h>
//---------------------------------------------------------------------------
class CxTest_[CxTemplate] :
    public CxTest
    ///< tests for [CxTemplate]
{
    public:
                      CxTest_[CxTemplate]();
            ///< constructor
        virtual      ~CxTest_[CxTemplate]();
            ///< destructor

        virtual void  vUnit(const ulonglong_t &cullCaseLoops) xOVERRIDE;
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif // CxTest_[CxTemplate]H
