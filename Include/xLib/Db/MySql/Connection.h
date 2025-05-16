/**
 * \file  Connection.h
 * \brief DB connection
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
#include <xLib/Db/MySql/Options.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Query;

class Connection
    /// MySql connection
{
public:
///\name ctors, dtor
///\{
	explicit Connection(const Options &options);
		///< Read options from Options struct
	explicit Connection(std::ctstring_t &optionsFile);
		///< Read options from the named option file instead of from my.cnf
	virtual ~Connection() = default;

	xNO_DEFAULT_CONSTRUCT(Connection);
	xNO_COPY_ASSIGN(Connection);
///\}

    cHandleMySqlConn &get() const;
        ///< get handle
    std::ctstring_t  &lastSql() const;
        ///< last SQL query

///\name Connection
///\{
	void_t connect() const;
		///< attempts to establish a connection to a MySql database engine running on host
	void_t reconnect();
		///< reconnect to DB
	bool_t ping() const;
		///< checks whether the connection to the server is working
	void_t selectDb(std::ctstring_t &dbName) const;
		///< Causes the DB specified by dbName to become the default (current) DB on the connection
    void_t close();
        ///< closes a previously opened connection
    void_t kill(culong_t pid);
        ///< Asks the server to kill the thread specified by pid.
///\}

///\name Commit
///\{
	void_t setAutoCommit(cbool_t flag) const;
		///< sets autocommit mode on
		///< \note: Must be called AFTER connect()
	void_t commit();
		///< commits the current transaction
	void_t rollback();
		///< rolls back the current transaction
	Query  query(std::ctstring_t &sql);
		///< get Query object
///\}

private:
    const Options   _options;		///< Connection data
    std::ctstring_t _optionsFile;	///< Connection data from file my.cnf
    HandleMySqlConn _conn;			///< handler for one database connection
    std::tstring_t  _lastSql;		///< last SQL query

    void_t _init();
		///< initiation

///\name Options
///\{
	void_t _setOption(const mysql_option option, cptr_cvoid_t arg) const;
		///< set extra connect options and affect behavior
	void_t _setOptions(const std::map<mysql_option, cptr_cvoid_t> &options) const;
		///< set extra connect options and affect behavior
///\}

///\name Connection
///\{
	void_t _connectByOptions() const;
	void_t _connectByOptionsFile() const;
///\}
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * \code{.cpp}
 *
 * ::mysql_library_init()
 *
 * // Connection
 * {
 * 	MYSQL *conn = ::mysql_init();
 *
 * 	::mysql_options(conn);
 * 	::mysql_real_connect(conn);
 *
 * 	// Query
 * 	{
 * 		::mysql_real_query(conn);
 *
 * 		// Result
 * 		{
 * 			MYSQL_RES *result = ::mysql_store_result(conn) / ::mysql_use_result(conn);
 *
 * 			uint_t    rows    = ::mysql_num_rows(result);
 * 			uint_t    fields  = ::mysql_num_fields(result);
 * 			ulong_t **lengths = ::mysql_fetch_lengths(result);	// row lengths
 *
 * 			// Rows
 * 			{
 * 				MYSQL_ROW row;
 *
 * 				while ((row = ::mysql_fetch_row(result)) != nullptr) {
 * 					printf("Field %s: ", row[0]);
 *
 * 					for (uint_t i = 0; i < fields; ++ i) {
 * 						printf("Column %u is %lu bytes in length.\n", i, lengths[i]);
 * 					}
 *
 *					MYSQL_FIELD *field {};
 *					std::size_t  index {};
 *
 *					while ((field = ::mysql_fetch_field(result)) != nullptr) {
 *						std::string key(field->name);
 *						std::string value(row[index ++]);
 *
 *						data.push_back( {key, value} );
 *					}
 * 				}
 * 			} // Rows
 *
 * 			::mysql_free_result(result);
 * 		}
 * 	}
 *
 * 	::mysql_close(conn);
 * }
 *
 * ::mysql_library_end();
 *
 * \endcode
 */
//-------------------------------------------------------------------------------------------------
