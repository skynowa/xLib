/**
 * \file   CxTest_CxLastError.h
 * \brief
 */


#ifndef CxTest_CxLastErrorH
#define CxTest_CxLastErrorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxLastError.h>
//---------------------------------------------------------------------------
class CxTest_CxLastError :
    public CxTest
{
    public:
                     CxTest_CxLastError();
        virtual     ~CxTest_CxLastError();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxLastErrorH
