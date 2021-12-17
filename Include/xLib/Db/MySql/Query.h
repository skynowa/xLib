/**
 * \file  Query.h
 * \brief MySql query
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Query
    /// MySql query
{
public:
///@name ctors, dtor
///@{
			 Query(const Connection &conn);
	virtual ~Query() = default;

	xNO_COPY_ASSIGN(Query)
///@}

	std::tstring_t escape(std::ctstring_t &sqlValue) const;
		///< creates a legal SQL string for use in an SQL statement:
		///<
		///< Double quotes turn into: \"
		///< single quotes turn into: \'
		///< Single slashes turn into: \\ (double slashes)
		///< Note unescaped: spaces, |, ?, <, >, {, }, :, ~, @, !, (,), `, #, %,,,;, &, - and _, etc
    void_t         exec(cptr_ctchar_t sqlFormat, ...) const;
        ///< executes the SQL statement

private:
    const Connection &_conn; ///< DB connection
};

} // namespace
//-------------------------------------------------------------------------------------------------
