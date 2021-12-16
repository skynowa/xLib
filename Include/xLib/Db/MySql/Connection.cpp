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
Connection::~Connection()
{
    close();
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
		constexpr int_t connect_timeout_sec {5};
		constexpr int_t read_timeout_sec    {connect_timeout_sec * 10};
		constexpr int_t write_timeout_sec   {connect_timeout_sec * 10};

		const std::map<mysql_option, cptr_cvoid_t> &options
		{
			{MYSQL_OPT_CONNECT_TIMEOUT, &connect_timeout_sec},
			{MYSQL_OPT_READ_TIMEOUT,    &read_timeout_sec},
			{MYSQL_OPT_WRITE_TIMEOUT,   &write_timeout_sec}
		};

		_setOptions(options);
	}

	const char *db {};
	{
		if ( !_options.db.empty() ) {
			db = xT2A(_options.db).c_str();
		}
	}

	const char *unixSocket {};
	{
		if ( !_options.unixSocket.empty() ) {
			unixSocket = xT2A(_options.unixSocket).c_str();
		}
	}

	ulong_t clientFlag {};
	{
		if (_options.isCompress) {
			clientFlag |= CLIENT_COMPRESS;
		}
	}

	// options - set/rewrite
	_setOptions(_options.options);

    MYSQL *conn = ::mysql_real_connect(_conn.get(), xT2A(_options.host).c_str(),
        xT2A(_options.user).c_str(), xT2A(_options.password).c_str(), db, _options.port,
		unixSocket, clientFlag);
    xTEST_PTR_MSG(conn, Error(*this).str());
    xTEST_EQ(_conn.get(), conn);

	int_t iRv = ::mysql_set_character_set(_conn.get(), _options.charset.c_str());
	xTEST_EQ_MSG(iRv, 0, Error(*this).str());

    // setAutoCommit() must be called AFTER connect()
    /// setAutoCommit(a_options.isAutoCommit);
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
    int_t *out_errorCode    /* = nullptr */
) const
{
    int_t iRv = ::mysql_ping( _conn.get() );

    Utils::ptrAssignT(out_errorCode, iRv);

    if (iRv != 0) {
        return false;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
/**
 * If the ANSI_QUOTES SQL mode is enabled:
 *
 * string literals can be quoted only within single quotation marks because
 * a string quoted within double quotation marks is interpreted as an identifier.
 */
std::tstring_t
Connection::escapeString(
	std::ctstring_t &a_sqlValue	///< SQL string value
) const
{
	if ( a_sqlValue.empty() ) {
		return Const::sqm() + Const::sqm();
	}

	if (a_sqlValue == xT("NULL")) {
	   /**
		* If the argument is NULL:
		*
		* the return value is the word “NULL” without enclosing single quotation marks
		*/
		return a_sqlValue;
	}

	std::tstring_t sRv(a_sqlValue.size() * 2 + 1, xT('\0'));

	culong_t quotedSize = ::mysql_real_escape_string_quote(_conn.get(), &sRv[0],
		a_sqlValue.data(), static_cast<ulong_t>(a_sqlValue.size()), Const::sqmA()[0]);
	xTEST_GR_MSG(quotedSize, 0UL, Error(*this).str());

	sRv.resize(quotedSize * sizeof(std::tstring_t::value_type));

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::query(
    cptr_ctchar_t a_sqlFormat, ...
) const
{
    xTEST(_conn.isValid());
    xTEST_PTR(a_sqlFormat);

    std::tstring_t sqlQuery;
    va_list        args;

    xVA_START(args, a_sqlFormat);
    sqlQuery = FormatC::strV(a_sqlFormat, args);
    xVA_END(args);

    std::cstring_t asSqlQuery = xT2A(sqlQuery);

    int_t iRv = ::mysql_real_query(_conn.get(), asSqlQuery.data(),
        static_cast<ulong_t>( asSqlQuery.size() ));
    xTEST_EQ_MSG(iRv, 0, Error(*this).str());
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::setAutoCommit(
	cbool_t a_flag	///< flag (if mode is true, off if mode is false)
) const
{
	bool_t bRv = ::mysql_autocommit(_conn.get(), a_flag);
	xTEST_MSG(bRv, Error(*this).str());
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
uint_t
Connection::fieldCount() const
{
    xTEST(_conn.isValid());

    return ::mysql_field_count(_conn.get());
}
//-------------------------------------------------------------------------------------------------
void_t
Connection::close()
{
    xTEST_NA(_conn);

    _conn.close();
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

} // namespace
