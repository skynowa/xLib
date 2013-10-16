/**
 * \file  CxMySql.cpp
 * \brief MySQL data base v.5.1
 */


#include <xLib/Db/CxMySql.h>

#if xCXMYSQL_IS_USE

#include <xLib/Core/CxString.h>

#if xOS_ENV_WIN
    #if !xCOMPILER_MINGW
        #pragma comment(lib, "mysqlclient.lib")
    #endif
#else
    // lib: -lmysqlclient
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    CxMySQLConnection
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxMySQLConnection::CxMySQLConnection() :
    _connection(NULL)
{
    xTEST_EQ(false, isValid());

    MYSQL *_pmsConnection = ::mysql_init(NULL);
    xTEST_MSG_PTR(_pmsConnection, lastErrorStr());

    _connection = _pmsConnection;
}
//------------------------------------------------------------------------------
/* virtual */
CxMySQLConnection::~CxMySQLConnection()
{
    close();
}
//------------------------------------------------------------------------------
MYSQL *
CxMySQLConnection::get() const
{
    xTEST_EQ(true, isValid());

    return _connection;
}
//------------------------------------------------------------------------------
bool_t
CxMySQLConnection::isValid() const
{
    // n/a

    return (NULL != _connection);
}
//------------------------------------------------------------------------------
void_t
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
//-------------------------------------------------------------------------------------------------------
/* static */
bool_t
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

    CxMySQLConnection conConn;

    {
        bRv = conConn.isValid();
        xCHECK_RET(!bRv, false);

        conConn.connect(a_host, a_user, a_password, xT(""), a_port, a_unixSocket, a_clientFlag);
        conConn.query(xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '%s'), 'true', 'false')"),
                       a_db.c_str());
    }

    CxMySQLRecordset recRec(conConn, false);

    {
        bRv = recRec.isValid();
        xTEST_EQ(true, bRv);
        xTEST_EQ(1ULL, recRec.rowsNum());

        std::vec_tstring_t vsRow;

        recRec.fetchRow(&vsRow);
        xTEST_EQ(static_cast<size_t>( 1U ), vsRow.size());

        xCHECK_RET(CxString::compareNoCase(xT("false"), vsRow.at(0)), false);

        xTEST_EQ(true, CxString::compareNoCase(xT("true"), vsRow.at(0)));
    }

    return true;
}
//------------------------------------------------------------------------------
void_t
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

    MYSQL *pmsConnection = ::mysql_real_connect(
                                _connection,
                                xTS2S(a_host).c_str(),
                                xTS2S(a_user).c_str(), xTS2S(a_password).c_str(),
                                xTS2S(a_db).c_str(),   a_port,
                                xTS2S(a_unixSocket).c_str(), a_clientFlag);

    xTEST_MSG_PTR(pmsConnection, lastErrorStr());
    xTEST_MSG_EQ(_connection, pmsConnection, lastErrorStr());

    _connection = pmsConnection;
}
//------------------------------------------------------------------------------
void_t
CxMySQLConnection::query(
    ctchar_t *a_sqlFormat, ...
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(a_sqlFormat);

    std::tstring_t sSqlQuery;
    va_list        palArgs;

    xVA_START(palArgs, a_sqlFormat);
    sSqlQuery = CxString::formatV(a_sqlFormat, palArgs);
    xVA_END(palArgs);

    std::string asSqlQuery = xTS2S(sSqlQuery);

    int_t iRv = ::mysql_real_query(_connection,
                                 asSqlQuery.data(),
                                 static_cast<ulong_t>( asSqlQuery.size() ));
    xTEST_MSG_EQ(0, iRv, lastErrorStr());
}
//------------------------------------------------------------------------------
uint_t
CxMySQLConnection::fieldCount() const
{
    xTEST_EQ(true, isValid());

    uint_t uiRes = ::mysql_field_count(_connection);
    // n/a

    return uiRes;
}
//------------------------------------------------------------------------------
void_t
CxMySQLConnection::close()
{
    // _connection - n/a

    if (isValid()) {
        (void_t)::mysql_close(_connection);

        _connection = NULL;
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    errors
*
*******************************************************************************/

//------------------------------------------------------------------------------
uint_t
CxMySQLConnection::lastError() const
{
    xTEST_EQ(true, isValid());

    uint_t uiRes = ::mysql_errno(_connection);
    // n/a

    return uiRes;
}
//------------------------------------------------------------------------------
std::tstring_t
CxMySQLConnection::lastErrorStr() const
{
    xTEST_EQ(true, isValid());

    std::tstring_t sRv;

    cuint_t  cuiLastError = lastError();
    const char   *cpszRes      = ::mysql_error(_connection);
    // n/a
    xTEST_PTR(cpszRes);

    if (0 == cuiLastError) {
        sRv = CxString::format(xT("%u - \"%s\""), cuiLastError, xT("Success"));
    } else {
        sRv = CxString::format(xT("%u - \"%s\""), cuiLastError, cpszRes);
    }

    return sRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    CxMySQLRecordset
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxMySQLRecordset::CxMySQLRecordset(
    const CxMySQLConnection &a_connection, ///< connection
    cbool_t                 &a_isUseResult  ///< use result or store result
) :
    _connection(&a_connection),
    _result     (NULL)
{
    xTEST_EQ(false, isValid());
    xTEST_PTR(_connection->get());

    MYSQL_RES *pmrResult = NULL;

    if (a_isUseResult) {
        pmrResult = ::mysql_use_result  (_connection->get());
        xTEST_MSG_PTR(pmrResult, _connection->lastErrorStr());
    } else {
        pmrResult = ::mysql_store_result(_connection->get());
        xTEST_MSG_PTR(pmrResult, _connection->lastErrorStr());
    }

    _result = pmrResult;
}
//------------------------------------------------------------------------------
/* virtual */
CxMySQLRecordset::~CxMySQLRecordset() {
    // _result - n/a

    if (isValid()) {
        (void_t)::mysql_free_result(_result);

        _result = NULL;
    }
}
//------------------------------------------------------------------------------
MYSQL_RES *
CxMySQLRecordset::get() const {
    xTEST_EQ(true, isValid());

    return _result;
}
//------------------------------------------------------------------------------
bool_t
CxMySQLRecordset::isValid() const {
    // n/a

    return (NULL != _result);
}
//------------------------------------------------------------------------------
uint_t
CxMySQLRecordset::fieldsNum() const {
    xTEST_EQ(true, isValid());

    uint_t uiRes = ::mysql_num_fields(_result);
    // n/a

    return uiRes;
}
//------------------------------------------------------------------------------
my_ulonglong
CxMySQLRecordset::rowsNum() const {
    xTEST_EQ(true, isValid());

    my_ulonglong ullRv = ::mysql_num_rows(_result);
    // n/a

    return ullRv;
}
//------------------------------------------------------------------------------
void_t
CxMySQLRecordset::fetchField(
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_field(_result);
    xTEST_MSG_PTR(a_field, _connection->lastErrorStr());
}
//------------------------------------------------------------------------------
void_t
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
//------------------------------------------------------------------------------
void_t
CxMySQLRecordset::fetchFields(
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_fields(_result);
    xTEST_MSG_PTR(a_field, _connection->lastErrorStr());
}
//------------------------------------------------------------------------------
void_t
CxMySQLRecordset::fetchRow(
    std::vec_tstring_t *a_row
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(a_row);

    uint_t     uiFieldsNum     = 0;
    MYSQL_ROW  mrRow           = NULL;
    ulong_t   *pulFieldLengths = NULL;

    (*a_row).clear();

    // TODO: CxMySQLRecordset::vFetchRow
    #if xTODO
        //--uint_t   uiFieldsNum   = mysql_num_fields   (_result);
        uint_t     uiFieldsNum   = _connection->ufieldCount();
        MYSQL_ROW  prow       = mysql_fetch_row    (_result);   // array of strings
        ulong_t   *pulRowLengths = mysql_fetch_lengths(_result);   // TODO: may be 64-bit bug
    #endif

    // fields count
    uiFieldsNum   = _connection->fieldCount();

    // fetch row
    _fetchRow(&mrRow);

    // field lengths
    _fetchLengths(&pulFieldLengths);
    xTEST_PTR(pulFieldLengths);

    // push to std::vector
    std::tstring_t sField;

    for (uint_t i = 0; i < uiFieldsNum; ++ i) {
        if (NULL == mrRow[i]) {
            sField = std::tstring_t();
        } else {
            std::string asField = std::string(mrRow[i], pulFieldLengths[i]);

            sField = xS2TS(asField);
        }

        (*a_row).push_back(sField);
    }
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
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
//------------------------------------------------------------------------------
void_t
CxMySQLRecordset::_fetchLengths(
    ulong_t **a_fieldLengths
) const
{
    xTEST_EQ(true, isValid());
    xTEST_PTR(*a_fieldLengths);

    *a_fieldLengths = ::mysql_fetch_lengths(_result);
    xTEST_MSG_PTR(*a_fieldLengths, _connection->lastErrorStr());
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif // CXMYSQL_IS_USE
