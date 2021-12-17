/**
 * \file   Test_MySql.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_MySql)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_MySql::unit()
{
	using namespace mysql;

	{
		// TODO: Test_MySql - setup environment for tests (Mocks)
		xTRACE_NOT_IMPLEMENTED

		return true;
	}

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
		.host         = xT("127.0.0.1"),	// xT("localhost");
		.user         = xT("root"),
		.password     = xT("root"),
		.db           = xT("db_test"),
		.port         = 3306,	// 0
		.unixSocket   = xT(""),
		.charset      = xT("utf8"),
		.isAutoCommit = true,
		.isCompress   = true,
		.options      = mysqlOptions
	};

    std::ctstring_t tableName = xT("Main");

    /*******************************************************************************
    *    Connection
    *
    *******************************************************************************/

    Db         db(options);
    Connection mysqlConn(options);

    xTEST_CASE("Connection::get")
    {
        cHandleMySqlConn &handle = mysqlConn.get();
        xTEST(handle.isValid());
    }

    xTEST_CASE("Connection::isValid")
    {
        m_bRv = mysqlConn.get().isValid();
        xTEST(m_bRv);
    }

    xTEST_CASE("Database::isExists,create,drop")
    {
		if ( db.isExists() ) {
			db.drop();
		}

		db.create();
    }

    xTEST_CASE("Query::escape")
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

		for (const auto &it_data : data) {
			Query query(mysqlConn);

			m_sRv = query.escape(it_data.test);
			xTEST_EQ(m_sRv, it_data.expect);

			std::cout << xTRACE_VAR(m_sRv) << std::endl;
		}
    }

	cOptions optionsDefault
    {
        .host         = options.host,
        .user         = options.user,
        .password     = options.password,
        .db           = {},  // create Db
        .port         = options.port,
        .unixSocket   = options.unixSocket,
        .charset      = options.charset,
        .isAutoCommit = options.isAutoCommit,
        .isCompress   = options.isCompress,
        .options      = options.options
	};

    Connection mysqlConn2(options);

    xTEST_CASE("Connection::connect")
    {
        if ( !db.isExists() ) {
            mysqlConn2.connect();

            Query query(mysqlConn2);
            query.exec(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"),
                options.db.c_str());
        } else {
            // connect to Db
            mysqlConn2.connect();
        }

        m_bRv = db.isExists();
        xTEST(m_bRv);
    }

    xTEST_CASE("Connection::reconnect")
    {
        mysqlConn2.reconnect();
    }

    xTEST_CASE("Connection::ping")
    {
        int_t errorCode {};
        m_bRv = mysqlConn2.ping(&errorCode);
        xTEST(!m_bRv);
        xTEST_DIFF(errorCode, 0);
    }

    xTEST_CASE("Query::exec")
    {
        mysqlConn2.connect();

        // create table
        Query query(mysqlConn2);
        query.exec(
            xT("CREATE TABLE IF NOT EXISTS ")
            xT("   `%s` (")
            xT("       `f_id`    int_t(11)   NOT NULL AUTO_INCREMENT,")
            xT("       `f_name`  char(30)    NOT NULL,")
            xT("       `f_age`   SMALLINT(6) NOT NULL")
            xT("   )"),
            tableName.c_str());
        xTEST(m_bRv);

        // insert records
        query.exec(
            xT("INSERT INTO")
            xT("    `%s` (`f_name`, `f_age`)")
            xT("VALUES")
            xT("    ('Katya', 12),")
            xT("    ('Lena',  18),")
            xT("    ('Misha', 16),")
            xT("    ('Vasya', 24),")
            xT("    ('Sasha', 20)"),
            tableName.c_str());

        // select all records
    #if 0
        query.exec(xT("SELECT * FROM %s"), tableName.c_str());
    #else
        query.exec(xT("CHECK TABLE %s"), tableName.c_str());
    #endif
    }

    /*******************************************************************************
    *    Recordset
    *
    *******************************************************************************/

    Recordset mysqlRecord(mysqlConn2, false);

    xTEST_CASE("Recordset::get")
    {
        HandleMySqlResult &handle = mysqlRecord.get();
        xTEST(handle.isValid());
    }

    xTEST_CASE("Recordset::isValid")
    {
        m_bRv = mysqlRecord.get().isValid();
        xTEST(m_bRv);
    }

    xTEST_CASE("Recordset::fields")
    {
        m_uiRv = mysqlRecord.fields();
        xTEST_EQ(m_uiRv, 3U);
    }

    xTEST_CASE("Recordset::fieldCount")
    {
        m_uiRv = mysqlRecord.fieldCount();
        xTEST_EQ(m_uiRv, 3U);
    }

    xTEST_CASE("Recordset::rows")
    {
    	std::size_t ullRv = mysqlRecord.rows();
        xTEST_DIFF(ullRv, 0ULL);
    }

    xTEST_CASE("Recordset::fetchField")
    {
        MYSQL_FIELD field;

        mysqlRecord.fetchField(&field);
    }

    xTEST_CASE("Recordset::fetchFieldDirect")
    {
        uint_t      fieldNumber {};
        MYSQL_FIELD field;

        mysqlRecord.fetchFieldDirect(fieldNumber, &field);
    }

    xTEST_CASE("Recordset::fetchFields")
    {
        MYSQL_FIELD field;

        mysqlRecord.fetchFields(&field);
    }

    xTEST_CASE("Recordset::fetchRow")
    {
        // TEST: Mysql::fetchRow()

        //MYSQL_ROW row;

        //mysqlRecord.fetchRow(&row);
    }

    xTEST_CASE("Recordset::fetchLengths")
    {
        // TEST: Mysql::fetchLengths()

        //ulong_t *fieldLengths {};

        //mysqlRecord.fetchLengths(&fieldLengths);
        //xTEST_PTR(fieldLengths);
    }

    xTEST_CASE("Recordset::fetchRow")
    {
        for (std::size_t i = 0; i < mysqlRecord.rows(); ++ i) {
        	std::vec_tstring_t row;
            mysqlRecord.fetchRow(&row);

            // Cout() << xTRACE_VAR(row);
        }
    }

    // drop DB, cleaning
    {
        Query query(mysqlConn2);

        query.exec(xT("DROP TABLE IF EXISTS `%s`"),    tableName.c_str());
        query.exec(xT("DROP DATABASE IF EXISTS `%s`"), options.db.c_str());

        m_bRv = db.isExists();
        xTEST(!m_bRv);
    }

    xTEST_CASE("Recordset::close")
    {
        mysqlConn2.close();
    }
#else
    Trace() << xT("[skip]");
#endif // cmMYSQL_FOUND

    return true;
}
//-------------------------------------------------------------------------------------------------
