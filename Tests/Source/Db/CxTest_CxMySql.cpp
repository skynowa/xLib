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
CxTest_CxMySql::bUnit() {
    tString csHost       = xT("127.0.0.1");
    tString csUser       = xT("root");
    tString csPassword   = xT("root");
    tString csDbName     = xT("db_test");
    UINT    uiPort       = 0;
    tString sTableName   = xT("t_main");


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
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bOptions
    {
        mysql_option moOption = MYSQL_OPT_COMPRESS;
        const void  *cpvArg   = NULL;

        m_bRes = conConn.bOptions(moOption, cpvArg);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bConnect
    {
        tString csUnixSocket = xT("");
        ULONG   ulClientFlag = 0;

        m_bRes = conConn.bConnect(csHost, csUser, csPassword, csDbName, uiPort, csUnixSocket, ulClientFlag);
        if (FALSE == m_bRes) {
            csDbName = xT("");

            m_bRes = conConn.bConnect(csHost, csUser, csPassword, csDbName, uiPort, csUnixSocket, ulClientFlag);
            xASSERT(FALSE != m_bRes);
        }
    }

    //--------------------------------------------------
    //bQuery
    {
        //create Db
        m_bRes = conConn.bQuery("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8", csDbName.c_str());
        xASSERT(FALSE != m_bRes);

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
        xASSERT(FALSE != m_bRes);

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
        xASSERT(FALSE != m_bRes);

        //select all records
        m_bRes = conConn.bQuery(xT("SELECT * FROM `t_main`"));
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //uiFieldCount
    {
        m_uiRes = conConn.uiFieldCount();
        //xTRACE("uiFieldsNum: %i", m_uiRes);
        xASSERT(3 == m_uiRes);
    }

    //--------------------------------------------------
    //uiGetLastError
    {
        m_uiRes = conConn.uiGetLastError();
        xASSERT(0 == m_uiRes);
    }

    //--------------------------------------------------
    //sGetLastErrorStr
    {
        m_sRes = conConn.sGetLastErrorStr();
        xASSERT_MSG(false == m_sRes.empty(), m_sRes.c_str());
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
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //uiFieldsNum
    {
        m_uiRes = recRec.uiFieldsNum();
        //xTRACE("uiFieldsNum: %i", m_uiRes);
        xASSERT(3 == m_uiRes);
    }

    //--------------------------------------------------
    //ullRowsNum
    {
        my_ulonglong ullRes = recRec.ullRowsNum();
        //xTRACE("ullRowsNum: %lli", ullRes);
        xASSERT(5 == ullRes);
    }

    //--------------------------------------------------
    //bFetchField
    {
        MYSQL_FIELD mfField;

        m_bRes = recRec.bFetchField(&mfField);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bFetchFieldDirect
    {
        UINT        uiFieldNumber = 0;
        MYSQL_FIELD mfField;

        m_bRes = recRec.bFetchFieldDirect(uiFieldNumber, &mfField);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bFetchFields
    {
        MYSQL_FIELD mfField;

        m_bRes = recRec.bFetchFields(&mfField);
        xASSERT(FALSE != m_bRes);
    }

//    //--------------------------------------------------
//    //bFetchRow
//    {
//        MYSQL_ROW mrRow;
//
//        m_bRes = recRec.bFetchRow(&mrRow);
//        xASSERT(FALSE != m_bRes);
//    }
//
//    //--------------------------------------------------
//    //bFetchLengths
//    {
//        ULONG *pulFieldLengths = NULL;
//
//        m_bRes = recRec.bFetchLengths(&pulFieldLengths);
//        xASSERT(FALSE != m_bRes);
//        xASSERT(NULL  != pulFieldLengths);
//    }


    //--------------------------------------------------
    //bFetchRow
    {
        std::vector<tString> vecsRow;

        for (my_ulonglong i = 0; i < recRec.ullRowsNum(); ++ i) {
            m_bRes = recRec.bFetchRow(&vecsRow);
            xASSERT(FALSE != m_bRes);

            //CxString::vStdVectorPrintT(vecsRow);
        }
    }

    //--------------------------------------------------
    //drop Db
    {
        m_bRes = conConn.bQuery(xT("DROP TABLE IF EXISTS `%s`"), sTableName.c_str());
        xASSERT(FALSE != m_bRes);

        ////m_bRes = conConn.bQuery(xT("DROP DATABASE IF EXISTS `%s`"), csDbName.c_str());
        ////xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bClose
    {
        m_bRes = conConn.bClose();
        xASSERT(FALSE != m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
