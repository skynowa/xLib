/**
 * \file   CxTest_CxConnectionString.h
 * \brief
 */


#ifndef CxTest_CxConnectionStringH
#define CxTest_CxConnectionStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Db/CxConnectionString.h>
//---------------------------------------------------------------------------
class CxTest_CxConnectionString :
    public CxTest
{
    public:
                     CxTest_CxConnectionString();
        virtual     ~CxTest_CxConnectionString();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxConnectionStringH
