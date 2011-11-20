/**
 * \file   CxTest_CxCrc32.h
 * \brief
 */


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

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCrc32H
