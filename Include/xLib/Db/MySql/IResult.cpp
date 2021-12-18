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

	if     ( _result.isValid() ) {
		uiRv = ::mysql_num_fields( _result.get() );
	}
	else if (_conn->get().isValid() ) {
		uiRv = ::mysql_field_count( _conn->get().get() );
	}

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
uint64_t
IResult::rows() const
{
    xTEST_NA(_result);
    xTEST_NA(_conn);

    uint64_t ullRv {};

	if     ( _result.isValid() ) {
		ullRv = ::mysql_num_rows( _result.get() );
	}
	else if (_conn->get().isValid() ) {
		ullRv = ::mysql_affected_rows( _conn->get().get() );
	}

    return ullRv;
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

    MYSQL_ROW     row          = _fetchRow();
    std::csize_t  fields_      = fields();
    culong_t     *fieldLengths = _fetchLengths();

    for (uint_t i = 0; i < fields_; ++ i) {
        std::tstring_t field;

        if (row[i] != nullptr) {
            std::string asField(row[i], fieldLengths[i]);

            field = xA2T(asField);
        }

        // [out]
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
