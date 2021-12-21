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

	bool_t isFabrica() const
	{
		return true;
	}
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_MySql::unit()
{
	using namespace mysql;

#if cmMYSQL_FOUND
    std::ctstring_t tableName = xT("ARecErrors");

	FabricaOptions options;
	Db             db(options);
	Connection     conn(options);

	/*******************************************************************************
	*    Db
	*
	*******************************************************************************/

	{
		xTEST_GROUP("Db");

		xTEST_CASE("isExists")
		{
			m_bRv = db.isExists();
			xTEST(m_bRv);
		}

		xTEST_CASE("create")
		{
			if (options.isFabrica()) {
				// n/a
			} else {
				/// db.create();
				/// xTEST(db.isExists());
			}
		}

		xTEST_CASE("drop")
		{
			if (options.isFabrica()) {
				// n/a
			} else {
				/// db.drop();
				/// xTEST(!db.isExists());
			}
		}
	}

	/*******************************************************************************
	*    Connection
	*
	*******************************************************************************/

	{
		xTEST_GROUP("Connection");

		xTEST_CASE("get")
		{
			cHandleMySqlConn &handle = conn.get();
			xTEST(handle.isValid());
		}

		xTEST_CASE("isValid")
		{
			m_bRv = conn.get().isValid();
			xTEST(m_bRv);
		}

		xTEST_CASE("connect")
		{
			conn.connect();
			xTEST(db.isExists());
		}

		xTEST_CASE("reconnect")
		{
			conn.reconnect();
		}

		xTEST_CASE("ping")
		{
			int_t errorCode {};
			m_bRv = conn.ping(&errorCode);
			xTEST(m_bRv);
			xTEST_EQ(errorCode, 0);
		}
	}

    /*******************************************************************************
    *    Query
    *
    *******************************************************************************/

	{
		xTEST_GROUP("Query");

		xTEST_CASE("exec")
		{
			Query query(conn);
			query.exec( Format::str("SELECT count(*) FROM {}", tableName) );

			StoreResult result(conn);
			xTEST(result.get().isValid());

			rows_t rows;
			result.fetchRows(&rows);
			xTEST_EQ(rows.size(), std::size_t(1));
			xTEST_EQ(std::stoull(rows[0][0]), std::size_t(34));
		}
	}
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
