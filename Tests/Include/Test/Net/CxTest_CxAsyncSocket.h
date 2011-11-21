/**
 * \file   CxTest_CxAsyncSocket.h
 * \brief
 */


#ifndef CxTest_CxAsyncSocketH
#define CxTest_CxAsyncSocketH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxAsyncSocket.h>
//---------------------------------------------------------------------------
class CxTest_CxAsyncSocket :
    public CxTest
{
    public:
                     CxTest_CxAsyncSocket();
        virtual     ~CxTest_CxAsyncSocket();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAsyncSocketH
