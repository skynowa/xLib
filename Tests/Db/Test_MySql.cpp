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
	std::map<mysql_option, cptr_cvoid_t> mysqlOptions;
	{
		const unsigned int connectTimeout {60};
		const bool         isReconnect    {true};
		const char         initCommand[]  {"SET autocommit=1"};

		mysqlOptions =
		{
			{MYSQL_OPT_COMPRESS,        0 /* not used */},
			{MYSQL_OPT_CONNECT_TIMEOUT, &connectTimeout},
			{MYSQL_OPT_RECONNECT,       &isReconnect},
			{MYSQL_INIT_COMMAND,        &initCommand}
		};
	}

	cOptions options
	{
		.host         = xT("mysql-api-master.office.fabrica.net.ua"),
		.user         = xT("triptake"),
		.password     = xT("inae4Ees"),
		.db           = xT("triptake"),
		.port         = 3306,
		.unixSocket   = xT(""),
		.charset      = xT("utf8"),
		.isAutoCommit = true,
		.isCompress   = true,
		.options      = mysqlOptions
	};

    std::ctstring_t tableName = xT("ARecErrors");

    /*******************************************************************************
    *    Connection
    *
    *******************************************************************************/

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
    	Cout() << db.isExists();
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

#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
