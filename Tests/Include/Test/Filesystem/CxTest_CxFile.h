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

        virtual  bool  bUnit        (const ulonglong_t cullBlockLoops);

    private:
        bool           bUnit1       (const ulonglong_t cullBlockLoops);
        bool           bUnitPrivate (const ulonglong_t cullBlockLoops);

};
//---------------------------------------------------------------------------
#endif //CxTest_CxFileH
