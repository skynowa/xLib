/**
 * \file   CxTest_CxFile.h
 * \brief
 */


#ifndef CxTest_CxFileH
#define CxTest_CxFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxFile.h>
//---------------------------------------------------------------------------
class CxTest_CxFile :
    public CxTest
{
    public:
                       CxTest_CxFile();
        virtual       ~CxTest_CxFile();

        virtual  BOOL  bUnit        (const ULONGLONG cullBlockLoops);

    private:
        BOOL           bUnit1       (const ULONGLONG cullBlockLoops);
        BOOL           bUnitPrivate (const ULONGLONG cullBlockLoops);

};
//---------------------------------------------------------------------------
#endif //CxTest_CxFileH
