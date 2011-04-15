/****************************************************************************
* Class name:  CxMySql
* Description: MySQL data base v.5.1
* File name:   CxMySql.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.01.2011 23:27:12
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Db_CxMySqlH
#define xLib_Db_CxMySqlH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
    #include <mysql.h>
    #include <errmsg.h>
    
    #pragma comment(lib, "libmysql.lib")
#elif defined(xOS_LINUX)
    #include <mysql/mysql.h>
    #include <mysql/errmsg.h>
#endif
//---------------------------------------------------------------------------
class CxMySQLConnection : public CxNonCopyable  {
    public:
                     CxMySQLConnection();
        virtual     ~CxMySQLConnection();

        MYSQL       *pmsGet           () const;
        BOOL         bIsValid         () const;
        BOOL         bOptions         (mysql_option moOption, const void *cpvArg) const;
        BOOL         bConnect         (const tString &csHost, const tString &csUser, const tString &csPassword, const tString &csDb, UINT uiPort, const tString &csUnixSocket, ULONG ulClientFlag);
        BOOL         bQuery           (LPCTSTR pcszSqlFormat, ...) const;
        UINT         uiFieldCount     () const;
        BOOL         bClose           ();

        //errors
        UINT         uiGetLastError   () const;
        tString      sGetLastErrorStr () const;

    private:
        MYSQL       *_m_pmsConnection;
};
//---------------------------------------------------------------------------
class CxMySQLRecordset : public CxNonCopyable {
	public:
                     CxMySQLRecordset (const CxMySQLConnection &cmsConnection, BOOL bIsUseResult);
		virtual     ~CxMySQLRecordset ();

		MYSQL_RES   *pmrGet           () const;
        BOOL         bIsValid         () const;

        UINT         uiFieldsNum      () const;
        my_ulonglong ullRowsNum       () const;
        BOOL         bFetchField      (MYSQL_FIELD *pmfField) const;
        BOOL         bFetchFieldDirect(UINT uiFieldNumber, MYSQL_FIELD *pmfField) const;
        BOOL         bFetchFields     (MYSQL_FIELD *pmfField) const;
        BOOL         bFetchRow        (std::vector<tString> *pvecsRow) const;

    private:
		MYSQL_RES               *_m_pmrResult;
		const CxMySQLConnection *_m_pmcConnection;

        BOOL         bFetchLengths    (ULONG **ppulFieldLengths) const;
        BOOL         bFetchRow        (MYSQL_ROW *pmrRow) const;
};
//---------------------------------------------------------------------------
#endif //xLib_Db_CxMySqlH

/*
MYSQL_ROW row;
unsigned long *lengths;
unsigned int num_fields;
unsigned int i;

row = mysql_fetch_row(result);
if (row)
{
    num_fields = mysql_num_fields(result);
    lengths = mysql_fetch_lengths(result);
    for(i = 0; i < num_fields; i++)
    {
         printf("Column %u is %lu bytes in length.\n",         i, lengths[i]);
    }
}
*/



/*
mysql_library_init()
{
    mysql_init()

    mysql_options()

    mysql_real_connect()
    {
        //mysql_query()
        mysql_real_query()

        //Recordset
        {
            mysql_use_result()
            mysql_store_result()

            {
                mysql_num_fields()
                mysql_num_rows()

                mysql_fetch_row    (pMySqlRes); //row
                mysql_fetch_lengths(result);    //row length
            }

            mysql_free_result()
        }
    }
    mysql_close()
}
mysql_library_end()
*/





