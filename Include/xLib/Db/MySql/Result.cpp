/**
 * \file  Result.cpp
 * \brief
 */


#include <xLib/Db/MySql/Result.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
IResult::IResult(
	const Connection &a_connection    ///< connection
) :
    _conn(&a_connection)
{
    xTEST(!_result.isValid());
    xTEST(_conn->get().isValid());
}
//-------------------------------------------------------------------------------------------------
IResult::~IResult()
{
}
//-------------------------------------------------------------------------------------------------
HandleMySqlResult &
IResult::get()
{
    return _result;
}
//-------------------------------------------------------------------------------------------------
/**
 * Get the number of columns either from a pointer to a result set or to a connection handler.
 * You would use the connection handler if mysql_store_result() or mysql_use_result() returned NULL
 * (and thus you have no result set pointer). In this case, you can call mysql_field_count()
 * to determine whether mysql_store_result() should have produced a nonempty result.
 * This enables the client program to take proper action without knowing whether the query
 * was a SELECT (or SELECT-like) statement. The example shown here illustrates how this may be done.
 *
 * \example https://dev.mysql.com/doc/c-api/8.0/en/mysql-field-count.html
 */
std::size_t
IResult::fields() const
{
    xTEST_NA(_result);
    xTEST_NA(_conn);

    std::size_t uiRv {};

	if      ( _result.isValid() ) {
		uiRv = ::mysql_num_fields( _result.get() );
	}
	else if (_conn->get().isValid() ) {
		uiRv = ::mysql_field_count( _conn->get().get() );
	}

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
/**
 * mysql_num_rows() is intended for use with statements that return a result set, such as SELECT.
 * For statements such as INSERT, UPDATE, or DELETE, the number of affected rows can be obtained
 * with mysql_affected_rows().
 */
std::uint64_t
IResult::rows() const
{
    xTEST_NA(_result);
    xTEST_NA(_conn);

    std::uint64_t ullRv {};

	if      ( _result.isValid() ) {
		ullRv = ::mysql_num_rows( _result.get() );
	}
	else if ( _conn->get().isValid() ) {
		ullRv = ::mysql_affected_rows( _conn->get().get() );
		xTEST_DIFF(ullRv, MYSQL_COUNT_ERROR);
	}

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
MYSQL_FIELD *
IResult::fetchField() const
{
    xTEST(_result.isValid());

    MYSQL_FIELD *field = ::mysql_fetch_field( _result.get() );
    xTEST_NA(field);

    return field;
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
MYSQL_FIELD *
IResult::fetchFields() const
{
    xTEST(_result.isValid());

    MYSQL_FIELD *field = ::mysql_fetch_fields( _result.get() );
    xTEST_NA(field);

    return field;
}
//-------------------------------------------------------------------------------------------------
void_t
IResult::fetchRow(
	row_t *out_row	///< [out]
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_row);

    out_row->clear();

    const MYSQL_ROW row = _fetchRow();
    if (row == nullptr) {
        return;
    }

    std::csize_t  fieldsNum    = fields();
    MYSQL_FIELD  *fields       = fetchFields();
    culong_t     *fieldLengths = _fetchLengths();

	for (std::size_t i = 0; i < fieldsNum; ++ i) {
		std::ctstring_t &it_key = fields[i].name;

		std::tstring_t it_value;
		{
			cptr_cchar_t it_field     = (row[i] == nullptr) ? nullStr.c_str() : row[i];
			std::csize_t it_fieldSize = fieldLengths[i];

			std::cstring_t asField(it_field, it_fieldSize);

			it_value = xA2T(asField);
		}

		// [out]
		out_row->insert( {it_key, it_value} );
	}
}
//-------------------------------------------------------------------------------------------------
void_t
IResult::fetchRows(
	rows_t *out_rows	///< [out]
) const
{
    xTEST(_result.isValid());
    xTEST_PTR(out_rows);

    out_rows->clear();

    row_t row;

	for (fetchRow(&row); !row.empty(); fetchRow(&row)) {
		out_rows->emplace_back(row);
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/**
 * \return
 *
 * - mysql_store_result() - returns NULL if there are no more rows to retrieve
 * - mysql_use_result()   - returns NULL if there are no more rows to retrieve or an error occurred
 */
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

   /**
    * \return nullptr - length for empty columns and for columns containing NULL values
    *
    * The length for empty columns and for columns containing NULL values is zero.
    * \see how to distinguish these two cases, see the description for mysql_fetch_row().
    */
    culong_t *fieldLengths = ::mysql_fetch_lengths(_result.get());
	xTEST_PTR_MSG(fieldLengths, Error(*_conn).str());

    return fieldLengths;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    StoreResult: public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
StoreResult::StoreResult(
	const Connection &a_connection	///< connection
) :
    IResult(a_connection)
{
   /**
	* Retrieves all the rows immediately (small result)
	*
	* \return NULL if:
    *
	* - There was a malloc() failure (for example, if the result set was too large).
	* - The data could not be read (an error occurred on the connection).
	* - The query returned no data (for example, it was an INSERT, UPDATE, or DELETE).
	*
	* \see https://dev.mysql.com/doc/c-api/8.0/en/null-mysql-store-result.html
	*      https://dev.mysql.com/doc/c-api/8.0/en/mysql-field-count.html
	*/
	_result = ::mysql_store_result( _conn->get().get() );
	xTEST_MSG(_result.isValid(), Error(*_conn).str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    UseResult: public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
UseResult::UseResult(
	const Connection &a_connection    ///< connection
) :
    IResult(a_connection)
{
   /**
	* Initiates the retrieval but doesn't actually get any of the rows (very big result)
	*/
	_result = ::mysql_use_result( _conn->get().get() );
	xTEST_MSG(_result.isValid(), Error(*_conn).str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
