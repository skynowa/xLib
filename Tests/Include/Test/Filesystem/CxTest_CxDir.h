/**
 * \file   CxTest_CxDir.h
 * \brief
 */


#ifndef CxTest_CxDirH
#define CxTest_CxDirH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>
//---------------------------------------------------------------------------
class CxTest_CxDir :
    public CxTest
{
    public:
                     CxTest_CxDir();
        virtual     ~CxTest_CxDir();

        virtual void vUnit(const ulonglong_t &cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDirH
