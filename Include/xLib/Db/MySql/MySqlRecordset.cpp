/**
 * \file  MySqlRecordset.cpp
 * \brief MySql client
 */


#include "MySqlRecordset.h"

#include <xLib/Db/MySql/MySqlConnection.h>

namespace xl::db
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MySqlRecordset::MySqlRecordset(
    MySqlConnection &a_connection,  ///< connection
    cbool_t          a_isUseResult  ///< use result or store result
) :
    _conn(&a_connection)
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
HandleMySqlResult &
MySqlRecordset::get()
{
    return _result;
}
//-------------------------------------------------------------------------------------------------
uint_t
MySqlRecordset::fieldsNum() const
{
    xTEST(_result.isValid());

    return ::mysql_num_fields( _result.get() );
}
//-------------------------------------------------------------------------------------------------
std::size_t
MySqlRecordset::rowsNum() const
{
    xTEST(_result.isValid());

    return ::mysql_num_rows( _result.get() );
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::fetchField(
    MYSQL_FIELD *out_field	///< metadata: information about a field
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_field);

    out_field = ::mysql_fetch_field( _result.get() );
    xTEST_PTR_MSG(out_field, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::fetchFieldDirect(
    cuint_t      a_fieldNumber,
    MYSQL_FIELD *out_field
) const
{
    xTEST(_result.isValid());
    xTEST_NA(a_fieldNumber);
    xTEST_PTR(out_field);

    out_field = ::mysql_fetch_field_direct(_result.get(), a_fieldNumber);
    xTEST_PTR_MSG(out_field, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::fetchFields(
    MYSQL_FIELD *out_field
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_field);

    out_field = ::mysql_fetch_fields(_result.get());
    xTEST_PTR_MSG(out_field, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::fetchRow(
    std::vec_tstring_t *out_row
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_row);

    uint_t     fieldsNum    {};
    MYSQL_ROW  row          {};
    ulong_t   *fieldLengths {};

    out_row->clear();

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

        if (row[i] == nullptr) {
            field.clear();
        } else {
            std::string asField(row[i], fieldLengths[i]);

            field = xA2T(asField);
        }

        out_row->push_back(field);
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
    MYSQL_ROW *out_row	///< one row of data
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_row);

    *out_row = ::mysql_fetch_row(_result.get());
    xTEST_NA(out_row);
    xTEST_PTR(*out_row);
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlRecordset::_fetchLengths(
    ulong_t **out_fieldLengths
) const
{
    xTEST(_result.isValid());
    xTEST_PTR_FAIL(*out_fieldLengths);

    *out_fieldLengths = ::mysql_fetch_lengths(_result.get());
    xTEST_PTR_MSG(*out_fieldLengths, _conn->lastErrorStr());
}
//-------------------------------------------------------------------------------------------------

} // namespace
