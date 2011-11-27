/**
 * \file   CxTest_CxConsole.h
 * \brief
 */


#ifndef CxTest_CxConsoleH
#define CxTest_CxConsoleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxConsole.h>
//---------------------------------------------------------------------------
class CxTest_CxConsole :
    public CxTest
{
    public:
                     CxTest_CxConsole();
        virtual     ~CxTest_CxConsole();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxConsoleH
