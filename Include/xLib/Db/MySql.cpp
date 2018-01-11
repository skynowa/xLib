/**
 * \file  MySql.inl
 * \brief MySql client
 */


#include "MySql.h"

#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>


xNAMESPACE_BEGIN2(xl, db)

/**************************************************************************************************
*    MySqlConnection
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MySqlConnection::MySqlConnection() :
    _conn()
{
    xTEST_EQ(_conn.isValid(), false);

    _conn = ::mysql_init(xPTR_NULL);
    xTEST_EQ_MSG(_conn.isValid(), true, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
MySqlConnection::~MySqlConnection()
{
}
//-------------------------------------------------------------------------------------------------
HandleMySqlConn &
MySqlConnection::get()
{
    xTEST_EQ(_conn.isValid(), true);

    return _conn;
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::options(
    const mysql_option &a_option,
    cptr_cvoid_t        a_arg
) const
{
    xTEST_EQ(_conn.isValid(), true);
    xTEST_NA(a_option);
    xTEST_NA(a_arg);

#if MYSQL_VERSION_ID < 50154
    int_t iRv = ::mysql_options(_conn.get(), a_option, static_cast<ctchar_t *>( a_arg ));
#else
    int_t iRv = ::mysql_options(_conn.get(), a_option, a_arg);
#endif
    xTEST_EQ_MSG(0, iRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
bool_t
MySqlConnection::ping(
    int_t *out_errorCode    /* = xPTR_NULL */
) const
{
    int_t iRv = ::mysql_ping( _conn.get() );

    Utils::ptrAssignT(out_errorCode, iRv);

    if (iRv != 0) {
        return false;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
MySqlConnection::isExists(
    cMySqlConnectionData &a_data
)
{
    bool_t bRv = false;

    MySqlConnection conn;

    {
        bRv = conn.get().isValid();
        xCHECK_RET(!bRv, false);

        bRv = conn.ping();
        xCHECK_RET(!bRv, false);

        conn.connect(a_data);
        conn.query(xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA "
            "WHERE SCHEMA_NAME = '%s'), 'true', 'false')"), a_data.db.c_str());
    }

    MySqlRecordset rec(conn, false);

    {
        bRv = rec.get().isValid();
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
void_t
MySqlConnection::connect(
    cMySqlConnectionData &a_data
)
{
    xTEST_EQ(_conn.isValid(), true);
    xTEST_NA(a_data);

    _conn = ::mysql_real_connect(_conn.get(), xT2A(a_data.host).c_str(), xT2A(a_data.user).c_str(),
        xT2A(a_data.password).c_str(), xT2A(a_data.db).c_str(), a_data.port,
        xT2A(a_data.unixSocket).c_str(), a_data.clientFlag);

    xTEST_EQ_MSG(_conn.isValid(), true, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::query(
    cptr_ctchar_t a_sqlFormat, ...
) const
{
    xTEST_EQ(_conn.isValid(), true);
    xTEST_PTR(a_sqlFormat);

    std::tstring_t sqlQuery;
    va_list        args;

    xVA_START(args, a_sqlFormat);
    sqlQuery = FormatC::strV(a_sqlFormat, args);
    xVA_END(args);

    const std::string asSqlQuery = xT2A(sqlQuery);

    int_t iRv = ::mysql_real_query(_conn.get(), asSqlQuery.data(),
        static_cast<ulong_t>( asSqlQuery.size() ));
    xTEST_EQ_MSG(0, iRv, lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
uint_t
MySqlConnection::fieldCount() const
{
    xTEST_EQ(_conn.isValid(), true);

    return ::mysql_field_count(_conn.get());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlConnection::close()
{
    xTEST_NA(_conn);

    _conn.close();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    errors
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
uint_t
MySqlConnection::lastError() const
{
    xTEST_EQ(_conn.isValid(), true);

    return ::mysql_errno( _conn.get() );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
MySqlConnection::lastErrorStr() const
{
    xTEST_EQ(_conn.isValid(), true);

    std::tstring_t sRv;

    cuint_t     _lastError = lastError();
    const char *error      = ::mysql_error( _conn.get() );
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
MySqlRecordset::MySqlRecordset(
    MySqlConnection &a_connection,  ///< connection
    cbool_t         &a_isUseResult  ///< use result or store result
) :
    _conn  (&a_connection),
    _result()
{
    xTEST_EQ(_result.isValid(), false);
    xTEST_EQ(_conn->get().isValid(), true);

    if (a_isUseResult) {
        _result = ::mysql_use_result  ( _conn->get().get() );
        xTEST_EQ_MSG(_result.isValid(), true, _conn->lastErrorStr());
    } else {
        _result = ::mysql_store_result( _conn->get().get() );
        xTEST_EQ_MSG(_result.isValid(), true, _conn->lastErrorStr());
    }
}
//-------------------------------------------------------------------------------------------------
/* virtual */
MySqlRecordset::~MySqlRecordset()
{
}
//-------------------------------------------------------------------------------------------------
HandleMySqlResult &
MySqlRecordset::get()
{
    xTEST_EQ(_result.isValid(), true);

    return _result;
}
//-------------------------------------------------------------------------------------------------
uint_t
MySqlRecordset::fieldsNum() const
{
    xTEST_EQ(_result.isValid(), true);

    return ::mysql_num_fields( _result.get() );
}
//-------------------------------------------------------------------------------------------------
my_ulonglong
MySqlRecordset::rowsNum() const
{
    xTEST_EQ(_result.isValid(), true);

    return ::mysql_num_rows( _result.get() );
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::fetchField(
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(_result.isValid(), true);
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_field( _result.get() );
    xTEST_PTR_MSG(a_field, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::fetchFieldDirect(
    cuint_t     &a_fieldNumber,
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(_result.isValid(), true);
    xTEST_NA(a_fieldNumber)
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_field_direct(_result.get(), a_fieldNumber);
    xTEST_PTR_MSG(a_field, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::fetchFields(
    MYSQL_FIELD *a_field
) const
{
    xTEST_EQ(_result.isValid(), true);
    xTEST_PTR(a_field);

    a_field = ::mysql_fetch_fields(_result.get());
    xTEST_PTR_MSG(a_field, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::fetchRow(
    std::vec_tstring_t *a_row
) const
{
    xTEST_EQ(_result.isValid(), true);
    xTEST_PTR(a_row);

    uint_t     fieldsNum    = 0;
    MYSQL_ROW  row          = xPTR_NULL;
    ulong_t   *fieldLengths = xPTR_NULL;

    a_row->clear();

    // TODO: [skynowa] MySqlRecordset::fetchRow()
#if xTODO
    //--uint_t   fieldsNum   = mysql_num_fields   (_result.get());
    uint_t     fieldsNum  = _conn->ufieldCount();
    MYSQL_ROW  prow       = mysql_fetch_row    (_result.get()); // array of strings
    ulong_t   *rowLengths = mysql_fetch_lengths(_result.get()); // TODO: [skynowa] MySqlRecordset::fetchRow() - may be 64-bit bug
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
void_t
MySqlRecordset::_fetchRow(
    MYSQL_ROW *a_row
) const
{
    xTEST_EQ(_result.isValid(), true);
    xTEST_PTR(a_row);

    *a_row = ::mysql_fetch_row(_result.get());
    xTEST_NA(a_row);
    xTEST_PTR(*a_row);
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::_fetchLengths(
    ulong_t **a_fieldLengths
) const
{
    xTEST_EQ(_result.isValid(), true);
    xTEST_PTR(*a_fieldLengths);

    *a_fieldLengths = ::mysql_fetch_lengths(_result.get());
    xTEST_PTR_MSG(*a_fieldLengths, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, db)
