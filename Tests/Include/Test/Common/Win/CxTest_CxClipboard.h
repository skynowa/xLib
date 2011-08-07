/****************************************************************************
* Class name:  CxTest_CxClipboard
* Description: test CxClipboard
* File name:   CxTest_CxClipboard.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxClipboardH
#define CxTest_CxClipboardH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxClipboard.h>
//---------------------------------------------------------------------------
class CxTest_CxClipboard :
    public CxTest
{
    public:
                     CxTest_CxClipboard();
       virtual      ~CxTest_CxClipboard();

       virtual BOOL  bUnit             (const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxClipboardH
