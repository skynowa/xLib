/**
 * \file   CxTest_CxFunctorT.h
 * \brief
 */


#ifndef CxTest_CxFunctorTH
#define CxTest_CxFunctorTH
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

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxFunctorTH
