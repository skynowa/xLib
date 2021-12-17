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
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Connection;

class StoreResult
    /// MySql recordset
{
public:
///@name ctors, dtor
///@{
             StoreResult(Connection &connection, cbool_t isStore);
	virtual ~StoreResult();

    xNO_COPY_ASSIGN(StoreResult)
///@}

    HandleMySqlResult &get();
        ///< get handle

    uint_t      fields() const;
        ///< number of columns in a result set
	uint_t      fieldCount() const;
		///< number of columns for the most recent query on the connection
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

private:
    Connection        *_conn {};
        ///< pointer to connection object
    HandleMySqlResult  _result;
        ///< result of a query that returns row

    void_t _fetchLengths(ulong_t **fieldLengths) const;
        ///< An array of unsigned long_t integers representing the size of each column
    void_t _fetchRow(MYSQL_ROW *row) const;
        ///< A MYSQL_ROW structure for the next row
};

} // namespace
//-------------------------------------------------------------------------------------------------
