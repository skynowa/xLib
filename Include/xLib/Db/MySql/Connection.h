/**
 * \file  Connection.h
 * \brief MySql client
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Options;

class Connection
    /// MySql connection
{
public:
///@name ctors, dtor
///@{
			 Connection(const Options &options);
	virtual ~Connection() = default;

	xNO_COPY_ASSIGN(Connection)
///@}

    cHandleMySqlConn &get() const;
        ///< get handle

///@name Connection
///@{
	void_t connect();
		///< attempts to establish a connection to a MySql database engine running on host
	void_t reconnect();
		///< reconnect to DB
	bool_t ping(int_t *errorCode) const;
		///< checks whether the connection to the server is working
    void_t close();
        ///< closes a previously opened connection
///@}

///@name Commit
///@{
	void_t commit();
		///< commits the current transaction
	void_t rollback();
		///< rolls back the current transaction
///@}

private:
    const Options   &_options; ///< Connection data
    HandleMySqlConn  _conn; ///< handler for one database connection

    void_t _init();
		///< initiation

///@name Options
///@{
	void_t _setOption(const mysql_option option, cptr_cvoid_t arg) const;
		///< set extra connect options and affect behavior
	void_t _setOptions(const std::map<mysql_option, cptr_cvoid_t> &options) const;
		///< set extra connect options and affect behavior
	void_t _setAutoCommit() const;
		///< sets autocommit mode on
		///< \note: Must be called AFTER connect()
///@}
};

} // namespace
//-------------------------------------------------------------------------------------------------
#if xTODO
	::mysql_library_init()

	// Connection
	{
		MYSQL *conn = ::mysql_init();

		::mysql_options(conn);
		::mysql_real_connect(conn);

		// Query
		{
			::mysql_real_query(conn) / ::mysql_query(conn);

			// Result
			{
				MYSQL_RES *result = ::mysql_use_result(conn) / ::mysql_store_result(conn);

				uint_t    rows    = ::mysql_num_rows(result);
				uint_t    fields  = ::mysql_num_fields(result);
				ulong_t **lengths = ::mysql_fetch_lengths(result);	// row lengths

				// Rows
				{
					MYSQL_ROW row;

					while ((row = ::mysql_fetch_row(result)) != nullptr) {
						printf("Row %s: ", row[0]);

						for (uint_t i = 0; i < fields; ++ i) {
							printf("Column %u is %lu bytes in length.\n", i, lengths[i]);
						}
					}
				}

				::mysql_free_result(result);
			}
		}

		::mysql_close(conn);
	}

    ::mysql_library_end()
#endif

#if 0
	<?php
	function mysql_current_db()
    {
		$r = mysql_query("SELECT DATABASE()") or die(mysql_error());

		return mysql_result($r,0);
	}
	?>
#endif
