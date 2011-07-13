/****************************************************************************
* Class name:  CxTest_CxIni
* Description: test CxIni
* File name:   CxTest_CxIni.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#if defined(xOS_WIN)
#ifndef CxTest_CxIniH
#define CxTest_CxIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/Win/CxIni.h>
//---------------------------------------------------------------------------
class CxTest_CxIni : public CxTest {
    public:
        CxTest_CxIni();
        virtual     ~CxTest_CxIni();

        virtual BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxIniH
#elif defined(xOS_LINUX)

#endif
