/**
 * \file   CxTest_CxDebugger.h
 * \brief
 */


#ifndef CxTest_CxDebuggerH
#define CxTest_CxDebuggerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxDebugger.h>
//---------------------------------------------------------------------------
class CxTest_CxDebugger :
    public CxTest
{
    public:
                     CxTest_CxDebugger();
        virtual     ~CxTest_CxDebugger();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDebuggerH
