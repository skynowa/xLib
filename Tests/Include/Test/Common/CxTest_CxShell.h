/****************************************************************************
* Class name:  CxTest_CxShell
* Description: test CxShell
* File name:   CxTest_CxShell.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxShellH
#define CxTest_CxShellH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxShell.h>
//---------------------------------------------------------------------------
class CxTest_CxShell :
    public CxTest
{
    public:
                     CxTest_CxShell();
        virtual     ~CxTest_CxShell();

        virtual BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxShellH
