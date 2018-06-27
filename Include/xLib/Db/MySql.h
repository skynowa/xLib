/**
 * \file  MySql.h
 * \brief MySql client
 */


#pragma once

#include <mysql/mysql.h>
#include <mysql/errmsg.h>
#include <mysql/mysqld_error.h>

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/Interface/ILastError.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, db)

struct MySqlConnectionData
    /// MySqlConnection data
{
    std::tstring_t host;
    std::tstring_t user;
    std::tstring_t password;
    std::tstring_t db;
    uint_t         port {};
    std::tstring_t unixSocket;
    ulong_t        clientFlag {};
};
xTYPEDEF_CONST(MySqlConnectionData);

class MySqlConnection :
	public xl::interface::ILastError<uint_t>
    /// MySql connection
{
public:
                   MySqlConnection();
        ///< constructor
    virtual       ~MySqlConnection();
        ///< destructor

    HandleMySqlConn &get() xWARN_UNUSED_RV;
        ///< get handle
    void_t         options(const mysql_option &option, cptr_cvoid_t arg) const;
        ///< set extra connect options and affect behavior
    bool_t         ping(int_t *errorCode = xPTR_NULL) const xWARN_UNUSED_RV;
        ///< checks whether the connection to the server is working
    static
    bool_t         isExists(cMySqlConnectionData &data) xWARN_UNUSED_RV;
        ///< check connection
    void_t         connect(cMySqlConnectionData &data);
        ///< attempts to establish a connection to a MySql database engine running on host
    void_t         query(cptr_ctchar_t sqlFormat, ...) const;
        ///< executes the SQL statement
    uint_t         fieldCount() const xWARN_UNUSED_RV;
        ///< number of columns in a result set
    void_t         close();
        ///< closes a previously opened connection

    // errors
    uint_t         lastError() const xOVERRIDE xWARN_UNUSED_RV;
        ///< error code for the most recently invoked API function that can succeed or fail
    std::tstring_t lastErrorStr() const xOVERRIDE xWARN_UNUSED_RV;
        ///< error message for the most recently invoked API function that failed

private:
    HandleMySqlConn _conn;
        ///< pointer to connection

    xNO_COPY_ASSIGN(MySqlConnection)
};

xNAMESPACE_END2(xl, db)
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, db)

class MySqlRecordset
    /// MySql recordset
{
public:
                 MySqlRecordset(MySqlConnection &connection, cbool_t isUseResult);
        ///< constructor
    virtual     ~MySqlRecordset();
        ///< destructor

    HandleMySqlResult &get() xWARN_UNUSED_RV;
        ///< get handle

    uint_t       fieldsNum() const xWARN_UNUSED_RV;
        ///< number of columns in a result set
    my_ulonglong rowsNum() const xWARN_UNUSED_RV;
        ///< number of rows in the result set
    void_t       fetchField(MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the current column
    void_t       fetchFieldDirect(cuint_t &fieldNumber, MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the specified column
    void_t       fetchFields(MYSQL_FIELD *field) const;
        ///< An array of MYSQL_FIELD structures for all columns of a result set
    void_t       fetchRow(std::vec_tstring_t *row) const;
        ///< fetching row

private:
    MySqlConnection  *_conn;
        ///< pointer to connection object
    HandleMySqlResult _result;
        ///< for private use

    void_t       _fetchLengths(ulong_t **fieldLengths) const;
        ///< An array of unsigned long_t integers representing the size of each column
    void_t       _fetchRow(MYSQL_ROW *row) const;
        ///< A MYSQL_ROW structure for the next row

    xNO_COPY_ASSIGN(MySqlRecordset)
};

xNAMESPACE_END2(xl, db)

//-------------------------------------------------------------------------------------------------

#if xTODO
    MYSQL_ROW row;
    unsigned long_t *lengths;
    unsigned int_t num_fields;
    unsigned int_t i;

    row = mysql_fetch_row(result);
    if (row)
    {
        num_fields = mysql_num_fields(result);
        lengths = mysql_fetch_lengths(result);
        for(i = 0; i < num_fields; i++)
        {
             printf("Column %u is %lu bytes in length.\n",         i, lengths[i]);
        }
    }
#endif


#if xTODO
    mysql_library_init()
    {
        mysql_init()

        mysql_options()

        mysql_real_connect()
        {
            //mysql_query()
            mysql_real_query()

            //Recordset
            {
                mysql_use_result()
                mysql_store_result()

                {
                    mysql_num_fields()
                    mysql_num_rows()

                    mysql_fetch_row    (pMySqlRes); //row
                    mysql_fetch_lengths(result);    //row length
                }

                mysql_free_result()
            }
        }
        mysql_close()
    }
    mysql_library_end()
#endif
