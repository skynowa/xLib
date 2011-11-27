/**
 * \file   CxTest_CxClipboard.h
 * \brief
 */


#ifndef CxTest_CxClipboardH
#define CxTest_CxClipboardH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxClipboard.h>
//---------------------------------------------------------------------------
class CxTest_CxClipboard :
    public CxTest
{
    public:
                     CxTest_CxClipboard();
       virtual      ~CxTest_CxClipboard();

       virtual bool  bUnit             (const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxClipboardH
