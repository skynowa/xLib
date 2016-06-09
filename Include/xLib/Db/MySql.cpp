/**
 * \file  MySql.inl
 * \brief MySql client
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "MySql.h"
#endif

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>

#if xENV_WIN
    #if !xCOMPILER_MINGW
        #pragma comment(lib, "mysqlclient.lib")
    #endif
#else
    // lib: -lmysqlclient
#endif


xNAMESPACE_BEGIN2(xlib, db)

/**************************************************************************************************
*    MySqlConnection
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
MySqlConnection::MySqlConnection() :
    _conn(xPTR_NULL)
{
    xTEST_EQ(isValid(), false);

    _conn = ::mysql_init(xPTR_NULL);
    xTEST_PTR_MSG(_conn, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
MySqlConnection::~MySqlConnection()
{
    close();
}
//-------------------------------------------------------------------------------------------------
xINLINE MYSQL *
MySqlConnection::get() const
{
    xTEST_EQ(isValid(), true);

    return _conn;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
MySqlConnection::isValid() const
{
    return (_conn != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlConnection::options(
    const mysql_option &a_option,
    cvoid_t            *a_arg
) const
{
    xTEST_EQ(isValid(), true);
    xTEST_NA(a_option);
    xTEST_NA(a_arg);

#if MYSQL_VERSION_ID < 50154
    int_t iRv = ::mysql_options(_conn, a_option, static_cast<ctchar_t *>( a_arg ));
#else
    int_t iRv = ::mysql_options(_conn, a_option, a_arg);
#endif
    xTEST_EQ_MSG(0, iRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
MySqlConnection::ping(
    int_t *out_errorCode    /* = xPTR_NULL */
) const
{
    int_t iRv = ::mysql_ping( get() );

    Utils::ptrAssignT(out_errorCode, iRv);

    if (iRv != 0) {
        return false;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
MySqlConnection::isExists(
    cMySqlConnectionData &a_data
)
{
    bool_t bRv = false;

    MySqlConnection conn;

    {
        bRv = conn.isValid();
        xCHECK_RET(!bRv, false);

        bRv = conn.ping();
        xCHECK_RET(!bRv, false);

        conn.connect(a_data);
        conn.query(xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA "
            "WHERE SCHEMA_NAME = '%s'), 'true', 'false')"), a_data.db.c_str());
    }

    MySqlRecordset rec(conn, false);

    {
        bRv = rec.isValid();
        xTEST_EQ(bRv, true);
        xTEST_EQ(rec.rowsNum(), 1ULL);

        std::vec_tstring_t row;
        rec.fetchRow(&row);
        xTEST_EQ(row.size(), static_cast<size_t>(1));
        xCHECK_RET(StringCI::compare(xT("false"), row.at(0)), false);
        xTEST_EQ(StringCI::compare(xT("true"), row.at(0)), true);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlConnection::connect(
    cMySqlConnectionData &a_data
)
{
    xTEST_EQ(isValid(), true);
    xTEST_NA(a_data);

    _conn = ::mysql_real_connect(_conn, xT2A(a_data.host).c_str(), xT2A(a_data.user).c_str(),
        xT2A(a_data.password).c_str(), xT2A(a_data.db).c_str(), a_data.port,
        xT2A(a_data.unixSocket).c_str(), a_data.clientFlag);

    xTEST_PTR_MSG(_conn, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlConnection::query(
    ctchar_t *a_sqlFormat, ...
) const
{
    xTEST_EQ(isValid(), true);
    xTEST_PTR(a_sqlFormat);

    std::tstring_t sqlQuery;
    va_list        args;

    xVA_START(args, a_sqlFormat);
    sqlQuery = Format::c_strV(a_sqlFormat, args);
    xVA_END(args);

    const std::string asSqlQuery = xT2A(sqlQuery);

    int_t iRv = ::mysql_real_query(_conn, asSqlQuery.data(),
        static_cast<ulong_t>( asSqlQuery.size() ));
    xTEST_EQ_MSG(0, iRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
xINLINE uint_t
MySqlConnection::fieldCount() const
{
    xTEST_EQ(isValid(), true);

    return ::mysql_field_count(_conn);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlConnection::close()
{
    xTEST_NA(_conn);

    xCHECK_DO(!isValid(), return);

    (void_t)::mysql_close(_conn);
    _conn = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    errors
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE uint_t
MySqlConnection::lastError() const
{
    xTEST_EQ(isValid(), true);

    return ::mysql_errno(_conn);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
MySqlConnection::lastErrorStr() const
{
    xTEST_EQ(isValid(), true);

    std::tstring_t sRv;

    cuint_t     _lastError = lastError();
    const char *error      = ::mysql_error(_conn);
    xTEST_PTR(error);

    if (_lastError == 0U) {
        sRv = Format::str(xT("{} - \"{}\""), _lastError, xT("Success"));
    } else {
        sRv = Format::str(xT("{} - \"{}\""), _lastError, error);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    MySqlRecordset
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
MySqlRecordset::MySqlRecordset(
    const MySqlConnection &a_connection, ///< connection
    cbool_t               &a_isUseResult  ///< use result or store result
) :
    _conn  (&a_connection),
    _result(xPTR_NULL)
{
    xTEST_EQ(isValid(), false);
    xTEST_PTR(_conn->get());

    if (a_isUseResult) {
        _result = ::mysql_use_result  ( _conn->get() );
        xTEST_PTR_MSG(_result, _conn->lastErrorStr());
    } else {
        _result = ::mysql_store_result( _conn->get() );
        xTEST_PTR_MSG(_result, _conn->lastErrorStr());
    }
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
MySqlRecordset::~MySqlRecordset()
{
    xTEST_NA(_result);

    xCHECK_DO(!isValid(), return);

    (void_t)::mysql_free_result(_result);
    _result = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------
xINLINE MYSQL_RES *
MySqlRecordset::get() const
{
    xTEST_EQ(isValid(), true);

    return _result;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
MySqlRecordset::isValid() const
{
    return (_result != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
uint_t
MySqlRecordset::fieldsNum() const
{
    xTEST_EQ(isValid(), true);

    return ::mysql_num_fields(_result);
}
//-------------------------------------------------------------------------------------------------
xINLINE my_ulonglong
MySqlRecordset::rowsNum() const
{
    xTEST_EQ(isValid(), true);

    return ::mysql_num_rows(_result);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlRecordset::fetchField(
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(isValid(), true);
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_field(_result);
    xTEST_PTR_MSG(a_field, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlRecordset::fetchFieldDirect(
    cuint_t     &a_fieldNumber,
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(isValid(), true);
    xTEST_NA(a_fieldNumber)
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_field_direct(_result, a_fieldNumber);
    xTEST_PTR_MSG(a_field, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlRecordset::fetchFields(
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(isValid(), true);
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_fields(_result);
    xTEST_PTR_MSG(a_field, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlRecordset::fetchRow(
    std::vec_tstring_t *a_row
) const
{
    xTEST_EQ(isValid(), true);
    xTEST_PTR(a_row);

    uint_t     fieldsNum    = 0;
    MYSQL_ROW  row          = xPTR_NULL;
    ulong_t   *fieldLengths = xPTR_NULL;

    a_row->clear();

    // TODO: MySqlRecordset::fetchRow()
#if xTODO
    //--uint_t   fieldsNum   = mysql_num_fields   (_result);
    uint_t     fieldsNum  = _conn->ufieldCount();
    MYSQL_ROW  prow       = mysql_fetch_row    (_result); // array of strings
    ulong_t   *rowLengths = mysql_fetch_lengths(_result); // TODO: MySqlRecordset::fetchRow() - may be 64-bit bug
#endif

    fieldsNum = _conn->fieldCount();
    _fetchRow(&row);
    _fetchLengths(&fieldLengths);
    xTEST_PTR(fieldLengths);

    // [out]
    for (uint_t i = 0; i < fieldsNum; ++ i) {
        std::tstring_t field;

        if (row[i] == xPTR_NULL) {
            field = std::tstring_t();
        } else {
            std::string asField(row[i], fieldLengths[i]);

            field = xA2T(asField);
        }

        a_row->push_back(field);
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlRecordset::_fetchRow(
    MYSQL_ROW *a_row
) const
{
    xTEST_EQ(isValid(), true);
    xTEST_PTR(a_row);

    *a_row = ::mysql_fetch_row(_result);
    xTEST_NA(a_row);
    xTEST_PTR(*a_row);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySqlRecordset::_fetchLengths(
    ulong_t **a_fieldLengths
) const
{
    xTEST_EQ(isValid(), true);
    xTEST_PTR(*a_fieldLengths);

    *a_fieldLengths = ::mysql_fetch_lengths(_result);
    xTEST_PTR_MSG(*a_fieldLengths, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, db)
