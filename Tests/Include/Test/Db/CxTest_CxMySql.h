/**
 * \file   CxTest_CxMySql.h
 * \brief
 */


#pragma once

#if xHAVE_MYSQL

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Db/CxMySql.h>
//------------------------------------------------------------------------------
class CxTest_CxMySql :
    public CxTest
{
public:
                   CxTest_CxMySql() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//------------------------------------------------------------------------------

#endif // CXMYSQL_IS_USE
