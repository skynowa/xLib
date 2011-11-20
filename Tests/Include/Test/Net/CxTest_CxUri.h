/**
 * \file   CxTest_CxUri.h
 * \brief
 */


#ifndef CxTest_CxUriH
#define CxTest_CxUriH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxUri.h>
//---------------------------------------------------------------------------
class CxTest_CxUri :
    public CxTest
{
    public:
                     CxTest_CxUri();
        virtual     ~CxTest_CxUri();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxUriH
