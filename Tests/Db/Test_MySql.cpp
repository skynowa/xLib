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
    std::ctstring_t csHost        = xT("127.0.0.1");
    std::ctstring_t csUser        = xT("root");
    std::ctstring_t csPassword    = xT("root");
    std::ctstring_t csDbName      = xT("db_test");
    cuint_t         cuiPort       = 0U;
    std::ctstring_t sTableName    = xT("t_main");
    std::ctstring_t csUnixSocket;
    culong_t        culClientFlag = 0UL;


    /*******************************************************************************
    *    MySQLConnection
    *
    *******************************************************************************/

    MySQLConnection conConn;


    //--------------------------------------------------
    //pmsGet
    {
        MYSQL *pmsRes = conConn.get();
        xTEST_PTR(pmsRes);
    }

    //--------------------------------------------------
    //bIsValid
    {
        m_bRv = conConn.isValid();
        xTEST_EQ(m_bRv, true);
    }

    //--------------------------------------------------
    //bOptions
    {
        mysql_option  moOption = MYSQL_OPT_COMPRESS;
        cvoid_t      *cpvArg   = xPTR_NULL;

        conConn.options(moOption, cpvArg);
    }

    xTEST_CASE("bIsExists")
    {
        std::ctstring_t casData[][2] = {
            { xT("000000"),     xT("false") },
            { xT("1111111"),    xT("false") },
            { xT("222222222"),  xT("false") },
            { xT("xxxxxxxxxx"), xT("false") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
            bool_t bRes1 = MySQLConnection::isExists(csHost, csUser, csPassword, casData[i][0], cuiPort, csUnixSocket, culClientFlag);
            bool_t bRes2 = String::castBool(casData[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    //--------------------------------------------------
    //bConnect
    {
        bool_t bIsDbExists = false;

        bIsDbExists = MySQLConnection::isExists(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);
        if (!bIsDbExists) {
            //create Db
            std::tstring_t csDbDefaultName = xT("");

            conConn.connect(csHost, csUser, csPassword, csDbDefaultName, cuiPort, csUnixSocket, culClientFlag);
            conConn.query(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"), csDbName.c_str());
        } else {
            //connect to Db
            conConn.connect(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);
        }

        m_bRv = MySQLConnection::isExists(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);
        xTEST_EQ(m_bRv, true);
    }

    //--------------------------------------------------
    //bQuery
    {
        conConn.connect(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);

        //create table
        conConn.query(
                        xT("CREATE TABLE IF NOT EXISTS ")
                        xT("   `%s` (")
                        xT("       `f_id`    int_t(11)     NOT NULL AUTO_INCREMENT,")
                        xT("       `f_name`  char(30)    NOT NULL,")
                        xT("       `f_age`   SMALLINT(6) NOT NULL")
                        xT("   )"),
                        sTableName.c_str());
        xTEST_EQ(m_bRv, true);

        //insert records
        conConn.query(
                        xT("INSERT INTO")
                        xT("    `%s` (`f_name`, `f_age`)")
                        xT("VALUES")
                        xT("    ('Katya', 12),")
                        xT("    ('Lena',  18),")
                        xT("    ('Misha', 16),")
                        xT("    ('Vasya', 24),")
                        xT("    ('Sasha', 20)"),
                        sTableName.c_str());

        //select all records
        #if 0
            conConn.query(xT("SELECT * FROM `t_main`"));
        #else
            conConn.query(xT("CHECK TABLE `t_main`"));
        #endif
    }

    //--------------------------------------------------
    //uiFieldCount
    {
        m_uiRv = conConn.fieldCount();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    //--------------------------------------------------
    // uiLastError
    {
        m_uiRv = conConn.lastError();
        xTEST_EQ(0U, m_uiRv);
    }

    //--------------------------------------------------
    // sLastErrorStr
    {
        m_sRv = conConn.lastErrorStr();
        xTEST_EQ(false, m_sRv.empty());
    }


    /*******************************************************************************
    *    MySQLRecordset
    *
    *******************************************************************************/

    MySQLRecordset recRec(conConn, false);

    //--------------------------------------------------
    //pmrGet
    {
        MYSQL_RES *pmrRes = recRec.get();
        xTEST_PTR(pmrRes);
    }

    //--------------------------------------------------
    //bIsValid
    {
        m_bRv = recRec.isValid();
        xTEST_EQ(m_bRv, true);
    }

    //--------------------------------------------------
    //uiFieldsNum
    {
        m_uiRv = recRec.fieldsNum();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    //--------------------------------------------------
    //ullRowsNum
    {
        my_ulonglong ullRv = recRec.rowsNum(); xUNUSED(ullRv);
        //xTRACE("ullRowsNum: %lli", ullRv);
        //TODO: xTEST_LESS(0ULL, ullRv);
    }

    //--------------------------------------------------
    //bFetchField
    {
        MYSQL_FIELD mfField;

        recRec.fetchField(&mfField);
    }

    //--------------------------------------------------
    //bFetchFieldDirect
    {
        uint_t      uiFieldNumber = 0;
        MYSQL_FIELD mfField;

        recRec.fetchFieldDirect(uiFieldNumber, &mfField);
    }

    //--------------------------------------------------
    //bFetchFields
    {
        MYSQL_FIELD mfField;

        recRec.fetchFields(&mfField);
    }

    //--------------------------------------------------
    // vFetchRow
    {
        // TEST: Mysql::fetchRow()

        //MYSQL_ROW mrRow;

        //recRec.vFetchRow(&mrRow);
    }

    //--------------------------------------------------
    // vFetchLengths
    {
        // TEST: Mysql::fetchLengths()

        //ulong_t *pulFieldLengths = xPTR_NULL;

        //recRec.vFetchLengths(&pulFieldLengths);
        //xTEST_PTR(pulFieldLengths);
    }


    //--------------------------------------------------
    //bFetchRow
    {
        std::vec_tstring_t vsRow;

        for (my_ulonglong i = 0; i < recRec.rowsNum(); ++ i) {
            recRec.fetchRow(&vsRow);

            //std::tcout << xT("Row ") << i << xT(": ") << vsRow << std::endl;
        }
    }

    //--------------------------------------------------
    //drop Db (cleaning)
    {
        conConn.query(xT("DROP TABLE IF EXISTS `%s`"), sTableName.c_str());
        conConn.query(xT("DROP DATABASE IF EXISTS `%s`"), csDbName.c_str());

        m_bRv = MySQLConnection::isExists(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);
        xTEST_EQ(m_bRv, false);
    }

    //--------------------------------------------------
    //bClose
    conConn.close();
#else
    Trace() << xT("[skip]");
#endif // xHAVE_MYSQL

    return true;
}
//-------------------------------------------------------------------------------------------------
