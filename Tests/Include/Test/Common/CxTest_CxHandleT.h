/****************************************************************************
* Class name:  CxTest_CxHandleT
* Description: test CxHandle
* File name:   CxTest_CxHandleT.h
* Compilers:   Visual C++ 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxHandleT_CxHandleH
#define CxHandleT_CxHandleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxHandleT.h>
//---------------------------------------------------------------------------
class CxTest_CxHandleT :
    public CxTest
{
    public:
                 CxTest_CxHandleT();
        virtual ~CxTest_CxHandleT();

        virtual BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxHandleT_CxHandleH
