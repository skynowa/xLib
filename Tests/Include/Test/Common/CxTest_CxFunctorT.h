/****************************************************************************
* Class name:  CxTest_CxFunctorT
* Description: testing CxFunctor
* File name:   CxTest_CxFunctorT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxFunctorH
#define CxTest_CxFunctorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxFunctorT.h>
//---------------------------------------------------------------------------
class CxTest_CxFunctorT :
    public CxTest
{
    public:
                    CxTest_CxFunctorT();
        virtual     ~CxTest_CxFunctorT();

        virtual     BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxFunctorH
