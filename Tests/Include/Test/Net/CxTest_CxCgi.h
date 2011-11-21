/**
 * \file   CxTest_CxCgi.h
 * \brief
 */


#ifndef CxTest_CxCgiH
#define CxTest_CxCgiH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxCgi.h>
//---------------------------------------------------------------------------
class CxTest_CxCgi :
    public CxTest
{
    public:
                     CxTest_CxCgi();
        virtual     ~CxTest_CxCgi();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCgiH
