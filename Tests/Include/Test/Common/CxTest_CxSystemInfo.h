/**
 * \file   CxTest_CxSystemInfo.h
 * \brief
 */


#ifndef CxTest_CxSystemInfoH
#define CxTest_CxSystemInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxSystemInfo.h>
//---------------------------------------------------------------------------
class CxTest_CxSystemInfo :
    public CxTest
{
    public:
                     CxTest_CxSystemInfo();
        virtual     ~CxTest_CxSystemInfo();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSystemInfoH
