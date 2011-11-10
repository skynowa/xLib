/****************************************************************************
* Class name:  CxTest_CxDir
* Description: testing CxDir
* File name:   CxTest_CxDir.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxDirH
#define CxTest_CxDirH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>
//---------------------------------------------------------------------------
class CxTest_CxDir :
    public CxTest
{
    public:
                     CxTest_CxDir();
        virtual     ~CxTest_CxDir();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDirH
