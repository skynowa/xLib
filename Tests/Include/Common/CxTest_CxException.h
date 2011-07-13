/****************************************************************************
* Class name:  CxTest_CxException
* Description: test CxException
* File name:   CxTest_CxException.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxExceptionH
#define CxTest_CxExceptionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxException.h>
//---------------------------------------------------------------------------
class CxTest_CxException :
    public CxTest
{
    public:
        CxTest_CxException();
        virtual     ~CxTest_CxException();

        /*virtual*/ BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxExceptionH
