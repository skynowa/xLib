/**
 * \file  Connection.cpp
 * \brief Database connection
 */


#include "Connection.h"

#include <xLib/Fs/FileInfo.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Connection::Connection(
	const Options &a_options
) :
	_options{a_options}
{
    xTEST_NA(a_options);

    _init();
}
//-------------------------------------------------------------------------------------------------
Connection::Connection(
	std::ctstring_t &a_optionsFile
) :
	_optionsFile{a_optionsFile}
{
    xTEST(FileInfo(a_optionsFile).isExists());

    _init();
}
//-------------------------------------------------------------------------------------------------
cHandleMySqlConn &
Connection::get() const
{
    return _conn;
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::setAutoCommit(
	cbool_t a_flag
) const
{
	bool_t bRv = ::mysql_autocommit(_conn.get(), a_flag);
	xTEST_MSG(bRv, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::connect() const
{
	if ( !_optionsFile.empty() ) {
		_connectByOptionsFile();
	} else {
		_connectByOptions();
	}
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::reconnect()
{
    close();
    _init();
    connect();
}
//-------------------------------------------------------------------------------------------------
bool_t
Connection::ping() const
{
    int_t iRv = ::mysql_ping( _conn.get() );
    xTEST_EQ(iRv, 0);

    return (iRv == 0);
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::selectDb(
	std::ctstring_t &a_dbName	///< DB name
) const
{
	int_t iRv = ::mysql_select_db(_conn.get(), xT2A(a_dbName).c_str());
	xTEST_EQ_MSG(iRv, 0, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::close()
{
    xTEST_NA(_conn);

    _conn.close();
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::kill(
	culong_t a_pid
)
{
    xTEST_GR(a_pid, 0UL);

    int_t iRv = ::mysql_kill(_conn.get(), a_pid);
    xTEST_EQ_MSG(iRv, 0, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::commit()
{
	bool_t bRv = ::mysql_commit(_conn.get());
	xTEST_MSG(bRv, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::rollback()
{
	bool_t bRv = ::mysql_rollback(_conn.get());
	xTEST_MSG(bRv, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
Query
Connection::query(
	std::ctstring_t &a_sql
) const
{
	return Query(*this, a_sql);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Connection::_init()
{
    xTEST(!_conn.isValid());

    _conn = ::mysql_init(nullptr);
    xTEST_MSG(_conn.isValid(), Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
/**
 * By using mysql_options() the MySQL client library reads the [client] and [your_prog_name]
 * sections in the my.cnf file. This enables you to add options to the [your_prog_name] section to
 * ensure that your program works, even if someone has set up MySQL in some nonstandard way.
 *
 * \see https://dev.mysql.com/doc/refman/8.0/en/mysql-get-option.html
 */
void_t
Connection::_setOption(
    const mysql_option a_option,
    cptr_cvoid_t       a_arg
) const
{
    xTEST(_conn.isValid());
    xTEST_NA(a_option);
    xTEST_NA(a_arg);

    int_t iRv = ::mysql_options(_conn.get(), a_option, a_arg);
    xTEST_EQ_MSG(iRv, 0, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::_setOptions(
	const std::map<mysql_option, cptr_cvoid_t> &a_options
) const
{
	for (const auto &[it_name, it_value] : a_options) {
		_setOption(it_name, it_value);
	}
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::_connectByOptions() const
{
    xTEST(_conn.isValid());

	// options - default
	{
		constexpr int_t connectTimeoutSec {5};
		constexpr int_t readTimeoutSec    {connectTimeoutSec * 10};
		constexpr int_t writeTimeoutSec   {connectTimeoutSec * 10};

		static const std::map<mysql_option, cptr_cvoid_t> &options
		{
			{MYSQL_OPT_CONNECT_TIMEOUT, &connectTimeoutSec},
			{MYSQL_OPT_READ_TIMEOUT,    &readTimeoutSec},
			{MYSQL_OPT_WRITE_TIMEOUT,   &writeTimeoutSec}
		};

		_setOptions(options);
	}

	// options - rewrite
	_setOptions(_options.options);

	cchar_t  *host       = xT2A(_options.host).c_str();
	cchar_t  *user       = xT2A(_options.user).c_str();
	cchar_t  *password   = xT2A(_options.password).c_str();
	cchar_t  *db         = _options.db.empty() ?         nullptr : xT2A(_options.db).c_str();
	cuint_t   port       = _options.port;
	cchar_t  *unixSocket = _options.unixSocket.empty() ? nullptr : xT2A(_options.unixSocket).c_str();
	culong_t  clientFlag = !_options.isCompress ?        0       : CLIENT_COMPRESS;	// bit mask

    MYSQL *conn = ::mysql_real_connect(_conn.get(), host, user, password, db, port, unixSocket,
        clientFlag);
    if (conn == nullptr) {
        xTEST_MSG(false, Error(*this).str());
        return;
    }

    xTEST_EQ(_conn.get(), conn);

	int_t iRv = ::mysql_set_character_set(_conn.get(), _options.charset.c_str());
	xTEST_EQ_MSG(iRv, 0, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::_connectByOptionsFile() const
{
    xTEST(_conn.isValid());

    // options - from file
	_setOption(MYSQL_READ_DEFAULT_FILE, const_cast<char *>(xT2A(_optionsFile).c_str()));

	cchar_t  *host {};
	cchar_t  *user {};
	cchar_t  *password {};
	cchar_t  *db {};
	cuint_t   port {};
	cchar_t  *unixSocket {};
	culong_t  clientFlag {CLIENT_COMPRESS};	// bit mask

    MYSQL *conn = ::mysql_real_connect(_conn.get(), host, user, password, db, port, unixSocket,
        clientFlag);
    if (conn == nullptr) {
        xTEST_MSG(false, Error(*this).str());
        return;
    }

    xTEST_EQ(_conn.get(), conn);

	int_t iRv = ::mysql_set_character_set(_conn.get(), _options.charset.c_str());
	xTEST_EQ_MSG(iRv, 0, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
