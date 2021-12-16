/**
 * \file  Connection.h
 * \brief MySql client
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Connection
    /// MySql connection
{
public:
///@name ctors, dtor
///@{
			 Connection(cOptions &options);
	virtual ~Connection();

	xNO_COPY_ASSIGN(Connection)
///@}

    cHandleMySqlConn &get() const;
        ///< get handle

    void_t         connect();
        ///< attempts to establish a connection to a MySql database engine running on host
    void_t         reconnect();
        ///< reconnect to DB
    bool_t         ping(int_t *errorCode = nullptr) const;
        ///< checks whether the connection to the server is working

	std::tstring_t escapeString(std::ctstring_t &sqlValue, cbool_t isQuoted) const;
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
    uint_t         fieldCount() const;
        ///< number of columns in a result set
    void_t         close();
        ///< closes a previously opened connection

private:
    cOptions        _options; ///< Connection data
    HandleMySqlConn _conn; ///< handler for one database connection

    void_t _setOption(const mysql_option option, cptr_cvoid_t arg) const;
        ///< set extra connect options and affect behavior
    void_t _setOptions(const std::map<mysql_option, cptr_cvoid_t> &options) const;
        ///< set extra connect options and affect behavior
};

} // namespace
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
