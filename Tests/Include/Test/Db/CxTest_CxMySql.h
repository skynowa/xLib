/**
 * \file   CxTest_CxMySql.h
 * \brief
 */


#ifndef CxTest_CxMySqlH
#define CxTest_CxMySqlH
//------------------------------------------------------------------------------
#if xCXMYSQL_IS_USE

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Db/CxMySql.h>
//------------------------------------------------------------------------------
class CxTest_CxMySql :
    public CxTest
{
public:
                 CxTest_CxMySql();
    virtual     ~CxTest_CxMySql();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};

#endif // CXMYSQL_IS_USE
//------------------------------------------------------------------------------
#endif //CxTest_CxMySqlH
