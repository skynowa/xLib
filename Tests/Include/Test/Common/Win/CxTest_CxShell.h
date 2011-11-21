/**
 * \file   CxTest_CxShell.h
 * \brief
 */


#ifndef CxTest_CxShellH
#define CxTest_CxShellH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxShell.h>
//---------------------------------------------------------------------------
class CxTest_CxShell :
    public CxTest
{
    public:
                     CxTest_CxShell();
        virtual     ~CxTest_CxShell();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxShellH
