/**
 * \file  CxMySql.h
 * \brief MySQL data base v.5.1
 */


#ifndef xLib_Db_CxMySqlH
#define xLib_Db_CxMySqlH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if   xOS_ENV_WIN
    #include <mysql.h>
    #include <errmsg.h>
    #include <mysqld_error.h>
#elif xOS_ENV_UNIX
    #include <mysql/mysql.h>
    #include <mysql/errmsg.h>
    #include <mysql/mysqld_error.h>
#endif
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMySQLConnection :
    private CxNonCopyable
    /// MySQL connection
{
public:
                             CxMySQLConnection();
        ///< constructor
    virtual                 ~CxMySQLConnection();
        ///< destructor

    MYSQL                   *pmsGet           () const;
        ///< get handle
    bool                     bIsValid         () const;
        ///< validating handle
    void                     vOptions         (const mysql_option &cmoOption, const void *cpvArg) const;
        ///< set extra connect options and affect behavior
    static bool              bIsExists        (const std::tstring_t &csHost, const std::tstring_t &csUser, const std::tstring_t &csPassword, const std::tstring_t &csDb, const uint_t &cuiPort, const std::tstring_t &csUnixSocket, const ulong_t &culClientFlag);
        ///<
    void                     vConnect         (const std::tstring_t &csHost, const std::tstring_t &csUser, const std::tstring_t &csPassword, const std::tstring_t &csDb, const uint_t &cuiPort, const std::tstring_t &csUnixSocket, const ulong_t &culClientFlag);
        ///< attempts to establish a connection to a MySQL database engine running on host
    void                     vQuery           (const tchar_t *pcszSqlFormat, ...) const;
        ///< executes the SQL statement
    uint_t                   uiFieldCount     () const;
        ///< number of columns in a result set
    void                     vClose           ();
        ///< closes a previously opened connection

    //errors
    uint_t                   uiLastError      () const;
        ///< error code for the most recently invoked API function that can succeed or fail
    std::tstring_t           sLastErrorStr    () const;
        ///< error message for the most recently invoked API function that failed

private:
    MYSQL                   *_m_pmsConnection;
        ///< pointer to connection
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMySQLRecordset :
    private CxNonCopyable
    /// MySQL recordset
{
public:
                             CxMySQLRecordset (const CxMySQLConnection &cmsConnection, const bool &cbIsUseResult);
        ///< constructor
    virtual                 ~CxMySQLRecordset ();
        ///< destructor

    MYSQL_RES               *pmrGet           () const;
        ///< get handle
    bool                     bIsValid         () const;
        ///< validating handle

    uint_t                   uiFieldsNum      () const;
        ///< number of columns in a result set
    my_ulonglong             ullRowsNum       () const;
        ///< number of rows in the result set
    void                     vFetchField      (MYSQL_FIELD *pmfField) const;
        ///< The MYSQL_FIELD structure for the current column
    void                     vFetchFieldDirect(const uint_t &cuiFieldNumber, MYSQL_FIELD *pmfField) const;
        ///< The MYSQL_FIELD structure for the specified column
    void                     vFetchFields     (MYSQL_FIELD *pmfField) const;
        ///< An array of MYSQL_FIELD structures for all columns of a result set
    void                     vFetchRow        (std::vec_tstring_t *pvsRow) const;
        ///< fetching row

private:
    const CxMySQLConnection *_m_pcmcConnection;
        ///< pointer to connection object
    MYSQL_RES               *_m_pmrResult;
        ///< for private use

    void                     _vFetchLengths   (ulong_t **ppulFieldLengths) const;
        ///< An array of unsigned long_t integers representing the size of each column
    void                     _vFetchRow       (MYSQL_ROW *pmrRow) const;
        ///< A MYSQL_ROW structure for the next row
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Db_CxMySqlH


#if xTODO
    MYSQL_ROW row;
    unsigned long_t *lengths;
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
