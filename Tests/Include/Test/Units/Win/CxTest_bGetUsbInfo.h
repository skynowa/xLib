/****************************************************************************
* Class name:  CxTest_bGetUsbInfo
* Description: test bGetUsbInfo
* File name:   CxTest_bGetUsbInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_bGetUsbInfoH
#define CxTest_bGetUsbInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Units/Win/bGetUsbInfo.h>
//---------------------------------------------------------------------------
class CxTest_bGetUsbInfo :
    public CxTest
{
    public:
                     CxTest_bGetUsbInfo();
        virtual     ~CxTest_bGetUsbInfo();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_bGetUsbInfoH
