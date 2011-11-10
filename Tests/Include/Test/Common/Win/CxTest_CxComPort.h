/**
 * \file   CxTest_CxComPort.h
 * \brief
 */


#ifndef CxTest_CxComPortH
#define CxTest_CxComPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxComPort.h>
//---------------------------------------------------------------------------
class CxTest_CxComPort :
    public CxTest
{
    public:
                     CxTest_CxComPort();
        virtual     ~CxTest_CxComPort();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxComPortH
