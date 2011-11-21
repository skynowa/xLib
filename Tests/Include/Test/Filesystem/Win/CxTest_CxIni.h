/**
 * \file   CxTest_CxIni.h
 * \brief
 */


#ifndef CxTest_Win_CxIniH
#define CxTest_Win_CxIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/Win/CxIni.h>
//---------------------------------------------------------------------------
class CxTest_CxIni:
    public CxTest
{
    public:
                     CxTest_CxIni();
        virtual     ~CxTest_CxIni();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_Win_CxIniH
