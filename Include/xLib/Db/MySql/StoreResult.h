/**
 * \file  StoreResult.h
 * \brief MySql client
 *
 * \see mysqlpp
 * - https://tangentsoft.com/mysqlpp/file?name=examples/simple1.cpp
 * - https://tangentsoft.com/mysqlpp/file?name=examples/simple2.cpp
 * - https://tangentsoft.com/mysqlpp/file?name=examples/simple3.cpp
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
#include <xLib/Db/MySql/IResult.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class StoreResult :
	public IResult
    /// MySql recordset
{
public:
///@name ctors, dtor
///@{
	explicit  StoreResult(Connection &connection);
	virtual  ~StoreResult() = default;

    xNO_COPY_ASSIGN(StoreResult)
///@}

private:

};

} // namespace
//-------------------------------------------------------------------------------------------------
