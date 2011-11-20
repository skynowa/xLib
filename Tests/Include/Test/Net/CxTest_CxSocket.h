/**
 * \file   CxTest_CxSocket.h
 * \brief
 */


#ifndef CxTest_CxSocketH
#define CxTest_CxSocketH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxSocket :
    public CxTest
{
    public:
                     CxTest_CxSocket();
        virtual     ~CxTest_CxSocket();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSocketH
