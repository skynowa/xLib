/**
 * \file   CxTest_CxCommandLine.h
 * \brief
 */


#ifndef CxTest_CxCommandLineH
#define CxTest_CxCommandLineH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxCommandLine.h>
//---------------------------------------------------------------------------
class CxTest_CxCommandLine :
    public CxTest
{
    public:
                     CxTest_CxCommandLine();
        virtual     ~CxTest_CxCommandLine();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCommandLineH
