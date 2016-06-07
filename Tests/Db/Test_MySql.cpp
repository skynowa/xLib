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

    MySQLConnection conConn;

    xTEST_CASE("MySQLConnection::get")
    {
        MYSQL *pmsRes = conConn.get();
        xTEST_PTR(pmsRes);
    }

    xTEST_CASE("MySQLConnection::isValid")
    {
        m_bRv = conConn.isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySQLConnection::options")
    {
        mysql_option  moOption = MYSQL_OPT_COMPRESS;
        cvoid_t      *cpvArg   = xPTR_NULL;

        conConn.options(moOption, cpvArg);
    }

    xTEST_CASE("MySQLConnection::isExists")
    {
        std::ctstring_t casData[][2] = {
            { xT("000000"),     xT("false") },
            { xT("1111111"),    xT("false") },
            { xT("222222222"),  xT("false") },
            { xT("xxxxxxxxxx"), xT("false") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
            bool_t bRes1 = MySQLConnection::isExists(host, user, password, casData[i][0], port, unixSocket, clientFlag);
            bool_t bRes2 = String::castBool(casData[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    xTEST_CASE("MySQLConnection::connect")
    {
        bool_t bIsDbExists = false;

        bIsDbExists = MySQLConnection::isExists(host, user, password, dbName, port, unixSocket, clientFlag);
        if (!bIsDbExists) {
            //create Db
            std::tstring_t csDbDefaultName = xT("");

            conConn.connect(host, user, password, csDbDefaultName, port, unixSocket, clientFlag);
            conConn.query(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"), dbName.c_str());
        } else {
            //connect to Db
            conConn.connect(host, user, password, dbName, port, unixSocket, clientFlag);
        }

        m_bRv = MySQLConnection::isExists(host, user, password, dbName, port, unixSocket, clientFlag);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySQLConnection::query")
    {
        conConn.connect(host, user, password, dbName, port, unixSocket, clientFlag);

        // create table
        conConn.query(
                        xT("CREATE TABLE IF NOT EXISTS ")
                        xT("   `%s` (")
                        xT("       `f_id`    int_t(11)   NOT NULL AUTO_INCREMENT,")
                        xT("       `f_name`  char(30)    NOT NULL,")
                        xT("       `f_age`   SMALLINT(6) NOT NULL")
                        xT("   )"),
                        tableName.c_str());
        xTEST_EQ(m_bRv, true);

        // insert records
        conConn.query(
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
            conConn.query(xT("SELECT * FROM `t_main`"));
        #else
            conConn.query(xT("CHECK TABLE `t_main`"));
        #endif
    }

    xTEST_CASE("MySQLConnection::fieldCount")
    {
        m_uiRv = conConn.fieldCount();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    xTEST_CASE("MySQLConnection::lastError")
    {
        m_uiRv = conConn.lastError();
        xTEST_EQ(0U, m_uiRv);
    }

    xTEST_CASE("MySQLConnection::lastErrorStr")
    {
        m_sRv = conConn.lastErrorStr();
        xTEST_EQ(false, m_sRv.empty());
    }


    /*******************************************************************************
    *    MySQLRecordset
    *
    *******************************************************************************/

    MySQLRecordset recRec(conConn, false);

    xTEST_CASE("MySQLRecordset::get")
    {
        MYSQL_RES *pmrRes = recRec.get();
        xTEST_PTR(pmrRes);
    }

    xTEST_CASE("MySQLRecordset::isValid")
    {
        m_bRv = recRec.isValid();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("MySQLRecordset::fieldsNum")
    {
        m_uiRv = recRec.fieldsNum();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    xTEST_CASE("MySQLRecordset::rowsNum")
    {
        my_ulonglong ullRv = recRec.rowsNum(); xUNUSED(ullRv);
        //xTRACE("ullRowsNum: %lli", ullRv);
        //TODO: xTEST_LESS(0ULL, ullRv);
    }

    xTEST_CASE("MySQLRecordset::fetchField")
    {
        MYSQL_FIELD mfField;

        recRec.fetchField(&mfField);
    }

    xTEST_CASE("MySQLRecordset::fetchFieldDirect")
    {
        uint_t      uiFieldNumber = 0;
        MYSQL_FIELD mfField;

        recRec.fetchFieldDirect(uiFieldNumber, &mfField);
    }

    //bFetchFields
    xTEST_CASE("MySQLRecordset::fetchFields")
    {
        MYSQL_FIELD mfField;

        recRec.fetchFields(&mfField);
    }

    xTEST_CASE("MySQLRecordset::fetchRow")
    {
        // TEST: Mysql::fetchRow()

        //MYSQL_ROW mrRow;

        //recRec.vFetchRow(&mrRow);
    }

    xTEST_CASE("MySQLRecordset::fetchLengths")
    {
        // TEST: Mysql::fetchLengths()

        //ulong_t *pulFieldLengths = xPTR_NULL;

        //recRec.vFetchLengths(&pulFieldLengths);
        //xTEST_PTR(pulFieldLengths);
    }

    xTEST_CASE("MySQLRecordset::fetchRow")
    {
        std::vec_tstring_t vsRow;

        for (my_ulonglong i = 0; i < recRec.rowsNum(); ++ i) {
            recRec.fetchRow(&vsRow);

            //std::tcout << xT("Row ") << i << xT(": ") << vsRow << std::endl;
        }
    }

    // drop DB, cleaning
    {
        conConn.query(xT("DROP TABLE IF EXISTS `%s`"), tableName.c_str());
        conConn.query(xT("DROP DATABASE IF EXISTS `%s`"), dbName.c_str());

        m_bRv = MySQLConnection::isExists(host, user, password, dbName, port, unixSocket, clientFlag);
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("MySQLRecordset::close")
    {
        conConn.close();
    }
#else
    Trace() << xT("[skip]");
#endif // xHAVE_MYSQL

    return true;
}
//-------------------------------------------------------------------------------------------------
