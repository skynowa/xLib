/**
 * \file   Test_MySql_Fabrica.cpp
 * \brief
 */


#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_MySql)
//-------------------------------------------------------------------------------------------------
class FabricaOptions :
	public mysql::Options
{
public:
	FabricaOptions() :
		mysql::Options(xT("mysql-api-master.office.fabrica.net.ua"), xT("triptake"), xT("inae4Ees"),
			xT("triptake"), 3306, {}, xT("utf8mb4"), true, {})
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
	if ( isGithubCI() ) {
		Cout() << "GithubCI - skip";
		return true;
	}

	using namespace mysql;

	FabricaOptions options;
	Db             db(options);
	Connection     conn(options);

	/*******************************************************************************
	*    Db
	*
	*******************************************************************************/

	xTEST_GROUP("Db");
	{
		xTEST_CASE("show")
		{
			std::vec_tstring_t dbNames;

			db.show(xT("%a%"), &dbNames);
			// Cout() << xSTD_TRACE_VAR(dbNames);
			xTEST(!dbNames.empty());

			db.show(xT("%XXXXXXXXXXx%"), &dbNames);
			// Cout() << xSTD_TRACE_VAR(dbNames);
			xTEST(dbNames.empty());

			db.show(&dbNames);
			// Cout() << xSTD_TRACE_VAR(dbNames);
			xTEST(!dbNames.empty());
		}

		xTEST_CASE("isExists")
		{
			m_bRv = db.isExists();
			xTEST(m_bRv);
		}

		xTEST_CASE("create")
		{
			if (options.isFabrica()) {
				Cout() << xT("n/a");
			} else {
				/// db.create();
				/// xTEST(db.isExists());
			}
		}

		xTEST_CASE("drop")
		{
			if (options.isFabrica()) {
				Cout() << xT("n/a");
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

	xTEST_GROUP("Connection");
	{
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
			m_bRv = conn.ping();
			xTEST(m_bRv);
		}
	}

   /*******************************************************************************
	*    Query
	*
	*******************************************************************************/

	xTEST_GROUP("Query");
	{
		std::ctstring_t tableName = xT("ARecErrors");

		xTEST_CASE("store")
		{
			std::ctstring_t sql = Format::str("SELECT count(*) FROM {}", tableName);

			StoreResult result = conn.query(sql).store();

			rows_t rows;
			result.fetchRows(&rows);
			xTEST_EQ(rows.size(), std::size_t(1));
			xTEST_EQ(std::stoull(rows[0].begin()->second), std::size_t(34));
		}

		xTEST_CASE("store")
		{
			std::ctstring_t sql = Format::str("SELECT * FROM {}", tableName);

			StoreResult result = conn.query(sql).store();

			rows_t rows;
			result.fetchRows(&rows);

			for (const auto &it_row : rows) {
				Cout() << xSTD_TRACE_VAR(it_row);
			}

		}
	}

	xTEST_CASE("EscapeQuoted")
	{
		const std::vector<data2_tstring_t> data
		{
			{xT(""),                 xT("''")},
			{xT("NULL"),             xT("NULL")},
			{xT("value"),            xT("'value'")},
			{xT("\"value\""),        xT("'\\\"value\\\"'")},
			{xT("'value'"),          xT("'\\\'value\\\''")},
			{xT("\\value\\"),        xT("'\\\\value\\\\'")},
			{xT(" value xxx"),       xT("' value xxx'")},
			{{xT("value\0\r\n"), 8}, {xT("'value\\0\\r\\n'"), 13}},
			{xT(" , |, ?, <, >, {, }, :, ~, @, !, (,), `, #, %,,,;, &, - and _"),
									 xT("' , |, ?, <, >, {, }, :, ~, @, !, (,), `, #, %,,,;, &, - and _'")}
		};

		for (const auto &[it_test, it_expect] : data) {
			EscapeQuoted escapeQuoted(conn, it_test);

			m_sRv = escapeQuoted.forSqm();
			xTEST_EQ(m_sRv, it_expect);
		}
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
