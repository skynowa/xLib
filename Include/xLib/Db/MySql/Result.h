/**
 * \file  Result.h
 * \brief SQL query result
 *
 * \libs mysqlpp
 *
 * - https://tangentsoft.com/mysqlpp/file?name=examples/simple1.cpp
 * - https://tangentsoft.com/mysqlpp/file?name=examples/simple2.cpp
 * - https://tangentsoft.com/mysqlpp/file?name=examples/simple3.cpp
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Connection;

class IResult
    /// MySql recordset
{
public:
///\name ctors, dtor
///\{
    explicit  IResult(const Connection &connection);
	virtual  ~IResult() = 0;

	xNO_DEFAULT_CONSTRUCT(IResult);
    xNO_COPY_ASSIGN(IResult);
///\}

    HandleMySqlResult &get();
        ///< get handle

    std::size_t   fields() const;
        ///< number of columns in a result set / connection
    std::uint64_t rows() const;
        ///< number of rows in the result set / connection

///\name Fetch
///\{
	MYSQL_FIELD * fetchField() const;
		///< The MYSQL_FIELD structure for the current column
	void_t        fetchFieldDirect(cuint_t fieldNumber, MYSQL_FIELD *field) const;
		///< The MYSQL_FIELD structure for the specified column
	MYSQL_FIELD * fetchFields() const;
		///< An array of MYSQL_FIELD structures for all columns of a result set
	void_t        fetchRow(row_t *row) const;
		///< fetching row
	void_t        fetchRows(rows_t *rows) const;
		///< fetching rows
///\}

protected:
	const Connection  *_conn {};
        ///< pointer to connection object
    HandleMySqlResult  _result;
        ///< result of a query that returns row

    MYSQL_ROW  _fetchRow() const;
        ///< A MYSQL_ROW structure for the next row
    culong_t * _fetchLengths() const;
        ///< An array of unsigned long_t integers representing the size of each column
};
//-------------------------------------------------------------------------------------------------
class StoreResult final :
	public IResult
	/// Recordset
{
public:
///\name ctors, dtor
///\{
	explicit  StoreResult(const Connection &connection);
	virtual  ~StoreResult() = default;

	xNO_DEFAULT_CONSTRUCT(StoreResult);
    xNO_COPY_ASSIGN(StoreResult);
///\}
};
//-------------------------------------------------------------------------------------------------
class UseResult final :
	public IResult
	/// Recordset
{
public:
///\name ctors, dtor
///\{
	explicit  UseResult(const Connection &connection);
	virtual  ~UseResult() = default;

	xNO_DEFAULT_CONSTRUCT(UseResult);
	xNO_COPY_ASSIGN(UseResult);
///\}
};
//-------------------------------------------------------------------------------------------------

} // namespace
