/**
 * \file   Test_MySql_Fabrica.cpp
 * \brief
 */


#include <xLib/xLib.h>

#include <xLib/Db/MySql/StoreResult.h>
#include <xLib/Db/MySql/UseResult.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_MySql)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_MySql::unit()
{
	using namespace mysql;

#if cmMYSQL_FOUND
	Options options;
	options.host         = xT("mysql-api-master.office.fabrica.net.ua");
	options.user         = xT("triptake");
	options.password     = xT("inae4Ees");
	options.db           = xT("triptake");
	options.port         = 3306;
	options.unixSocket   = xT("");
	options.charset      = xT("utf8mb4");
	options.isAutoCommit = true;
	options.isCompress   = true;

	const unsigned int connectTimeout {60};
	const bool         isReconnect    {true};
	const char         initCommand[]  {"SET autocommit=1"};

	options.options =
		{
			{MYSQL_OPT_COMPRESS,        0 /* not used */},
			{MYSQL_OPT_CONNECT_TIMEOUT, &connectTimeout},
			{MYSQL_OPT_RECONNECT,       &isReconnect},
			{MYSQL_INIT_COMMAND,        &initCommand}
		};

    std::ctstring_t tableName = xT("ARecErrors");

    /*******************************************************************************
    *    Connection
    *
    *******************************************************************************/

	if (1) {
		Connection conn(options);
		conn.connect();

		Query query(conn);
		query.exec( Format::str("SELECT count(*) FROM {}", tableName) );

		StoreResult result(conn);

		m_bRv = result.get().isValid();
		xTEST(m_bRv);

		rows_t rows;
		result.fetchRows(&rows);
		xTEST_EQ(rows.size(), std::size_t(1));

		Cout() << xTRACE_VAR(rows);
	}

    /*******************************************************************************
    *    Connection
    *
    *******************************************************************************/

	if (1) {
		Db         db(options);
		Connection conn(options);

		xTEST_CASE("Connection::get")
		{
			cHandleMySqlConn &handle = conn.get();
			xTEST(handle.isValid());
		}

		xTEST_CASE("Connection::isValid")
		{
			m_bRv = conn.get().isValid();
			xTEST(m_bRv);
		}

		xTEST_CASE("Database::isExists")
		{
			m_bRv = db.isExists();
			xTEST(m_bRv);
		}

		xTEST_CASE("Connection::connect")
		{
			conn.connect();

			m_bRv = db.isExists();
			xTEST(m_bRv);
		}

		xTEST_CASE("Connection::reconnect")
		{
			conn.reconnect();
		}

		xTEST_CASE("Connection::ping")
		{
			int_t errorCode {};
			m_bRv = conn.ping(&errorCode);
			xTEST(!m_bRv);
			xTEST_DIFF(errorCode, 0);
		}
	}

#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
