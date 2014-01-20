/**
 * \file  CxMySql.cpp
 * \brief MySQL data base v.5.1
 */


#if xHAVE_MYSQL

#include <xLib/Core/CxString.h>

#if xOS_ENV_WIN
    #if !xCOMPILER_MINGW
        #pragma comment(lib, "mysqlclient.lib")
    #endif
#else
    // lib: -lmysqlclient
#endif


xNAMESPACE_BEGIN(xlib)

/**************************************************************************************************
*    CxMySQLConnection
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxMySQLConnection::CxMySQLConnection() :
    _connection(NULL)
{
    xTEST_EQ(false, isValid());

    MYSQL *_connection = ::mysql_init(NULL);
    xTEST_MSG_PTR(_connection, lastErrorStr());

    _connection = _connection;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxMySQLConnection::~CxMySQLConnection()
{
    close();
}
//-------------------------------------------------------------------------------------------------
MYSQL *
CxMySQLConnection::get() const
{
    xTEST_EQ(true, isValid());

    return _connection;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxMySQLConnection::isValid() const
{
    // n/a

    return (NULL != _connection);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLConnection::options(
    const mysql_option &a_option,
    cvoid_t            *a_arg
) const
{
    xTEST_EQ(true, isValid());
    // moOption - n/a
    // arg   - n/a

#if MYSQL_VERSION_ID < 50154
    int_t iRv = ::mysql_options(_connection, a_option, static_cast<ctchar_t *>( a_arg ));
#else
    int_t iRv = ::mysql_options(_connection, a_option, a_arg);
#endif
    xTEST_MSG_EQ(0, iRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxMySQLConnection::isExists(
    std::ctstring_t &a_host,
    std::ctstring_t &a_user,
    std::ctstring_t &a_password,
    std::ctstring_t &a_db,
    cuint_t         &a_port,
    std::ctstring_t &a_unixSocket,
    culong_t        &a_clientFlag
)
{
    bool_t bRv = false;

    CxMySQLConnection connection;

    {
        bRv = connection.isValid();
        xCHECK_RET(!bRv, false);

        connection.connect(a_host, a_user, a_password, xT(""), a_port, a_unixSocket, a_clientFlag);
        connection.query(xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA "
            "WHERE SCHEMA_NAME = '%s'), 'true', 'false')"), a_db.c_str());
    }

    CxMySQLRecordset rec(connection, false);

    {
        bRv = rec.isValid();
        xTEST_EQ(true, bRv);
        xTEST_EQ(1ULL, rec.rowsNum());

        std::vec_tstring_t vsRow;

        rec.fetchRow(&vsRow);
        xTEST_EQ(static_cast<size_t>( 1U ), vsRow.size());

        xCHECK_RET(CxStringCI::compare(xT("false"), vsRow.at(0)), false);

        xTEST_EQ(true, CxStringCI::compare(xT("true"), vsRow.at(0)));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLConnection::connect(
    std::ctstring_t &a_host,
    std::ctstring_t &a_user,
    std::ctstring_t &a_password,
    std::ctstring_t &a_db,
    cuint_t         &a_port,
    std::ctstring_t &a_unixSocket,
    culong_t        &a_clientFlag
)
{
    xTEST_EQ(true, isValid());
    // host       - n/a
    // user       - n/a
    // password   - n/a
    // db         - n/a
    // port      - n/a
    // unixSocket - n/a
    // ulClientFlag - n/a

    MYSQL *connection = ::mysql_real_connect(
                                _connection,
                                xTS2S(a_host).c_str(),
                                xTS2S(a_user).c_str(), xTS2S(a_password).c_str(),
                                xTS2S(a_db).c_str(),   a_port,
                                xTS2S(a_unixSocket).c_str(), a_clientFlag);

    xTEST_MSG_PTR(connection, lastErrorStr());
    xTEST_MSG_EQ(_connection, connection, lastErrorStr());

    _connection = connection;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLConnection::query(
    ctchar_t *a_sqlFormat, ...
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(a_sqlFormat);

    std::tstring_t sqlQuery;
    va_list        args;

    xVA_START(args, a_sqlFormat);
    sqlQuery = CxString::formatV(a_sqlFormat, args);
    xVA_END(args);

    std::string asSqlQuery = xTS2S(sqlQuery);

    int_t iRv = ::mysql_real_query(_connection,
                                 asSqlQuery.data(),
                                 static_cast<ulong_t>( asSqlQuery.size() ));
    xTEST_MSG_EQ(0, iRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
inline uint_t
CxMySQLConnection::fieldCount() const
{
    xTEST_EQ(true, isValid());

    uint_t uiRv = ::mysql_field_count(_connection);
    // n/a

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLConnection::close()
{
    // _connection - n/a

    if (isValid()) {
        (void_t)::mysql_close(_connection);

        _connection = NULL;
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    errors
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline uint_t
CxMySQLConnection::lastError() const
{
    xTEST_EQ(true, isValid());

    uint_t uiRv = ::mysql_errno(_connection);
    // n/a

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxMySQLConnection::lastErrorStr() const
{
    xTEST_EQ(true, isValid());

    std::tstring_t sRv;

    cuint_t      lastError = lastError();
    const char * cpszRv    = ::mysql_error(_connection);
    // n/a
    xTEST_PTR(cpszRv);

    if (0 == lastError) {
        sRv = CxString::format(xT("%u - \"%s\""), lastError, xT("Success"));
    } else {
        sRv = CxString::format(xT("%u - \"%s\""), lastError, cpszRv);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    CxMySQLRecordset
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxMySQLRecordset::CxMySQLRecordset(
    const CxMySQLConnection &a_connection, ///< connection
    cbool_t                 &a_isUseResult  ///< use result or store result
) :
    _connection(&a_connection),
    _result     (NULL)
{
    xTEST_EQ(false, isValid());
    xTEST_PTR(_connection->get());

    MYSQL_RES *result = NULL;

    if (a_isUseResult) {
        result = ::mysql_use_result  (_connection->get());
        xTEST_MSG_PTR(result, _connection->lastErrorStr());
    } else {
        result = ::mysql_store_result(_connection->get());
        xTEST_MSG_PTR(result, _connection->lastErrorStr());
    }

    _result = result;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxMySQLRecordset::~CxMySQLRecordset()
{
    // _result - n/a

    if (isValid()) {
        (void_t)::mysql_free_result(_result);

        _result = NULL;
    }
}
//-------------------------------------------------------------------------------------------------
inline MYSQL_RES *
CxMySQLRecordset::get() const {
    xTEST_EQ(true, isValid());

    return _result;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxMySQLRecordset::isValid() const
{
    // n/a

    return (NULL != _result);
}
//-------------------------------------------------------------------------------------------------
uint_t
CxMySQLRecordset::fieldsNum() const
{
    xTEST_EQ(true, isValid());

    uint_t uiRv = ::mysql_num_fields(_result);
    // n/a

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
inline my_ulonglong
CxMySQLRecordset::rowsNum() const
{
    xTEST_EQ(true, isValid());

    my_ulonglong ullRv = ::mysql_num_rows(_result);
    // n/a

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLRecordset::fetchField(
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_field(_result);
    xTEST_MSG_PTR(a_field, _connection->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLRecordset::fetchFieldDirect(
    cuint_t     &a_fieldNumber,
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(true, isValid());
    // uiFieldNumber - n/a
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_field_direct(_result, a_fieldNumber);
    xTEST_MSG_PTR(a_field, _connection->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLRecordset::fetchFields(
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_fields(_result);
    xTEST_MSG_PTR(a_field, _connection->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLRecordset::fetchRow(
    std::vec_tstring_t *a_row
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(a_row);

    uint_t     fieldsNum    = 0;
    MYSQL_ROW  row          = NULL;
    ulong_t   *fieldLengths = NULL;

    (*a_row).clear();

    // TODO: CxMySQLRecordset::fetchRow()
    #if xTODO
        //--uint_t   fieldsNum   = mysql_num_fields   (_result);
        uint_t     fieldsNum  = _connection->ufieldCount();
        MYSQL_ROW  prow       = mysql_fetch_row    (_result); // array of strings
        ulong_t   *rowLengths = mysql_fetch_lengths(_result); // TODO: CxMySQLRecordset::fetchRow() - may be 64-bit bug
    #endif

    // fields count
    fieldsNum = _connection->fieldCount();

    // fetch row
    _fetchRow(&row);

    // field lengths
    _fetchLengths(&fieldLengths);
    xTEST_PTR(fieldLengths);

    // push to std::vector
    std::tstring_t sField;

    for (uint_t i = 0; i < fieldsNum; ++ i) {
        if (NULL == row[i]) {
            sField = std::tstring_t();
        } else {
            std::string asField = std::string(row[i], fieldLengths[i]);

            sField = xS2TS(asField);
        }

        (*a_row).push_back(sField);
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLRecordset::_fetchRow(
    MYSQL_ROW *a_row
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(a_row);

    *a_row = ::mysql_fetch_row(_result);
    // n/a
    xTEST_PTR(*a_row);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMySQLRecordset::_fetchLengths(
    ulong_t **a_fieldLengths
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(*a_fieldLengths);

    *a_fieldLengths = ::mysql_fetch_lengths(_result);
    xTEST_MSG_PTR(*a_fieldLengths, _connection->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)

#endif // CXMYSQL_IS_USE
