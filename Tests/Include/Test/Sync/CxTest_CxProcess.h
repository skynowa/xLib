/**
 * \file   CxTest_CxProcess.h
 * \brief
 */


#ifndef CxTest_CxTest_CxProcessH
#define CxTest_CxTest_CxProcessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxProcess.h>
//---------------------------------------------------------------------------
class CxTest_CxProcess :
    public CxTest
{
    public:
                     CxTest_CxProcess();
        virtual     ~CxTest_CxProcess();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTest_CxProcessH
