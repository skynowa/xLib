/****************************************************************************
* Class name:  CxTest_CxEnvironment
* Description: test CxEnvironment
* File name:   CxTest_CxEnvironment.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxEnvironmentH
#define CxTest_CxEnvironmentH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxEnvironment.h>
//---------------------------------------------------------------------------
class CxTest_CxEnvironment :
    public CxTest
{
    public:
                     CxTest_CxEnvironment();
        virtual     ~CxTest_CxEnvironment();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxEnvironmentH
