/**
 * \file   CxTest_CxBase64.h
 * \brief
 */


#ifndef CxTest_CxBase64H
#define CxTest_CxBase64H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Crypt/OpenSSL/CxBase64.h>
//---------------------------------------------------------------------------
class CxTest_CxBase64 :
    public CxTest
{
    public:
                     CxTest_CxBase64();
        virtual     ~CxTest_CxBase64();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxBase64H
