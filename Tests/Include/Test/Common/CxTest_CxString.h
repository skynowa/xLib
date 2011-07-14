/****************************************************************************
* Class name:  CxTest_CxString
* Description: test CxString
* File name:   CxTest_CxString.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxStringH
#define CxTest_CxStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxString.h>
//---------------------------------------------------------------------------
class CxTest_CxString :
    public CxTest
{
    public:
        CxTest_CxString();
        virtual     ~CxTest_CxString();

        virtual     BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxStringH
