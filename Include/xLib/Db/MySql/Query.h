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

///@name Executes the SQL statement
///@{
	void_t exec(std::ctstring_t &sql) const;
	void_t exec(cptr_ctchar_t sqlFormat, ...) const;
///@}

///@name Escape with quote
///@{
	std::tstring_t escapeQuoted(std::ctstring_t &sqlValue, std::ctstring_t &forQuote) const;
		///< Creates a legal SQL string for use in an SQL statement as qouted:
		///< - Double quotes turn into: \"
		///< - single quotes turn into: \'
		///< - Single slashes turn into: \\ (double slashes)
		///< - Unescaped: spaces, |, ?, <, >, {, }, :, ~, @, !, (,), `, #, %,,,;, &, - and _, etc

	std::tstring_t escapeQuotedSqm(std::ctstring_t &sqlValue) const;
	std::tstring_t escapeQuotedDqm(std::ctstring_t &sqlValue) const;
	std::tstring_t escapeQuotedGa(std::ctstring_t &sqlValue) const;
///@}

private:
    const Connection &_conn; ///< DB connection
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - Select, Update, Insert methods
 */
//-------------------------------------------------------------------------------------------------
