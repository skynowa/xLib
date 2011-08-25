/****************************************************************************
* Class name:  CxTest_CxMySql
* Description: test CxMySql
* File name:   CxTest_CxMySql.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Db/CxTest_CxMySql.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxMySql
CxTest_CxMySql::CxTest_CxMySql() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxMySql
CxTest_CxMySql::~CxTest_CxMySql() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxMySql::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    std::tstring csHost       = xT("127.0.0.1");
    std::tstring csUser       = xT("root");
    std::tstring csPassword   = xT("root");
    std::tstring csDbName     = xT("db_test");
    UINT    uiPort       = 0;
    std::tstring sTableName   = xT("t_main");


    /****************************************************************************
    *	CxMySQLConnection
    *
    *****************************************************************************/

    CxMySQLConnection conConn;


    //--------------------------------------------------
    //pmsGet
    {
        MYSQL *pmsRes = conConn.pmsGet();
        xASSERT(NULL != pmsRes);
    }

    //--------------------------------------------------
    //bIsValid
    {
        m_bRes = conConn.bIsValid();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bOptions
    {
        mysql_option moOption = MYSQL_OPT_COMPRESS;
        const void  *cpvArg   = NULL;

        m_bRes = conConn.bOptions(moOption, cpvArg);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bConnect
    {
        std::tstring csUnixSocket = xT("");
        ULONG   ulClientFlag = 0;

        m_bRes = conConn.bConnect(csHost, csUser, csPassword, csDbName, uiPort, csUnixSocket, ulClientFlag);
        if (FALSE == m_bRes) {
            csDbName = xT("");

            m_bRes = conConn.bConnect(csHost, csUser, csPassword, csDbName, uiPort, csUnixSocket, ulClientFlag);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //--------------------------------------------------
    //bQuery
    {
        //create Db
        m_bRes = conConn.bQuery("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8", csDbName.c_str());
        xASSERT_NOT_EQ(FALSE, m_bRes);

        //create table
        m_bRes = conConn.bQuery(
                             xT("CREATE TABLE IF NOT EXISTS "
                                "   `%s` ("
                                "       `f_id`    INT(11)     NOT NULL AUTO_INCREMENT,"
                                "       `f_name`  CHAR(30)    NOT NULL,"
                                "       `f_age`   SMALLINT(6) NOT NULL,"
                                ""
                                "       PRIMARY KEY(`f_id`)"
                                "   )"),
                                sTableName.c_str());
        xASSERT_NOT_EQ(FALSE, m_bRes);

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
        xASSERT_NOT_EQ(FALSE, m_bRes);

        //select all records
        m_bRes = conConn.bQuery(xT("SELECT * FROM `t_main`"));
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //uiFieldCount
    {
        m_uiRes = conConn.uiFieldCount();
        //xTRACE("uiFieldsNum: %i", m_uiRes);
        xASSERT_EQ(3U, m_uiRes);
    }

    //--------------------------------------------------
    //uiGetLastError
    {
        m_uiRes = conConn.uiGetLastError();
        xASSERT_EQ(0U, m_uiRes);
    }

    //--------------------------------------------------
    //sGetLastErrorStr
    {
        m_sRes = conConn.sGetLastErrorStr();
        xASSERT_EQ(false, m_sRes.empty());
    }


    /****************************************************************************
    *	CxMySQLRecordset
    *
    *****************************************************************************/

    CxMySQLRecordset recRec(conConn, FALSE);

    //--------------------------------------------------
    //pmrGet
    {
        MYSQL_RES *pmrRes = recRec.pmrGet();
        xASSERT(NULL != pmrRes);
    }

    //--------------------------------------------------
    //bIsValid
    {
        m_bRes = recRec.bIsValid();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //uiFieldsNum
    {
        m_uiRes = recRec.uiFieldsNum();
        //xTRACE("uiFieldsNum: %i", m_uiRes);
        xASSERT_EQ(3U, m_uiRes);
    }

    //--------------------------------------------------
    //ullRowsNum
    {
        my_ulonglong ullRes = recRec.ullRowsNum();
        //xTRACE("ullRowsNum: %lli", ullRes);
        xASSERT_EQ(5ULL, ullRes);
    }

    //--------------------------------------------------
    //bFetchField
    {
        MYSQL_FIELD mfField;

        m_bRes = recRec.bFetchField(&mfField);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bFetchFieldDirect
    {
        UINT        uiFieldNumber = 0;
        MYSQL_FIELD mfField;

        m_bRes = recRec.bFetchFieldDirect(uiFieldNumber, &mfField);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bFetchFields
    {
        MYSQL_FIELD mfField;

        m_bRes = recRec.bFetchFields(&mfField);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    #if xTODO
        //--------------------------------------------------
        //bFetchRow
        {
            MYSQL_ROW mrRow;

            m_bRes = recRec.bFetchRow(&mrRow);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //--------------------------------------------------
        //bFetchLengths
        {
            ULONG *pulFieldLengths = NULL;

            m_bRes = recRec.bFetchLengths(&pulFieldLengths);
            xASSERT_NOT_EQ(FALSE, m_bRes);
            xASSERT(NULL  != pulFieldLengths);
        }
    #endif

    //--------------------------------------------------
    //bFetchRow
    {
        std::vector<std::tstring> vsRow;

        for (my_ulonglong i = 0; i < recRec.ullRowsNum(); ++ i) {
            m_bRes = recRec.bFetchRow(&vsRow);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            //CxString::vStdVectorPrintT(vsRow);
        }
    }

    //--------------------------------------------------
    //drop Db
    {
        m_bRes = conConn.bQuery(xT("DROP TABLE IF EXISTS `%s`"), sTableName.c_str());
        xASSERT_NOT_EQ(FALSE, m_bRes);

        #if xTODO
            m_bRes = conConn.bQuery(xT("DROP DATABASE IF EXISTS `%s`"), csDbName.c_str());
            xASSERT_NOT_EQ(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bClose
    {
        m_bRes = conConn.bClose();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
