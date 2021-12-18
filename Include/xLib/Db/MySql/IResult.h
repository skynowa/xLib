/**
 * \file  IResult.h
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

class Connection;

class IResult
    /// MySql recordset
{
public:
///@name ctors, dtor
///@{
    explicit  IResult(Connection &connection);
	virtual  ~IResult() = 0;

    xNO_COPY_ASSIGN(IResult)
///@}

    HandleMySqlResult &get();
        ///< get handle

    std::size_t fields() const;
        ///< number of columns in a result set / connection
    std::size_t rows() const;
        ///< number of rows in the result set
    void_t      fetchField(MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the current column
    void_t      fetchFieldDirect(cuint_t fieldNumber, MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the specified column
    void_t      fetchFields(MYSQL_FIELD *field) const;
        ///< An array of MYSQL_FIELD structures for all columns of a result set
    void_t      fetchRow(std::vec_tstring_t *row) const;
        ///< fetching row

protected:
    Connection        *_conn {};
        ///< pointer to connection object
    HandleMySqlResult  _result;
        ///< result of a query that returns row

    MYSQL_ROW  _fetchRow() const;
        ///< A MYSQL_ROW structure for the next row
    culong_t * _fetchLengths() const;
        ///< An array of unsigned long_t integers representing the size of each column
};

} // namespace
//-------------------------------------------------------------------------------------------------
