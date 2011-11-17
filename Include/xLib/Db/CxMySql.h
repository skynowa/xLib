/**
 * \file  CxMySql.h
 * \brief MySQL data base v.5.1
 */


#ifndef xLib_Db_CxMySqlH
#define xLib_Db_CxMySqlH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOS_ENV_WIN
    #include <mysql.h>
    #include <errmsg.h>
#elif xOS_ENV_UNIX
    #include <mysql/mysql.h>
    #include <mysql/errmsg.h>
#endif
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMySQLConnection :
    public CxNonCopyable
    /// MySQL connection
{
    public:
                                 CxMySQLConnection();
            ///< constructor
        virtual                 ~CxMySQLConnection();
            ///< destructor

        MYSQL                   *pmsGet           () const;
            ///< get handle
        BOOL                     bIsValid         () const;
            ///< validating handle
        BOOL                     bOptions         (const mysql_option cmoOption, const void *cpvArg) const;
            ///< set extra connect options and affect behavior
        BOOL                     bConnect         (const std::string_t &csHost, const std::string_t &csUser, const std::string_t &csPassword, const std::string_t &csDb, const UINT cuiPort, const std::string_t &csUnixSocket, const ULONG culClientFlag);
            ///< attempts to establish a connection to a MySQL database engine running on host
        BOOL                     bQuery           (const char_t *pcszSqlFormat, ...) const;
            ///< executes the SQL statement
        UINT                     uiFieldCount     () const;
            ///< number of columns in a result set
        BOOL                     bClose           ();
            ///< closes a previously opened connection

        //errors
        UINT                     uiGetLastError   () const;
            ///< error code for the most recently invoked API function that can succeed or fail
        std::string_t             sGetLastErrorStr () const;
            ///< error message for the most recently invoked API function that failed

    private:
        MYSQL                   *_m_pmsConnection;
            ///< pointer to connection
};
//---------------------------------------------------------------------------
class CxMySQLRecordset :
    public CxNonCopyable
    /// MySQL recordset
{
    public:
                                 CxMySQLRecordset (const CxMySQLConnection &cmsConnection, const BOOL cbIsUseResult);
            ///< constructor
        virtual                 ~CxMySQLRecordset ();
            ///< destructor

        MYSQL_RES               *pmrGet           () const;
            ///< get handle
        BOOL                     bIsValid         () const;
            ///< validating handle

        UINT                     uiFieldsNum      () const;
            ///< number of columns in a result set
        my_ulonglong             ullRowsNum       () const;
            ///< number of rows in the result set
        BOOL                     bFetchField      (MYSQL_FIELD *pmfField) const;
            ///< The MYSQL_FIELD structure for the current column
        BOOL                     bFetchFieldDirect(const UINT cuiFieldNumber, MYSQL_FIELD *pmfField) const;
            ///< The MYSQL_FIELD structure for the specified column
        BOOL                     bFetchFields     (MYSQL_FIELD *pmfField) const;
            ///< An array of MYSQL_FIELD structures for all columns of a result set
        BOOL                     bFetchRow        (std::vector<std::string_t> *pvsRow) const;
            ///< fetching row

    private:
        const CxMySQLConnection *_m_pcmcConnection;
            ///< pointer to connection object
        MYSQL_RES               *_m_pmrResult;
            ///< for private use

        BOOL                     _bFetchLengths   (ULONG **ppulFieldLengths) const;
            ///< An array of unsigned long integers representing the size of each column
        BOOL                     _bFetchRow       (MYSQL_ROW *pmrRow) const;
            ///< A MYSQL_ROW structure for the next row
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Db_CxMySqlH


#if xTODO
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
#endif


#if xTODO
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
#endif
