/****************************************************************************
* Class name:  CxTest_CxCrc32
* Description: test CxCrc32
* File name:   CxTest_CxCrc32.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCrc32H
#define CxTest_CxCrc32H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Crypt/CxCrc32.h>
#include <xLib/Filesystem/CxFile.h>
//---------------------------------------------------------------------------
class CxTest_CxCrc32 :
    public CxTest
{
    public:
                     CxTest_CxCrc32();
        virtual     ~CxTest_CxCrc32();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCrc32H
