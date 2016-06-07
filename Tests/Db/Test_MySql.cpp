/**
 * \file   Test_MySql.cpp
 * \brief
 */


#include "Test_MySql.h"


#include <xLib/Core/String.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_MySql)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_MySql::unit()
{
#if xHAVE_MYSQL
    std::ctstring_t host       = xT("127.0.0.1");
    std::ctstring_t user       = xT("root");
    std::ctstring_t password   = xT("root");
    std::ctstring_t dbName     = xT("db_test");
    cuint_t         port       = 0U;
    std::ctstring_t tableName  = xT("t_main");
    std::ctstring_t unixSocket;
    culong_t        clientFlag = 0UL;


    /*******************************************************************************
    *    MySQLConnection
    *
    *******************************************************************************/

    MySQLConnection mysqlConn;

    xTEST_CASE("MySQLConnection::get")
    {
        MYSQL *handle = mysqlConn.get();
        xTEST_PTR(handle);
    }

    xTEST_CASE("MySQLConnection::isValid")
    {
        m_bRv = mysqlConn.isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySQLConnection::options")
    {
        mysql_option  option = MYSQL_OPT_COMPRESS;
        cvoid_t      *arg    = xPTR_NULL;

        mysqlConn.options(option, arg);
    }

    xTEST_CASE("MySQLConnection::isExists")
    {
        std::ctstring_t data[][2] = {
            { xT("000000"),     xT("false") },
            { xT("1111111"),    xT("false") },
            { xT("222222222"),  xT("false") },
            { xT("xxxxxxxxxx"), xT("false") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            bool_t bRes1 = MySQLConnection::isExists(host, user, password, data[i][0], port, unixSocket, clientFlag);
            bool_t bRes2 = String::castBool(data[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    xTEST_CASE("MySQLConnection::connect")
    {
        bool_t isDbExists = false;

        isDbExists = MySQLConnection::isExists(host, user, password, dbName, port, unixSocket, clientFlag);
        if (!isDbExists) {
            // create Db
            std::tstring_t dbNameDefault = xT("");

            mysqlConn.connect(host, user, password, dbNameDefault, port, unixSocket, clientFlag);
            mysqlConn.query(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"), dbName.c_str());
        } else {
            // connect to Db
            mysqlConn.connect(host, user, password, dbName, port, unixSocket, clientFlag);
        }

        m_bRv = MySQLConnection::isExists(host, user, password, dbName, port, unixSocket, clientFlag);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySQLConnection::query")
    {
        mysqlConn.connect(host, user, password, dbName, port, unixSocket, clientFlag);

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

    xTEST_CASE("MySQLConnection::fieldCount")
    {
        m_uiRv = mysqlConn.fieldCount();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    xTEST_CASE("MySQLConnection::lastError")
    {
        m_uiRv = mysqlConn.lastError();
        xTEST_EQ(0U, m_uiRv);
    }

    xTEST_CASE("MySQLConnection::lastErrorStr")
    {
        m_sRv = mysqlConn.lastErrorStr();
        xTEST_EQ(false, m_sRv.empty());
    }


    /*******************************************************************************
    *    MySQLRecordset
    *
    *******************************************************************************/

    MySQLRecordset mysqlRecord(mysqlConn, false);

    xTEST_CASE("MySQLRecordset::get")
    {
        MYSQL_RES *handle = mysqlRecord.get();
        xTEST_PTR(handle);
    }

    xTEST_CASE("MySQLRecordset::isValid")
    {
        m_bRv = mysqlRecord.isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySQLRecordset::fieldsNum")
    {
        m_uiRv = mysqlRecord.fieldsNum();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    xTEST_CASE("MySQLRecordset::rowsNum")
    {
        my_ulonglong ullRv = mysqlRecord.rowsNum(); xUNUSED(ullRv);
        //xTRACE("ullRowsNum: %lli", ullRv);
        //TODO: xTEST_LESS(0ULL, ullRv);
    }

    xTEST_CASE("MySQLRecordset::fetchField")
    {
        MYSQL_FIELD field;

        mysqlRecord.fetchField(&field);
    }

    xTEST_CASE("MySQLRecordset::fetchFieldDirect")
    {
        uint_t      fieldNumber = 0;
        MYSQL_FIELD field;

        mysqlRecord.fetchFieldDirect(fieldNumber, &field);
    }

    //bFetchFields
    xTEST_CASE("MySQLRecordset::fetchFields")
    {
        MYSQL_FIELD field;

        mysqlRecord.fetchFields(&field);
    }

    xTEST_CASE("MySQLRecordset::fetchRow")
    {
        // TEST: Mysql::fetchRow()

        //MYSQL_ROW mrRow;

        //mysqlRecord.vFetchRow(&mrRow);
    }

    xTEST_CASE("MySQLRecordset::fetchLengths")
    {
        // TEST: Mysql::fetchLengths()

        //ulong_t *pulFieldLengths = xPTR_NULL;

        //mysqlRecord.vFetchLengths(&pulFieldLengths);
        //xTEST_PTR(pulFieldLengths);
    }

    xTEST_CASE("MySQLRecordset::fetchRow")
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
        mysqlConn.query(xT("DROP DATABASE IF EXISTS `%s`"), dbName.c_str());

        m_bRv = MySQLConnection::isExists(host, user, password, dbName, port, unixSocket, clientFlag);
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("MySQLRecordset::close")
    {
        mysqlConn.close();
    }
#else
    Trace() << xT("[skip]");
#endif // xHAVE_MYSQL

    return true;
}
//-------------------------------------------------------------------------------------------------
