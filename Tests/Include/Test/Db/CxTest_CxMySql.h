/**
 * \file   CxTest_CxMySql.h
 * \brief
 */


#pragma once

#if xCXMYSQL_IS_USE

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Db/CxMySql.h>
//------------------------------------------------------------------------------
class CxTest_CxMySql :
    public CxTest
{
public:
                   CxTest_CxMySql();
    virtual       ~CxTest_CxMySql();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

#endif // CXMYSQL_IS_USE
