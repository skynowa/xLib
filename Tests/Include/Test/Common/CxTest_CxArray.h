/****************************************************************************
* Array name:  CxTest_CxArray
* Description: test CxArray
* File name:   CxTest_CxArray.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxArrayH
#define CxTest_CxArrayH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxArray.h>
//---------------------------------------------------------------------------
class CxTest_CxArray :
    public CxTest
{
    public:
                     CxTest_CxArray();
        virtual     ~CxTest_CxArray();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxArrayH
