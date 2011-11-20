/**
 * \file   CxTest_CxMySql.h
 * \brief
 */


#ifndef CxTest_CxMySqlH
#define CxTest_CxMySqlH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Db/CxMySql.h>
//---------------------------------------------------------------------------
class CxTest_CxMySql :
    public CxTest
{
    public:
                     CxTest_CxMySql();
        virtual     ~CxTest_CxMySql();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxMySqlH
