/****************************************************************************
* Class name:  CxTest_CxConsole
* Description: test CxConsole
* File name:   CxTest_CxConsole.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxConsole.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxConsole
CxTest_CxConsole::CxTest_CxConsole() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxConsole
CxTest_CxConsole::~CxTest_CxConsole() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL 
CxTest_CxConsole::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    CxConsole cnConsole;

    CxConsole::EModalResult mrRes = cnConsole.iMsgBox(xT("Text"), xT("Title"), 0U);

#if xTODO
    cnConsole.bSetTextColor(0xa);
    cnConsole.bEnableClose(true);
    cnConsole.bClear();
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
