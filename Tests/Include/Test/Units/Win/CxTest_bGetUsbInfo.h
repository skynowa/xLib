/**
 * \file   CxTest_bGetUsbInfo.h
 * \brief
 */


#ifndef CxTest_bGetUsbInfoH
#define CxTest_bGetUsbInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Units/Win/bGetUsbInfo.h>
//---------------------------------------------------------------------------
class CxTest_bGetUsbInfo :
    public CxTest
{
    public:
                     CxTest_bGetUsbInfo();
        virtual     ~CxTest_bGetUsbInfo();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_bGetUsbInfoH
