/**
 * \file  IResult.cpp
 * \brief MySql client
 */


#include <xLib/Db/MySql/IResult.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
IResult::IResult(
    Connection &a_connection    ///< connection
) :
    _conn(&a_connection)
{
    xTEST(!_result.isValid());
    xTEST(_conn->get().isValid());
}
//-------------------------------------------------------------------------------------------------
IResult::~IResult()
{
	(void_t)::mysql_free_result( _result.get() );
}
//-------------------------------------------------------------------------------------------------
HandleMySqlResult &
IResult::get()
{
    return _result;
}
//-------------------------------------------------------------------------------------------------
uint_t
IResult::fields() const
{
    xTEST(_result.isValid());

    return ::mysql_num_fields( _result.get() );
}
//-------------------------------------------------------------------------------------------------
/**
 * \example https://dev.mysql.com/doc/c-api/8.0/en/mysql-field-count.html
 */
uint_t
IResult::fieldCount() const
{
    xTEST(_conn->get().isValid());

    return ::mysql_field_count( _conn->get().get() );
}
//-------------------------------------------------------------------------------------------------
std::size_t
IResult::rows() const
{
    xTEST(_result.isValid());

    return ::mysql_num_rows( _result.get() );
}
//-------------------------------------------------------------------------------------------------
void_t
IResult::fetchField(
    MYSQL_FIELD *out_field	///< metadata: information about a field
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_field);

    out_field = ::mysql_fetch_field( _result.get() );
    xTEST_PTR_MSG(out_field, Error(*_conn).str());
}
//-------------------------------------------------------------------------------------------------
void_t
IResult::fetchFieldDirect(
    cuint_t      a_fieldNumber,
    MYSQL_FIELD *out_field
) const
{
    xTEST(_result.isValid());
    xTEST_NA(a_fieldNumber);
    xTEST_PTR(out_field);

    out_field = ::mysql_fetch_field_direct(_result.get(), a_fieldNumber);
    xTEST_PTR_MSG(out_field, Error(*_conn).str());
}
//-------------------------------------------------------------------------------------------------
void_t
IResult::fetchFields(
    MYSQL_FIELD *out_field
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_field);

    out_field = ::mysql_fetch_fields( _result.get() );
    xTEST_PTR_MSG(out_field, Error(*_conn).str());
}
//-------------------------------------------------------------------------------------------------
void_t
IResult::fetchRow(
    std::vec_tstring_t *out_row	///< [out]
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_row);

    out_row->clear();

    // TODO: [skynowa] IResult::fetchRow()
#if xTODO
    //--uint_t   fieldsNum   = mysql_num_fields   (_result.get());
    uint_t     fields  = _conn->ufieldCount();
    MYSQL_ROW  prow       = mysql_fetch_row    (_result.get()); // array of strings
    ulong_t   *rowLengths = mysql_fetch_lengths(_result.get()); // TODO: [skynowa] IResult::fetchRow() - may be 64-bit bug
#endif

    cuint_t    fieldsNum    = fieldCount();
    MYSQL_ROW  row          = _fetchRow();
    culong_t  *fieldLengths = _fetchLengths();

    // [out]
    for (uint_t i = 0; i < fieldsNum; ++ i) {
        std::tstring_t field;

        if (row[i] != nullptr) {
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
MYSQL_ROW
IResult::_fetchRow() const
{
    xTEST(_result.isValid());

    MYSQL_ROW row = ::mysql_fetch_row(_result.get());
    xTEST_NA(row);

    return row;
}
//-------------------------------------------------------------------------------------------------
culong_t *
IResult::_fetchLengths() const
{
    xTEST(_result.isValid());

    ulong_t *fieldLengths = ::mysql_fetch_lengths(_result.get());
    xTEST_PTR_MSG(fieldLengths, Error(*_conn).str());

    return fieldLengths;
}
//-------------------------------------------------------------------------------------------------

} // namespace
