/****************************************************************************
* Class name:  CxTest_CxCom
* Description: test CxCom
* File name:   CxTest_CxCom.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxComH
#define CxTest_CxComH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxCom.h>
//---------------------------------------------------------------------------
class CxTest_CxCom :
    public CxTest
{
    public:
                     CxTest_CxCom();
        virtual     ~CxTest_CxCom();

        virtual BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxComH
