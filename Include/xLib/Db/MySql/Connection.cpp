/**
 * \file  Connection.cpp
 * \brief MySql client
 */


#include "Connection.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Connection::Connection(
	cOptions &a_options
) :
	_options{a_options}
{
    xTEST(!_conn.isValid());
    xTEST_NA(a_options);

    _conn = ::mysql_init(nullptr);
    xTEST_MSG(_conn.isValid(), Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
cHandleMySqlConn &
Connection::get() const
{
    return _conn;
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::connect()
{
    xTEST(_conn.isValid());

	// options - default
	{
		constexpr int_t connectTimeoutSec {5};
		constexpr int_t readTimeoutSec    {connectTimeoutSec * 10};
		constexpr int_t writeTimeoutSec   {connectTimeoutSec * 10};

		const std::map<mysql_option, cptr_cvoid_t> &options
		{
			{MYSQL_OPT_CONNECT_TIMEOUT, &connectTimeoutSec},
			{MYSQL_OPT_READ_TIMEOUT,    &readTimeoutSec},
			{MYSQL_OPT_WRITE_TIMEOUT,   &writeTimeoutSec}
		};

		_setOptions(options);
	}

	// options - set/rewrite
	_setOptions(_options.options);

	cchar    *db         = _options.db.empty() ?         nullptr : xT2A(_options.db).c_str();
	cchar    *unixSocket = _options.unixSocket.empty() ? nullptr : xT2A(_options.unixSocket).c_str();
	culong_t  clientFlag = !_options.isCompress ?        0       : CLIENT_COMPRESS;	// bit mask

    MYSQL *conn = ::mysql_real_connect(_conn.get(), xT2A(_options.host).c_str(),
        xT2A(_options.user).c_str(), xT2A(_options.password).c_str(), db, _options.port,
		unixSocket, clientFlag);
    xTEST_PTR_MSG(conn, Error(*this).str());
    xTEST_EQ(_conn.get(), conn);

	int_t iRv = ::mysql_set_character_set(_conn.get(), _options.charset.c_str());
	xTEST_EQ_MSG(iRv, 0, Error(*this).str());

    _setAutoCommit();
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::reconnect()
{
    close();

    xTEST(!_conn.isValid());

    _conn = ::mysql_init(nullptr);
    xTEST_EQ_MSG(_conn.isValid(), true, Error(*this).str());

    connect();
}
//-------------------------------------------------------------------------------------------------
bool_t
Connection::ping(
    int_t *out_errorCode	///< [out] error code
) const
{
	xTEST_PTR(out_errorCode);

	Utils::ptrAssignT(out_errorCode, 0);

    int_t iRv = ::mysql_ping( _conn.get() );
    if (iRv != 0) {
        Utils::ptrAssignT(out_errorCode, iRv);
        return false;
    }

    return true;
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


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
// https://dev.mysql.com/doc/refman/8.0/en/mysql-get-option.html
void_t
Connection::_setOption(
    const mysql_option a_option,
    cptr_cvoid_t       a_arg
) const
{
    xTEST(_conn.isValid());
    xTEST_NA(a_option);
    xTEST_NA(a_arg);

#if MYSQL_VERSION_ID < 50154
    int_t iRv = ::mysql_options(_conn.get(), a_option, static_cast<cptr_ctchar_t>(a_arg));
#else
    int_t iRv = ::mysql_options(_conn.get(), a_option, a_arg);
#endif
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
Connection::_setAutoCommit() const
{
	const char autoMode = static_cast<my_bool>(_options.isAutoCommit);
		///< flag (if mode is true, off if mode is false)

	bool_t bRv = ::mysql_autocommit(_conn.get(), autoMode);
	xTEST_MSG(bRv, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
