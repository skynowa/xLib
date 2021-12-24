/**
 * \file  Query.h
 * \brief MySql query
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
#include <xLib/Db/MySql/Result.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Connection;
class StoreResult;
class UseResult;

class Query
    /// MySql query
{
public:
///\name ctors, dtor
///\{
			 Query(const Connection &conn, std::ctstring_t &sql);
	virtual ~Query() = default;

	xNO_DEFAULT_CONSTRUCT(Query)
	xNO_COPY_ASSIGN(Query)
///\}

///\name Executes the SQL statement
///\{
	void_t      exec() const;
	StoreResult store() const;
	UseResult   use() const;
///\}

///\name  Escape with quote
///\brief Creates a legal SQL string for use in an SQL statement as qouted:
/// - Double quotes turn into: \"
/// - single quotes turn into: \'
/// - Single slashes turn into: \\ (double slashes)
/// - Unescaped: spaces, |, ?, <, >, {, }, :, ~, @, !, (,), `, #, %,,,;, &, - and _, etc
///\{
	std::tstring_t escapeQuoted(std::ctstring_t &sqlValue, std::ctstring_t &forQuote) const;
	std::tstring_t escapeQuotedSqm(std::ctstring_t &sqlValue) const;
	std::tstring_t escapeQuotedDqm(std::ctstring_t &sqlValue) const;
	std::tstring_t escapeQuotedGa(std::ctstring_t &sqlValue) const;
///\}

private:
    const Connection &_conn;	///< DB connection
    std::ctstring_t   _sql;		///< SQL query
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - Select, Update, Insert methods
 */
//-------------------------------------------------------------------------------------------------
