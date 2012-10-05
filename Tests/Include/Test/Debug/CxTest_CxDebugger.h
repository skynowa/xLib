/**
 * \file   CxTest_CxDebugger.h
 * \brief
 */


#ifndef CxTest_CxDebuggerH
#define CxTest_CxDebuggerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxDebugger.h>
//---------------------------------------------------------------------------
class CxTest_CxDebugger :
    public CxTest
{
    public:
                     CxTest_CxDebugger();
        virtual     ~CxTest_CxDebugger();

        virtual void vUnit(const ulonglong_t &cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDebuggerH
