/**
 * \file   Test_MySql.h
 * \brief
 */


#pragma once

#if xHAVE_MYSQL

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_MySql :
    public Unit
{
public:
                   Test_MySql() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

#endif // CXMYSQL_IS_USE
