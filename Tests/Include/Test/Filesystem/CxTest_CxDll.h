/****************************************************************************
* Class name:  CxTest_CxDll
* Description: test CxDll
* File name:   CxTest_CxDll.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxDllH
#define CxTest_CxDllH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxDll.h>
//---------------------------------------------------------------------------
class CxTest_CxDll :
    public CxTest
{
    public:
                     CxTest_CxDll();
        virtual     ~CxTest_CxDll();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDllH
