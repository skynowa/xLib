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
class FabricaOptions :
	public mysql::Options
{
public:
	FabricaOptions() :
		mysql::Options(xT("mysql-api-master.office.fabrica.net.ua"), xT("triptake"), xT("inae4Ees"),
			xT("triptake"), 3306, {}, xT("utf8mb4"), true, true, {})
	{
	}
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_MySql::unit()
{
	using namespace mysql;

#if cmMYSQL_FOUND
	FabricaOptions options;

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
