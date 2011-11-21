/**
 * \file   CxTest_CxDir.h
 * \brief
 */


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

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDirH
