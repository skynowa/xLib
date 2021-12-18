/**
 * \file  StoreResult.cpp
 * \brief MySql client
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
	* \see https://dev.mysql.com/doc/c-api/8.0/en/null-mysql-store-result.html
	*      https://dev.mysql.com/doc/c-api/8.0/en/mysql-field-count.html
	*/
	_result = ::mysql_store_result( _conn->get().get() );
	xTEST_MSG(_result.isValid(), Error(*_conn).str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
