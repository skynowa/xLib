/**
 * \file  CxMySql.h
 * \brief MySQL data base v.5.1
 */


#pragma once

#include <xLib/Core/xCore.h>

#if xCXMYSQL_IS_USE

#if xOS_ENV_WIN
    #include <mysql.h>
    #include <errmsg.h>
    #include <mysqld_error.h>
#else
    #include <mysql/mysql.h>
    #include <mysql/errmsg.h>
    #include <mysql/mysqld_error.h>
#endif
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMySQLConnection :
    private CxNonCopyable
    /// MySQL connection
{
public:
                             CxMySQLConnection();
        ///< constructor
    virtual                 ~CxMySQLConnection();
        ///< destructor

    MYSQL                   *get() const xWARN_UNUSED_RV;
        ///< get handle
    bool_t                   isValid() const xWARN_UNUSED_RV;
        ///< validating handle
    void_t                   options(const mysql_option &option, cvoid_t *arg) const;
        ///< set extra connect options and affect behavior
    static bool_t            isExists(std::ctstring_t &host, std::ctstring_t &user,
                                 std::ctstring_t &password, std::ctstring_t &db,
                                 cuint_t &port, std::ctstring_t &unixSocket,
                                 culong_t &clientFlag) xWARN_UNUSED_RV;
        ///<
    void_t                   connect(std::ctstring_t &host, std::ctstring_t &user,
                                 std::ctstring_t &password, std::ctstring_t &db,
                                 cuint_t &port, std::ctstring_t &unixSocket,
                                 culong_t &clientFlag);
        ///< attempts to establish a connection to a MySQL database engine running on host
    void_t                   query(ctchar_t *sqlFormat, ...) const;
        ///< executes the SQL statement
    uint_t                   fieldCount() const xWARN_UNUSED_RV;
        ///< number of columns in a result set
    void_t                   close();
        ///< closes a previously opened connection

    //errors
    uint_t                   lastError() const xWARN_UNUSED_RV;
        ///< error code for the most recently invoked API function that can succeed or fail
    std::tstring_t           lastErrorStr() const xWARN_UNUSED_RV;
        ///< error message for the most recently invoked API function that failed

private:
    MYSQL                   *_connection;
        ///< pointer to connection
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMySQLRecordset :
    private CxNonCopyable
    /// MySQL recordset
{
public:
                             CxMySQLRecordset(const CxMySQLConnection &connection,
                                 cbool_t &isUseResult);
        ///< constructor
    virtual                 ~CxMySQLRecordset();
        ///< destructor

    MYSQL_RES               *get() const xWARN_UNUSED_RV;
        ///< get handle
    bool_t                   isValid() const xWARN_UNUSED_RV;
        ///< validating handle

    uint_t                   fieldsNum() const xWARN_UNUSED_RV;
        ///< number of columns in a result set
    my_ulonglong             rowsNum() const xWARN_UNUSED_RV;
        ///< number of rows in the result set
    void_t                   fetchField(MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the current column
    void_t                   fetchFieldDirect(cuint_t &fieldNumber, MYSQL_FIELD *field) const;
        ///< The MYSQL_FIELD structure for the specified column
    void_t                   fetchFields(MYSQL_FIELD *field) const;
        ///< An array of MYSQL_FIELD structures for all columns of a result set
    void_t                   fetchRow(std::vec_tstring_t *row) const;
        ///< fetching row

private:
    const CxMySQLConnection *_connection;
        ///< pointer to connection object
    MYSQL_RES               *_result;
        ///< for private use

    void_t                   _fetchLengths(ulong_t **fieldLengths) const;
        ///< An array of unsigned long_t integers representing the size of each column
    void_t                   _fetchRow(MYSQL_ROW *row) const;
        ///< A MYSQL_ROW structure for the next row
};

xNAMESPACE_END(NxLib)

#endif // CXMYSQL_IS_USE
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif


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
