/**
 * \file   CxTest_CxSocketInit.h
 * \brief
 */


#ifndef CxTest_CxSocketInitH
#define CxTest_CxSocketInitH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxSocketInit :
    public CxTest
{
    public:
                     CxTest_CxSocketInit();
        virtual     ~CxTest_CxSocketInit();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSocketInitH
