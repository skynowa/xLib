/**
 * \file   Test_MySql.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_MySql)
xTEST_UNIT(Test_MySql)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_MySql::unit()
{
#if cmMYSQL_FOUND
    MySqlConnectionData mysqlData;
    mysqlData.host         = xT("127.0.0.1");	// xT("localhost");
    mysqlData.user         = xT("root");
    mysqlData.password     = xT("root");
    mysqlData.db           = xT("db_test");
    mysqlData.port         = 3306;	// 0;
    mysqlData.unixSocket   = xT("");
    mysqlData.charset      = xT("utf8");
    mysqlData.isAutoCommit = true;
    mysqlData.isCompress   = true;

	std::map<mysql_option, cptr_cvoid_t> options;
	{
		const unsigned int connectTimeout {60};
		const bool         isReconnect    {true};
		const char         initCommand[]  {"SET autocommit=1"};

		options =
		{
			{MYSQL_OPT_COMPRESS,        0 /* not used */},
			{MYSQL_OPT_CONNECT_TIMEOUT, &connectTimeout},
			{MYSQL_OPT_RECONNECT,       &isReconnect},
			{MYSQL_INIT_COMMAND,        &initCommand}
		};
	}

	mysqlData.options = options;

    std::ctstring_t tableName = xT("t_main");


    /*******************************************************************************
    *    MySqlConnection
    *
    *******************************************************************************/

    MySqlConnection mysqlConn;

    xTEST_CASE("MySqlConnection::get")
    {
        HandleMySqlConn &handle = mysqlConn.get();
        xTEST_EQ(handle.isValid(), true);
    }

    xTEST_CASE("MySqlConnection::isValid")
    {
        m_bRv = mysqlConn.get().isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySqlConnection::isDbExists,dbCreate,dbDrop")
    {
		cbool_t isExists = MySqlConnection::isDbExists(mysqlData);
		if (isExists) {
			MySqlConnection::dbDrop(mysqlData);
			MySqlConnection::dbCreate(mysqlData);
		} else {
			MySqlConnection::dbCreate(mysqlData);
		}
    }

    xTEST_CASE("MySqlConnection::escapeString")
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
			m_sRv = mysqlConn.escapeString(it_data.test);
			xTEST_EQ(m_sRv, it_data.expect);

			std::cout << xTRACE_VAR(m_sRv) << std::endl;
		}
    }

    xTEST_CASE("MySqlConnection::connect")
    {
        cbool_t isDbExists = MySqlConnection::isDbExists(mysqlData);
        if ( !isDbExists ) {
            MySqlConnectionData mysqlDataDefault;
            mysqlDataDefault.host         = mysqlData.host;
            mysqlDataDefault.user         = mysqlData.user;
            mysqlDataDefault.password     = mysqlData.password;
            mysqlDataDefault.db           = {};  // create Db
            mysqlDataDefault.port         = mysqlData.port;
            mysqlDataDefault.unixSocket   = mysqlData.unixSocket;
            mysqlDataDefault.charset      = mysqlData.charset;
            mysqlDataDefault.isAutoCommit = mysqlData.isAutoCommit;
            mysqlDataDefault.isCompress   = mysqlData.isCompress;
            mysqlDataDefault.options      = mysqlData.options;

            mysqlConn.connect(mysqlDataDefault);
            mysqlConn.query(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"),
                mysqlData.db.c_str());
        } else {
            // connect to Db
            mysqlConn.connect(mysqlData);
        }

        m_bRv = MySqlConnection::isDbExists(mysqlData);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySqlConnection::reconnect")
    {
        mysqlConn.reconnect();
    }

    xTEST_CASE("MySqlConnection::ping")
    {
        int_t errorCode;
        m_bRv = mysqlConn.ping(&errorCode);
        xTEST_EQ(m_bRv, false);
        xTEST_DIFF(errorCode, 0);
    }

    xTEST_CASE("MySqlConnection::query")
    {
        mysqlConn.connect(mysqlData);

        // create table
        mysqlConn.query(
            xT("CREATE TABLE IF NOT EXISTS ")
            xT("   `%s` (")
            xT("       `f_id`    int_t(11)   NOT NULL AUTO_INCREMENT,")
            xT("       `f_name`  char(30)    NOT NULL,")
            xT("       `f_age`   SMALLINT(6) NOT NULL")
            xT("   )"),
            tableName.c_str());
        xTEST_EQ(m_bRv, true);

        // insert records
        mysqlConn.query(
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
        mysqlConn.query(xT("SELECT * FROM `t_main`"));
    #else
        mysqlConn.query(xT("CHECK TABLE `t_main`"));
    #endif
    }

    xTEST_CASE("MySqlConnection::fieldCount")
    {
        m_uiRv = mysqlConn.fieldCount();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    xTEST_CASE("MySqlConnection::lastError")
    {
        m_uiRv = mysqlConn.lastError();
        xTEST_EQ(0U, m_uiRv);
    }

    xTEST_CASE("MySqlConnection::lastErrorStr")
    {
        m_sRv = mysqlConn.lastErrorStr();
        xTEST_EQ(false, m_sRv.empty());
    }


    /*******************************************************************************
    *    MySqlRecordset
    *
    *******************************************************************************/

    MySqlRecordset mysqlRecord(mysqlConn, false);

    xTEST_CASE("MySqlRecordset::get")
    {
        HandleMySqlResult &handle = mysqlRecord.get();
        xTEST_EQ(handle.isValid(), true);
    }

    xTEST_CASE("MySqlRecordset::isValid")
    {
        m_bRv = mysqlRecord.get().isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySqlRecordset::fieldsNum")
    {
        m_uiRv = mysqlRecord.fieldsNum();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    xTEST_CASE("MySqlRecordset::rowsNum")
    {
    	std::size_t ullRv = mysqlRecord.rowsNum(); xUNUSED(ullRv);
        //xTRACE("ullRowsNum: %lli", ullRv);
        //TODO: xTEST_LESS(0ULL, ullRv);
    }

    xTEST_CASE("MySqlRecordset::fetchField")
    {
        MYSQL_FIELD field;

        mysqlRecord.fetchField(&field);
    }

    xTEST_CASE("MySqlRecordset::fetchFieldDirect")
    {
        uint_t      fieldNumber = 0;
        MYSQL_FIELD field;

        mysqlRecord.fetchFieldDirect(fieldNumber, &field);
    }

    //bFetchFields
    xTEST_CASE("MySqlRecordset::fetchFields")
    {
        MYSQL_FIELD field;

        mysqlRecord.fetchFields(&field);
    }

    xTEST_CASE("MySqlRecordset::fetchRow")
    {
        // TEST: Mysql::fetchRow()

        //MYSQL_ROW mrRow;

        //mysqlRecord.vFetchRow(&mrRow);
    }

    xTEST_CASE("MySqlRecordset::fetchLengths")
    {
        // TEST: Mysql::fetchLengths()

        //ulong_t *pulFieldLengths = nullptr;

        //mysqlRecord.vFetchLengths(&pulFieldLengths);
        //xTEST_PTR(pulFieldLengths);
    }

    xTEST_CASE("MySqlRecordset::fetchRow")
    {
        std::vec_tstring_t row;

        for (std::size_t i = 0; i < mysqlRecord.rowsNum(); ++ i) {
            mysqlRecord.fetchRow(&row);

            //std::tcout << xT("Row ") << i << xT(": ") << row << std::endl;
        }
    }

    // drop DB, cleaning
    {
        mysqlConn.query(xT("DROP TABLE IF EXISTS `%s`"),    tableName.c_str());
        mysqlConn.query(xT("DROP DATABASE IF EXISTS `%s`"), mysqlData.db.c_str());

        m_bRv = MySqlConnection::isDbExists(mysqlData);
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("MySqlRecordset::close")
    {
        mysqlConn.close();
    }
#else
    Trace() << xT("[skip]");
#endif // cmMYSQL_FOUND

    return true;
}
//-------------------------------------------------------------------------------------------------
