/**
 * \file  UseResult.cpp
 * \brief
 */


#include <xLib/Db/MySql/UseResult.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
UseResult::UseResult(
    Connection &a_connection    ///< connection
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
