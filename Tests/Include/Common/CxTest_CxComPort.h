/****************************************************************************
* Class name:  CxTest_CxComPort
* Description: test CxComPort
* File name:   CxTest_CxComPort.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxComPortH
#define CxTest_CxComPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxComPort.h>
//---------------------------------------------------------------------------
class CxTest_CxComPort :
    public CxTest
{
    public:
        CxTest_CxComPort();
        virtual     ~CxTest_CxComPort();

        virtual     BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxComPortH
