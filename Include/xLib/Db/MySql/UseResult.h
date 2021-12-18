/**
 * \file  UseResult.h
 * \brief MySql client
 *
 * \see mysqlpp
 * - https://tangentsoft.com/mysqlpp/file?name=examples/simple1.cpp
 * - https://tangentsoft.com/mysqlpp/file?name=examples/simple2.cpp
 * - https://tangentsoft.com/mysqlpp/file?name=examples/simple3.cpp
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class UseResult :
	public IResult
    /// MySql recordset
{
public:
///@name ctors, dtor
///@{
	explicit  UseResult(Connection &connection);
	virtual  ~UseResult() = default;

    xNO_COPY_ASSIGN(UseResult)
///@}

private:

};

} // namespace
//-------------------------------------------------------------------------------------------------
