/**
 * \file   CxTest_[CxTemplate].h
 * \brief  test [CxTemplate]
 */


#ifndef CxTest_[CxTemplate]H
#define CxTest_[CxTemplate]H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/xxxxxxxxx/[CxTemplate].h>
//---------------------------------------------------------------------------
class CxTest_[CxTemplate] :
    public CxTest
{
    public:
                      CxTest_[CxTemplate]();
            ///< constructor
        virtual      ~CxTest_[CxTemplate]();
            ///< destructor

        virtual bool  bUnit(const ulonglong_t cullBlockLoops);
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_[CxTemplate]H
