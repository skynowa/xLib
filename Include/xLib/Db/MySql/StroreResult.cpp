/**
 * \file  StoreResult.cpp
 * \brief MySql client
 */


#include <xLib/Db/MySql/StoreUseResult.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
StoreResult::StoreResult(
    Connection &a_connection,  ///< connection
    cbool_t     a_isStore      ///< store / use result
) :
    _conn(&a_connection)
{
    xTEST(!_result.isValid());
    xTEST(_conn->get().isValid());

    if (a_isStore) {
        /**
         * Retrieves all the rows immediately (small result)
         *
         * \see https://dev.mysql.com/doc/c-api/8.0/en/null-mysql-store-result.html
         *      https://dev.mysql.com/doc/c-api/8.0/en/mysql-field-count.html
         */
        _result = ::mysql_store_result( _conn->get().get() );
        xTEST_EQ_MSG(_result.isValid(), true, Error(*_conn).str());
    } else {
       /**
        * Initiates the retrieval but doesn't actually get any of the rows (very big result)
        */
        _result = ::mysql_use_result( _conn->get().get() );
        xTEST_EQ_MSG(_result.isValid(), true, Error(*_conn).str());
    }
}
//-------------------------------------------------------------------------------------------------
StoreResult::~StoreResult()
{
	(void_t)::mysql_free_result( _result.get() );
}
//-------------------------------------------------------------------------------------------------
HandleMySqlResult &
StoreResult::get()
{
    return _result;
}
//-------------------------------------------------------------------------------------------------
uint_t
StoreResult::fields() const
{
    xTEST(_result.isValid());

    return ::mysql_num_fields( _result.get() );
}
//-------------------------------------------------------------------------------------------------
/**
 * \example https://dev.mysql.com/doc/c-api/8.0/en/mysql-field-count.html
 */
uint_t
StoreResult::fieldCount() const
{
    xTEST(_conn->get().isValid());

    return ::mysql_field_count( _conn->get().get() );
}
//-------------------------------------------------------------------------------------------------
std::size_t
StoreResult::rows() const
{
    xTEST(_result.isValid());

    return ::mysql_num_rows( _result.get() );
}
//-------------------------------------------------------------------------------------------------
void_t
StoreResult::fetchField(
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
StoreResult::fetchFieldDirect(
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
StoreResult::fetchFields(
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
StoreResult::fetchRow(
    std::vec_tstring_t *out_row	///< [out]
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_row);

    out_row->clear();

    // TODO: [skynowa] StoreResult::fetchRow()
#if xTODO
    //--uint_t   fieldsNum   = mysql_num_fields   (_result.get());
    uint_t     fields  = _conn->ufieldCount();
    MYSQL_ROW  prow       = mysql_fetch_row    (_result.get()); // array of strings
    ulong_t   *rowLengths = mysql_fetch_lengths(_result.get()); // TODO: [skynowa] StoreResult::fetchRow() - may be 64-bit bug
#endif

    cuint_t fieldsNum = fieldCount();

    MYSQL_ROW row {};
    _fetchRow(&row);

    ulong_t *fieldLengths {};
    _fetchLengths(&fieldLengths);
    xTEST_PTR(fieldLengths);

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
void_t
StoreResult::_fetchRow(
    MYSQL_ROW *out_row	///< [out] one row of data
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
StoreResult::_fetchLengths(
    ulong_t **out_fieldLengths	///< [out]
) const
{
    xTEST(_result.isValid());
    xTEST_PTR_FAIL(*out_fieldLengths);

    *out_fieldLengths = ::mysql_fetch_lengths(_result.get());
    xTEST_PTR_MSG(*out_fieldLengths, Error(*_conn).str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
