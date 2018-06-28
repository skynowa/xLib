/**
 * \file  MySql.inl
 * \brief MySql client
 */


#include "MySqlRecordset.h"


xNAMESPACE_BEGIN2(xl, db)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MySqlRecordset::MySqlRecordset(
    MySqlConnection &a_connection,  ///< connection
    cbool_t          a_isUseResult  ///< use result or store result
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
    xTEST_NA(a_fieldNumber);
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
