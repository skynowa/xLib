/**
 * \file  MySqlRecordset.h
 * \brief MySql client
 */


#pragma once

#include <mysql/mysql.h>

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db
{

class MySqlConnection;

class MySqlRecordset
    /// MySql recordset
{
public:
                MySqlRecordset(MySqlConnection &connection, cbool_t isUseResult);
    virtual    ~MySqlRecordset() = default;

    HandleMySqlResult &get();
        ///< get handle

    uint_t      fieldsNum() const;
        ///< number of columns in a result set
    std::size_t rowsNum() const;
        ///< number of rows in the result set
    void_t      fetchField(MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the current column
    void_t      fetchFieldDirect(cuint_t &fieldNumber, MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the specified column
    void_t      fetchFields(MYSQL_FIELD *field) const;
        ///< An array of MYSQL_FIELD structures for all columns of a result set
    void_t      fetchRow(std::vec_tstring_t *row) const;
        ///< fetching row

private:
    MySqlConnection  *_conn {};
        ///< pointer to connection object
    HandleMySqlResult _result;
        ///< result of a query that returns row

    void_t _fetchLengths(ulong_t **fieldLengths) const;
        ///< An array of unsigned long_t integers representing the size of each column
    void_t _fetchRow(MYSQL_ROW *row) const;
        ///< A MYSQL_ROW structure for the next row

    xNO_COPY_ASSIGN(MySqlRecordset)
};

} // namespace
//-------------------------------------------------------------------------------------------------
