/**
 * \file  MySql.inl
 * \brief MySql client
 */


#include "MySqlConnection.h"

#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>

#include <xLib/Db/MySql/MySqlRecordset.h>


xNAMESPACE_BEGIN2(xl, db)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MySqlConnection::MySqlConnection()
{
    xTEST_EQ(_conn.isValid(), false);

    _conn = ::mysql_init(xPTR_NULL);
    xTEST_EQ_MSG(_conn.isValid(), true, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
MySqlConnection::~MySqlConnection()
{
}
//-------------------------------------------------------------------------------------------------
HandleMySqlConn &
MySqlConnection::get()
{
    return _conn;
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::setOption(
    const mysql_option &a_option,
    cptr_cvoid_t        a_arg
) const
{
    xTEST_EQ(_conn.isValid(), true);
    xTEST_NA(a_option);
    xTEST_NA(a_arg);

#if MYSQL_VERSION_ID < 50154
    int_t iRv = ::mysql_options(_conn.get(), a_option, static_cast<cptr_ctchar_t>( a_arg ));
#else
    int_t iRv = ::mysql_options(_conn.get(), a_option, a_arg);
#endif
    xTEST_EQ_MSG(0, iRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::setOptions(
	const std::map<mysql_option, cptr_cvoid_t> &a_options
) const
{
	for (auto &it_option : a_options) {
		setOption(it_option.first, it_option.second);
	}
}
//-------------------------------------------------------------------------------------------------
bool_t
MySqlConnection::ping(
    int_t *out_errorCode    /* = xPTR_NULL */
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
/* static */
bool_t
MySqlConnection::isExists(
    cMySqlConnectionData &a_data
)
{
    bool_t bRv = false;

    MySqlConnection conn;

    {
        bRv = conn.get().isValid();
        xCHECK_RET(!bRv, false);

        bRv = conn.ping();
        xCHECK_RET(!bRv, false);

        conn.connect(a_data);
        conn.query(xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA "
            "WHERE SCHEMA_NAME = '%s'), 'true', 'false')"), a_data.db.c_str());
    }

    MySqlRecordset rec(conn, false);

    {
        bRv = rec.get().isValid();
        xTEST_EQ(bRv, true);
        xTEST_EQ(rec.rowsNum(), 1ULL);

        std::vec_tstring_t row;
        rec.fetchRow(&row);
        xTEST_EQ(row.size(), static_cast<size_t>(1));
        xCHECK_RET(StringCI::compare(xT("false"), row.at(0)), false);
        xTEST_EQ(StringCI::compare(xT("true"), row.at(0)), true);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::connect(
    cMySqlConnectionData &a_data
)
{
    xTEST_EQ(_conn.isValid(), true);
    xTEST_NA(a_data);

    _conn = ::mysql_real_connect(_conn.get(), xT2A(a_data.host).c_str(), xT2A(a_data.user).c_str(),
        xT2A(a_data.password).c_str(), xT2A(a_data.db).c_str(), a_data.port,
        xT2A(a_data.unixSocket).c_str(), a_data.clientFlag);

    xTEST_EQ_MSG(_conn.isValid(), true, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
MySqlConnection::quoted(
	std::ctstring_t &a_sql
) const
{
    unsigned long  n {};

    std::tstring_t from = a_sql;
    std::tstring_t to(from.size() * 2 + 1, '\0');

    // \'
	{
	    n = ::mysql_real_escape_string_quote(_conn.get(), &to[0], from.data(), static_cast<unsigned long>(from.size()), '\'');
		if (n < 0) {
			to.resize(0);
		} else {
			to.resize(n);
			fprintf(stdout, "['] %s\n", to.c_str());
		}
	}

    // \"
	{
	    from = to;
		to.resize(from.size() * 2 + 1, '\0');

		n = ::mysql_real_escape_string_quote(_conn.get(), &to[0], from.data(), static_cast<unsigned long>(from.size()), '"');
		if (n < 0) {
			to.resize(0);
		} else {
			to.resize(n);
			fprintf(stdout, "[\"] %s\n", to.c_str());
		}
	}

	// '\\'
	{
	    from = to;
		to.resize(from.size() * 2 + 1, '\0');

		n = ::mysql_real_escape_string_quote(_conn.get(), &to[0], from.data(), static_cast<unsigned long>(from.size()), '\\');
		if (n < 0) {
			to.resize(0);
		} else {
			to.resize(n);
			fprintf(stdout, "[\\] %s\n", to.c_str());
		}
	}

    return to;
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::query(
    cptr_ctchar_t a_sqlFormat, ...
) const
{
    xTEST_EQ(_conn.isValid(), true);
    xTEST_PTR(a_sqlFormat);

    std::tstring_t sqlQuery;
    va_list        args;

    xVA_START(args, a_sqlFormat);
    sqlQuery = FormatC::strV(a_sqlFormat, args);
    xVA_END(args);

    const std::string asSqlQuery = xT2A(sqlQuery);

    int_t iRv = ::mysql_real_query(_conn.get(), asSqlQuery.data(),
        static_cast<ulong_t>( asSqlQuery.size() ));
    xTEST_EQ_MSG(0, iRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
uint_t
MySqlConnection::fieldCount() const
{
    xTEST_EQ(_conn.isValid(), true);

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
    xTEST_EQ(_conn.isValid(), true);

    return ::mysql_errno( _conn.get() );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
MySqlConnection::lastErrorStr() const
{
    xTEST_EQ(_conn.isValid(), true);

    std::tstring_t sRv;

    cuint_t     _lastError = lastError();
    const char *error      = ::mysql_error( _conn.get() );
    xTEST_PTR(error);

    if (_lastError == 0U) {
        sRv = Format::str(xT("{} - \"{}\""), _lastError, xT("Success"));
    } else {
        sRv = Format::str(xT("{} - \"{}\""), _lastError, error);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, db)
