/**
 * \file   Test_MySql.h
 * \brief
 */


#pragma once

#if xHAVE_MYSQL

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Db/MySql.h>
//-------------------------------------------------------------------------------------------------
class Test_MySql :
    public UnitTest
{
public:
                   Test_MySql() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

#endif // CXMYSQL_IS_USE
