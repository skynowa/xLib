/****************************************************************************
* Class name:  CxTest_CxConsole
* Description: test CxConsole
* File name:   CxTest_CxConsole.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Common/CxTest_CxConsole.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxConsole (comment)
CxTest_CxConsole::CxTest_CxConsole() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxConsole (comment)
CxTest_CxConsole::~CxTest_CxConsole() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL CxTest_CxConsole::bUnit() {
    /*DEBUG*/

    #if xTODO
        CxConsole cnConsole;
    #endif

    //////Console.vSetTextColor(0xa);
    //////Console.bEnableClose(true);
    //////cout << "111111111111111111111111111111111111111";
    //////Console.bClearScreen();

    return TRUE;
}
//---------------------------------------------------------------------------
