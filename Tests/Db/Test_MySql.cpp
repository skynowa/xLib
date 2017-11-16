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
    mysqlData.host       = xT("127.0.0.1");
    mysqlData.user       = xT("root");
    mysqlData.password   = xT("root");
    mysqlData.db         = xT("db_test");
    mysqlData.port       = 0U;
    mysqlData.unixSocket = xT("");
    mysqlData.clientFlag = 0UL;

    std::ctstring_t tableName  = xT("t_main");


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
        m_bRv = mysqlConn.isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySqlConnection::options")
    {
        mysql_option option = MYSQL_OPT_COMPRESS;
        cptr_cvoid_t arg    = xPTR_NULL;

        mysqlConn.options(option, arg);
    }

    xTEST_CASE("MySqlConnection::ping")
    {
        int_t errorCode;
        m_bRv = mysqlConn.ping(&errorCode);
        xTEST_EQ(m_bRv, false);
        xTEST_DIFF(errorCode, 0);
    }

    xTEST_CASE("MySqlConnection::isExists")
    {
        std::ctstring_t data[][2] = {
            { xT("000000"),     xT("false") },
            { xT("1111111"),    xT("false") },
            { xT("222222222"),  xT("false") },
            { xT("xxxxxxxxxx"), xT("false") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            bool_t bRes1 = MySqlConnection::isExists(mysqlData);
            bool_t bRes2 = String::castBool(data[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    xTEST_CASE("MySqlConnection::connect")
    {
        cbool_t isDbExists = MySqlConnection::isExists(mysqlData);
        if ( !isDbExists ) {
            MySqlConnectionData mysqlDataDefault;
            mysqlDataDefault.host       = mysqlData.host;
            mysqlDataDefault.user       = mysqlData.user;
            mysqlDataDefault.password   = mysqlData.password;
            mysqlDataDefault.db         = xT("");  // create Db
            mysqlDataDefault.port       = mysqlData.port;
            mysqlDataDefault.unixSocket = mysqlData.unixSocket;
            mysqlDataDefault.clientFlag = mysqlData.clientFlag;

            mysqlConn.connect(mysqlDataDefault);
            mysqlConn.query(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"),
                mysqlData.db.c_str());
        } else {
            // connect to Db
            mysqlConn.connect(mysqlData);
        }

        m_bRv = MySqlConnection::isExists(mysqlData);
        xTEST_EQ(m_bRv, true);
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
        m_bRv = mysqlRecord.isValid();
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
        my_ulonglong ullRv = mysqlRecord.rowsNum(); xUNUSED(ullRv);
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

        //ulong_t *pulFieldLengths = xPTR_NULL;

        //mysqlRecord.vFetchLengths(&pulFieldLengths);
        //xTEST_PTR(pulFieldLengths);
    }

    xTEST_CASE("MySqlRecordset::fetchRow")
    {
        std::vec_tstring_t row;

        for (my_ulonglong i = 0; i < mysqlRecord.rowsNum(); ++ i) {
            mysqlRecord.fetchRow(&row);

            //std::tcout << xT("Row ") << i << xT(": ") << row << std::endl;
        }
    }

    // drop DB, cleaning
    {
        mysqlConn.query(xT("DROP TABLE IF EXISTS `%s`"),    tableName.c_str());
        mysqlConn.query(xT("DROP DATABASE IF EXISTS `%s`"), mysqlData.db.c_str());

        m_bRv = MySqlConnection::isExists(mysqlData);
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
