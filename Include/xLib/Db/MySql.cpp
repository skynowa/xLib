/**
 * \file  MySql.inl
 * \brief MySQL client
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
*    MySQLConnection
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
MySQLConnection::MySQLConnection() :
    _conn(xPTR_NULL)
{
    xTEST_EQ(isValid(), false);

    _conn = ::mysql_init(xPTR_NULL);
    xTEST_PTR_MSG(_conn, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
MySQLConnection::~MySQLConnection()
{
    close();
}
//-------------------------------------------------------------------------------------------------
xINLINE MYSQL *
MySQLConnection::get() const
{
    xTEST_EQ(isValid(), true);

    return _conn;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
MySQLConnection::isValid() const
{
    // n/a

    return (_conn != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySQLConnection::options(
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
/* static */
xINLINE bool_t
MySQLConnection::isExists(
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

    MySQLConnection conn;

    {
        bRv = conn.isValid();
        xCHECK_RET(!bRv, false);

        conn.connect(a_host, a_user, a_password, xT(""), a_port, a_unixSocket, a_clientFlag);
        conn.query(xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA "
            "WHERE SCHEMA_NAME = '%s'), 'true', 'false')"), a_db.c_str());
    }

    MySQLRecordset rec(conn, false);

    {
        bRv = rec.isValid();
        xTEST_EQ(bRv, true);
        xTEST_EQ(1ULL, rec.rowsNum());

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
MySQLConnection::connect(
    std::ctstring_t &a_host,
    std::ctstring_t &a_user,
    std::ctstring_t &a_password,
    std::ctstring_t &a_db,
    cuint_t         &a_port,
    std::ctstring_t &a_unixSocket,
    culong_t        &a_clientFlag
)
{
    xTEST_EQ(isValid(), true);
    xTEST_NA(a_host);
    xTEST_NA(a_user);
    xTEST_NA(a_password);
    xTEST_NA(a_db);
    xTEST_NA(a_port);
    xTEST_NA(a_unixSocket);
    xTEST_NA(a_clientFlag);

    MYSQL *conn = ::mysql_real_connect(_conn, xT2A(a_host).c_str(), xT2A(a_user).c_str(),
        xT2A(a_password).c_str(), xT2A(a_db).c_str(), a_port, xT2A(a_unixSocket).c_str(),
        a_clientFlag);

    xTEST_PTR_MSG(conn, lastErrorStr());
    xTEST_EQ_MSG(_conn, conn, lastErrorStr());

    _conn = conn;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySQLConnection::query(
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

    std::string asSqlQuery = xT2A(sqlQuery);

    int_t iRv = ::mysql_real_query(_conn, asSqlQuery.data(),
        static_cast<ulong_t>( asSqlQuery.size() ));
    xTEST_EQ_MSG(0, iRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
xINLINE uint_t
MySQLConnection::fieldCount() const
{
    xTEST_EQ(isValid(), true);

    uint_t uiRv = ::mysql_field_count(_conn);
    // n/a

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySQLConnection::close()
{
    xTEST_NA(_conn);

    if ( isValid() ) {
        (void_t)::mysql_close(_conn);
        _conn = xPTR_NULL;
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    errors
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE uint_t
MySQLConnection::lastError() const
{
    xTEST_EQ(isValid(), true);

    uint_t uiRv = ::mysql_errno(_conn);
    xTEST_NA(uiRv);

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
MySQLConnection::lastErrorStr() const
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
*    MySQLRecordset
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
MySQLRecordset::MySQLRecordset(
    const MySQLConnection &a_connection, ///< connection
    cbool_t               &a_isUseResult  ///< use result or store result
) :
    _conn  (&a_connection),
    _result(xPTR_NULL)
{
    xTEST_EQ(isValid(), false);
    xTEST_PTR(_conn->get());

    MYSQL_RES *result = xPTR_NULL;

    if (a_isUseResult) {
        result = ::mysql_use_result  ( _conn->get() );
        xTEST_PTR_MSG(result, _conn->lastErrorStr());
    } else {
        result = ::mysql_store_result( _conn->get() );
        xTEST_PTR_MSG(result, _conn->lastErrorStr());
    }

    _result = result;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
MySQLRecordset::~MySQLRecordset()
{
    xTEST_NA(_result);

    if ( isValid() ) {
        (void_t)::mysql_free_result(_result);

        _result = xPTR_NULL;
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE MYSQL_RES *
MySQLRecordset::get() const
{
    xTEST_EQ(isValid(), true);

    return _result;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
MySQLRecordset::isValid() const
{
    // n/a

    return (_result != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
uint_t
MySQLRecordset::fieldsNum() const
{
    xTEST_EQ(isValid(), true);

    uint_t uiRv = ::mysql_num_fields(_result);
    xTEST_NA(uiRv);

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE my_ulonglong
MySQLRecordset::rowsNum() const
{
    xTEST_EQ(isValid(), true);

    my_ulonglong ullRv = ::mysql_num_rows(_result);
    xTEST_NA(ullRv);

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
MySQLRecordset::fetchField(
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
MySQLRecordset::fetchFieldDirect(
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
MySQLRecordset::fetchFields(
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
MySQLRecordset::fetchRow(
    std::vec_tstring_t *a_row
) const
{
    xTEST_EQ(isValid(), true);
    xTEST_PTR(a_row);

    uint_t     fieldsNum    = 0;
    MYSQL_ROW  row          = xPTR_NULL;
    ulong_t   *fieldLengths = xPTR_NULL;

    (*a_row).clear();

    // TODO: MySQLRecordset::fetchRow()
#if xTODO
    //--uint_t   fieldsNum   = mysql_num_fields   (_result);
    uint_t     fieldsNum  = _conn->ufieldCount();
    MYSQL_ROW  prow       = mysql_fetch_row    (_result); // array of strings
    ulong_t   *rowLengths = mysql_fetch_lengths(_result); // TODO: MySQLRecordset::fetchRow() - may be 64-bit bug
#endif

    // fields count
    fieldsNum = _conn->fieldCount();

    // fetch row
    _fetchRow(&row);

    // field lengths
    _fetchLengths(&fieldLengths);
    xTEST_PTR(fieldLengths);

    // push to std::vector
    std::tstring_t field;

    for (uint_t i = 0; i < fieldsNum; ++ i) {
        if (row[i] == xPTR_NULL) {
            field = std::tstring_t();
        } else {
            std::string asField = std::string(row[i], fieldLengths[i]);

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
MySQLRecordset::_fetchRow(
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
MySQLRecordset::_fetchLengths(
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
