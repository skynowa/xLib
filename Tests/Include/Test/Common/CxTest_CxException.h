/**
 * \file   CxTest_CxException.h
 * \brief
 */


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

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxExceptionH
