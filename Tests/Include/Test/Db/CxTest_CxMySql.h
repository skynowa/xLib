/**
 * \file   CxTest_CxMySql.h
 * \brief
 */


#ifndef CxTest_CxMySqlH
#define CxTest_CxMySqlH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Db/CxMySql.h>
//---------------------------------------------------------------------------
class CxTest_CxMySql :
    public CxTest
{
public:
                 CxTest_CxMySql();
    virtual     ~CxTest_CxMySql();

    virtual void vUnit(const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxMySqlH
