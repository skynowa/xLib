/**
 * \file   CxTest_CxDll.h
 * \brief
 */


#ifndef CxTest_CxDllH
#define CxTest_CxDllH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxDll.h>
//---------------------------------------------------------------------------
class CxTest_CxDll :
    public CxTest
{
    public:
                     CxTest_CxDll();
        virtual     ~CxTest_CxDll();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDllH
