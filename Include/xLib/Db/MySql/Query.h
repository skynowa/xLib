/**
 * \file  Query.h
 * \brief MySql query
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
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

	xNO_DEFAULT_CONSTRUCT(Query);
	xNO_COPY_ASSIGN(Query);
///\}

///\name Executes the SQL statement
///\{
	void_t      exec() const;
	StoreResult store() const;
	UseResult   use() const;
///\}

private:
    const Connection &_conn;	///< DB connection
    std::ctstring_t   _sql;		///< SQL query
};
//-------------------------------------------------------------------------------------------------
class EscapeQuoted
	/// Escape with quote (Brief Creates a legal SQL string for use in an SQL statement as qouted)
{
public:
///\name ctors, dtor
///\{
			 EscapeQuoted(const Connection &conn, std::ctstring_t &sqlValue);
	virtual ~EscapeQuoted() = default;

	xNO_DEFAULT_CONSTRUCT(EscapeQuoted);
	xNO_COPY_ASSIGN(EscapeQuoted);
///\}

	std::tstring_t forQuote(std::ctstring_t &forQuote) const;
	std::tstring_t forSqm() const;
	std::tstring_t forDqm() const;
	std::tstring_t forGa() const;

private:
    const Connection &_conn;		///< DB connection
    std::ctstring_t   _sqlValue;	///< SQL query value
};
//-------------------------------------------------------------------------------------------------

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - Select, Update, Insert methods
 */
//-------------------------------------------------------------------------------------------------
