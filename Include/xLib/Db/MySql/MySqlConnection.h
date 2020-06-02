/**
 * \file  MySqlConnection.h
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
        ///< host name or an IP address. If host is empty or the string "localhost",
        ///< a connection to the local host is assumed
    std::tstring_t user;
        ///< MySQL login ID. If user is empty string, the current user is assumed
    std::tstring_t password;
        ///< password
    std::tstring_t db;
        ///< DB name.
    uint_t         port {};
        ///< If port is not 0, the value is used as the port number for the TCP/IP connection
    std::tstring_t unixSocket;
        ///< If unix_socket is not empty, the string specifies the socket or named pipe to use
    std::tstring_t charset;
        ///< specifies character name
    bool_t         isAutoCommit {};
        ///< sets autocommit mode on
    bool_t         isCompress {};
        ///< Use compression in the client/server protocol
    std::map<mysql_option, cptr_cvoid_t> options;
        ///< extra options
};
xUSING_CONST(MySqlConnectionData);

class MySqlConnection :
	public xl::interface::ILastError<uint_t>
    /// MySql connection
{
public:
                   MySqlConnection();
    virtual       ~MySqlConnection() = default;

    xNO_COPY_ASSIGN(MySqlConnection)

    HandleMySqlConn &get() xWARN_UNUSED_RV;
        ///< get handle

    void_t         connect(cMySqlConnectionData &data);
        ///< attempts to establish a connection to a MySql database engine running on host
    void_t         reconnect();
        ///< reconnect to DB
    bool_t         ping(int_t *errorCode = nullptr) const xWARN_UNUSED_RV;
        ///< checks whether the connection to the server is working

	std::tstring_t escapeString(std::ctstring_t &sqlValue, cbool_t isQuoted = true) const
						xWARN_UNUSED_RV;
		///< creates a legal SQL string for use in an SQL statement:
		///<
		///< Double quotes turn into: \"
		///< single quotes turn into: \'
		///< Single slashes turn into: \\ (double slashes)
		///< Note unescaped: spaces, |, ?, <, >, {, }, :, ~, @, !, (,), `, #, %,,,;, &, - and _, etc
    void_t         query(cptr_ctchar_t sqlFormat, ...) const;
        ///< executes the SQL statement
    void_t         setAutoCommit(cbool_t flag) const;
        ///< sets autocommit mode on (setAutoCommit() must be called AFTER connect())
    void_t         commit();
        ///< commits the current transaction
    void_t         rollback();
        ///< rolls back the current transaction
    uint_t         fieldCount() const xWARN_UNUSED_RV;
        ///< number of columns in a result set
    void_t         close();
        ///< closes a previously opened connection

    // errors
    uint_t         lastError() const override xWARN_UNUSED_RV;
        ///< error code for the most recently invoked API function that can succeed or fail
    std::tstring_t lastErrorStr() const override xWARN_UNUSED_RV;
        ///< error message for the most recently invoked API function that failed

xPUBLIC_STATIC:
	static
	bool_t isDbExists(cMySqlConnectionData &data) xWARN_UNUSED_RV;
		///< check connection
	static
	void_t dbCreate(cMySqlConnectionData &data);
		///< create DB
	static
	void_t dbDrop(cMySqlConnectionData &data);
		///< drop DB

private:
	MySqlConnectionData _data; ///< MySqlConnection data
    HandleMySqlConn     _conn; ///< handler for one database connection

    void_t _setOption(const mysql_option &option, cptr_cvoid_t arg) const;
        ///< set extra connect options and affect behavior
    void_t _setOptions(const std::map<mysql_option, cptr_cvoid_t> &options) const;
        ///< set extra connect options and affect behavior
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

#if 0
	<?php
	function mysql_current_db() {
		$r = mysql_query("SELECT DATABASE()") or die(mysql_error());
		return mysql_result($r,0);
	}
	?>
#endif
