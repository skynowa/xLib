/****************************************************************************
* Class name:  CxTest_CxConsole
* Description: test CxConsole
* File name:   CxTest_CxConsole.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxConsoleH
#define CxTest_CxConsoleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxConsole.h>
//---------------------------------------------------------------------------
class CxTest_CxConsole :
    public CxTest
{
    public:
        CxTest_CxConsole();
        virtual     ~CxTest_CxConsole();

        virtual     BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxConsoleH
