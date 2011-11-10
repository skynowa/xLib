/**
 * \file   CxTest_CxMacros.h
 * \brief
 */


#ifndef CxTest_CxMacrosH
#define CxTest_CxMacrosH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxMacros.h>
//---------------------------------------------------------------------------
class CxTest_CxMacros :
    public CxTest
{
    public:
                       CxTest_CxMacros();
        virtual       ~CxTest_CxMacros();

        virtual  BOOL  bUnit          (const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxMacrosH
