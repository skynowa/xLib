/**
 * \file  StoreResult.cpp
 * \brief
 */


#include <xLib/Db/MySql/StoreResult.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
StoreResult::StoreResult(
    Connection &a_connection	///< connection
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

} // namespace
