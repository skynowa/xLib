/**
 * \file   CxTest_CxMySql.cpp
 * \brief
 */


#include <Test/Db/CxTest_CxMySql.h>


//---------------------------------------------------------------------------
CxTest_CxMySql::CxTest_CxMySql() {

}
//---------------------------------------------------------------------------
CxTest_CxMySql::~CxTest_CxMySql() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxMySql::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const std::tstring_t csHost        = xT("127.0.0.1");
    const std::tstring_t csUser        = xT("root");
    const std::tstring_t csPassword    = xT("root");
    const std::tstring_t csDbName      = xT("db_test");
    const uint_t         uiPort        = 0U;
    const std::tstring_t sTableName    = xT("t_main");
    const std::tstring_t csUnixSocket;
    const ulong_t        culClientFlag = 0UL;


    /****************************************************************************
    *    CxMySQLConnection
    *
    *****************************************************************************/

    CxMySQLConnection conConn;


    //--------------------------------------------------
    //pmsGet
    {
        MYSQL *pmsRes = conConn.pmsGet();
        xTEST_PTR(pmsRes);
    }

    //--------------------------------------------------
    //bIsValid
    {
        m_bRes = conConn.bIsValid();
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bOptions
    {
        mysql_option moOption = MYSQL_OPT_COMPRESS;
        const void  *cpvArg   = NULL;

        m_bRes = conConn.bOptions(moOption, cpvArg);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bIsExists
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t casData[][2] = {
            { xT("000000"),     xT("false") },
            { xT("1111111"),    xT("false") },
            { xT("222222222"),  xT("false") },
            { xT("xxxxxxxxxx"), xT("false") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
            bool bRes1 = CxMySQLConnection::bIsExists(csHost, csUser, csPassword, casData[i][0], uiPort, csUnixSocket, culClientFlag);
            bool bRes2 = CxString::bStrToBool(casData[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    //--------------------------------------------------
    //bConnect
    {
        bool bIsDbExists = false;

        bIsDbExists = CxMySQLConnection::bIsExists(csHost, csUser, csPassword, csDbName, uiPort, csUnixSocket, culClientFlag);
        if (false == bIsDbExists) {
            //create Db
            std::tstring_t csDbDefaultName = xT("");

            m_bRes = conConn.bConnect(csHost, csUser, csPassword, csDbDefaultName, uiPort, csUnixSocket, culClientFlag);
            xTEST_EQ(true, m_bRes);

            m_bRes = conConn.bQuery("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8", csDbName.c_str());
            xTEST_EQ(true, m_bRes);
        } else {
            //connect to Db
            m_bRes = conConn.bConnect(csHost, csUser, csPassword, csDbName, uiPort, csUnixSocket, culClientFlag);
            xTEST_EQ(true, m_bRes);
        }

        m_bRes = CxMySQLConnection::bIsExists(csHost, csUser, csPassword, csDbName, uiPort, csUnixSocket, culClientFlag);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bQuery
    {
        m_bRes = conConn.bConnect(csHost, csUser, csPassword, csDbName, uiPort, csUnixSocket, culClientFlag);
        xTEST_EQ(true, m_bRes);

        //create table
        m_bRes = conConn.bQuery(
                             xT("CREATE TABLE IF NOT EXISTS "
                                "   `%s` ("
                                "       `f_id`    int(11)     NOT NULL AUTO_INCREMENT,"
                                "       `f_name`  char(30)    NOT NULL,"
                                "       `f_age`   SMALLINT(6) NOT NULL,"
                                ""
                                "       PRIMARY KEY(`f_id`)"
                                "   )"),
                                sTableName.c_str());
        xTEST_EQ(true, m_bRes);

        //insert records
        m_bRes = conConn.bQuery(
                             xT("INSERT INTO"
                                "    `%s` (`f_name`, `f_age`)"
                                "VALUES"
                                "    ('Katya', 12),"
                                "    ('Lena',  18),"
                                "    ('Misha', 16),"
                                "    ('Vasya', 24),"
                                "    ('Sasha', 20)"),
                                sTableName.c_str());
        xTEST_EQ(true, m_bRes);

        //select all records
        #if 0
            m_bRes = conConn.bQuery(xT("SELECT * FROM `t_main`"));
            xTEST_EQ(true, m_bRes);
        #else
            m_bRes = conConn.bQuery(xT("CHECK TABLE `t_main`"));
            xTEST_EQ(true, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //uiFieldCount
    {
        m_uiRes = conConn.uiFieldCount();
        //xTRACE("uiFieldsNum: %i", m_uiRes);
        //TODO: xTEST_EQ(3U, m_uiRes);
    }

    //--------------------------------------------------
    //uiGetLastError
    {
        m_uiRes = conConn.uiGetLastError();
        xTEST_EQ(0U, m_uiRes);
    }

    //--------------------------------------------------
    //sGetLastErrorStr
    {
        m_sRes = conConn.sGetLastErrorStr();
        xTEST_EQ(false, m_sRes.empty());
    }


    /****************************************************************************
    *    CxMySQLRecordset
    *
    *****************************************************************************/

    CxMySQLRecordset recRec(conConn, false);

    //--------------------------------------------------
    //pmrGet
    {
        MYSQL_RES *pmrRes = recRec.pmrGet();
        xTEST_PTR(pmrRes);
    }

    //--------------------------------------------------
    //bIsValid
    {
        m_bRes = recRec.bIsValid();
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //uiFieldsNum
    {
        m_uiRes = recRec.uiFieldsNum();
        //xTRACE("uiFieldsNum: %i", m_uiRes);
        //TODO: xTEST_EQ(3U, m_uiRes);
    }

    //--------------------------------------------------
    //ullRowsNum
    {
        my_ulonglong ullRes = recRec.ullRowsNum();
        //xTRACE("ullRowsNum: %lli", ullRes);
        //TODO: xTEST_LESS(0ULL, ullRes);
    }

    //--------------------------------------------------
    //bFetchField
    {
        MYSQL_FIELD mfField;

        m_bRes = recRec.bFetchField(&mfField);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bFetchFieldDirect
    {
        uint_t      uiFieldNumber = 0;
        MYSQL_FIELD mfField;

        m_bRes = recRec.bFetchFieldDirect(uiFieldNumber, &mfField);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bFetchFields
    {
        MYSQL_FIELD mfField;

        m_bRes = recRec.bFetchFields(&mfField);
        xTEST_EQ(true, m_bRes);
    }

    #if xTODO
        //--------------------------------------------------
        //bFetchRow
        {
            MYSQL_ROW mrRow;

            m_bRes = recRec.bFetchRow(&mrRow);
            xTEST_EQ(true, m_bRes);
        }

        //--------------------------------------------------
        //bFetchLengths
        {
            ulong_t *pulFieldLengths = NULL;

            m_bRes = recRec.bFetchLengths(&pulFieldLengths);
            xTEST_EQ(true, m_bRes);
            xASSERT(NULL  != pulFieldLengths);
        }
    #endif

    //--------------------------------------------------
    //bFetchRow
    {
        std::vector<std::tstring_t> vsRow;

        for (my_ulonglong i = 0; i < recRec.ullRowsNum(); ++ i) {
            m_bRes = recRec.bFetchRow(&vsRow);
            xTEST_EQ(true, m_bRes);

            //std::tcout << xT("Row ") << i << xT(": ") << vsRow << std::endl;
        }
    }

    //--------------------------------------------------
    //drop Db (cleaning)
    {
        m_bRes = conConn.bQuery(xT("DROP TABLE IF EXISTS `%s`"), sTableName.c_str());
        xTEST_EQ(true, m_bRes);

        m_bRes = conConn.bQuery(xT("DROP DATABASE IF EXISTS `%s`"), csDbName.c_str());
        xTEST_EQ(true, m_bRes);

        m_bRes = CxMySQLConnection::bIsExists(csHost, csUser, csPassword, csDbName, uiPort, csUnixSocket, culClientFlag);
        xTEST_EQ(false, m_bRes);
    }

    //--------------------------------------------------
    //bClose
    {
        m_bRes = conConn.bClose();
        xTEST_EQ(true, m_bRes);
    }

    return true;
}
//---------------------------------------------------------------------------
