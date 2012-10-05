/**
 * \file   CxTest_CxMySql.cpp
 * \brief
 */


#include <Test/Db/CxTest_CxMySql.h>

#include <xLib/Common/CxString.h>


//---------------------------------------------------------------------------
CxTest_CxMySql::CxTest_CxMySql() {

}
//---------------------------------------------------------------------------
CxTest_CxMySql::~CxTest_CxMySql() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxMySql::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csHost        = xT("127.0.0.1");
    const std::tstring_t csUser        = xT("root");
    const std::tstring_t csPassword    = xT("root");
    const std::tstring_t csDbName      = xT("db_test");
    const uint_t         cuiPort       = 0U;
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
        m_bRv = conConn.bIsValid();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bOptions
    {
        mysql_option moOption = MYSQL_OPT_COMPRESS;
        const void  *cpvArg   = NULL;

        conConn.vOptions(moOption, cpvArg);
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
            bool bRes1 = CxMySQLConnection::bIsExists(csHost, csUser, csPassword, casData[i][0], cuiPort, csUnixSocket, culClientFlag);
            bool bRes2 = CxString::bStrToBool(casData[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    //--------------------------------------------------
    //bConnect
    {
        bool bIsDbExists = false;

        bIsDbExists = CxMySQLConnection::bIsExists(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);
        if (false == bIsDbExists) {
            //create Db
            std::tstring_t csDbDefaultName = xT("");

            conConn.vConnect(csHost, csUser, csPassword, csDbDefaultName, cuiPort, csUnixSocket, culClientFlag);
            conConn.vQuery("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8", csDbName.c_str());
        } else {
            //connect to Db
            conConn.vConnect(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);
        }

        m_bRv = CxMySQLConnection::bIsExists(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bQuery
    {
        conConn.vConnect(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);

        //create table
        conConn.vQuery(
                        xT("CREATE TABLE IF NOT EXISTS "
                        "   `%s` ("
                        "       `f_id`    int(11)     NOT NULL AUTO_INCREMENT,"
                        "       `f_name`  char(30)    NOT NULL,"
                        "       `f_age`   SMALLINT(6) NOT NULL"
                        "   )"),
                        sTableName.c_str());
        xTEST_EQ(true, m_bRv);

        //insert records
        conConn.vQuery(
                        xT("INSERT INTO"
                        "    `%s` (`f_name`, `f_age`)"
                        "VALUES"
                        "    ('Katya', 12),"
                        "    ('Lena',  18),"
                        "    ('Misha', 16),"
                        "    ('Vasya', 24),"
                        "    ('Sasha', 20)"),
                        sTableName.c_str());

        //select all records
        #if 0
            conConn.vQuery(xT("SELECT * FROM `t_main`"));
        #else
            conConn.vQuery(xT("CHECK TABLE `t_main`"));
        #endif
    }

    //--------------------------------------------------
    //uiFieldCount
    {
        m_uiRv = conConn.uiFieldCount();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    //--------------------------------------------------
    //uiGetLastError
    {
        m_uiRv = conConn.uiGetLastError();
        xTEST_EQ(0U, m_uiRv);
    }

    //--------------------------------------------------
    //sGetLastErrorStr
    {
        m_sRv = conConn.sGetLastErrorStr();
        xTEST_EQ(false, m_sRv.empty());
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
        m_bRv = recRec.bIsValid();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //uiFieldsNum
    {
        m_uiRv = recRec.uiFieldsNum();
        //xTRACE("uiFieldsNum: %i", m_uiRv);
        //TODO: xTEST_EQ(3U, m_uiRv);
    }

    //--------------------------------------------------
    //ullRowsNum
    {
        my_ulonglong ullRv = recRec.ullRowsNum(); xUNUSED(ullRv);
        //xTRACE("ullRowsNum: %lli", ullRv);
        //TODO: xTEST_LESS(0ULL, ullRv);
    }

    //--------------------------------------------------
    //bFetchField
    {
        MYSQL_FIELD mfField;

        recRec.vFetchField(&mfField);
    }

    //--------------------------------------------------
    //bFetchFieldDirect
    {
        uint_t      uiFieldNumber = 0;
        MYSQL_FIELD mfField;

        recRec.vFetchFieldDirect(uiFieldNumber, &mfField);
    }

    //--------------------------------------------------
    //bFetchFields
    {
        MYSQL_FIELD mfField;

        recRec.vFetchFields(&mfField);
    }

    #if xTODO
        //--------------------------------------------------
        //bFetchRow
        {
            MYSQL_ROW mrRow;

            recRec.vFetchRow(&mrRow);
        }

        //--------------------------------------------------
        //bFetchLengths
        {
            ulong_t *pulFieldLengths = NULL;

            recRec.vFetchLengths(&pulFieldLengths);
            xTEST_PTR(pulFieldLengths);
        }
    #endif

    //--------------------------------------------------
    //bFetchRow
    {
        std::vec_tstring_t vsRow;

        for (my_ulonglong i = 0; i < recRec.ullRowsNum(); ++ i) {
            recRec.vFetchRow(&vsRow);

            //std::tcout << xT("Row ") << i << xT(": ") << vsRow << std::endl;
        }
    }

    //--------------------------------------------------
    //drop Db (cleaning)
    {
        conConn.vQuery(xT("DROP TABLE IF EXISTS `%s`"), sTableName.c_str());
        conConn.vQuery(xT("DROP DATABASE IF EXISTS `%s`"), csDbName.c_str());

        m_bRv = CxMySQLConnection::bIsExists(csHost, csUser, csPassword, csDbName, cuiPort, csUnixSocket, culClientFlag);
        xTEST_EQ(false, m_bRv);
    }

    //--------------------------------------------------
    //bClose
    conConn.vClose();
}
//---------------------------------------------------------------------------
