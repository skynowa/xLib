/**
 * \file  MySqlConnection.cpp
 * \brief MySql client
 */


#include "MySqlConnection.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>

#include <xLib/Db/MySql/MySqlRecordset.h>


namespace xl::db
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MySqlConnection::MySqlConnection()
{
    xTEST(!_conn.isValid());

    _conn = ::mysql_init(nullptr);
    xTEST_MSG(_conn.isValid(), lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
HandleMySqlConn &
MySqlConnection::get()
{
    return _conn;
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::connect(
    cMySqlConnectionData &a_data
)
{
    xTEST(_conn.isValid());
    xTEST_NA(a_data);

	const char *db {};
	{
		if ( !a_data.db.empty() ) {
			db = xT2A(a_data.db).c_str();
		}
	}

	const char *unixSocket {};
	{
		if ( !a_data.unixSocket.empty() ) {
			unixSocket = xT2A(a_data.unixSocket).c_str();
		}
	}

	ulong_t clientFlag {};
	{
		if (a_data.isCompress) {
			clientFlag |= CLIENT_COMPRESS;
		}
	}

	{
		_setOptions(a_data.options);

		constexpr int connect_timeout_sec = 5;
		constexpr int read_timeout_sec    = connect_timeout_sec * 10;
		constexpr int write_timeout_sec   = connect_timeout_sec * 10;

		::mysql_options(_conn.get(), MYSQL_OPT_CONNECT_TIMEOUT, &connect_timeout_sec);
		::mysql_options(_conn.get(), MYSQL_OPT_READ_TIMEOUT,    &read_timeout_sec);
		::mysql_options(_conn.get(), MYSQL_OPT_WRITE_TIMEOUT,   &write_timeout_sec);
	}

    MYSQL *conn = ::mysql_real_connect(_conn.get(), xT2A(a_data.host).c_str(),
    	xT2A(a_data.user).c_str(), xT2A(a_data.password).c_str(), db, a_data.port, unixSocket,
		clientFlag);
    xTEST_PTR_MSG(conn, lastErrorStr());
    xTEST_EQ(_conn.get(), conn);

	int_t iRv = ::mysql_set_character_set(_conn.get(), a_data.charset.c_str());
	xTEST_EQ_MSG(iRv, 0, lastErrorStr());

    // setAutoCommit() must be called AFTER connect()
    /// setAutoCommit(a_data.isAutoCommit);
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::reconnect()
{
    close();

    xTEST_EQ(_conn.isValid(), false);

    _conn = ::mysql_init(nullptr);
    xTEST_EQ_MSG(_conn.isValid(), true, lastErrorStr());

    connect(_data);
}
//-------------------------------------------------------------------------------------------------
bool_t
MySqlConnection::ping(
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
std::tstring_t
MySqlConnection::escapeString(
	std::ctstring_t &a_sqlValue,				///< SQL string value
	cbool_t          a_isQuoted /* = true */	///< is quote SQL string value
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
	xTEST_GR_MSG(quotedSize, 0UL, lastErrorStr());

	sRv.resize(quotedSize * sizeof(std::tstring_t::value_type));

	if (a_isQuoted) {
	   /**
		* If the ANSI_QUOTES SQL mode is enabled:
		*
		* string literals can be quoted only within single quotation marks because
		* a string quoted within double quotation marks is interpreted as an identifier.
		*/
		sRv = Const::sqm() + sRv + Const::sqm();
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::query(
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
    xTEST_EQ_MSG(iRv, 0, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::setAutoCommit(
	cbool_t a_flag	///< flag (if mode is true, off if mode is false)
) const
{
	bool_t bRv = ::mysql_autocommit(_conn.get(), a_flag);
	xTEST_MSG(bRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::commit()
{
	bool_t bRv = ::mysql_commit(_conn.get());
	xTEST_MSG(bRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::rollback()
{
	bool_t bRv = ::mysql_rollback(_conn.get());
	xTEST_MSG(bRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
uint_t
MySqlConnection::fieldCount() const
{
    xTEST(_conn.isValid());

    return ::mysql_field_count(_conn.get());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::close()
{
    xTEST_NA(_conn);

    _conn.close();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    errors
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
uint_t
MySqlConnection::lastError() const
{
    xTEST(_conn.isValid());

    return ::mysql_errno( _conn.get() );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
MySqlConnection::lastErrorStr() const
{
    xTEST(_conn.isValid());

    std::tstring_t sRv;

    cuint_t    _lastError = lastError();
    cptr_cchar error      = ::mysql_error( _conn.get() );
    xTEST_PTR(error);

    if (_lastError == 0U) {
        sRv = Format::str(xT("{} - \"{}\""), _lastError, xT("Success"));
    } else {
        sRv = Format::str(xT("{} - \"{}\""), _lastError, error);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
bool_t
MySqlConnection::isDbExists(
    cMySqlConnectionData &a_data
)
{
    bool_t bRv {};

    MySqlConnectionData data = a_data;
    data.db = {};

    MySqlConnection conn;
    {
        bRv = conn.get().isValid();
        xCHECK_RET(!bRv, false);

        conn.connect(data);
        conn.query(
            xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA "
               "WHERE SCHEMA_NAME = '%s'), 'true', 'false')"),
               a_data.db.c_str());
    }

    {
        MySqlRecordset rec(conn, false);

        bRv = rec.get().isValid();
        xTEST(bRv);
        xTEST_EQ(rec.rowsNum(), std::size_t(1));

        std::vec_tstring_t row;
        rec.fetchRow(&row);
        xTEST_EQ(row.size(), static_cast<size_t>(1));
        xCHECK_RET(StringCI::compare(xT("false"), row[0]), false);
        xTEST_EQ(StringCI::compare(xT("true"), row[0]), true);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
MySqlConnection::dbCreate(
    cMySqlConnectionData &a_data
)
{
	std::ctstring_t db = a_data.db;

	MySqlConnectionData data = a_data;
	data.db = {};

	MySqlConnection conn;
	conn.connect(data);
	conn.query(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"), db.c_str());
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
MySqlConnection::dbDrop(
    cMySqlConnectionData &a_data
)
{
	MySqlConnectionData data = a_data;
	data.db = {};

	MySqlConnection conn;
	conn.connect(data);
	conn.query(xT("DROP DATABASE IF EXISTS `%s`"), a_data.db.c_str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
// https://dev.mysql.com/doc/refman/8.0/en/mysql-get-option.html
void_t
MySqlConnection::_setOption(
    const mysql_option &a_option,
    cptr_cvoid_t        a_arg
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
    xTEST_EQ_MSG(iRv, 0, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::_setOptions(
	const std::map<mysql_option, cptr_cvoid_t> &a_options
) const
{
	for (const auto &[name, value] : a_options) {
		_setOption(name, value);
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
